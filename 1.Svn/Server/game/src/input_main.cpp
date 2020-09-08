//Find
void CInputMain::ItemMove(LPCHARACTER ch, const char * data)
{
	struct command_item_move * pinfo = (struct command_item_move *) data;

	if (ch)
		ch->MoveItem(pinfo->Cell, pinfo->CellTo, pinfo->count);
}

///Add
#if defined(__BL_SOUL_ROULETTE__)
void CInputMain::SoulRoulette(LPCHARACTER ch, const char* data)
{
	if (!ch)
		return;

	const TPacketCGSoulRoulette* pinfo = reinterpret_cast<const TPacketCGSoulRoulette*>(data);
	enum { CLOSE, TURN, GIVE };

	switch (pinfo->option) {
	case CLOSE:
		if (ch->GetSoulRoulette()) {
			if (ch->GetSoulRoulette()->GetGiftVnum())
				ch->ChatPacket(CHAT_TYPE_INFO, "Please wait, <Soul Roulette> is active now.");
			else
			{
				ch->GetSoulRoulette()->SendPacket(CSoulRoulette::CLOSE);
				ch->SetSoulRoulette(NULL);
			}
		}
		break;
	case TURN:
		if (ch->GetSoulRoulette())
			ch->GetSoulRoulette()->TurnWheel();
		break;
	case GIVE:
		if (ch->GetSoulRoulette())
			ch->GetSoulRoulette()->GiveGift();
		break;
	default:
		sys_err("CInputMain::SoulRoulette : Unknown option %d : %s", pinfo->option, ch->GetName());
		break;
	}
}
#endif

//Find
		case HEADER_CG_ITEM_PICKUP:
			if (!ch->IsObserverMode())
				ItemPickup(ch, c_pData);
			break;
			
///Add
#if defined(__BL_SOUL_ROULETTE__)
		case HEADER_CG_SOUL_ROULETTE:
			if (!ch->IsObserverMode())
				SoulRoulette(ch, c_pData);
			break;
#endif