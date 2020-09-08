//Find
	HEADER_CG_RUNUP_MATRIX_ANSWER               = 201,
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	HEADER_CG_SOUL_ROULETTE = 136,
#endif

//Find
	HEADER_GC_MAIN_CHARACTER4_BGM_VOL			= 138,
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	HEADER_GC_SOUL_ROULETTE = 145,
#endif

//Find
typedef struct command_item_pickup
{
	BYTE header;
	DWORD vid;
} TPacketCGItemPickUp;

///Add
#if defined(__BL_SOUL_ROULETTE__)
typedef struct command_cgroulette
{
	BYTE	header;
	BYTE 	option;
} TPacketCGSoulRoulette;
typedef struct command_gcroulette
{
	BYTE	header;
	BYTE 	option;
	int		yang;
	struct {
		DWORD vnum;
		BYTE count;
	} ItemInfo[ROULETTE_ITEM_MAX];
} TPacketGCSoulRoulette;
#endif