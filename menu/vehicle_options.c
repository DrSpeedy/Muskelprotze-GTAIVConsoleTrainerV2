#pragma once

bool vo_invincibility = false;
bool vo_flywalls = false;
bool vo_stick_to_ground = false;
bool vo_booster = false;
bool vo_helispeed = false;

///================================================
///Display Setup - Muskelprotze
///================================================

void vo_MainSetup(void){
	bool lock;
	uint status;
	Vehicle pveh;
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		GET_CAR_DOOR_LOCK_STATUS(pveh,&status);
		
		if(status != VEHICLE_DOOR_UNLOCKED)
			lock = true;
	}
	menu_header = "Vehicle Options";
	
	menu_addItem("Vehicle Spawner",false);
	//menu_addItem("Paint & Upgrades",false);
	menu_addItemBool("Invincibilty",vo_invincibility);
	menu_addItemBool("Fly Through Walls",vo_flywalls);
	menu_addItemBool("Stick to Ground",vo_stick_to_ground);
	menu_addItemBool("Boosters (~PAD_DPAD_DOWN~ + ~PAD_X~)",vo_booster);
	menu_addItemBool("Super Speed Heli",vo_helispeed);
	menu_addItemBool("Locked Doors",lock);
	menu_addItem("Fix & Wash",true);
	menu_addItem("Flip Vehicle",true);
	menu_addItem("Delete Vehicle",true);
	menu_addItem("Kill Passengers",true);
	return;
}

void vo_SpawnerMainSetup(void){
	menu_header = "Vehicle Spawner";
	
	menu_addItem("Sports",false);
	menu_addItem("Vintige",false);
	menu_addItem("Two Door",false);
	menu_addItem("Four Door",false);
	menu_addItem("Junkers",false);
	menu_addItem("SUVs, Vans & Trucks",false);
	menu_addItem("Commercial",false);
	menu_addItem("Emergency",false);
	menu_addItem("Service",false);
	menu_addItem("Bikes",false);
	menu_addItem("Boats",false);
	menu_addItem("Helicopters",false);	
	return;
}

