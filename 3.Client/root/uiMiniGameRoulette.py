#Created by blackdragonx61(Mali61)

import ui, app, net, wndMgr, localeInfo

ROULETTE_SLOT_MAX = 20

class RouletteWindow(ui.ScriptWindow):		
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.isLoaded = False
		
		self.spin_button					= None
		self.slot_edge_effect				= None
		self.items_slot						= None
		self.item_vnums						= [0 for col in range(0, ROULETTE_SLOT_MAX)]
		self.tooltipItem					= None
		self.IsTurning						= False
		self.Price							= None
		self.Soul							= None
		self.CurrentPos						= 0
		self.NextPos						= -1
		self.SpinTour 						= 1
		self.lastUpdate 					= 0
		self.__LoadWindow()
		
	def __del__(self):
		ui.ScriptWindow.__del__(self)
		
	def Show(self, price):
		self.__LoadWindow()
		self.Reset()
		self.Price.SetText(localeInfo.NumberToMoneyString(price))
		ui.ScriptWindow.Show(self)
		self.SetTop()

	def Hide(self):
		wndMgr.Hide(self.hWnd)
		
	def Close(self):
		net.SoulRoulettePacket(1) # Request Close
		
	def __LoadScript(self, fileName):
		pyScrLoader = ui.PythonScriptLoader()
		pyScrLoader.LoadScriptFile(self, fileName)
	
	def OnPressEscapeKey(self):
		self.Close()
		return True
		
	def __LoadWindow(self):
		if self.isLoaded:
			return
		self.isLoaded = True
		try:
			self.__LoadScript("UIScript/minigameroulettewindow.py")
		except:
			import exception
			exception.Abort("RouletteWindow.LoadWindow.__LoadScript")
		try:
			self.spin_button				= self.GetChild("spin_button")
			self.slot_edge_effect			= self.GetChild("slot_edge_effect")			
			self.items_slot					= self.GetChild("item_slot")
			self.slot_edge_effect			= self.GetChild("slot_edge_effect")
			self.Soul						= self.GetChild("spin_button_text2")
			self.Soul.Hide() # 50 Soul Text Hide
			self.Price						= self.GetChild("spin_button_text3")
		
		except:
			import exception
			exception.Abort("RouletteWindow.LoadWindow.__BindObject")
			
		try:			
			self.GetChild("board").SetCloseEvent( ui.__mem_func__(self.Close) )	
			if self.items_slot:
				self.items_slot.SetOverInItemEvent(ui.__mem_func__(self.__SlotOverInItem))
				self.items_slot.SetOverOutItemEvent(ui.__mem_func__(self.__SlotOverOutItem))
			if self.spin_button:
				self.spin_button.SetEvent( ui.__mem_func__(self.TurnPacket) )
		except:
			import exception
			exception.Abort("RouletteWindow.LoadWindow.__BindEvent")
			
	def TurnPacket(self):
		net.SoulRoulettePacket(2) # Request Turn
		
	def EdgeEffect(self, i):
		edge_effect_pos_tuple = ((25, 46), (69, 46), (113, 46), (157, 46), (201, 46), (245, 46), (245, 90), (245, 134), (245, 178), (245, 222), (245, 266), (201, 266), (157, 266), (113, 266), (69, 266), (25, 266), (25, 222), (25, 178), (25, 134), (25, 90))
		self.slot_edge_effect.SetPosition(edge_effect_pos_tuple[i][0], edge_effect_pos_tuple[i][1])
	
	def TurnWheel(self, spin, i):
		self.spin_button.Disable()
		self.SpinTour = spin
		self.NextPos = i
		self.IsTurning = True
		
	def OnUpdate(self):
		if not self.IsTurning or app.GetGlobalTime() - self.lastUpdate < 100:
			return
			
		self.lastUpdate = app.GetGlobalTime()
		
		if self.CurrentPos == self.NextPos and self.SpinTour <= 0:
			net.SoulRoulettePacket(3) # Request gift
			self.IsTurning = False
			self.NextPos = -1
			self.SpinTour = 1
			self.spin_button.Enable()
		else:
			self.CurrentPos += 1
			if self.CurrentPos >= ROULETTE_SLOT_MAX:
				self.CurrentPos = 0
				self.SpinTour -= 1
			self.EdgeEffect(self.CurrentPos)
			
	def Reset(self):		
		self.IsTurning = False
		self.EdgeEffect(0)
		self.lastUpdate = 0	
		self.CurrentPos = 0
		self.NextPos = -1
		self.SpinTour = 1
		
	def Destroy(self):
		self.isLoaded = 0
		self.Reset()
		self.item_vnums	= [0 for col in range(0, ROULETTE_SLOT_MAX)]
		self.tooltipItem			= None
		if self.Price:
			del self.Price
		if self.Soul:
			del self.Soul
		if self.spin_button:
			del self.spin_button
		if self.slot_edge_effect:
			del self.slot_edge_effect
		if self.items_slot:
			del self.items_slot
		
	def SetSlotItem(self, slotIndex, item_vnum, item_count):
		if not self.items_slot or not self.item_vnums:
			return
		
		self.items_slot.SetItemSlot( slotIndex, item_vnum, item_count )
		self.item_vnums[slotIndex] = item_vnum
		
	def __SlotOverInItem(self, slotIndex):
		if self.tooltipItem:
			if self.item_vnums and self.item_vnums[slotIndex]:
				self.tooltipItem.SetItemToolTip( self.item_vnums[slotIndex] )
	
	def __SlotOverOutItem(self):
		if self.tooltipItem:
			self.tooltipItem.HideToolTip()
			
	def SetItemToolTip(self, tooltipItem):
		self.tooltipItem = tooltipItem	