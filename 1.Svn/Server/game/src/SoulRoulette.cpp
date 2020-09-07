#include "stdafx.h"
#include "char.h"

#if defined(__BL_SOUL_ROULETTE__)
static const int RoulettePrice = 250000;
static const int RouletteItemMax = 20;
static const struct SRoulette
{
	DWORD vnum;
	BYTE count;
	BYTE chance; // max 255
} SRouletteData[RouletteItemMax] = {
	{ 50011, 61, 0 }, { 1019, 1, 0 }, { 1029, 1, 0 }, { 1039, 1, 0 },
	{ 1049, 1, 0 }, { 1059, 1, 0 }, { 1069, 1, 0 }, { 1079, 1, 0 },
	{ 1089, 1, 0 }, { 1099, 1, 0 }, { 1109, 1, 100 }, { 1119, 1, 0 },
	{ 1129, 1, 0 }, { 1139, 1, 0 }, { 1149, 1, 0 }, { 1159, 1, 0 },
	{ 1169, 1, 0 }, { 1179, 1, 0 }, { 1189, 1, 0 }, { 1349, 1, 0 }
};

CSoulRoulette::CSoulRoulette(LPCHARACTER m_ch)
	: ch(m_ch), gift_vnum(0), gift_count(1), turn_count(0)
{
	for (int i = 0; i < RouletteItemMax; i++)
		ch->ChatPacket(CHAT_TYPE_COMMAND, "BINARY_ROULETTE_ICON %d %lu %d", i, SRouletteData[i].vnum, SRouletteData[i].count);
	ch->ChatPacket(CHAT_TYPE_COMMAND, "BINARY_ROULETTE_OPEN");
}

CSoulRoulette::~CSoulRoulette() {
	if (GetGiftVnum())
		sys_log(0, "<CSoulRoulette> player(%s) didn't get his gift(vnum: %lu(%d.x))!!", ch->GetName(), GetGiftVnum(), GetGiftCount());
}

static std::string& MoneyString()
{
	static std::string str;
	if (!str.empty())
		return str;

	const int comma = 3;
	str = std::to_string(RoulettePrice);
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
		ch->ChatPacket(CHAT_TYPE_INFO, "Wait motherfucker!");
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
	ch->ChatPacket(CHAT_TYPE_COMMAND, "BINARY_ROULETTE_TURN %d %d", number(1, 3), Rand);

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

	while (true) {
		const int rand_pos = number(0, RouletteItemMax - 1);
		const SRoulette& Roulette = SRouletteData[rand_pos];

		if (Chance >= Roulette.chance) {
			SetGift(Roulette.vnum, Roulette.count);
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

void CSoulRoulette::GiveMyFuckingGift()
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
