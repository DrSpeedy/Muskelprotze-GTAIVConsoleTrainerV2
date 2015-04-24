#pragma once

///================================================
///Display Setup - Muskelprotze
///================================================

void np_NetworkMainSetup(void){
	uint i;
	menu_header = "Network Players";
	player_count = 0;
	
	for(i = 0;i <= 15;i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
		if(GET_PLAYER_ID() == i) continue;
			GET_PLAYER_CHAR(i,&players[player_count].ped);
			players[player_count].gamertag = GET_PLAYER_NAME(i);
			players[player_count].id = i;
			player_count++;
	}
				
	if(player_count > 0){
		menu_addItem("All Players",false);
		for(i = 0;i <= player_count;i++){
			if(!IS_STRING_NULL(players[i].gamertag)){
				menu_addItem(players[i].gamertag,false);
				menu_item[menu_len].type = 7;
			}
		}
	}
	else{
		inError = true;
		menu_header = "Error";
		menu_addItem("Game is empty",false);
		menu_addItem("Press ~PAD_B~ to return",false);
	}
}

void np_AllOptionsSetup(void){ //All Players
	menu_header = "All Players";
	
	menu_addItem("Give Weapons",true);
	menu_addItem("Remove Weapons",true);
	menu_addItem("Nuke",true);
	menu_addItem("Burn",true);
	menu_addItem("Hippotize",true);
	menu_addItem("Delete Vehicles",true);
	menu_addItem("Party Time",true);
	menu_addItem("Prison Derby",true);
	//menu_addItem("Air Superiority",true);
	return;
}

void np_NetworkOptionsSetup(void){
	int index = last_selected[(menu_level - 1)] - 2;
	int id = players[index].id;
	
	menu_header = players[index].gamertag;
	
	menu_addItem("Weapons",false);
	menu_addItem("Teleport",false);
	menu_addItem("Vehicle",false);
	menu_addItemBool("Juggernaut",players[id].juggernaut);
	menu_addItemBool("Force Field",players[id].forcefield);
	menu_addItem("Nuke",true);
	menu_addItem("Burn",true);
	menu_addItem("Taser",true);
	menu_addItem("Hippotize",true);
	menu_addItem("Cube-ify",true);
	menu_addItem("Jail",true);
	menu_addItem("Kick",true);
}

void np_NetworkWeaponSetup(void){
	int index = last_selected[(menu_level - 2)] - 2;
	menu_header = players[index].gamertag;
	
	menu_addItem("Advanced Weapons",true);
	menu_addItem("Poor Weapons",true);
	menu_addItem("TBOGT Weapons",true);
	menu_addItem("Remove Weapons",true);
}

void np_NetworkTeleportSetup(void){
	int index = last_selected[(menu_level - 2)] - 2;
	menu_header = players[index].gamertag;
	
	menu_addItem("To Them",true);
	menu_addItem("Into Their Vehicle",true);
	menu_addItem("To You",true);
}

void np_NetworkVehicleSetup(void){
	int index = last_selected[(menu_level - 2)] - 2;
	menu_header = players[index].gamertag;
	
	menu_addItem("Delete Vehicle",true);
	menu_addItem("Slingshot",true);
	menu_addItem("Break Engine/Tires",true);
	menu_addItem("Attach Self",true);
}

///================================================
///Function Setup - Muskelprotze
///================================================

