//Find
			Set(HEADER_GC_EXCHANGE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCExchange), STATIC_SIZE_PACKET));
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
			Set(HEADER_GC_SOUL_ROULETTE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCSoulRoulette), STATIC_SIZE_PACKET));
#endif