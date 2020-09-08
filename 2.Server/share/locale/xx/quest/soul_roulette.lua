quest soul_roulette begin
	state start begin	
		when 33009.chat."Soul Roulette" begin
			say_title(mob_name(33009))
			say("")
			say("Do you want to open Soul Roulette?")
			say("")
			if select("Yes", "No") == 1 then
				setskin(NOWINDOW)
				pc.open_soul_roulette()
			end			
		end
	end
end