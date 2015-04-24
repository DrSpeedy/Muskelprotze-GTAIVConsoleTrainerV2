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

Style: 2

Name: ModManager.

Desc: Only types 0 & 3 supported.

*/

void style_setup(void)
{
	// Start y positioning.
	if (GET_IS_WIDESCREEN())
		menu_start_y = 0.2120 + 0.1300;
	else
		menu_start_y = 0.2180 + 0.1300;
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
	CREATE_MOBILE_PHONE(2);

	DISABLE_FRONTEND_RADIO();

	BLOCK_PED_WEAPON_SWITCHING(GetPlayerPed(), true);

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

	SET_CINEMATIC_BUTTON_ENABLED(true);

	DESTROY_MOBILE_PHONE();

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
	float title_y, title_width, title_height;

	if (GET_IS_WIDESCREEN())
		title_y = 0.2120, title_width = 0.7799, title_height = 1.2000;
	else
		title_y = 0.2180, title_width = 0.6000, title_height = 0.9830;

#ifdef PC
	SET_TEXT_FONT(7);
#else
	SET_TEXT_FONT(6);
#endif

	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(1, 0, 0, 0, 255);
	SET_TEXT_PROPORTIONAL(1);
	SET_TEXT_WRAP(0.0000, 1.0000);	

	SET_TEXT_COLOUR(253, 160, 35, 255);
	SET_TEXT_SCALE(title_width, title_height);
	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(1);
	SET_TEXT_RIGHT_JUSTIFY(0);

	DISPLAY_TEXT_WITH_LITERAL_STRING(0.5000, title_y, "STRING", menu_header);
}

void drawWindow(void)
{
	HIDE_HELP_TEXT_THIS_FRAME();
	DRAW_RECT(0.5000, 0.5000, 1.0000, 1.0000, 0, 0, 0, 167);
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

	float pos_x = 0.2000, 

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

			DISPLAY_TEXT_WITH_LITERAL_STRING(pos_x, Ipos_y, "STRING", menu_item[I].name);

			if (menu_item[I].type == 3)
			{
				if (menu_item[I].extra_val)
				{
					set_up_draw(menu_width, menu_height, h_r, h_g, h_b, a);
					char *txt_on;
					if (!IS_STRING_NULL(custom_bool_on))
						txt_on = custom_bool_on;
					else
						txt_on = menu_on;
					DISPLAY_TEXT_WITH_LITERAL_STRING(pos_x + toggle_pos_x, Ipos_y, "STRING", txt_on);
				}
				else
				{
					set_up_draw(menu_width, menu_height, d_r, d_g, d_b, a);
					char *txt_off;
					if (!IS_STRING_NULL(custom_bool_off))
						txt_off = custom_bool_off;
					else
						txt_off = menu_off;
					DISPLAY_TEXT_WITH_LITERAL_STRING(pos_x + toggle_pos_x, Ipos_y, "STRING", txt_off);
				}
			}
		}
	}

	if (menu_len > menu_consts_max && item_highlighted > menu_start_scrolling)
		DRAW_SPRITE(arrow_txd, 0.1900, 0.1260, 0.0160, 0.0160, 0, 255, 255, 255, 255);

	if (menu_len > menu_consts_max)
		DRAW_SPRITE(arrow_txd, 0.1900, 0.6890, 0.0160, 0.0160, 180.0000, 255, 255, 255, 255);
}