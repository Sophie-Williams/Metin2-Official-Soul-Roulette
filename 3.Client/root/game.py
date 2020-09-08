#Find
	def AskSafeboxPassword(self):
		self.interface.AskSafeboxPassword()
		
#Add
	if app.__BL_SOUL_ROULETTE__:
		def BINARY_ROULETTE_OPEN(self, price):
			if self.interface:
				self.interface.Roulette_Open(price)
		def BINARY_ROULETTE_CLOSE(self):
			if self.interface:
				self.interface.Roulette_Close()
		def BINARY_ROULETTE_TURN(self, spin, idx):
			if self.interface:
				self.interface.Roulette_TurnWheel(spin, idx)
		def BINARY_ROULETTE_ICON(self, idx, vnum, count):
			if self.interface:
				self.interface.Roulette_SetIcons(idx, vnum, count)