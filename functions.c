//functions.c
#pragma once

#define do_toggle(x) x = !x; menu_items_set = false; menu_clean();

#include "menu/shared_functions.c"
#include "menu/player_options.c"
#include "menu/vehicle_options.c"
#include "menu/weapon_options.c"
#include "menu/network_players.c"
#include "menu/teleports.c"
#include "menu/misc.c"

void project_doAction(void){
	if(menu_level == 2){
		if(last_selected[1] == 1){
			po_MainAction();
			return;
		}
		if(last_selected[1] == 2){
			vo_MainAction();
			return;
		}
		if(last_selected[1] == 3){
			wo_MainAction();
			return;
		}
		if(last_selected[1] == 5){
			tele_Action();
			return;
		}
		if(last_selected[1] == 6){
			m_MainAction();
			return;
		}
	}
	
	if(menu_level == 3){
		if(last_selected[1] == 1){
			if(last_selected[2] == 1){
				po_AnimAction();
				return;
			}
		}
		if(last_selected[1] == 3){
			if(last_selected[2] == 1){
				wo_SpawnerAction();
				return;
			}
		}
		if(last_selected[1] == 4){
			if(last_selected[2] == 1){
				np_AllNetworkAction();
				return;
			}
			np_NetworkOptionsAction((last_selected[(menu_level - 1)] - 2));
			return;
		}
		if(last_selected[1] == 6){
			if(last_selected[2] == 1){
				m_ThrowAction();
				return;
			}
			if(last_selected[2] == 2){
				m_AirAction();
				return;
			}
		}
	}
	
	if(menu_level == 4){
		if(last_selected[1] == 2){
			if(last_selected[2] == 1){
				vo_SpawnerAction();
				return;
			}
		}
		if(last_selected[1] == 3){
			if(last_selected[2] == 1){
				if(last_selected[3] == 2){
					wo_TBOGTSpawnerAction();
					return;
				}
			}
		}
		if(last_selected[1] == 4){
			if(last_selected[2] != 1){
				if(last_selected[3] == 1){
					np_NetworkWeaponAction((last_selected[2] - 2));
					return;
				}
				if(last_selected[3] == 2){
					np_NetworkTeleportAction((last_selected[2] - 2));
					return;
				}
				if(last_selected[3] == 3){
					np_NetworkVehicleAction((last_selected[2] - 2));
					return;
				}
			}
		}
	}

	menu_clean();
	inError = true;
	actionError = true;
	menu_header = "Error";
	menu_addItem("File: Functions.c",false);
	menu_addItem("Press ~PAD_B~ to return",false);
	return;
}

void project_catchFunctionButtonPress(void){
	//Nothing goes here
	return;
}

void project_loopedFunctions(void){
	po_LoopedAction();
	np_networkLoop();
	
	vo_LoopedAction();
	wo_LoopedAction();
	
	m_LoopedAction();
	
	Vehicle tmp,tmp2;
	
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		Ped driver;
		SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(pPlayer,false); // Seat belt ;D
		GET_CAR_CHAR_IS_USING(pPlayer,&tmp);
		GET_DRIVER_OF_CAR(tmp,&driver);
		if(driver == pPlayer){
			GET_NETWORK_ID_FROM_VEHICLE(tmp,&tmp2);
			SET_NETWORK_ID_CAN_MIGRATE(tmp2,false);
		}
	}
	else if(HAS_CONTROL_OF_NETWORK_ID(tmp2))
		SET_NETWORK_ID_CAN_MIGRATE(tmp2,true);
		
		
	if(HAS_CHAR_GOT_WEAPON(pPlayer,WEAPON_ROCKET)){
		REMOVE_WEAPON_FROM_CHAR(pPlayer,WEAPON_ROCKET);
		print("~r~Someone just tried to freeze you!");
	}
}