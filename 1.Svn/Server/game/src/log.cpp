//Find
void LogManager::HackCRCLog(const char * c_pszHackName, const char * c_pszLogin, const char * c_pszName, const char * c_pszIP, DWORD dwCRC)
{
	...
}

///Add
#if defined(__BL_SOUL_ROULETTE__)
void LogManager::SoulRouletteLog(const char* Name, const int vnum, const int count)
{
	Query("INSERT INTO soul_roulette_log%s (name, vnum, count, date) VALUES('%s', '%d', '%d', NOW())", get_table_postfix(), Name, vnum, count);
}
#endif