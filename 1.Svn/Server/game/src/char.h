///Add
#if defined(__BL_SOUL_ROULETTE__)
#include "SoulRoulette.h"
#endif

//Find
	public:
		bool			ExchangeStart(LPCHARACTER victim);
		void			SetExchange(CExchange * pkExchange);
		CExchange *		GetExchange() const	{ return m_pkExchange;	}

	protected:
		CExchange *		m_pkExchange;
		
///Add
#if defined(__BL_SOUL_ROULETTE__)
	public:
		void SetSoulRoulette(CSoulRoulette* pt);
		CSoulRoulette* GetSoulRoulette() const { return pSoulRoulette; }
	private:
		CSoulRoulette* pSoulRoulette;
#endif