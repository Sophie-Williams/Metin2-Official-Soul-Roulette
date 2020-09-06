//Find in void CHARACTER::Initialize()
	m_pkShop		= NULL;
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	pSoulRoulette = NULL;
#endif

//Find
	HorseSummon(false);
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	if (pSoulRoulette) {
		delete pSoulRoulette;
		pSoulRoulette = NULL;
	}
#endif

//Find
void CHARACTER::SetExchange(CExchange * pkExchange)
{
	m_pkExchange = pkExchange;
}

///Add
#if defined(__BL_SOUL_ROULETTE__)
void CHARACTER::SetSoulRoulette(CSoulRoulette* pt)
{
	if (pSoulRoulette)
		delete pSoulRoulette;
	pSoulRoulette = pt;
}
#endif

//Find in bool CHARACTER::IsHack(bool bSendMsg, bool bCheckShopOwner, int limittime)
		if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen())
			
///Change
		if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
#if defined(__BL_SOUL_ROULETTE__)
			|| GetSoulRoulette()
#endif
			)
			
//Find
		if (GetExchange() || GetMyShop() || IsOpenSafebox() || IsCubeOpen())

///Change
		if (GetExchange() || GetMyShop() || IsOpenSafebox() || IsCubeOpen()
#if defined(__BL_SOUL_ROULETTE__)
			|| GetSoulRoulette()
#endif
			)