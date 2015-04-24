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

void menu_core_startup(void)
{
	if (menu_level == 0)
	{
		item_highlighted = 1;
		menu_level = 1;
		press_counter = 2;
		press_counter_timesby = 1;

		custom_bool_on = null_string;
		custom_bool_off = null_string;
	}

	style_setup();

	menu_consts_start_y = menu_start_y;
	menu_consts_max = menu_max;
	
	WAIT(50);
	if(network){
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mpcellphone");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mpcellphonemain");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mpcellphonenetwork");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mpcellphoneparty");
	}
	else{
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("spcellphone");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("spcellphonemain");
		TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("spcellphonenetwork");
	}
	
	show_menu = true;
}

void menu_core_shutdown(void)
{
	char* phone_script;
	if(network)
		phone_script = "mpcellphone";
	else
		phone_script = "spcellphone";
	
	REQUEST_SCRIPT(phone_script);
	while(!HAS_SCRIPT_LOADED(phone_script)) WAIT(0);
	START_NEW_SCRIPT(phone_script,1024);
	MARK_SCRIPT_AS_NO_LONGER_NEEDED(phone_script);
	
	show_menu = false;
	draw_shutdown();
}

void menu_core_catchButtonPress(void)
{
	if (menu_up_pressed(true) && !inError)
	{
		if (item_highlighted == 1)
			item_highlighted = menu_len;
		else
		{
			item_highlighted--;

			if (menu_len > menu_consts_max && item_highlighted > (menu_start_scrolling - 1))
			{
				menu_start_y += menu_spacing;
				menu_max--;
			}
		}

		PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_SERVER_HIGHLIGHT");
	}

	if (menu_down_pressed(true) && !inError)
	{
		
		if (item_highlighted == menu_len)
		{
			item_highlighted = 1;
			menu_start_y = menu_consts_start_y;
			menu_max = menu_consts_max;
		}
		else
		{
			item_highlighted++;

			if (menu_len > menu_consts_max && item_highlighted > menu_start_scrolling)
			{
				menu_start_y -= menu_spacing;
				menu_max++;
			}
		}

		PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_SERVER_HIGHLIGHT");
	}

	if (menu_left_pressed(true) && !inError)
	{
		if (menu_item[item_highlighted].type == 1)
		{
			if (menu_item[item_highlighted].num_val == 1)
				menu_item[item_highlighted].num_val = menu_item[item_highlighted].extra_val;
			else
				menu_item[item_highlighted].num_val = menu_item[item_highlighted].num_val - 1;

			PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_SERVER_OPTION_CHANGE");
		}
		else if (menu_item[item_highlighted].type == 2)
		{
			if (menu_item[item_highlighted].extra_val != 0 && menu_item[item_highlighted].float_val <= (float) 0.1)
				menu_item[item_highlighted].float_val = menu_item[item_highlighted].extra_val;
			else
			{
				float minus;
				if (custom_float_change != 0)
					minus = custom_float_change;
				else
					minus = 0.100;
				menu_item[item_highlighted].float_val = menu_item[item_highlighted].float_val - minus;
			}

			PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_SERVER_OPTION_CHANGE");
		}
	}

	if (menu_right_pressed(true) && !inError)
	{
		if (menu_item[item_highlighted].type == 1)
		{
			if (menu_item[item_highlighted].num_val == menu_item[item_highlighted].extra_val)
				menu_item[item_highlighted].num_val = 1;
			else
				menu_item[item_highlighted].num_val = menu_item[item_highlighted].num_val + 1;
				
			PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_SERVER_OPTION_CHANGE");
		}
		else if (menu_item[item_highlighted].type == 2)
		{
			if (menu_item[item_highlighted].extra_val != 0 && menu_item[item_highlighted].float_val == (float) menu_item[item_highlighted].extra_val)
				menu_item[item_highlighted].float_val = 0.0;
			else
			{
				float plus;
				if (custom_float_change != 0)
					plus = custom_float_change;
				else
					plus = 0.100;
				menu_item[item_highlighted].float_val = menu_item[item_highlighted].float_val + plus;
			}
			
			PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_SERVER_OPTION_CHANGE");
		}
	}

	if (menu_forward_pressed() && press_counter_timesby < 2 && !inError)
	{
		// Set the selected item.
		item_selected = item_highlighted;

		if (menu_item[item_selected].action)
			project_doAction();
		else
		{
			// Reset the items set. So the new items can be set.
			menu_items_set = false;

			// Remember the last highlighted so we can hightlight back to it.
			last_selected[menu_level] = item_selected;

			// Reset the highlighted item. 
			item_highlighted = 1;

			menu_clean();
			
			// Next level.
			menu_level++;
		}

		if (menu_item[item_selected].action)
			PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_READY");
		else
			PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_SERVER_HIGHLIGHT");
		
	}

	if (menu_back_pressed())
	{
		// Don't do anything if we are on the main menu.
		if (menu_level != 1 || inError)
		{
			// Reset the items set. So the new items can be set.
			menu_items_set = false;

			menu_clean();

			if (!actionError)
				// Go back one level.
				menu_level--;

			item_selected = last_selected[menu_level - 1];

			if (inError)
			{
				if (actionError)
					actionError = false;

				inError = false;
			}
		}
		else if (!disableMenu)
		{
			menu_core_shutdown();
			menu_level = 0;
		}

		PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_SERVER_HIGHLIGHT");
	}

	if (reset_counter)
	{
		press_counter = 2;
		reset_counter = false;
	}
}

void menu_core(void)
{
	if (menu_shutdown)
		menu_core_shutdown();

	menu_core_catchButtonPress();

	project_catchFunctionButtonPress();

	if (!menu_items_set)
	{
		project_set();

		// Set the highlighted item to the last item selected.
		if (menu_back_pressed() && last_selected[menu_level] != 0)
		{
			if (last_selected[menu_level] <= menu_len)
				item_highlighted = last_selected[menu_level];
			else
				item_highlighted = menu_len;

			last_selected[menu_level] = 0;
			
			if (menu_len > menu_consts_max && item_highlighted > menu_start_scrolling)
			{
				uint I;
				for (I = (menu_start_scrolling + 1); I <= item_highlighted; I++)
				{
					menu_start_y -= menu_spacing;
					menu_max++;
				}
			}
		}
	}

	// catchAfterMenuSetButtonPress
	if (menu_up_pressed(false))
	{
		if (menu_len > menu_consts_max && item_highlighted == menu_len)
		{
			menu_start_y = (menu_consts_start_y) - ((menu_len - menu_start_scrolling) * menu_spacing);
			menu_max = menu_len + menu_start_scrolling;
		}
	}
}