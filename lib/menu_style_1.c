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

Style: 1

Name: Three-Socks Trainer.

Desc: Mimics GTA Frontend.

*/

void style_setup(void)
{
	// Start y positioning.
	menu_start_y = 0.0890;
	// Spacing between each item.
	menu_spacing = 0.0400;
	// Max number of items before scrolling.
	menu_max = 14;
	// When to start scrolling.
	menu_start_scrolling = 7;
}

void draw_startup(void)
{
	SET_CINEMATIC_BUTTON_ENABLED(false);

	#ifdef PC
	if (!IS_FONT_LOADED(7))
		LOAD_TEXT_FONT(7);
	#else
	if (!IS_FONT_LOADED(6))
		LOAD_TEXT_FONT(6);
	#endif

	// Mimic cell phone.
	WAIT(500);
	//CREATE_MOBILE_PHONE(0);
	
	DISABLE_FRONTEND_RADIO();

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

	ENABLE_FRONTEND_RADIO();

	BLOCK_PED_WEAPON_SWITCHING(GetPlayerPed(), false);

	SET_PLAYER_CAN_DO_DRIVE_BY(GetPlayerIndex(), true);

	SET_CINEMATIC_BUTTON_ENABLED(true);

	//DESTROY_MOBILE_PHONE();
	//SCRIPT_IS_USING_MOBILE_PHONE(false);

	PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_UNREADY");
}

void set_up_draw(float width, float height, uint r, uint g, uint b, uint a)
{
#ifdef PC
	SET_TEXT_FONT(7);
#else
	SET_TEXT_FONT(6);
#endif
	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(0, 0, 0, 0, 255);

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_PROPORTIONAL(1);

	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(0);
	SET_TEXT_RIGHT_JUSTIFY(0);

}

void drawHeader()
{
	float x, y, x2, y2;

	//if (GET_IS_HIDEF())
	//{
		x = 0.0103;
		y = 0.0960 - 0.0120;
	/*}
	else
	{
		x = 0.0303;
		y = 0.116 - 0.0120;
	}*/

	set_up_draw(0.3500, 0.4775, 255, 255, 255, 255);
	DISPLAY_TEXT_WITH_LITERAL_STRING(0.0826, 0.0710, "STRING", menu_header);
	DRAW_RECT(x + (0.35 * 0.50000000), (y + -0.00370000) + 0.03450000, (0.2250 - 0.01000000) - 0.01000000, 0.00300000, 255, 255, 255, 255);
}

void drawWindow(void)
{
	float x, y, x2, y2;

	HIDE_HELP_TEXT_THIS_FRAME();

	x = 0.0700;
	y = 0.0640 - 0.0120;

	if (menu_len > menu_consts_max)
		y2 = 0.09 + (menu_consts_max * 0.04);
	else
		y2 = 0.09 + (menu_len * 0.04);

	DRAW_CURVED_WINDOW(x, y, 0.2300, y2, 255);
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
	uint d_r = 137, d_g = 137, d_b = 137, 
	h_r = 251, h_g = 162, h_b = 6;
	//h_r = 206, h_g = 160, h_b = 22;

	float pos_x = 0.0826, 

	toggle_pos_x = 0.2500, 

	menu_width = 0.3100, menu_height = 0.4550;

	uint r, g, b, a = 255;
	int I;
	float Ipos_y = menu_start_y;

	for (I = 1; I <= menu_len; I++)
	{
		Ipos_y = Ipos_y + menu_spacing;
		if (I <= menu_max && Ipos_y > (menu_consts_start_y + 0.0100))
		{
			r = d_r;
			g = d_g;
			b = d_b;

			if (item_highlighted == I && !inError)
			{
				r =  h_r;
				g =  h_g;
				b =  h_b;
			}

			set_up_draw(menu_width, menu_height, r, g, b, a);

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
							left_pos_x = 0.2260;
							main_pos_x = 0.2370;
						}
						else if (menu_item[I].float_val < 10.0)
						{
							left_pos_x = 0.2370;
							main_pos_x = 0.2470;
						}
					}
					else if (dp == 3)
					{
						left_pos_x = 0.2060;
						main_pos_x = 0.2170;
					}
				}
				else
				{
					if (menu_item[I].num_val < 10)
					{
						left_pos_x = 0.2530;
						main_pos_x = 0.2630;
					}

					if (menu_item[I].num_val >= 10)
					{
						left_pos_x = 0.2430;
						main_pos_x = 0.2520;
					}

					if (menu_item[I].num_val >= 100)
					{
						left_pos_x = 0.2270;
						main_pos_x = 0.2380;
					}

					if (menu_item[I].num_val >= 1000)
					{
						left_pos_x = 0.2200;
						main_pos_x = 0.2300;
					}
				}

				DRAW_SPRITE(rightarrow_txd, left_pos_x, Ipos_y + 0.0150, 0.0160, 0.0160, 180.0000, r, g, b, a);
				set_up_draw(menu_width, menu_height, r, g, b, a);
				if (menu_item[I].type == 1)
					DISPLAY_TEXT_WITH_NUMBER(main_pos_x, Ipos_y, "NUMBR", menu_item[I].num_val);
				else if (menu_item[I].type == 2)
					DISPLAY_TEXT_WITH_FLOAT(main_pos_x, Ipos_y, "NUMBR", menu_item[I].float_val, dp);
				DRAW_SPRITE(rightarrow_txd, 0.2850, Ipos_y + 0.0150, 0.0160, 0.0160, 0.0000, r, g, b, a);
			}
			else if (menu_item[I].type == 3)
			{
				if (menu_item[I].extra_val)
				{
					set_up_draw(menu_width, menu_height, h_r, h_g, h_b, a);
					char *txt_on;
					if (!IS_STRING_NULL(custom_bool_on))
					{
						toggle_pos_x = 0.2000;
						txt_on = custom_bool_on;
					}
					else
						txt_on = menu_on;
					DISPLAY_TEXT_WITH_LITERAL_STRING(toggle_pos_x, Ipos_y, "STRING", txt_on);
				}
				else
				{
					set_up_draw(menu_width, menu_height, d_r, d_g, d_b, a);
					char *txt_off;
					if (!IS_STRING_NULL(custom_bool_off))
					{
						toggle_pos_x = 0.2000;
						txt_off = custom_bool_off;
					}
					else
						txt_off = menu_off;
					DISPLAY_TEXT_WITH_LITERAL_STRING(toggle_pos_x, Ipos_y, "STRING", txt_off);
				}
			}
		}
	}

	if (menu_len > menu_consts_max && item_highlighted > menu_start_scrolling)
		DRAW_SPRITE(arrow_txd, 0.1900, 0.1260, 0.0160, 0.0160, 0, 255, 255, 255, 255);

	if (menu_len > menu_consts_max)
		DRAW_SPRITE(arrow_txd, 0.1900, 0.6890, 0.0160, 0.0160, 180.0000, 255, 255, 255, 255);
}