#pragma once

bool po_ragdoll = false;
bool po_invincibility = true;
bool po_juggernaut = false;
bool po_brick_wall = false;
bool po_super_run = true;
bool po_super_jump = true;
bool po_forcefield = false;

///================================================
///Display Setup - Muskelprotze
///================================================
void po_MainSetup(void){
	menu_header = "Player Options";
	
	//menu_addItem("Network Players",false);
	menu_addItem("Animations",false);
	menu_addItem("Give Health & Armor",true);
	menu_addItemBool("Invincibility",po_invincibility);
	menu_addItemBool("Juggernaut",po_juggernaut);
	menu_addItemBool("Brick Wall",po_brick_wall);
	menu_addItemBool("Super Run (~PAD_LB~ + ~PAD_A~)",po_super_run);
	menu_addItemBool("Super Jump",po_super_jump);
	menu_addItemBool("Force Field",po_forcefield);
	return;
}

void po_AnimSetup(void){
	menu_addItemNumber("Taichi",1,2);
	menu_addItemNumber("Male Dance",1,4);
	menu_addItemNumber("Female Dance",1,3);
	menu_addItem("Pole Dance",true);
	menu_addItem("Stop Anim",true);
	menu_addItemBool("Ragdoll (~PAD_LB~ + ~PAD_B~)",po_ragdoll);
	return;
}

///================================================
///Function Setup - Muskelprotze
///================================================

void po_MainAction(void){
	if(item_selected == 2){
		SET_CHAR_HEALTH(pPlayer,500);
		ADD_ARMOUR_TO_CHAR(pPlayer,99);
		return;
	}
	if(item_selected == 3){
		if(po_juggernaut)
			po_juggernaut = false;
		do_toggle(po_invincibility);
		return;
	}
	if(item_selected == 4){
		if(po_invincibility)
			po_invincibility = false;
		do_toggle(po_juggernaut);
		return;
	}
	if(item_selected == 5){
		do_toggle(po_brick_wall);
		FREEZE_CHAR_POSITION(pPlayer,false);
		return;
	}
	if(item_selected == 6){
		do_toggle(po_super_run);
		return;
	}
	if(item_selected == 7){
		do_toggle(po_super_jump);
		return;
	}
	if(item_selected == 8){
		do_toggle(po_forcefield);
		return;
	}
}

void po_AnimAction(void){
	if(item_selected == 1){
		if(menu_item[item_selected].num_val == 1){
			REQUEST_ANIMS("amb@park_taichi_a");
			while(!HAVE_ANIMS_LOADED("amb@park_taichi_a")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"taichi01","amb@park_taichi_a",8.0,0,0);
			return;
		}
		if(menu_item[item_selected].num_val == 2){
			REQUEST_ANIMS("amb@park_taichi_b");
			while(!HAVE_ANIMS_LOADED("amb@park_taichi_b")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"taichi02","amb@park_taichi_b",8.0,0,0);
			return;
		}	
	}
	if(item_selected == 2){
		if(menu_item[item_selected].num_val == 1){
			REQUEST_ANIMS("amb@dance_maleidl_a");
			while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_a")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_a","amb@dance_maleidl_a",8.0,0,0);
			return;
		}
		if(menu_item[item_selected].num_val == 2){
			REQUEST_ANIMS("amb@dance_maleidl_b");
			while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_b")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_maleidl_b",8.0,0,0);
			return;
		}
		if(menu_item[item_selected].num_val == 3){
			REQUEST_ANIMS("amb@dance_maleidl_c");
			while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_c")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_c","amb@dance_maleidl_c",8.0,0,0);
			return;
		}
		if(menu_item[item_selected].num_val == 4){
			REQUEST_ANIMS("amb@dance_maleidl_b");
			while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_b")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_maleidl_b",8.0,0,0);
			return;
		}
	}
	if(item_selected == 3){
		if(menu_item[item_selected].num_val == 1){
			REQUEST_ANIMS("amb@dance_femidl_a");
			while(!HAVE_ANIMS_LOADED("amb@dance_femidl_a")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_a","amb@dance_femidl_a",8.0,0,0);
			return;
		}
		if(menu_item[item_selected].num_val == 2){
			REQUEST_ANIMS("amb@dance_femidl_b");
			while(!HAVE_ANIMS_LOADED("amb@dance_femidl_b")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_femidl_b",8.0,0,0);
			return;
		}
		if(menu_item[item_selected].num_val == 3){
			REQUEST_ANIMS("amb@dance_femidl_c");
			while(!HAVE_ANIMS_LOADED("amb@dance_femidl_c")) WAIT(0);
			TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_c","amb@dance_femidl_c",8.0,0,0);
			return;
		}					
	}
	if(item_selected == 4){
		REQUEST_ANIMS("missstripclublo");
		while(!HAVE_ANIMS_LOADED("missstripclublo")) WAIT(0);
		TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"pole_dance_a","missstripclublo",8.0,0,0);
		return;
	}
	if(item_selected == 5){
		SWITCH_PED_TO_RAGDOLL(pPlayer,20,30,false,false,false,false);
		SWITCH_PED_TO_ANIMATED(pPlayer,true);
		GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),true);
		WAIT(30);
		SWITCH_PED_TO_ANIMATED(pPlayer,false);
		GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),false);
		return;
	}
	if(item_selected == 6){
		do_toggle(po_ragdoll);
		return;
	}	
}

void po_LoopedAction(void){

	if(po_ragdoll){
		if(IS_BUTTON_PRESSED(0,BUTTON_L1) && IS_BUTTON_JUST_PRESSED(0,BUTTON_O)){
			if(!IS_PED_RAGDOLL(pPlayer)){
				SWITCH_PED_TO_RAGDOLL(pPlayer,20000,30000,false,false,false,false);
				SWITCH_PED_TO_ANIMATED(pPlayer,true);
				GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),true);
			}
			else{
				SWITCH_PED_TO_ANIMATED(pPlayer,false);
				GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),false);
			}
		}
	}
	
	SET_CHAR_INVINCIBLE(pPlayer,po_invincibility);
	
	if(po_juggernaut){
		uint armor;
		GET_CHAR_ARMOUR(pPlayer,&armor);
		if(armor < 80)
			ADD_ARMOUR_TO_CHAR(pPlayer,99);
	}
	
	if(po_brick_wall){
		uint pos[4];
		GET_POSITION_OF_ANALOGUE_STICKS(0,&pos[0],&pos[1],&pos[2],&pos[3]);
		if(pos[0] == 0 && pos[1] == 0)
			FREEZE_CHAR_POSITION(pPlayer,true);
		else
			FREEZE_CHAR_POSITION(pPlayer,false);
	}
	
	if(po_super_run){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_L1) && IS_BUTTON_PRESSED(0,BUTTON_X))
				APPLY_FORCE_TO_PED(pPlayer,true,0.0,2.5,-0.05,0.0,0.0,0.0,true,true,true,true);
		}
	}
	
	if(po_super_jump){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_JUST_PRESSED(0,BUTTON_S))
				APPLY_FORCE_TO_PED(pPlayer,true,0.0,1.2,10.0,0.0,0.0,0.0,true,true,true,true);
		}	
	}
	
	if(po_forcefield){
		float x,y,z;
		GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
		ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,10.0,false,true,0.0);
	}	
}