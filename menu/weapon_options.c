#pragma once

bool wo_ammo = true;
bool wo_eammo = false;

void wo_MainSetup(void){
	menu_header = "Weapon Options";
	bool stream = false;
	if(GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT("e_mp5") == 1)
		stream = true;
	else
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("e_mp5");//This is incase it was loaded more than once
		
	menu_addItem("Weapon Spawner",false);
	menu_addItemBool("Unlimited Ammo",wo_ammo);
	menu_addItemBool("Endless Magazine",wo_eammo);
	menu_addItemBool("Explosive MP5",stream);
}

void wo_SpawnerSetup(void){
	menu_header = "Weapon Spawner";
	
	menu_addItemNumber("All Weapons",1,3);
	menu_addItem("TBOGT Weapons",false);
	menu_addItem("Grenades",true);
	menu_addItem("Glock 17",true);
	menu_addItem("Deagle",true);
	menu_addItem("Pump Shotgun",true);
	menu_addItem("Semi-Auto Shotgun",true);
	menu_addItem("Micro Uzi",true);
	menu_addItem("MP5",true);
	menu_addItem("AK-47",true);
	menu_addItem("M4",true);
	menu_addItem("M40A5",true);
	menu_addItem("Sniper Rifle",true);
	menu_addItem("Rocket Launcher",true);
	menu_addItem("Baseball Bat",true);
	menu_addItem("Pool Cue",true);
}

void wo_TBOGTSpawnerSetup(void){
	menu_header = "TBOGT Weapons";
	
	menu_addItem(".44 Pistol",true);
	menu_addItem("Expl AA12",true);
	menu_addItem("AA12",true);
	menu_addItem("P-90",true);
	menu_addItem("Uzi",true);
	menu_addItem("M249",true);
	menu_addItem("Expl Sniper",true);
	menu_addItem("Grenade Launcher",true);
	menu_addItem("Sticky Bombs",true);
}

void wo_MainAction(void){
	if(item_selected == 2){
		wo_eammo = false;
		do_toggle(wo_ammo);
	}
	
	if(item_selected == 3){
		wo_ammo = false;
		do_toggle(wo_eammo);
	}
	
	if(item_selected == 4){
		bool stream = menu_item[item_selected].extra_val;
		if(stream)
			TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("e_mp5");
		else{
			if(DOES_SCRIPT_EXIST("e_mp5")){
				REQUEST_SCRIPT("e_mp5");
				while(!HAS_SCRIPT_LOADED("e_mp5"))
					WAIT(0);
				
				START_NEW_SCRIPT("e_mp5",512);
				MARK_SCRIPT_AS_NO_LONGER_NEEDED("e_mp5");
			}
			else return error("Missing Script: e_mp5.sco");
		}
		menu_items_set = false;
		menu_clean();
	}
}

void wo_SpawnerAction(void){
	if(item_selected == 1){
		if(menu_item[item_selected].num_val == 1){
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_DEAGLE,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_GRENADE,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MP5,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M4,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BARETTA,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
			print("You have been given advanced weapons.");
		}
		if(menu_item[item_selected].num_val == 2){
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_PISTOL,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MOLOTOV,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MICRO_UZI,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_AK47,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SHOTGUN,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M40A1,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
			print("You have been given poor weapons.");						
		}
		if(menu_item[item_selected].num_val == 3){
			if(episode == 2){
				GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_9,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_10,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_13,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_14,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_15,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_1,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_16,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
				print("You have been given TBOGT weapons.");
			}
			else error("TBOGT Only");
		}
	}
	if(item_selected == 3){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_GRENADE,AMMO_MAX,false);
		print("You have been given some grenades");				
	}
	if(item_selected == 4){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_PISTOL,AMMO_MAX,false);
		print("You have been given a Glock 17");		
	}
	if(item_selected == 5){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_DEAGLE,AMMO_MAX,false);
		print("You have been given a Desert Eagle");		
	}
	if(item_selected == 6){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SHOTGUN,AMMO_MAX,false);
		print("You have been given a Pump Shotgun");		
	}
	if(item_selected == 7){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BARETTA,AMMO_MAX,false);
		print("You have been given a Tactical Shotgun");		
	}
	if(item_selected == 8){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MICRO_UZI,AMMO_MAX,false);
		print("You have been given a Micro Uzi");		
	}
	if(item_selected == 9){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MP5,AMMO_MAX,false);
		print("You have been given an MP5");		
	}
	if(item_selected == 10){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_AK47,AMMO_MAX,false);
		print("You have been given an AK-47");		
	}
	if(item_selected == 11){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M4,AMMO_MAX,false);
		print("You have been given an AR-15");		
	}
	if(item_selected == 12){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M40A1,AMMO_MAX,false);
		print("You have been given an M40A1");		
	}
	if(item_selected == 13){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
		print("You have been given a Sniper Rifle");		
	}
	if(item_selected == 14){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
		print("You have been given an RPG");		
	}
	if(item_selected == 15){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
		print("You have been given a baseball bat");		
	}
	if(item_selected == 16){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
		print("You have been given a pool cue");			
	}	
}

void wo_TBOGTSpawnerAction(void){
	if(item_selected == 1){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_9,AMMO_MAX,false);
		print("You have been given a .44 Pistol.");
	}
	if(item_selected == 2){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_10,AMMO_MAX,false);
		print("You have been given an Explosive AA12.");
	}
	if(item_selected == 3){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_11,AMMO_MAX,false);
		print("You have been given an AA12.");
	}
	if(item_selected == 4){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_12,AMMO_MAX,false);
		print("You have been given a P-90.");
	}
	if(item_selected == 5){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_13,AMMO_MAX,false);
		print("You have been given an Uzi.");
	}
	if(item_selected == 6){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_14,AMMO_MAX,false);
		print("You have been given an M249.");
	}
	if(item_selected == 7){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_15,AMMO_MAX,false);
		print("You have been given an Explosive Sniper.");
	}
	if(item_selected == 8){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_1,AMMO_MAX,false);
		print("You have been given a Grenade Launcher.");
	}
	if(item_selected == 9){
		GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_16,AMMO_MAX,false);
		print("You have been given some Sticky Bombs.");
	}						
}

void wo_LoopedAction(void){
	if(wo_ammo){
		if(IS_CHAR_SHOOTING(pPlayer)){
			uint weapon;
			GET_CURRENT_CHAR_WEAPON(pPlayer,&weapon);
			GIVE_WEAPON_TO_CHAR(pPlayer,weapon,AMMO_MAX,false);
		}
	}

	if(wo_eammo){
		if(IS_CHAR_SHOOTING(pPlayer)){
			uint weapon,ammo;
			GET_CURRENT_CHAR_WEAPON(pPlayer,&weapon);
			if(weapon != WEAPON_GRENADE && weapon != WEAPON_MOLOTOV){
				GET_MAX_AMMO_IN_CLIP(pPlayer,weapon,&ammo);
				SET_AMMO_IN_CLIP(pPlayer,weapon,ammo);
			}
		}
	}
}