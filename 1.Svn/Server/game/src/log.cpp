//Find
void LogManager::HackCRCLog(const char * c_pszHackName, const char * c_pszLogin, const char * c_pszName, const char * c_pszIP, DWORD dwCRC)
{
	...
}

///Add
#if defined(__BL_SOUL_ROULETTE__)
void LogManager::SoulRouletteLog(const char* table, const char* Name, const int vnum, const int count, const bool state)
{
	Query("INSERT INTO %s%s (name, vnum, count, state, date) VALUES('%s', '%d', '%d', '%s', NOW())", table, get_table_postfix(), Name, vnum, count, (state ? "OK" : "ERROR"));
}
#endif