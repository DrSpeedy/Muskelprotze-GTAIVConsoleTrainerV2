#include <natives.h>
#include <consts.h>
#include <types.h>
#include <common.h>

#define MAX_MENU_ITEMS 30
#define MAX_MENU_LEVLS 6
#define STYLE 3

#include "locals.h"

#include "lib/menu.h"

#include "functions.c"
#include "setup.c"

#include "lib/menu_core.c"

void main(void){
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	
	network = IS_NETWORK_SESSION();
	episode = GET_CURRENT_EPISODE();
	SWITCH_RANDOM_BOATS(false);
	if(m_drive_free){
		SWITCH_ROADS_OFF(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
		SWITCH_AMBIENT_PLANES(false);
	}
	else{
		SWITCH_ROADS_ON(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
		SWITCH_AMBIENT_PLANES(true);
	}
	
	WAIT(500);
	
	while(true){
		pPlayer = GetPlayerPed();
		
		project_loopedFunctions();
		
		if(show_menu){
			menu_core();

			drawWindow();
			drawFrontend();
			drawHeader();
			menu_draw();
		}
		else if(IS_BUTTON_PRESSED(0,BUTTON_L1) && IS_BUTTON_JUST_PRESSED(0,BUTTON_DPAD_DOWN)){
			menu_core_startup();
			draw_startup();
		}
		
		WAIT(0);
	}
}