//Find
			case 'a':
				ch->ChatPacket(CHAT_TYPE_INFO, "Reloading Admin infomation.");
				db_clientdesc->DBPacket(HEADER_GD_RELOAD_ADMIN, 0, NULL, 0);
				sys_log(0, "Reloading admin infomation.");
				break;
				
///Add
#if defined(__BL_SOUL_ROULETTE__)
			case 'r':
				if (!CSoulRoulette::ReadRouletteData()) {
					ch->ChatPacket(CHAT_TYPE_INFO, "Error Reloading <CSoulRoulette>!");
					CSoulRoulette::ReadRouletteData(true); // reset
				}
				else
					ch->ChatPacket(CHAT_TYPE_INFO, "<CSoulRoulette> Reloaded!");
				break;
#endif