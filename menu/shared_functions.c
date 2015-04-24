#pragma once
void error(char* message){
	menu_clean();
	inError = true;
	actionError = true;
	menu_header = "Error";
	menu_addItem(message,false);
	menu_addItem("Press ~PAD_B~ to return",false);
}

bool network_control(int netid){
	uint tick = 0;
	REQUEST_CONTROL_OF_NETWORK_ID(netid);
	do{
		tick++;
		REQUEST_CONTROL_OF_NETWORK_ID(netid);
		if(HAS_CONTROL_OF_NETWORK_ID(netid))
			return true;
		else 
			WAIT(0);
	} while(tick < 50);
	return false;
}

void teleport_char(Ped ped,float x,float y,float z){
	if(DOES_CHAR_EXIST(ped)){
		if(IS_CHAR_IN_ANY_CAR(ped)){
			Vehicle netid,vehid;
			GET_CAR_CHAR_IS_USING(ped,&vehid);
			SET_CAR_COORDINATES(vehid,x,y,z);
			return;
		}
		SET_CHAR_COORDINATES(ped,x,y,z);
	}
	return;
}
void create_big_explosion(float fX,float fY,float fZ){
	ADD_EXPLOSION(fX,fY,fZ + 12.5,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 20.0,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 40.0,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX,fY + 20.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY + 30.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 20.0,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 40.0,fY,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX,fY + 20.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY - 40.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 12.5,fY + 12.5,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX + 25.0,fY + 25.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 12.5,fY - 12.5,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 25.0,fY - 25.0,fZ,EXPLOSION_SHIP_DESTROY,10.0f,true,false,0.7f);

}

void spawn_car(uint model){
	int pveh,driver;
	float x,y,z,h,s;
	bool speed = false;
	
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)) 
		WAIT(0);
	
	GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
	GET_CHAR_HEADING(pPlayer,&h);
	
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		GET_CAR_SPEED(pveh,&s);
		speed = true;
		GET_DRIVER_OF_CAR(pveh,&driver);
		WARP_CHAR_FROM_CAR_TO_COORD(pPlayer,x,y,z);
		if(!DOES_CHAR_EXIST(driver) || pPlayer == driver || !network){
			DELETE_CAR(&pveh);
			MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
		}
	}
	
	CREATE_CAR(model,x,y,z,&pveh,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
	SET_CAR_ENGINE_ON(pveh,true,true);
	WARP_CHAR_INTO_CAR(pPlayer,pveh);
	SET_CAR_HEADING(pveh,h);
	
	if(speed)
		SET_CAR_FORWARD_SPEED(pveh,s);
	return;
}

void spawn_stealable_object(uint model){
	Object obj = -1;
	float fX,fY,fZ;
	GET_CHAR_COORDINATES(pPlayer,&fX,&fY,&fZ);
	CREATE_OBJECT(model,fX,fY,fZ,&obj,true);
	SET_OBJECT_QUATERNION(obj,0,0,0,0);
	SET_OBJECT_INVINCIBLE(obj,false);
	FREEZE_OBJECT_POSITION(obj,false);
	SET_OBJECT_DYNAMIC(obj,true);
	SET_OBJECT_AS_STEALABLE(obj,true);
	SET_OBJECT_COLLISION(obj,true);
}