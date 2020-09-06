#Add
if app.__BL_SOUL_ROULETTE__:
	import uiMiniGameRoulette
	
#Find in def __init__(self):
		self.wndInventory = None
		
#Add
		if app.__BL_SOUL_ROULETTE__:
			self.wndMiniGameRoulette = None
			
#Find
		wndChatLog = uiChat.ChatLogWindow()
		
#Add
		if app.__BL_SOUL_ROULETTE__:
			self.wndMiniGameRoulette = uiMiniGameRoulette.RouletteWindow()
			
#Find
		self.privateShopBuilder.SetItemToolTip(self.tooltipItem)
		
#Add
		if app.__BL_SOUL_ROULETTE__:
			self.wndMiniGameRoulette.SetItemToolTip(self.tooltipItem)
			
#Find
		if self.wndCubeResult:
			self.wndCubeResult.Destroy()
			
#Add
		if app.__BL_SOUL_ROULETTE__:
			if self.wndMiniGameRoulette:
				self.wndMiniGameRoulette.Destroy()
				del self.wndMiniGameRoulette
				
#Find
	def HideAllWhisperButton(self):
		for btn in self.whisperButtonList:
			btn.Hide()
			
#Add	
	if app.__BL_SOUL_ROULETTE__:
		def Roulette_OPEN(self):
			if self.wndMiniGameRoulette:
				self.wndMiniGameRoulette.Show()			
		def Roulette_Close(self):
			if self.wndMiniGameRoulette:
				self.wndMiniGameRoulette.Hide()
		def Roulette_TurnWheel(self, spin, i):
			if self.wndMiniGameRoulette:
				self.wndMiniGameRoulette.TurnWheel(spin, i)
		def Roulette_SetIcons(self, i, vnum, count):
			if self.wndMiniGameRoulette:
				self.wndMiniGameRoulette.SetSlotItem(int(i), int(vnum), int(count))