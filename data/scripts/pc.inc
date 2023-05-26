EventScript_PC::
	lockall
	setvar VAR_0x8004, PC_LOCATION_OTHER
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox Text_BootUpPC, MSGBOX_DEFAULT
	goto EventScript_PCMainMenu
	end

EventScript_PCMainMenu::
	message gText_WhichPCShouldBeAccessed
	waitmessage
	special ScriptMenu_CreatePCMultichoice
	waitstate
	goto EventScript_AccessPC
	end

EventScript_AccessPC::
	switch VAR_RESULT
	case 0, EventScript_AccessPokemonStorage
	case 1, EventScript_AccessPlayersPC
	case 3, EventScript_AccessPokedexReward
	case 4, EventScript_AccessHallOfFame
	case 5, EventScript_TurnOffPC
	case MULTI_B_PRESSED, EventScript_TurnOffPC
	end

EventScript_AccessPlayersPC::
	playse SE_PC_LOGIN
	msgbox gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto EventScript_PCMainMenu
	end

EventScript_AccessPokedexReward::
	goto_if_unset FLAG_SYS_POKEDEX_GET, EventScript_TurnOffPC
	playse SE_PC_LOGIN
	msgbox gText_AccessedPokedexReward, MSGBOX_DEFAULT
	delay 10
	specialvar VAR_RESULT, CheckHasPokedexReward
	goto_if_eq VAR_RESULT, TRUE, EventScript_GivePokedexReward
	goto_if_eq VAR_RESULT, FALSE, EventScript_NoPokedexReward
	end

EventScript_GivePokedexReward::
	special ChoosePokedexReward
	giveitem VAR_RESULT
	call_if_eq VAR_RESULT, TRUE, EventScript_PokedexRewardReceived
	call_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	goto EventScript_PCMainMenu
	end

EventScript_PokedexRewardReceived::
	addvar VAR_POKEDEX_REWARD, 1
	specialvar VAR_RESULT, CheckHasPokedexReward
	goto_if_eq VAR_RESULT, TRUE, EventScript_GivePokedexReward
	return

EventScript_NoPokedexReward::
	msgbox gText_NoPokedexReward, MSGBOX_DEFAULT
	goto EventScript_PCMainMenu
	end

EventScript_AccessPokemonStorage::
	playse SE_PC_LOGIN
	msgbox gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto EventScript_PCMainMenu
	end

EventScript_AccessSomeonesPC::
	msgbox gText_AccessedSomeonesPC, MSGBOX_DEFAULT
	return

EventScript_AccessLanettesPC::
	msgbox gText_AccessedLanettesPC, MSGBOX_DEFAULT
	return

EventScript_TurnOffPC::
	setvar VAR_0x8004, PC_LOCATION_OTHER
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

EventScript_AccessHallOfFame::
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_TurnOffPC
	playse SE_PC_LOGIN
	special AccessHallOfFamePC
	waitstate
	goto EventScript_AccessPC
	end
