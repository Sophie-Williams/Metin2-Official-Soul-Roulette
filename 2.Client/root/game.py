#Find
		onPressKeyDict[app.DIK_F4]	= lambda : self.__PressQuickSlot(7)
		
#Add
		if app.__BL_SOUL_ROULETTE__:
			onPressKeyDict[app.DIK_F7]	= lambda : net.SoulRoulettePacket(0)
			
#Find
		self.serverCommander=stringCommander.Analyzer()
		for serverCommandItem in serverCommandList.items():
			self.serverCommander.SAFE_RegisterCallBack(
				serverCommandItem[0], serverCommandItem[1]
			)
			
#Add Above
		if app.__BL_SOUL_ROULETTE__:
			serverCommandList["BINARY_ROULETTE_OPEN"] = self.BINARY_ROULETTE_OPEN
			serverCommandList["BINARY_ROULETTE_CLOSE"] = self.BINARY_ROULETTE_CLOSE
			serverCommandList["BINARY_ROULETTE_TURN"] = self.BINARY_ROULETTE_TURN
			serverCommandList["BINARY_ROULETTE_ICON"] = self.BINARY_ROULETTE_ICON
			
#Find
	def AskSafeboxPassword(self):
		self.interface.AskSafeboxPassword()
		
#Add
	if app.__BL_SOUL_ROULETTE__:
		def BINARY_ROULETTE_OPEN(self):
			if self.interface:
				self.interface.Roulette_OPEN()
		def BINARY_ROULETTE_CLOSE(self):
			if self.interface:
				self.interface.Roulette_Close()
		def BINARY_ROULETTE_TURN(self, spin, idx):
			if self.interface:
				self.interface.Roulette_TurnWheel(spin, idx)
		def BINARY_ROULETTE_ICON(self, idx, vnum, count):
			if self.interface:
				self.interface.Roulette_SetIcons(idx, vnum, count)