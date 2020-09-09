#include "stdafx.h"
#include "char.h"
#include "packet.h"
#include "desc.h"
#include "group_text_parse_tree.h"
#include "locale_service.h"
#include "log.h"
#include "config.h"
#include "sectree_manager.h"

#if defined(__BL_SOUL_ROULETTE__)
static int RoulettePrice = 250000;
static bool EventActive;
static std::vector<CSoulRoulette::SRoulette*> v_RouletteItem;

CSoulRoulette::CSoulRoulette(LPCHARACTER m_ch)
	: ch(m_ch), gift_vnum(0), gift_count(1), turn_count(0)
{
	SendPacket(CSoulRoulette::OPEN);
}

CSoulRoulette::~CSoulRoulette() {
	if (GetGiftVnum())
		LogManager::instance().SoulRouletteLog(ch->GetName(), GetGiftVnum(), GetGiftCount(), false);
}

template <typename T> std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

bool CSoulRoulette::ReadRouletteData(bool NoMoreItem)
{
	for (std::vector<CSoulRoulette::SRoulette*>::const_iterator it = v_RouletteItem.begin(); it != v_RouletteItem.end(); ++it)
		delete (*it);

	v_RouletteItem.clear();

	if (NoMoreItem)
		return true;

	v_RouletteItem.reserve(ROULETTE_ITEM_MAX);

	char c_pszFileName[FILE_MAX_LEN];
	snprintf(c_pszFileName, sizeof(c_pszFileName), "%s/Roulette_Items.txt", LocaleService_GetBasePath().c_str());

	//std::auto_ptr<CGroupTextParseTreeLoader> loader(new CGroupTextParseTreeLoader());
	std::unique_ptr<CGroupTextParseTreeLoader> loader(new CGroupTextParseTreeLoader());

	if (!loader->Load(c_pszFileName)) {
		sys_err("ReadRouletteData %s: load error", c_pszFileName);
		return false;
	}

	static const char* GroupName = "main";
	CGroupNode* RouletteGroup = loader->GetGroup(GroupName);

	if (!RouletteGroup) {
		sys_err("%s isn't exist!", GroupName);
		return false;
	}

	if (!RouletteGroup->GetRowCount()) {
		sys_err("Group %s is empty!", GroupName);
		return false;
	}

	if (!RouletteGroup->GetValue("active", 0, EventActive)) {
		sys_err("Group %s does not have: active.", RouletteGroup->GetNodeName().c_str());
		return false;
	}

	if (!EventActive) // event disabled, no need to add items
		return true;

	if (!RouletteGroup->GetValue("price", 0, RoulettePrice)) {
		sys_err("Group %s does not have: price.", RouletteGroup->GetNodeName().c_str());
		return false;
	}

	int RowCount = RouletteGroup->GetRowCount() - 2; // -2: active, price
	for (int i = 1; i <= ROULETTE_ITEM_MAX && i <= RowCount; i++) {
		DWORD vnum;
		BYTE count, chance;

		//std::string id = std::to_string(i); // C++11(+)
		std::string id = NumberToString(i);

		// Why string? Because CGroupNode m_map_rows is map(sorted). It's storing strings not indexes.
		// Example GetValue(0) gives you row 1, GetValue(1) gives you row 10
		// Now I can access value with string directly

		if (!RouletteGroup->GetValue(id, "vnum", vnum)) {
			sys_err("CSoulRoulette::RouletteGroup vnum error. (line: %s)", id.c_str());
			return false;
		}

		if (!RouletteGroup->GetValue(id, "count", count)) {
			sys_err("CSoulRoulette::RouletteGroup count error. (line: %s)", id.c_str());
			return false;
		}

		if (!RouletteGroup->GetValue(id, "chance", chance)) {
			sys_err("CSoulRoulette::RouletteGroup chance error. (line: %s)", id.c_str());
			return false;
		}

		SRoulette* data = new SRoulette(vnum, count, chance);
		v_RouletteItem.push_back(data);
	}

	return true;
}

