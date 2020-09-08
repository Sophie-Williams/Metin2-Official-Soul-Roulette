//Find
	int pc_get_channel_id(lua_State* L)
	{
		...
	}
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	int pc_open_soul_roulette(lua_State* L)
	{
		LPCHARACTER pkChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if (pkChar && !pkChar->GetSoulRoulette())
			pkChar->SetSoulRoulette(new CSoulRoulette(pkChar));
		return 0;
	}
#endif

//Find
			{ "get_channel_id",		pc_get_channel_id	},
			
///Add
#if defined(__BL_SOUL_ROULETTE__)
			{ "open_soul_roulette",	pc_open_soul_roulette	},
#endif