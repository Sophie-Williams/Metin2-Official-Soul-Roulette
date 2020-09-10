//Find
	_send_bonus_info(ch);
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	CSoulRoulette::StateError(CSoulRoulette::Error::GIVE, ch);
#endif