void np_AllNetworkAction(void){
	uint player_loop = player_count - 1;
	uint i;
	if(item_selected == 1){
		for(i = 0;i <= player_loop;i++){
			if(DOES_CHAR_EXIST(players[i].ped)){
				REMOVE_ALL_CHAR_WEAPONS(players[i].ped);
				
				WAIT(10);
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_DEAGLE,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_GRENADE,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_MP5,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_M4,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_BARETTA,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_BASEBALLBAT,1,false);
				
				GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_ARMOUR,1,false);
				ADD_ARMOUR_TO_CHAR(players[i].ped,99);				
			}
		}
		print("All players armed");
		return;
	}
	if(item_selected == 2){
		for(i = 0;i <= player_loop;i++){
			if(DOES_CHAR_EXIST(players[i].ped))
				REMOVE_ALL_CHAR_WEAPONS(players[i].ped);
		}
		print("All players disarmed");
		return;
	}
	if(item_selected == 3){
		float x,y,z;
		print("This may take a moment..");
		for(i = 0;i <= player_loop;i++){
			if(DOES_CHAR_EXIST(players[i].ped)){
				if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
					Vehicle pveh,nveh;
					GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
					GET_NETWORK_ID_FROM_VEHICLE(pveh,&nveh);
					if(network_control(nveh)){
					
						SET_CAR_CAN_BE_DAMAGED(pveh,true);
						SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
						SET_CAN_BURST_CAR_TYRES(pveh,true);
						MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					}
				}
				GET_CHAR_COORDINATES(players[i].ped,&x,&y,&z);
				create_big_explosion(x,y,z);
			}
		}
		print("All players bombed");
		return;
	}
	if(item_selected == 4){
		for(i = 0;i <= player_loop;i++){
			if(DOES_CHAR_EXIST(players[i].ped))
				START_CHAR_FIRE(players[i].ped);
		}
		print("Set fire to all players");
		return;
	}
	if(item_selected == 5){
		for(i = 0;i <= player_loop;i++){
			if(DOES_CHAR_EXIST(players[i].ped)){
				Object otmp;
				CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
								
				ATTACH_OBJECT_TO_PED(otmp,players[i].ped,0,0.0,0.0,-0.11,0.0,0.0,3.0,false);
				WAIT(10);			
			}
		}
		print("All players have been hippotized");
		return;
	}
	if(item_selected == 6){
		print("This may take a moment..");
		for(i = 0;i <= player_loop;i++){
			if(DOES_CHAR_EXIST(players[i].ped)){
				if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
					Vehicle pveh,nveh;
					GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
					GET_NETWORK_ID_FROM_VEHICLE(pveh,&nveh);
					if(network_control(nveh)){
					
						DELETE_CAR(&pveh);
						MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					}
				}
			}
			
		}
		print("All players vehicle's have been deleted");
		return;
	}
	if(item_selected == 7){
		float x,y,z;
		print("This may take a moment..");
		GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
		for(i = 0;i <= player_loop;i++){
			if(DOES_CHAR_EXIST(players[i].ped)){
				Vehicle pveh,nveh;
				GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
				GET_NETWORK_ID_FROM_VEHICLE(pveh,&nveh);
				
				if(network_control(nveh))
					teleport_char(players[i].ped,x,y,z);
				
			}
		}
		print("It's party time!");
		return;
	}
	if(item_selected == 8){
		float x,y,z;
		print("This may take a moment..");
		for(i = 0;i <= player_loop;i++){
			if(DOES_CHAR_EXIST(players[i].ped)){
				Vehicle pveh,nveh;
				GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
				GET_NETWORK_ID_FROM_VEHICLE(pveh,&nveh);
				
				if(network_control(nveh))				
					teleport_char(players[i].ped,-1079.8,-469.7,2.62);
			}
		}
		print("Derby time!");
		return;
	}
}

