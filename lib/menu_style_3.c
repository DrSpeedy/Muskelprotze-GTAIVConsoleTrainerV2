/**
 * This file is from Three-Socks Menu Library https://bitbucket.org/ThreeSocks/gtaiv-menu-library
 *
 * GTAIV Menu Library
 *
 * @package menu
 * @author Three-Socks http://psx-scene.com/forums/members/three-socks/
 * @license LICENSE.txt DON'T BE A DICK PUBLIC LICENSE (DBAD)
 *
 * @version 1.2.1
 */

#pragma once

/*

Style: 5

Name: Three-Socks Trainer (edited)

Desc: Mimics GTA Frontend.

Edits:
- Switched to font "0" to allow underscores.
- Added SET_TEXT_USE_UNDERSCORE
- Added "2" to the custom_float_dp section in menu_draw (it only had 1 and 3)
- Adusted menu to the right
*/

void style_setup(void)
{
	// Start y positioning.
	menu_start_y = 0.2000;
	// Spacing between each item.
	menu_spacing = 0.0400;
	// Max number of items before scrolling.
	menu_max = 14;
	// When to start scrolling.
	menu_start_scrolling = 8;
}

void draw_startup(void)
{
	SET_CINEMATIC_BUTTON_ENABLED(false);

	if (!IS_FONT_LOADED(6))
		LOAD_TEXT_FONT(6);

	// Mimic cell phone.
	WAIT(500);

	if	(IS_NETWORK_SESSION())
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mpcellphone");
	else
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("spcellphone");
	
	CREATE_MOBILE_PHONE(2);
	
	//DISABLE_FRONTEND_RADIO();

	BLOCK_PED_WEAPON_SWITCHING(GetPlayerPed(), true);

	SET_PLAYER_CAN_DO_DRIVE_BY(GetPlayerIndex(), false);
	
	REQUEST_STREAMED_TXD("network", 0);
	while (!HAS_STREAMED_TXD_LOADED("network"))
		WAIT(0);

	arrow_txd = GET_TEXTURE_FROM_STREAMED_TXD("network", "ICON_W_ARROW_UP");
	rightarrow_txd = GET_TEXTURE_FROM_STREAMED_TXD("network", "ICON_W_ARROW_RIGHT");

	PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_READY");
}