void vo_SpawnerSetup(void){
	if(last_selected[(menu_level - 1)] == 1){
		menu_header = "Sports";
		
		menu_addItemGXTHash(MODEL_BANSHEE);
		menu_addItemGXTHash(MODEL_COMET);
		menu_addItemGXTHash(MODEL_COQUETTE);
		menu_addItemGXTHash(MODEL_FELTZER);
		menu_addItemGXTHash(MODEL_INFERNUS);
		menu_addItemGXTHash(MODEL_SULTAN);
		menu_addItemGXTHash(MODEL_SULTANRS);
		menu_addItemGXTHash(MODEL_SUPERGT);
		menu_addItemGXTHash(MODEL_TURISMO);
		
		if(episode == 2){
			menu_addItemGXTHash(MODEL_BUFFALO);
			menu_addItemGXTHash(MODEL_BULLET);
			menu_addItemGXTHash(MODEL_F620);
		}
	}
	if(last_selected[(menu_level - 1)] == 2){
		menu_header = "Vintige";
		
		menu_addItemGXTHash(MODEL_BUCCANEER);
		menu_addItemGXTHash(MODEL_DUKES);
		menu_addItemGXTHash(MODEL_FACTION);
		menu_addItemGXTHash(MODEL_MANANA);
		menu_addItemGXTHash(MODEL_PEYOTE);
		menu_addItemGXTHash(MODEL_RUINER);
		menu_addItemGXTHash(MODEL_SABRE);
		menu_addItemGXTHash(MODEL_SABREGT);
		menu_addItemGXTHash(MODEL_STALION);
		menu_addItemGXTHash(MODEL_VIGERO);
		menu_addItemGXTHash(MODEL_VIRGO);
		menu_addItemGXTHash(MODEL_VOODOO);

		if(episode == 2)
			menu_addItemGXTHash(MODEL_TAMPA);		
	}
	if(last_selected[(menu_level - 1)] == 3){
		menu_header = "Two Door";

		menu_addItemGXTHash(MODEL_BLISTA);
		menu_addItemGXTHash(MODEL_FORTUNE);
		menu_addItemGXTHash(MODEL_FUTO);
		menu_addItemGXTHash(MODEL_SENTINEL);
		menu_addItemGXTHash(MODEL_URANUS);
		
		if(episode == 2)
			menu_addItemGXTHash(MODEL_SUPERD);		
	}
	if(last_selected[(menu_level - 1)] == 4){
		menu_header = "Four Door";

		menu_addItemGXTHash(MODEL_ADMIRAL);
		menu_addItemGXTHash(MODEL_CHAVOS);
		menu_addItemGXTHash(MODEL_COGNOSCENTI);
		menu_addItemGXTHash(MODEL_DF8);
		menu_addItemGXTHash(MODEL_DILETTANTE);
		menu_addItemGXTHash(MODEL_EMPEROR);
		menu_addItemGXTHash(MODEL_ESPERANTO);
		menu_addItemGXTHash(MODEL_FEROCI);
		menu_addItemGXTHash(MODEL_HAKUMAI);
		menu_addItemGXTHash(MODEL_INGOT);
		menu_addItemGXTHash(MODEL_INTRUDER);
		menu_addItemGXTHash(MODEL_LOKUS);
		menu_addItemGXTHash(MODEL_MARBELLA);
		menu_addItemGXTHash(MODEL_MERIT);

		menu_addItemGXTHash(MODEL_ORACLE);
		menu_addItemGXTHash(MODEL_PINNACLE);
		menu_addItemGXTHash(MODEL_PMP600);
		menu_addItemGXTHash(MODEL_PREMIER);
		menu_addItemGXTHash(MODEL_PRES);
		menu_addItemGXTHash(MODEL_PRIMO);
		menu_addItemGXTHash(MODEL_ROM);
		menu_addItemGXTHash(MODEL_SCHAFTER);
		menu_addItemGXTHash(MODEL_SOLAIR);
		menu_addItemGXTHash(MODEL_STRATUM);
		menu_addItemGXTHash(MODEL_VINCENT);
		menu_addItemGXTHash(MODEL_WASHINGTON);
		menu_addItemGXTHash(MODEL_WILLARD);

		if(episode == 2){
			menu_addItemGXTHash(MODEL_SERRANO);
			menu_addItemGXTHash(MODEL_SCHAFTER2);
		}	
	}
	if(last_selected[(menu_level - 1)] == 5){
		menu_header = "Junkers";
		
		menu_addItemGXTHash(MODEL_EMPEROR2);
		menu_addItemGXTHash(MODEL_SABRE2);
		menu_addItemGXTHash(MODEL_VIGERO2);	
	}
	if(last_selected[(menu_level - 1)] == 6){
		menu_header = "SUVs, Vans & Trucks";

		menu_addItemGXTHash(MODEL_BOBCAT);
		menu_addItemGXTHash(MODEL_CAVALCADE);
		menu_addItemGXTHash(MODEL_FXT);
		menu_addItemGXTHash(MODEL_E109);
		menu_addItemGXTHash(MODEL_HABANERO);
		menu_addItemGXTHash(MODEL_HUNTLEY);
		menu_addItemGXTHash(MODEL_LANDSTALKER);
		menu_addItemGXTHash(MODEL_MINIVAN);
		menu_addItemGXTHash(MODEL_MOONBEAM);
		menu_addItemGXTHash(MODEL_PATRIOT);
		menu_addItemGXTHash(MODEL_PERENNIAL);
		menu_addItemGXTHash(MODEL_RANCHER);
		menu_addItemGXTHash(MODEL_REBLA);
		
		if(episode == 2)
			menu_addItemGXTHash(MODEL_CAVALCADE2);	
	}
	if(last_selected[(menu_level - 1)] == 7){
		menu_header = "Commercial";
		
		menu_addItemGXTHash(MODEL_AIRTUG);
		menu_addItemGXTHash(MODEL_BENSON);
		menu_addItemGXTHash(MODEL_BIFF);
		menu_addItemGXTHash(MODEL_BOXVILLE);
		menu_addItemGXTHash(MODEL_BURRITO);
		menu_addItemGXTHash(MODEL_FLATBED);
		menu_addItemGXTHash(MODEL_FEROCI2);
		menu_addItemGXTHash(MODEL_PERENNIAL2);
		menu_addItemGXTHash(MODEL_FORKLIFT);
		menu_addItemGXTHash(MODEL_BURRITO2);
		menu_addItemGXTHash(MODEL_MRTASTY);
		menu_addItemGXTHash(MODEL_MULE);
		menu_addItemGXTHash(MODEL_PACKER);
		menu_addItemGXTHash(MODEL_PHANTOM);
		menu_addItemGXTHash(MODEL_PONY);
		menu_addItemGXTHash(MODEL_RIPLEY);
		menu_addItemGXTHash(MODEL_STOCKADE);
		menu_addItemGXTHash(MODEL_SPEEDO);
		menu_addItemGXTHash(MODEL_STEED);
		menu_addItemGXTHash(MODEL_YANKEE);
		
		if(episode == 2)
			menu_addItemGXTHash(MODEL_CADDY);
	}
	if(last_selected[(menu_level - 1)] == 8){
		menu_header = "Emergency";
		
		menu_addItemGXTHash(MODEL_AMBULANCE);
		menu_addItemGXTHash(MODEL_NSTOCKADE);
		menu_addItemGXTHash(MODEL_FBI);
		menu_addItemGXTHash(MODEL_FIRETRUK);
		menu_addItemGXTHash(MODEL_NOOSE);
		menu_addItemGXTHash(MODEL_POLPATRIOT);
		menu_addItemGXTHash(MODEL_POLICE);
		menu_addItemGXTHash(MODEL_POLICE2);
		menu_addItemGXTHash(MODEL_PSTOCKADE);
		if(episode == 2){
			menu_addItemGXTHash(MODEL_APC);
			menu_addItemGXTHash(MODEL_POLICE3);
			menu_addItemGXTHash(MODEL_POLICEW);
			menu_addItemGXTHash(MODEL_POLICE4);
			menu_addItemGXTHash(MODEL_POLICEB);
		}	
	}
	if(last_selected[(menu_level - 1)] == 9){
		menu_header = "Service";
		
		menu_addItemGXTHash(MODEL_BUS);
		menu_addItemGXTHash(MODEL_CABBY);
		menu_addItemGXTHash(MODEL_ROMERO);
		menu_addItemGXTHash(MODEL_TAXI);
		menu_addItemGXTHash(MODEL_TAXI2);
		menu_addItemGXTHash(MODEL_TRASH);
		menu_addItemGXTHash(MODEL_STRETCH);
		if(episode == 2)
			menu_addItemGXTHash(MODEL_LIMO2);	
	}
	if(last_selected[(menu_level - 1)] == 10){
		menu_header = "Bikes";
		
		menu_addItemGXTHash(MODEL_FAGGIO);
		menu_addItemGXTHash(MODEL_BOBBER);
		menu_addItemGXTHash(MODEL_HELLFURY);
		menu_addItemGXTHash(MODEL_NRG900);
		menu_addItemGXTHash(MODEL_PCJ);
		menu_addItemGXTHash(MODEL_SANCHEZ);
		menu_addItemGXTHash(MODEL_ZOMBIEB);
		if(episode == 2){
			menu_addItemGXTHash(MODEL_HEXER);
			menu_addItemGXTHash(MODEL_FAGGIO2);
			menu_addItemGXTHash(MODEL_BATI2);
			menu_addItemGXTHash(MODEL_VADER);
			menu_addItemGXTHash(MODEL_AKUMA);
			menu_addItemGXTHash(MODEL_HAKUCHOU);
			menu_addItemGXTHash(MODEL_DOUBLE);
		}	
	}
	if(last_selected[(menu_level - 1)] == 11){
		menu_header = "Boats";

		menu_addItemGXTHash(MODEL_DINGHY);
		menu_addItemGXTHash(MODEL_JETMAX);
		menu_addItemGXTHash(MODEL_MARQUIS);
		menu_addItemGXTHash(MODEL_PREDATOR);
		menu_addItemGXTHash(MODEL_REEFER);
		menu_addItemGXTHash(MODEL_SQUALO);
		menu_addItemGXTHash(MODEL_TROPIC);
		menu_addItemGXTHash(MODEL_TUGA);
		if(episode == 2){
			menu_addItemGXTHash(MODEL_SMUGGLER);
			menu_addItemGXTHash(MODEL_FLOATER);
			menu_addItemGXTHash(MODEL_BLADE);
		}
	}
	if(last_selected[(menu_level - 1)] == 12){
		menu_header = "Helicopters";
		
		menu_addItemGXTHash(MODEL_ANNIHILATOR);
		menu_addItemGXTHash(MODEL_TOURMAV);
		menu_addItemGXTHash(MODEL_MAVERICK);
		menu_addItemGXTHash(MODEL_POLMAV);
		if(episode == 2){
			menu_addItemGXTHash(MODEL_BUZZARD);
			menu_addItemGXTHash(MODEL_SWIFT);
			menu_addItemGXTHash(MODEL_SKYLIFT);
		}
	}
	return;
}
/*
void vo_MainGarageSetup(void){ //Upgrades & paint
	menu_header = "Upgrades & Paint";
	menu_addItem("Upgrades",false);
	menu_addItem("Paint",false);
	return;
}

void vo_UpgradeSetup(void){
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		char* upgr[10];
		Vehicle pveh;
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		
		menu_header = "Upgrades";
		
		upgr[0] = "Upgrade 0";
		upgr[1] = "Upgrade 1";
		upgr[2] = "Upgrade 2";
		upgr[3] = "Upgrade 3";
		upgr[4] = "Upgrade 4";
		upgr[5] = "Upgrade 5";
		upgr[6] = "Upgrade 6";
		upgr[7] = "Upgrade 7";
		upgr[8] = "Upgrade 8";
		upgr[9] = "Upgrade 9";
		
		uint i = 0,upgr_i = 0;
		
		for(i;i <= 9;i++){
			bool upgr_on = false;
			if(!IS_VEHICLE_EXTRA_TURNED_ON(pveh,i)){
				TURN_OFF_VEHICLE_EXTRA(pveh,i,false);
				upgr_on = true;
			}

			if(IS_VEHICLE_EXTRA_TURNED_ON(pveh,i)){
				upgr_i++;
				if(upgr_on)
					TURN_OFF_VEHICLE_EXTRA(pveh,i,true);

				menu_addItemBool(upgr[upgr_i],IS_VEHICLE_EXTRA_TURNED_ON(pveh,i));
				menu_item[menu_len].num_val = i;
			}		
		}
		if(!upgr_i)
			error("No upgrades!");
	}
	else error("You need a vehicle!");

	return;
}
*/
///================================================
///Action Setup - Muskelprotze
///================================================

