///Add
#if defined(__BL_SOUL_ROULETTE__)
#include "SoulRoulette.h"
#endif

//Find
	PanamaLoad();
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	CSoulRoulette::ReadRouletteData();
#endif

//Find
	sys_log(0, "<shutdown> Starting...");
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	CSoulRoulette::ReadRouletteData(true);
#endif