void draw_shutdown(void)
{
	RELEASE_TEXTURE(arrow_txd);
	RELEASE_TEXTURE(rightarrow_txd);
	MARK_STREAMED_TXD_AS_NO_LONGER_NEEDED("network");

	//ENABLE_FRONTEND_RADIO();

	BLOCK_PED_WEAPON_SWITCHING(GetPlayerPed(), false);

	SET_PLAYER_CAN_DO_DRIVE_BY(GetPlayerIndex(), true);

	SET_CINEMATIC_BUTTON_ENABLED(true);

	DESTROY_MOBILE_PHONE();
	if	(IS_NETWORK_SESSION())
	{
		REQUEST_SCRIPT("mpcellphone");
			while(!HAS_SCRIPT_LOADED("mpcellphone")) WAIT(0);
		START_NEW_SCRIPT("mpcellphone",1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("mpcellphone");
	}
	else
	{
		REQUEST_SCRIPT("spcellphone");
			while(!HAS_SCRIPT_LOADED("spcellphone")) WAIT(0);
		START_NEW_SCRIPT("spcellphone",1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("spcellphone");				
	}
	
	PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_UNREADY");
}

void set_up_draw(int font, float width, float height, uint r, uint g, uint b, uint a)
{
	font = 6; //The lazy man's fix :P
	SET_TEXT_FONT(font);

	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(0, 0, 0, 0, 255);

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_PROPORTIONAL(1);

	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(0);
	SET_TEXT_RIGHT_JUSTIFY(0);
	SET_TEXT_USE_UNDERSCORE(1);
}

void set_up_draw2(int font, int type, float width, float height, uint r, uint g, uint b, uint a)
{
	font = 6;
	SET_TEXT_FONT(font);
		
	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(0, 0, 0, 0, 255);

	if (type == 1)
		SET_TEXT_BACKGROUND(1);
	else if (type == 2)
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 255);
	else if (type == 3)
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
	
	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(0.30000000, 0.30000000);
	SET_TEXT_PROPORTIONAL(1);

	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(0);
	SET_TEXT_RIGHT_JUSTIFY(0);
	SET_TEXT_USE_UNDERSCORE(1);
}

void drawHeader()
{
	float x, y, x2, y2;

	//if (GET_IS_HIDEF())
	//{
		x = 0.6603;
		y = 0.2070 - 0.0120;
	/*}
	else
	{
		x = 0.0303;
		y = 0.116 - 0.0120;
	}*/

	set_up_draw(0, 0.3500, 0.4775, 255, 255, 255, 255);
	DISPLAY_TEXT_WITH_LITERAL_STRING(0.7326, 0.1820, "STRING", menu_header);
	DRAW_RECT(x + (0.35 * 0.50000000), (y + -0.00370000) + 0.03450000, (0.2250 - 0.01000000) - 0.01000000, 0.00300000, 255, 255, 255, 255);
}

void drawWindow(void)
{
	float x, y, x2, y2;

	HIDE_HELP_TEXT_THIS_FRAME();

	x = 0.7200;
	y = 0.1750 - 0.0120;

	if (menu_len > menu_consts_max)
		y2 = 0.09 + (menu_consts_max * 0.04);
	else
		y2 = 0.09 + (menu_len * 0.04);

	DRAW_CURVED_WINDOW(x, y, 0.2300, y2, 245);
}

void drawFrontend(void)
{
	INIT_FRONTEND_HELPER_TEXT();

	if (menu_level == 1)
		DRAW_FRONTEND_HELPER_TEXT("LEAVE", "INPUT_F_CANCEL", 0);
	else
		DRAW_FRONTEND_HELPER_TEXT("BACK", "INPUT_F_CANCEL", 0);
	
	if (menu_item[item_highlighted].action)
		DRAW_FRONTEND_HELPER_TEXT("CONFIRM", "INPUT_F_ACCEPT", 0);
	else
		DRAW_FRONTEND_HELPER_TEXT("KYB_ENTER", "INPUT_F_ACCEPT", 0);

	if (menu_item[item_highlighted].type == 1 || menu_item[item_highlighted].type == 2)
		DRAW_FRONTEND_HELPER_TEXT("SCROLL", "PAD_DPAD_LR", 0);
}

// Draws the menu.
void menu_draw(void)
{
	uint d_r = 137, d_g = 137, d_b = 137;
	uint h_r, h_g, h_b;
	
	//if (GET_CURRENT_EPISODE() == 0)
	//{
		h_r = 220;
		h_g = 20;
		h_b = 60;
	/*}
	else if (GET_CURRENT_EPISODE() == 1)
	{
		h_r = 118;
		h_g = 14;
		h_b = 16;
	}
	else if (GET_CURRENT_EPISODE() == 2)
	{
		h_r = 194;
		h_g = 55;
		h_b = 137;
	}
	*/
	float pos_x = 0.7326, 

	toggle_pos_x = 0.9150,

	menu_width = 0.3100, menu_height = 0.4550;

	uint r, g, b, a = 255;
	int I;
	float Ipos_y = menu_start_y;

	for (I = 1; I <= menu_len; I++)
	{
		Ipos_y = Ipos_y + menu_spacing;
		if (I <= menu_max && Ipos_y > (menu_consts_start_y + 0.0100))
		{
			if(menu_item[I].type == 7){
				GET_PLAYER_RGB_COLOUR(players[(I - 2)].id,&r,&g,&b);
			}
			else{
				r = d_r;
				g = d_g;
				b = d_b;
			}
			if (item_highlighted == I && !inError)
			{
				r =  h_r;
				g =  h_g;
				b =  h_b;
			}

			set_up_draw(0, menu_width, menu_height, r, g, b, a);
			
			if (menu_item[I].type == 5)
				DISPLAY_TEXT_WITH_LITERAL_STRING(pos_x, Ipos_y, "STRING", GET_STRING_FROM_TEXT_FILE(GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(menu_item[I].num_val)));
			else
				DISPLAY_TEXT_WITH_LITERAL_STRING(pos_x, Ipos_y, "STRING", menu_item[I].name);

			if (menu_item[I].type == 1 || menu_item[I].type == 2)
			{
				float left_pos_x, main_pos_x;
				uint dp;

				if (menu_item[I].type == 2)
				{
					if (custom_float_dp != 0)
						dp = custom_float_dp;
					else
						dp = 1;

					if (dp == 1)
					{
						if (menu_item[I].float_val >= 10.0)
						{
							left_pos_x = 0.8760;
							main_pos_x = 0.8870;
						}
						else if (menu_item[I].float_val < 10.0)
						{
							left_pos_x = 0.8870;
							main_pos_x = 0.8970;
						}
					}
					else if (dp == 2)
					{
						left_pos_x = 0.8660;
						main_pos_x = 0.8770;
					}
					else if (dp == 3)
					{
						left_pos_x = 0.8560;
						main_pos_x = 0.8670;
					}
				}
				else
				{
					if (menu_item[I].num_val < 10)
					{
						left_pos_x = 0.9030;
						main_pos_x = 0.9130;
					}

					if (menu_item[I].num_val >= 10)
					{
						left_pos_x = 0.8930;
						main_pos_x = 0.9020;
					}

					if (menu_item[I].num_val >= 100)
					{
						left_pos_x = 0.8770;
						main_pos_x = 0.8880;
					}

					if (menu_item[I].num_val >= 1000)
					{
						left_pos_x = 0.8700;
						main_pos_x = 0.8800;
					}
				}

				DRAW_SPRITE(rightarrow_txd, left_pos_x, Ipos_y + 0.0150, 0.0160, 0.0160, 180.0000, r, g, b, a);
				set_up_draw(0, menu_width, menu_height, r, g, b, a);
				if (menu_item[I].type == 1)
					DISPLAY_TEXT_WITH_NUMBER(main_pos_x, Ipos_y, "NUMBR", menu_item[I].num_val);
				else if (menu_item[I].type == 2)
					DISPLAY_TEXT_WITH_FLOAT(main_pos_x, Ipos_y, "NUMBR", menu_item[I].float_val, dp);
				DRAW_SPRITE(rightarrow_txd, 0.9350, Ipos_y + 0.0150, 0.0160, 0.0160, 0.0000, r, g, b, a);
			}
			else if (menu_item[I].type == 3)
			{
				if (menu_item[I].extra_val)
				{
					set_up_draw(0, menu_width, menu_height, h_r, h_g, h_b, a);
					char *txt_on;
					if (!IS_STRING_NULL(custom_bool_on))
					{
						toggle_pos_x = 0.8650;
						txt_on = custom_bool_on;
					}
					else
						txt_on = menu_on;
					DISPLAY_TEXT_WITH_LITERAL_STRING(toggle_pos_x, Ipos_y, "STRING", txt_on);
				}
				else
				{
					set_up_draw(0, menu_width, menu_height, d_r, d_g, d_b, a);
					char *txt_off;
					if (!IS_STRING_NULL(custom_bool_off))
					{
						toggle_pos_x = 0.8650;
						txt_off = custom_bool_off;
					}
					else
						txt_off = menu_off;
					DISPLAY_TEXT_WITH_LITERAL_STRING(toggle_pos_x, Ipos_y, "STRING", txt_off);
				}
			}
			else if (menu_item[I].type == 6)
			{
				set_up_draw(0, menu_width, menu_height, r, g, b, a);
				DISPLAY_TEXT_WITH_LITERAL_STRING(pos_x, Ipos_y, "STRING", GET_STRING_FROM_HASH_KEY(menu_item[I].num_val));
			}
			/*else if(menu_item[I].type == 7){ //Colored star in the network players - Muskelprotze
				GET_PLAYER_RGB_COLOUR(players[(I - 2)].id,&n_r,&n_g,&n_b);
				
				set_up_draw(0, menu_width, menu_height, n_r, n_g, n_b, a);
				DISPLAY_TEXT_WITH_LITERAL_STRING(0.9100, Ipos_y, "STRING", "*");
			}*/
			/*else if (menu_item[I].type == 8)
			{
				float x, y, z, h, game_cam_x, game_cam_y, game_cam_z, game_cam_rx, game_cam_ry, game_cam_rz;
				Vehicle p_veh;
				Camera game_cam;
				GET_GAME_CAM(&game_cam);
				GET_CAM_POS(game_cam, &game_cam_x, &game_cam_y, &game_cam_z);
				GET_CAM_ROT(game_cam, &game_cam_rx, &game_cam_ry, &game_cam_rz);
				if (menu_item[I].num_val == 1) // X
				{
					if	(IS_CHAR_IN_ANY_CAR(GetPlayerPed())) 
					{
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &p_veh);
						GET_CAR_COORDINATES(p_veh, &x, &y, &z);
					}
					else
						GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);

					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", x, 4);
				}
				else if (menu_item[I].num_val == 2) // Y
				{
					if	(IS_CHAR_IN_ANY_CAR(GetPlayerPed())) 
					{
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &p_veh);
						GET_CAR_COORDINATES(p_veh, &x, &y, &z);
					}
					else
						GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);

					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", y, 4);
				}
				else if (menu_item[I].num_val == 3) // Z
				{
					if	(IS_CHAR_IN_ANY_CAR(GetPlayerPed())) 
					{
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &p_veh);
						GET_CAR_COORDINATES(p_veh, &x, &y, &z);
					}
					else
						GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);

					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", z, 4);
				}
				else if (menu_item[I].num_val == 4) // H
				{
					if	(IS_CHAR_IN_ANY_CAR(GetPlayerPed())) 
					{
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &p_veh);
						GET_CAR_HEADING(p_veh, &h);
					}
					else
						GET_CHAR_HEADING(GetPlayerPed(), &h);

					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", h, 4);
				}
				else if (menu_item[I].num_val == 5) // Camera X
				{
					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", game_cam_x, 4);
				}
				else if (menu_item[I].num_val == 6) // Camera Y
				{
					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", game_cam_y, 4);
				}
				else if (menu_item[I].num_val == 7) // Camera Z
				{
					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", game_cam_z, 4);
				}
				else if (menu_item[I].num_val == 8) // Camera Rotate X
				{
					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", game_cam_rx, 4);
				}
				else if (menu_item[I].num_val == 9) // Camera Rotate Y
				{
					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", game_cam_ry, 4);
				}
				else if (menu_item[I].num_val == 10) // Camera Rotate Z
				{
					set_up_draw(0, menu_width, menu_height, 255, 255, 255, 255);
					DISPLAY_TEXT_WITH_FLOAT(0.8550, Ipos_y, "NUMBR", game_cam_rz, 4);
				}
			}*/
		}
	}

	if (menu_len > menu_consts_max && item_highlighted > menu_start_scrolling)
		DRAW_SPRITE(arrow_txd, 0.8400, 0.2370, 0.0160, 0.0160, 0, 255, 255, 255, 255);

	if (menu_len > menu_consts_max)
		DRAW_SPRITE(arrow_txd, 0.8400, 0.8000, 0.0160, 0.0160, 180.0000, 255, 255, 255, 255);
}