void CSoulRoulette::SendPacket(BYTE option, int arg1, int arg2)
{
	if (!ch->GetDesc())
		return;

	TPacketGCSoulRoulette p;
	memset(&p, 0, sizeof(p));

	p.header = HEADER_GC_SOUL_ROULETTE;
	p.option = option;

	switch (option) {
	case CSoulRoulette::OPEN:
		p.yang = RoulettePrice;
		for (size_t i = 0; i < v_RouletteItem.size(); i++) {
			p.ItemInfo[i].vnum = v_RouletteItem[i]->vnum;
			p.ItemInfo[i].count = v_RouletteItem[i]->count;
		}
		break;
	case CSoulRoulette::TURN:
		p.ItemInfo[0].vnum = arg1;
		p.ItemInfo[0].count = arg2;
		break;
	}

	ch->GetDesc()->Packet(&p, sizeof(TPacketGCSoulRoulette));
}

template<typename T> std::string MoneyString(T val)
{
	const int comma = 3;
	std::string str = NumberToString(val);
	int pos = static_cast<int>(str.length()) - comma;

	while (pos > 0) {
		str.insert(pos, ".");
		pos -= comma;
	}

	return str;
}

void CSoulRoulette::TurnWheel()
{
	if (GetGiftVnum()) {
		ch->ChatPacket(CHAT_TYPE_INFO, "Please wait, <Soul Roulette> is active now.");
		return;
	}

	if (ch->GetGold() < RoulettePrice) {
		ch->ChatPacket(CHAT_TYPE_INFO, "You need %s yang for <Soul Roulette>", MoneyString(RoulettePrice).c_str());
		return;
	}

	int Rand = PickAGift();
	if (Rand == -1) {
		ch->ChatPacket(CHAT_TYPE_INFO, "<Soul Roulette> is currently disabled. Please try again later.");
		return;
	}

	ch->PointChange(POINT_GOLD, -RoulettePrice);

	//spin count, pos
	SendPacket(CSoulRoulette::TURN, number(3, 5), Rand);

	turn_count++;
}
#include <algorithm>
int CSoulRoulette::PickAGift()
{
	const BYTE Chance = GetChance();
	std::vector<CSoulRoulette::SRoulette*>::const_iterator it = std::min_element(v_RouletteItem.begin(), v_RouletteItem.end(), SRoulette::ByChance());

	if (it != v_RouletteItem.end()) {
		const BYTE MinChance = (*it)->chance;

		while (Chance >= MinChance) {
			const int rand_pos = number(0, static_cast<int>(v_RouletteItem.size()) - 1);
			const SRoulette* Roulette = v_RouletteItem[rand_pos];

			if (Chance >= Roulette->chance) {
				SetGift(Roulette->vnum, Roulette->count);
				return rand_pos;
			}
		}
	}

	return -1;
}

void CSoulRoulette::GiveGift()
{
	const DWORD GiftVnum = GetGiftVnum();

	if (GiftVnum) {
		ch->AutoGiveItem(GiftVnum, GetGiftCount());
		LogManager::instance().SoulRouletteLog(ch->GetName(), GiftVnum, GetGiftCount(), true);
		SetGift(0, 1); // reset
	}
	else
		sys_err("CSoulRoulette::GiveGift: <player: %s> is trying to get item without item data.", ch->GetName());
}

void CSoulRoulette::SetGift(const DWORD vnum, const BYTE count)
{
	gift_vnum = vnum;
	gift_count = count;
}

BYTE CSoulRoulette::GetChance() const
{
	const WORD TurnCount = GetTurnCount();
	if (TurnCount >= 10 && TurnCount < 25)
		return 25;
	if (TurnCount >= 25 && TurnCount < 40)
		return 50;
	if (TurnCount >= 40)
		return 255; // max
	return 0;
}

DWORD CSoulRoulette::GetGiftVnum() const
{
	return gift_vnum;
}

BYTE CSoulRoulette::GetGiftCount() const
{
	return gift_count;
}

WORD CSoulRoulette::GetTurnCount() const
{
	return turn_count;
}
#endif