void np_NetworkOptionsAction(uint index){
	if(item_selected == 4){
		int tmp = players[index].id;
		do_toggle(players[tmp].juggernaut);
		return;
	}
	if(item_selected == 5){
		int tmp = players[index].id;
		do_toggle(players[tmp].forcefield);
		return;
	}
	if(item_selected == 6){
		if(DOES_CHAR_EXIST(players[index].ped)){
			float x,y,z;
			if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
				Vehicle pveh,nveh;
				GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
				GET_NETWORK_ID_FROM_VEHICLE(pveh,&nveh);
				
				if(network_control(nveh)){
					SET_CAR_CAN_BE_DAMAGED(pveh,true);
					SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
					SET_CAN_BURST_CAR_TYRES(pveh,true);					
					MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
				}
			}
			GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
			create_big_explosion(x,y,z);
			print("That must have whiped them off the map!");
		}
		return;
	}
	if(item_selected == 7){ 
		if(DOES_CHAR_EXIST(players[index].ped)){
			START_CHAR_FIRE(players[index].ped);
			print("Smells like a poptart.");
			return;
		}
	}
	if(item_selected == 8){
		if(DOES_CHAR_EXIST(players[index].ped)){
			if(GET_HOST_ID() != GET_PLAYER_ID()){
				if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
					float x,y,z;
					GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
					ADD_EXPLOSION(x,y,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
					ADD_EXPLOSION(x + 2.0,y,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
					ADD_EXPLOSION(x,y + 2.0,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
					ADD_EXPLOSION(x - 2.0,y,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
					ADD_EXPLOSION(x,y - 2.0,z,EXPLOSION_DIR_WATER_HYDRANT,5.0,false,true,0.0);
					print("zZzZz!");
				}
				else print("Player not on foot");
			}
			else print("This will freeze you! Join a new game");
		}
		return;
	}
	if(item_selected == 9){
		if(DOES_CHAR_EXIST(players[index].ped)){
			Object otmp;
			CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
							
			ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0,0.0,0.0,-0.11,0.0,0.0,3.0,false);
			WAIT(10);
		}
		print("Hungry Hungry Hippo!");
		return;
	}
	if(item_selected == 10){
		if(DOES_CHAR_EXIST(players[index].ped)){
			uint cubes[6],rand;
			Object otmp;
			cubes[0] = 0x2718C626;
			cubes[1] = 0xDD28B247;
			cubes[2] = 0xCCEA11CA;
			cubes[3] = 0xBB1F6E71;
			cubes[4] = 0xA6E545FD;
			cubes[5] = 0x5C5030D4;
			GENERATE_RANDOM_INT_IN_RANGE(0,5,&rand);
			
			CREATE_OBJECT(cubes[rand],0.0,0.0,0.0,&otmp,true);
							
			ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0x4B5,0.0,0.0,0.0,0.0,0.0,3.0,false);
			WAIT(10);
		}
		print("Boxes don't go on player's heads!");
		return;
	}
	if(item_selected == 11){
		if(DOES_CHAR_EXIST(players[index].ped)){
				
			REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
			
			
			if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
				Vehicle pveh,nveh;
				GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
				GET_NETWORK_ID_FROM_VEHICLE(pveh,&nveh);
				
				if(network_control(nveh)){
					teleport_char(players[index].ped,-1079.8,-469.7,2.62);
					WAIT(100);
					DELETE_CAR(&pveh);
					MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					print("Should have behaved...");
				}
				else error("Network Control");
			}
			else print("Player not in vehicle");
			return;
			
		}
	}
	if(item_selected == 12){
		if(DOES_CHAR_EXIST(players[index].ped)){
			if(GET_PLAYER_ID() == GET_HOST_ID())
				NETWORK_KICK_PLAYER(players[index].id,true);
			else error("You are not host");		
		}
		return;
	}
}

void np_NetworkWeaponAction(uint index){
	if(DOES_CHAR_EXIST(players[index].ped)){
		if(item_selected == 1){
			REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
			WAIT(10);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_DEAGLE,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_GRENADE,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MP5,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_M4,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BARETTA,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BASEBALLBAT,1,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_ARMOUR,1,false);
			ADD_ARMOUR_TO_CHAR(players[index].ped,99);
			print("Player is now armed");
		}
		else if(item_selected == 2){
			REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
			WAIT(10);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_PISTOL,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MOLOTOV,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MICRO_UZI,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_AK47,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_SHOTGUN,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_M40A1,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BASEBALLBAT,1,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_ARMOUR,1,false);
			ADD_ARMOUR_TO_CHAR(players[index].ped,99);
			print("Player is now armed");
		}
		else if(item_selected == 3){
			REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
			WAIT(10);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_9,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_10,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_13,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_14,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_15,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_1,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_16,AMMO_MAX,false);
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BASEBALLBAT,1,false);	
			GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_ARMOUR,1,false);
			ADD_ARMOUR_TO_CHAR(players[index].ped,99);
			print("Player is now armed");
		}
		else if(item_selected == 4){
			REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
			print("Player is now unarmed");	
		}
	}
	else error("Char doesn't exist!");
}

