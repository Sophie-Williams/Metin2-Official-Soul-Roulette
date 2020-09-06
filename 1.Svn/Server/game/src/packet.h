//Find
	HEADER_CG_SCRIPT_SELECT_ITEM	= 114,
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	HEADER_CG_SOUL_ROULETTE = 136,
#endif

//Find
typedef struct command_item_pickup
{
	BYTE 	header;
	DWORD	vid;
} TPacketCGItemPickup;

///Add
#if defined(__BL_SOUL_ROULETTE__)
typedef struct command_roulette
{
	BYTE	header;
	BYTE 	option;
} TPacketCGSoulRoulette;
#endif