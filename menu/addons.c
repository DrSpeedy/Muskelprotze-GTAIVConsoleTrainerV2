#pragma once

#define MAX_ADDONS 10

struct Vector2{
	char* name;
	char* script;
} addons[12];

void addon_Setup(void){
	uint i;
	bool streaming;
	addons[0].name = "The Stash";
	addons[0].script = "m_modmenu";
	
	addons[1].name = "Weapon Mods";
	addons[1].script = "weapons";
	
	addons[2].name = "Debug Box";
	addons[2].script = "DebugBox";
	
	for(i = 0;i <= MAX_ADDONS;i++){
		if(!IS_STRING_NULL(addons[i].name) && !IS_STRING_NULL(addons[i].script)){
			streaming = false;
			if(GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(addons[i].script) == 1)
				streaming = true;
				
			menu_addItemBool(addons[i].name,streaming);
		}
	}
	return;
}

void addon_Action(void){
	uint index = item_selected - 1;

	if(GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(addons[index].script) == 1){
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(addons[index].script);
		menu_items_set = false;
		menu_clean();
	}
	else{
		REQUEST_SCRIPT(addons[index].script);
		while(!HAS_SCRIPT_LOADED(addons[index].script))
			WAIT(0);
			
		START_NEW_SCRIPT(addons[index].script,1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED(addons[index].script);
		
		menu_items_set = false;
		menu_clean();
	}
	return;
}