void np_NetworkTeleportAction(uint index){
	if(DOES_CHAR_EXIST(players[index].ped)){
		Vector3 Pos;
		if(item_selected == 1){
			GET_CHAR_COORDINATES(players[index].ped,&Pos.x,&Pos.y,&Pos.z);
			teleport_char(pPlayer,Pos.x,Pos.y,Pos.z);
		}
		else if(item_selected == 2){
			if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
				Vehicle pveh;
				uint i;
				Ped tmp;
				GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
				for(i = 0;i <= 2;i++){
					if(IS_CAR_PASSENGER_SEAT_FREE(pveh,i)){
						WARP_CHAR_INTO_CAR_AS_PASSENGER(pPlayer,pveh,i);
						return;
					}
				}
				error("No free seats");
				return;
			}
			else error("Player not in vehicle");
		}
		else if(item_selected == 3){
			Vehicle pveh,nveh;
			GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
			GET_NETWORK_ID_FROM_VEHICLE(pveh,&nveh);
				
			if(network_control(nveh)){
				GET_CHAR_COORDINATES(pPlayer,&Pos.x,&Pos.y,&Pos.z);
				teleport_char(players[index].ped,Pos.x,Pos.y,Pos.z);
			}
			else error("Network Control");
		}
	}
	else error("Char doesn't exist!");
}

void np_NetworkVehicleAction(uint index){
	if(DOES_CHAR_EXIST(players[index].ped)){
		if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
			Vehicle pveh,nveh;
			GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
			GET_NETWORK_ID_FROM_VEHICLE(pveh,&nveh);
			if(item_selected == 1){
				if(network_control(nveh)){
					DELETE_CAR(&pveh);
					print("Where'd it go!?");
				}
				else error("Network Control");
			}
			else if(item_selected == 2){
				if(network_control(nveh)){
					APPLY_FORCE_TO_CAR(pveh,true,0.0,0.0,1000.0,0.0,0.0,0.0,true,true,true,true);
					print("Think they can hold their lunch?");
				}
				else error("Network Control");
			}
			else if(item_selected == 3){
				if(network_control(nveh)){
					SET_CAR_CAN_BE_DAMAGED(pveh,true);
					SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
					SET_CAN_BURST_CAR_TYRES(pveh,true);
					BURST_CAR_TYRE(pveh,0);
					BURST_CAR_TYRE(pveh,1);
					BURST_CAR_TYRE(pveh,4);
					BURST_CAR_TYRE(pveh,5);
					SET_ENGINE_HEALTH(pveh,0.0);
					print("Vehicle's tires and engine have been destroyed");
				}
				else error("Network Control");
			}
			else if(item_selected == 4)
				ATTACH_PED_TO_CAR(pPlayer,pveh,0,0.00,0.00,1.5,0.00,0.00,1,1);
				
			MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
			//MARK_CAR_AS_NO_LONGER_NEEDED(&nveh);
		}
		else error("Player not in vehicle");
	}
	else error("Char doesn't exist!");
}

void np_networkLoop(void){
	int i;
	uint armor;
	float x,y,z;
	Ped tmp;
	for(i = 0;i <= 15;i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)){
			players[i].juggernaut = false;
			players[i].forcefield = false;
			continue;
		}
		GET_PLAYER_CHAR(i,&tmp);
		if(DOES_CHAR_EXIST(tmp)){
			if(players[i].juggernaut){
				GET_CHAR_ARMOUR(tmp,&armor);
				if(armor < 99){
					GIVE_WEAPON_TO_CHAR(tmp,WEAPON_ARMOUR,1,false);
					ADD_ARMOUR_TO_CHAR(tmp,99);
				}
			}
			if(players[i].forcefield){
				GET_CHAR_COORDINATES(tmp,&x,&y,&z);
				ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,10.0,false,true,0.0);
			}
		}
	}
	return;
}