//Find
	PyModule_AddIntConstant(poModule, "EQUIPMENT_PAGE_COUNT",	c_Equipment_Count);
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	PyModule_AddIntConstant(poModule, "ROULETTE_ITEM_MAX", 		ROULETTE_ITEM_MAX);
#endif