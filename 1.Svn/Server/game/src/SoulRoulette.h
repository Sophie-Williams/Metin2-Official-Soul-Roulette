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
	void GiveGift();
	DWORD GetGiftVnum() const;
	void SendPacket(BYTE option, int arg1 = 0 , int arg2 = 0);

	enum { OPEN, CLOSE, TURN };
	struct SRoulette
	{
		DWORD vnum;
		BYTE count;
		BYTE chance; // max 255
		SRoulette(DWORD m_vnum, BYTE m_count, BYTE m_chance)
			: vnum(m_vnum), count(m_count), chance(m_chance) {}
		
		struct ByChance 
		{
			bool operator ()(const CSoulRoulette::SRoulette* a, const CSoulRoulette::SRoulette* b) const
			{
				return a->chance < b->chance;
			}
		};
	};

	static bool ReadRouletteData(bool NoMoreItem = false);

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
