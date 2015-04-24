#pragma once

void tele_Setup(void){
	menu_header = "Teleports";
	
	menu_addItem("Waypoint",true);
	menu_addItem("Airport Helipads",true);
	menu_addItem("Hove Beach",true);
	menu_addItem("Majestic Hotel",true);
	menu_addItem("Skydive",true);
	menu_addItem("Middle Park",true);
	menu_addItem("Playboy X's Pad",true);
	menu_addItem("Rotterdam Tower",true);
	menu_addItem("Prison Cage",true);
	menu_addItem("Crack House",true);
	menu_addItem("Westminster Towers",true);
	menu_addItem("Parking Garage",true);
	menu_addItem("Algonquin Safe House",true);
	menu_addItem("Scrapyard",true);
	menu_addItem("Construction Site",true);
	menu_addItem("Subway",true);
	menu_addItem("Sprunk Factory",true);
	return;
}

void tele_Action(void){

	if(item_selected == 1){
		if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
			Vector3 pos;
			float z;
			GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&pos);
			teleport_char(pPlayer,pos.x,pos.y,0.0);
					
			GET_GROUND_Z_FOR_3D_COORD(pos.x,pos.y,1000,&z);
			WAIT(100);
			teleport_char(pPlayer,pos.x,pos.y,z);
		}
		else print("You need to set a waypoint!");			
	}
	else if(item_selected == 2)
		teleport_char(pPlayer,2175.3516,761.2235,30.0);

	else if(item_selected == 3)
		teleport_char(pPlayer,1100.5,-747.0,7.39);

	else if(item_selected == 4)
		teleport_char(pPlayer,-178.2,582.6,126.85);

	else if(item_selected == 5)
		teleport_char(pPlayer,-2476.0,942.7,1100.0);

	else if(item_selected == 6)
		teleport_char(pPlayer,-236.0,795.9,6.20);

	else if(item_selected == 7)
		teleport_char(pPlayer,-415.17,1463.54,39.0);

	else if(item_selected == 8)
		teleport_char(pPlayer,-279.77,-99.66,386.791);

	else if(item_selected == 9)
		teleport_char(pPlayer,-1079.8,-469.7,2.62);

	else if(item_selected == 10)
		teleport_char(pPlayer,1375.8765,197.4544,48.0);
			
	else if(item_selected == 11)
		teleport_char(pPlayer,-532.681,1273.3307,105.65);

	else if(item_selected == 12)
		teleport_char(pPlayer,55.3537,1125.3387,2.4527);
		
	else if(item_selected == 13)
		teleport_char(pPlayer,104.13,856.53,45.58);
		
	else if(item_selected == 14)
		teleport_char(pPlayer,-473.0176,1746.8829,6.26);
	
	else if(item_selected == 15)
		teleport_char(pPlayer,237.5457,-805.6555,13.7);

	else if(item_selected == 16)
		teleport_char(pPlayer,-3.4734,270.6067,-2.9470);

	else if(item_selected == 17)
		teleport_char(pPlayer,-1539.8414,163.2967,9.9000);
	
	return;
}