void vo_MainAction(void){
	if(item_selected == 2)
		do_toggle(vo_invincibility);
	
	if(item_selected == 3)
		do_toggle(vo_flywalls);
		
	if(item_selected == 4)
		do_toggle(vo_stick_to_ground);
		
	if(item_selected == 5)
		do_toggle(vo_booster);
		
	if(item_selected == 6)
		do_toggle(vo_helispeed);

	if(item_selected == 7){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			Vehicle pveh;
			uint lock;
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			GET_CAR_DOOR_LOCK_STATUS(pveh,&lock);
			if(lock == VEHICLE_DOOR_UNLOCKED)
				LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_LOCKED_BOTH_SIDES);
			else
				LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_UNLOCKED);
			
			menu_items_set = false;
			menu_clean();
		}
	}
		
	if(item_selected == 8){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			Vehicle pveh;
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			FIX_CAR(pveh);
			SET_VEHICLE_DIRT_LEVEL(pveh,0.0);
			print("Vehicle fixed & washed!");
		}	
	}
	
	if(item_selected == 9){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			Vehicle pveh;
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			SET_CAR_ON_GROUND_PROPERLY(pveh);
		}		
	}
	
	if(item_selected == 10){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			Vehicle pveh;
			Ped driver;
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			GET_DRIVER_OF_CAR(pveh,&driver);
			if(driver == pPlayer){
				DELETE_CAR(&pveh);
				MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
			}
			else print("You must be the driver of this vehicle");
		}
	}	
	
	if(item_selected == 11){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			Vehicle pveh[2];
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh[0]);
			if(network){
				GET_NETWORK_ID_FROM_VEHICLE(pveh[0],&pveh[1]);
				if(!network_control(pveh[1])){
					error("Network Control");
					return;
				}
				float x,y,z;
				GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
				teleport_char(pPlayer,0.0f,4000.0f,0.0f);
				WAIT(100);
				teleport_char(pPlayer,x,y,z);
			}
		}
	}
	
	return;
}

