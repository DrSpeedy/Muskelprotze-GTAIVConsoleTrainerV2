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

#include "menu_locals.h"
#include "menu_consts.h"

#if STYLE == 1
	#include "menu_style_1.c"
#endif
#if STYLE == 2
	#include "menu_style_2.c"
#endif
#if STYLE == 3
	#include "menu_style_3.c"
#endif
#if STYLE == 4
	#include "menu_style_4.c"
#endif
#if STYLE == 5
	#include "menu_style_5.c"
#endif


#include "menu_functions.c"