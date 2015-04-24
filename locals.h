#pragma once

uint episode;
bool network;

Ped pPlayer;

typedef struct _online_players{
	//Index
	Ped ped;
	char* gamertag;
	int id;
	bool active;
	
	//ID
	bool juggernaut;
	bool forcefield;
} online_players;

online_players players[16];
int player_count;