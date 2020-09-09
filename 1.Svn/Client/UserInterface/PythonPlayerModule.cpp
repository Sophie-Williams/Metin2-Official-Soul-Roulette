//Find
PyObject * playerGetTargetVID(PyObject* poSelf, PyObject* poArgs)
{
	...
}

///Add
#if defined(__BL_SOUL_ROULETTE__)
PyObject* playerGetRouletteData(PyObject* poSelf, PyObject* poArgs)
{
	int iOption;
	if (!PyTuple_GetInteger(poArgs, 0, &iOption))
		return Py_BuildException();
	
	enum { Speed, Position };
	PyObject* SList = PyList_New(0);

	if (iOption == Speed) {
		const std::vector<int> lSpeedList = { 325, 105, 75, 40, 25, 10 };
		for (auto it = lSpeedList.begin(); it != lSpeedList.end(); ++it)
			PyList_Append(SList, Py_BuildValue("i", (*it)));
	}
	else if (iOption == Position) {
		const std::vector<std::pair<int, int>> lPositionList = { {25, 46}, {69, 46}, {113, 46}, {157, 46}, {201, 46}, {245, 46}, {245, 90}, {245, 134}, {245, 178}, {245, 222}, {245, 266}, {201, 266}, {157, 266}, {113, 266}, {69, 266}, {25, 266}, {25, 222}, {25, 178}, {25, 134}, {25, 90} };
		for (auto it = lPositionList.begin(); it != lPositionList.end(); ++it)
			PyList_Append(SList, Py_BuildValue("[ii]", it->first, it->second));
	}

	return SList;
}
#endif

//Find
		{ "SetItemCount",				playerSetItemCount,					METH_VARARGS },
		
///Add
#if defined(__BL_SOUL_ROULETTE__)
		{ "GetRouletteData",			playerGetRouletteData,				METH_VARARGS },
#endif

//Find
	PyModule_AddIntConstant(poModule, "EQUIPMENT_PAGE_COUNT",	c_Equipment_Count);
	
///Add
#if defined(__BL_SOUL_ROULETTE__)
	PyModule_AddIntConstant(poModule, "ROULETTE_ITEM_MAX", ROULETTE_ITEM_MAX);
	PyModule_AddIntConstant(poModule, "ROULETTE_PACKET_CLOSE", 0);
	PyModule_AddIntConstant(poModule, "ROULETTE_PACKET_TURN", 1);
	PyModule_AddIntConstant(poModule, "ROULETTE_PACKET_GIFT", 2);
#endif