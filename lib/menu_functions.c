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

void menu_hold_pressed(uint p_id)
{
	uint button1;
	uint button2;

	if (p_id == 1)
	{
		button1 = BUTTON_DPAD_UP;
		button2 = KEY_UP_ARROW;
	}
	else if (p_id == 2)
	{
		button1 = BUTTON_DPAD_DOWN;
		button2 = KEY_DOWN_ARROW;
	}
	else if (p_id == 3)
	{
		button1 = BUTTON_DPAD_LEFT;
		button2 = KEY_LEFT_ARROW;
	}
	else if (p_id == 4)
	{
		button1 = BUTTON_DPAD_RIGHT;
		button2 = KEY_RIGHT_ARROW;
	}

	if (IS_BUTTON_PRESSED(0, button1) || IS_GAME_KEYBOARD_KEY_PRESSED(button2))
	{
		press_id = p_id;
		if (hold_counter > 40)
		{
			press_counter_timesby++;
			hold_counter = 0;
		}

		hold_counter++;
		press_counter++;
		press_counter *= press_counter_timesby;
	}
	else if (press_id == p_id)
	{
		press_counter_timesby = 1;
		hold_counter = 0;
	}
}

bool menu_up_pressed(bool counter)
{
	if ((IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_UP) || IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_UP_ARROW))
	 || (press_counter > 6 && (IS_BUTTON_PRESSED(0, BUTTON_DPAD_UP) || IS_GAME_KEYBOARD_KEY_PRESSED(KEY_UP_ARROW))))
	{
		reset_counter = true;
		return true;
	}
	
	if (counter)
		menu_hold_pressed(1);

	return false;
}

bool menu_down_pressed(bool counter)
{
	if ((IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_DOWN) || IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_DOWN_ARROW))
	 || (press_counter > 6 && (IS_BUTTON_PRESSED(0, BUTTON_DPAD_DOWN) || IS_GAME_KEYBOARD_KEY_PRESSED(KEY_DOWN_ARROW))))
	{
		reset_counter = true;
		return true;
	}

	if (counter)
		menu_hold_pressed(2);

	return false;
}

bool menu_left_pressed(bool counter)
{
	if ((IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_LEFT) || IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_LEFT_ARROW))
	 || (press_counter > 6 && (IS_BUTTON_PRESSED(0, BUTTON_DPAD_LEFT) || IS_GAME_KEYBOARD_KEY_PRESSED(KEY_LEFT_ARROW))))
	{
		reset_counter = true;
		return true;
	}

	if (counter)
		menu_hold_pressed(3);

	return false;
}

bool menu_right_pressed(bool counter)
{
	if ((IS_BUTTON_JUST_PRESSED(0, BUTTON_DPAD_RIGHT) || IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_RIGHT_ARROW))
	 || (press_counter > 6 && (IS_BUTTON_PRESSED(0, BUTTON_DPAD_RIGHT) || IS_GAME_KEYBOARD_KEY_PRESSED(KEY_RIGHT_ARROW))))
	{
		reset_counter = true;
		return true;
	}

	if (counter)
		menu_hold_pressed(4);

	return false;
}

bool menu_forward_pressed(void)
{
	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_X) || IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_ENTER))
		return true;

	return false;
}

bool menu_back_pressed(void)
{
	if (IS_BUTTON_JUST_PRESSED(0, BUTTON_O) || IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_BACKSPACE))
		return true;

	return false;
}

// Adds a menu item.
void menu_addItem(char* item_text, bool has_action) //edited by Muskelprotze
{
	menu_len++;
	menu_item[menu_len].name = item_text;
	menu_item[menu_len].action = has_action;
}

void menu_addItemNumber(char* item_text, uint item_num, uint item_max)
{
	menu_len++;
	menu_item[menu_len].name = item_text;
	menu_item[menu_len].action = true;
	menu_item[menu_len].num_val = item_num;
	menu_item[menu_len].extra_val = item_max;
	menu_item[menu_len].type = 1;
}

void menu_addItemFloat(char* item_text, float item_float, uint item_max)
{
	menu_len++;
	menu_item[menu_len].name = item_text;
	menu_item[menu_len].action = true;
	menu_item[menu_len].float_val = item_float;
	menu_item[menu_len].extra_val = item_max;
	menu_item[menu_len].type = 2;
}

void menu_addItemBool(char* item_text, bool item_bool)
{
	menu_len++;
	menu_item[menu_len].name = item_text;
	menu_item[menu_len].action = true;
	menu_item[menu_len].extra_val = item_bool;
	menu_item[menu_len].type = 3;
}

void menu_addItemHash(char* item_text, uint item_hash)
{
	menu_len++;
	menu_item[menu_len].name = item_text;
	menu_item[menu_len].action = true;
	menu_item[menu_len].num_val = item_hash;
	menu_item[menu_len].type = 4;
}

void menu_addItemGXTHash(uint item_gxt_hash)
{
	menu_len++;
	menu_item[menu_len].action = true;
	menu_item[menu_len].num_val = item_gxt_hash;
	menu_item[menu_len].type = 5;
}
/*
// Adds the action param to the last set menu.
void menu_addAction(void)
{
	menu_item[menu_len].action = true;
}*/

void menu_clean(void)
{
	int I;
	for (I = 1; I < (menu_len + 1); I++)
	{
		menu_item[I].name = null_string;
		menu_item[I].type = 0;
		menu_item[I].num_val = 1;
		menu_item[I].extra_val = 0;
		menu_item[I].float_val = 1.0;
		menu_item[I].action = false;
	}

	custom_bool_on = null_string;
	custom_bool_off = null_string;

	// Reset menu_start_y & menu_max
	menu_start_y = menu_consts_start_y;
	menu_max = menu_consts_max;

	// Reset menu_len.
	menu_len = 0;
}

float draw_text_width(char *gxtName, float x, float y, char *val)
{
	float result;
	result = GET_STRING_WIDTH_WITH_STRING(gxtName, val);
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, gxtName, val);
	return result;
}

void draw_number(char *gxtName, float x, float y, int val)
{
	DISPLAY_TEXT_WITH_NUMBER(x, y, gxtName, val);
}

void draw_float(char *gxtName, float x, float y, float val, uint dp)
{
	DISPLAY_TEXT_WITH_FLOAT(x, y, gxtName, val, dp);
}