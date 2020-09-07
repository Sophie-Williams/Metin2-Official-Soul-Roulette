#include "stdafx.h"
#include "char.h"
#include "packet.h"
#include "desc.h"
#include "group_text_parse_tree.h"
#include "locale_service.h"

#if defined(__BL_SOUL_ROULETTE__)
static int RoulettePrice = 250000;
static const int RouletteItemMax = 20;

CSoulRoulette::CSoulRoulette(LPCHARACTER m_ch)
	: ch(m_ch), gift_vnum(0), gift_count(1), turn_count(0)
{
	SendPacket(OPEN);
}

CSoulRoulette::~CSoulRoulette() {
	if (GetGiftVnum())
		sys_log(0, "<CSoulRoulette> player(%s) didn't get his gift(vnum: %lu(%d.x))!!", ch->GetName(), GetGiftVnum(), GetGiftCount());
}

static std::vector<CSoulRoulette::SRoulette*> v_RouletteItem;

void CSoulRoulette::ReadRouletteData(bool NoMoreItem)
{
	for (size_t i = 0; i < v_RouletteItem.size(); i++)
		delete v_RouletteItem[i];

	v_RouletteItem.clear();

	if (NoMoreItem)
		return;

	v_RouletteItem.reserve(RouletteItemMax);

	char c_pszFileName[FILE_MAX_LEN];
	snprintf(c_pszFileName, sizeof(c_pszFileName), "%s/Roulette_Items.txt", LocaleService_GetBasePath().c_str());

	//std::auto_ptr<CGroupTextParseTreeLoader> loader(new CGroupTextParseTreeLoader());
	std::unique_ptr<CGroupTextParseTreeLoader> loader(new CGroupTextParseTreeLoader());

	if (!loader->Load(c_pszFileName)) {
		sys_err("ReadRouletteData %s: load error", c_pszFileName);
		return;
	}

	const char* GroupName = "main";
	CGroupNode * RouletteGroup = loader->GetGroup(GroupName);

	if (!RouletteGroup) {
		sys_err("%s isn't exist!", GroupName);
		return;
	}

	if (!RouletteGroup->GetRowCount()) {
		sys_err("Group %s is empty!", GroupName);
		return;
	}

	if (!RouletteGroup->GetValue("price", 0, RoulettePrice)) {
		sys_err("Group %s does not have price.", RouletteGroup->GetNodeName().c_str());
		return;
	}
	
	for (int i = 0; i < RouletteItemMax && i < RouletteGroup->GetRowCount(); i++) {
		DWORD vnum;
		BYTE count, chance;
		
		if (!RouletteGroup->GetValue(i, "vnum", vnum)) {
			sys_err("RouletteGroup vnum error.");
			return;
		}
		if (!RouletteGroup->GetValue(i, "count", count)) {
			sys_err("RouletteGroup count error.");
			return;
		}
		if (!RouletteGroup->GetValue(i, "chance", chance)) {
			sys_err("RouletteGroup chance error.");
			return;
		}
		auto data = new CSoulRoulette::SRoulette(vnum, count, chance);
		v_RouletteItem.push_back(data);
	}
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
		for (size_t i = 0; option == CSoulRoulette::OPEN && i < v_RouletteItem.size(); i++) {
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

static std::string MoneyString()
{
	const int comma = 3;
	std::string str = std::to_string(RoulettePrice);
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
		ch->ChatPacket(CHAT_TYPE_INFO, "Please wait, wheel is turning.");
		return;
	}

	if (ch->GetGold() < RoulettePrice) {
		ch->ChatPacket(CHAT_TYPE_INFO, "You need %s yang for <Soul Roulette>", MoneyString().c_str());
		return;
	}

	int Rand = PickAGift();
	if (Rand == -1) {
		sys_err("CSoulRoulette::TurnWheel() Error Pick Gift (%s)", ch->GetName());
		return;
	}

	ch->PointChange(POINT_GOLD, -RoulettePrice);

	//spin count, pos
	SendPacket(CSoulRoulette::TURN, number(1, 3), Rand);

	turn_count++;
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

int CSoulRoulette::PickAGift()
{
	const BYTE Chance = GetChance();

	while (v_RouletteItem.size()) {
		const int rand_pos = number(0, static_cast<int>(v_RouletteItem.size()) - 1);
		const SRoulette* Roulette = v_RouletteItem[rand_pos];

		if (Chance >= Roulette->chance) {
			SetGift(Roulette->vnum, Roulette->count);
			return rand_pos;
		}
	}

	return -1;
}

void CSoulRoulette::SetGift(const DWORD vnum, const BYTE count)
{
	gift_vnum = vnum;
	gift_count = count;
}

void CSoulRoulette::GiveGift()
{
	const DWORD GiftVnum = GetGiftVnum();

	if (GiftVnum) {
		ch->AutoGiveItem(GiftVnum, GetGiftCount());
		SetGift(0, 1); // reset
	}
	else
		sys_err("Dude, where is the gift_vnum? <player: %s>", ch->GetName());
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
