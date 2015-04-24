#pragma once
bool m_drive_free = true;
bool m_chat = true;

bool m_grenade_active = false;

Object m_grenadeObj = -1;



void m_MainSetup(void){
	menu_header = "Misc";

	menu_addItem("Throwable Objects",false);
	menu_addItem("Air Strikes",false);
	menu_addItem("Get Host",true);
	menu_addItemBool("Drive Free",m_drive_free);
	menu_addItemBool("Show Chat",m_chat);
}

void m_ThrowSetup(void){
	menu_header = "Throwable Objects";

	menu_addItem("Pile O' Dildos",true);
	menu_addItem("Gumball Machine",true);
	menu_addItem("Cubes",true);
	menu_addItem("Knives",true);
	menu_addItem("HE Grenades",true);
}

void m_AirSetup(void){
	menu_header = "Air Strikes";
	
	//Airport only
	menu_addItem("Helipads",true);
	menu_addItem("Control Tower",true);
	menu_addItem("Parking Lot",true);
}

void m_MainAction(void){
	if(item_selected == 3)
		print(GET_PLAYER_NAME(GET_HOST_ID()));
	
	if(item_selected == 4){
		do_toggle(m_drive_free);
		if(m_drive_free){
			SWITCH_ROADS_OFF(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
			SWITCH_AMBIENT_PLANES(false);
		}
		else{
			SWITCH_ROADS_ON(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
			SWITCH_AMBIENT_PLANES(true);		
		}
	}
	
	if(item_selected == 5)
		do_toggle(m_chat);
}

void m_ThrowAction(void){
	if(item_selected == 1){
		uint i = 0;
		for(i;i <= 4;i++)
			spawn_stealable_object(0x9976ECC4);
	}
	if(item_selected == 2)
		spawn_stealable_object(0x6066DF1D);
	
	if(item_selected == 3){
		spawn_stealable_object(0x2718C626);
		spawn_stealable_object(0xDD28B247);
		spawn_stealable_object(0xCCEA11CA);
		spawn_stealable_object(0xBB1F6E71);
		spawn_stealable_object(0xA6E545FD);
		spawn_stealable_object(0x5C5030D4);
	}
	if(item_selected == 4){
		uint i = 0;
		for(i;i <= 4;i++)
			spawn_stealable_object(0x9D2A7EF8);
	}
	if(item_selected == 5){
		uint i = 0;
		for(i;i <= 4;i++)
			spawn_stealable_object(0x501811B6);
	}	
}

void m_AirAction(void){
	if(item_selected == 1){
		create_big_explosion(2247.4224,755.9057,5.853);
		WAIT(500);
		create_big_explosion(2231.6912,737.4642,5.853);
		WAIT(500);
		create_big_explosion(2214.0000,718.9000,5.83);                        
	}
	if(item_selected == 2)
		create_big_explosion(2621.6484,445.9162,5.35);
		
	if(item_selected == 3){
		create_big_explosion(2268.2544,519.2332,5.4396);
		WAIT(500);
		create_big_explosion(2228.9453,526.2129,5.4401);
		WAIT(500);
		create_big_explosion(2221.8818,484.9935,5.4562);
		WAIT(500);
		create_big_explosion(2234.6369,456.6962,5.4562);

	}	
}

void m_LoopedAction(void){
	if(m_chat){
		int i = 15;
		uint r,g,b;
		float pos_y = 0.8750;
		for(i;i >= 0;i--){
			if(i < 0) continue; //Anti-freeze check
			if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
			if(!NETWORK_IS_PLAYER_TALKING(i)) continue;
			if(NETWORK_IS_PLAYER_MUTED_BY_ME(i)) continue;
			
			GET_PLAYER_RGB_COLOUR(i,&r,&g,&b);
			
			set_up_draw2(0,3,0.32,0.38,r,g,b,255);
			DISPLAY_TEXT_WITH_LITERAL_STRING(0.20,pos_y,"STRING",GET_PLAYER_NAME(i));
			
			pos_y -= 0.032;
		}
	}
	
	if(m_grenade_active){
		if(!IS_PED_HOLDING_AN_OBJECT(pPlayer)){
			uint tick;
			float x,y,z;
			m_grenade_active = false;
			while(!HAS_OBJECT_COLLIDED_WITH_ANYTHING(m_grenadeObj)){
				tick++;
				if(tick > 100) break; //Just blow it
				WAIT(0);
			}
			GET_OBJECT_COORDINATES(m_grenadeObj,&x,&y,&z);
			ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
			DELETE_OBJECT(&m_grenadeObj);
			MARK_OBJECT_AS_NO_LONGER_NEEDED(&m_grenadeObj);
		}
	}
	
	if(IS_PED_HOLDING_AN_OBJECT(pPlayer)){
		uint tmp_model = GET_MODEL_PED_IS_HOLDING(pPlayer);
		if(tmp_model == 0x501811B6 || tmp_model == 0x1B42315D){//object to be new grenade
			m_grenade_active = true;
			m_grenadeObj = GET_OBJECT_PED_IS_HOLDING(pPlayer);
		}
		else m_grenade_active = false;
	}

}