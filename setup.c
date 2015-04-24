//setup.c
#pragma once

void project_set(void){
	menu_items_set = true;
	if(menu_level == 1){
		menu_header = "Main Menu";
		menu_addItem("Player Options",false);
		menu_addItem("Vehicle Options",false);
		menu_addItem("Weapon Options",false);
		menu_addItem("Network Players",false);
		menu_addItem("Teleports",false);
		menu_addItem("Misc",false);
		return;
	}
	if(menu_level == 2){
		if(last_selected[1] == 1){
			po_MainSetup();
			return;
		}
		if(last_selected[1] == 2){
			vo_MainSetup();
			return;
		}
		if(last_selected[1] == 3){
			wo_MainSetup();
			return;
		}
		if(last_selected[1] == 4){
			np_NetworkMainSetup();
			return;
		}
		if(last_selected[1] == 5){
			tele_Setup();
			return;
		}
		if(last_selected[1] == 6){
			m_MainSetup();
			return;
		}
		
	}
	if(menu_level == 3){
		if(last_selected[1] == 1){
			if(last_selected[2] == 1){
				po_AnimSetup();
				return;
			}
		}
		if(last_selected[1] == 2){
			if(last_selected[2] == 1){
				vo_SpawnerMainSetup();
				return;
			}
		}
		if(last_selected[1] == 3){
			if(last_selected[2] == 1){
				wo_SpawnerSetup();
				return;
			}
		}
		if(last_selected[1] == 4){
			if(last_selected[2] == 1){
				np_AllOptionsSetup();
				return;
			}
			np_NetworkOptionsSetup();
			return;
		}
		if(last_selected[1] == 6){
			if(last_selected[2] == 1){
				m_ThrowSetup();
				return;
			}
			if(last_selected[2] == 2){
				m_AirSetup();
				return;
			}
		}
		
	}
	if(menu_level == 4){
		if(last_selected[1] == 2){
			if(last_selected[2] == 1){
				vo_SpawnerSetup();	
				return;
			}
		}
		if(last_selected[1] == 3){
			if(last_selected[2] == 1){
				if(last_selected[3] == 2){
					wo_TBOGTSpawnerSetup();
					return;
				}	
			}
		}
		if(last_selected[1] == 4){
			if(last_selected[2] != 1){
				if(last_selected[3] == 1){
					np_NetworkWeaponSetup();
					return;
				}
				if(last_selected[3] == 2){
					np_NetworkTeleportSetup();
					return;
				}
				if(last_selected[3] == 3){
					np_NetworkVehicleSetup();
					return;
				}
				
			}
		}
	}
	inError = true;
	menu_header = "Error";
	menu_addItem("File: Setup.c",false);
	menu_addItem("Press ~PAD_B~ to return",false);
	return;
}