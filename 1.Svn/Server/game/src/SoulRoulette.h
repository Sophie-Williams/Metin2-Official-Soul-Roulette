#pragma once

/*
* Created by blackdragonx61
* Date:06.09.2020
*/
#if defined(__BL_SOUL_ROULETTE__)
class CSoulRoulette
{
public:
	CSoulRoulette(LPCHARACTER ch);
	~CSoulRoulette();
	void TurnWheel();
	void GiveMyFuckingGift();
	DWORD GetGiftVnum() const;

private:
	void SetGift(const DWORD vnum, const BYTE count);
	int PickAGift();

	BYTE GetGiftCount() const;
	WORD GetTurnCount() const;
	BYTE GetChance() const;

	LPCHARACTER ch;
	DWORD gift_vnum;
	BYTE gift_count;
	WORD turn_count;
};
#endif
