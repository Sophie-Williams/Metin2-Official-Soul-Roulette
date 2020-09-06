//Find
PyObject* netSendItemPickUpPacket(PyObject* poSelf, PyObject* poArgs)
{
	...
}

///Add
#if defined(__BL_SOUL_ROULETTE__)
PyObject* netSoulRoulettePacket(PyObject* poSelf, PyObject* poArgs)
{
	int option;
	if (!PyTuple_GetInteger(poArgs, 0, &option))
		return Py_BuildException();

	CPythonNetworkStream::Instance().SoulRoulette(option);
	return Py_BuildNone();
}
#endif

//Find
		{ "SendGiveItemPacket",					netSendGiveItemPacket,					METH_VARARGS },
		
///Add
#if defined(__BL_SOUL_ROULETTE__)
		{ "SoulRoulettePacket",					netSoulRoulettePacket,					METH_VARARGS },
#endif