//Find
			case HEADER_GC_EXCHANGE:
				ret = RecvExchangePacket();
				break;
				
///Add
#if defined(__BL_SOUL_ROULETTE__)
			case HEADER_GC_SOUL_ROULETTE:
				ret = RecvSoulRoulette();
				break;
#endif

//Find
void CPythonNetworkStream::ToggleGameDebugInfo()
{
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "ToggleDebugInfo", Py_BuildValue("()"));
}

///Add
#if defined(__BL_SOUL_ROULETTE__)
bool CPythonNetworkStream::RecvSoulRoulette()
{
	TPacketGCSoulRoulette Packet;
	if (!Recv(sizeof(Packet), &Packet)) {
		Tracen("RecvSoulRoulette Error");
		return false;
	}

	enum { OPEN, CLOSE, TURN };
	switch (Packet.option) {
	case OPEN:
		for (int i = 0; i < ROULETTE_ITEM_MAX; i++)
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_ROULETTE_ICON", Py_BuildValue("(iii)", i, Packet.ItemInfo[i].vnum, Packet.ItemInfo[i].count));
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_ROULETTE_OPEN", Py_BuildValue("(i)", Packet.yang));
		break;
	case CLOSE:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_ROULETTE_CLOSE", Py_BuildValue("()"));
		break;
	case TURN:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_ROULETTE_TURN", Py_BuildValue("(ii)", Packet.ItemInfo[0].vnum, Packet.ItemInfo[0].count));
		break;
	}

	return true;
}
bool CPythonNetworkStream::SoulRoulette(const BYTE option)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGSoulRoulette p;
	p.header = HEADER_CG_SOUL_ROULETTE;
	p.option = option;

	if (!Send(sizeof(p), &p)) {
		Tracen("Error SoulRoulette");
		return false;
	}

	return SendSequence();
}
#endif