void vo_SpawnerAction(void){
	spawn_car(menu_item[item_selected].num_val);
	return;
}

void vo_LoopedAction(void){
	Vehicle pveh;
	if(vo_invincibility){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			SET_CAR_CAN_BE_DAMAGED(pveh,false);
			SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
			SET_CAN_BURST_CAR_TYRES(pveh,false);
		}
	}
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		uint model;
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		GET_CAR_MODEL(pveh,&model);
		if(IS_THIS_MODEL_A_HELI(model) || IS_THIS_MODEL_A_PLANE(model))
			SET_CAR_COLLISION(pveh,!vo_flywalls);
	}
	if(vo_stick_to_ground){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			SET_CAR_ON_GROUND_PROPERLY(pveh);
		}
	}
	if(vo_booster){
		if(IS_CHAR_IN_ANY_CAR(pPlayer) && IS_BUTTON_PRESSED(0,BUTTON_DPAD_DOWN) && IS_BUTTON_JUST_PRESSED(0,BUTTON_S)){
			float speed;
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			GET_CAR_SPEED(pveh,&speed);
			SET_CAR_FORWARD_SPEED(pveh,(speed * 5.0f));
		}
	}
	if(vo_helispeed){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			uint model;
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			GET_CAR_MODEL(pveh,&model);
			if(IS_THIS_MODEL_A_HELI(model) && IS_BUTTON_PRESSED(0,BUTTON_R2)){
				float speed;
				GET_CAR_SPEED(pveh,&speed);
				if(speed >= 15.0f)
					SET_CAR_FORWARD_SPEED(pveh,(speed * 1.2f));
			}
		}
	}
}