//Find
void CPythonNetworkStream::ToggleGameDebugInfo()
{
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "ToggleDebugInfo", Py_BuildValue("()"));
}

///Add
#if defined(__BL_SOUL_ROULETTE__)
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