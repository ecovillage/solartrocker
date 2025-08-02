/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menue.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolf>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:14:09 by jweingar          #+#    #+#             */
/*   Updated: 2025/07/20 12:14:09 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arduino.h"
#include "menue.h"
#include "fan.h"
#include "lcd.h"
#include "buttons.h"
#include <Adafruit_SSD1306.h>
#include "damper_logic.h"
#include "damper_logic.h"
#include "storage.h"

MenuItem menuItems[] = {
  {"Lueften", set_state_lueften},
  {"Heizen", set_state_heizen},
  {"Reset max Temp", reset_max_temp},
  {"leer1", NULL},
  {"leer2", NULL},
  {"leer3", NULL},
  {"leer4", NULL},
  {"leer5", NULL},
  {"leer6", NULL},
  {"leer7", NULL}
};

const int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);
int selectedItem = 0;


void handleSelection() {
  if (menuItems[selectedItem].action != nullptr) {
    menuItems[selectedItem].action();
  }
}

void drawMenu() {
	clear_lcd();
	set_position_cursor_lcd(0,0);
	setTextColor_display(WHITE, BLACK);
	print_str_lcd("MENUE: Seite ");
	print_int_lcd((selectedItem / 6) + 1);
	print_str_lcd("/");
	print_int_lcd((menuItemCount / 6) + 1);
	print_str_lcd("\n\n");
	


	for (int i = 0; i < min(menuItemCount, 6); i++) {
		if (i + (selectedItem / 6) * 6 == selectedItem)
			setTextColor_display(BLACK, WHITE);
		else
			setTextColor_display(WHITE, BLACK);
		print_str_lcd(menuItems[i + (selectedItem / 6) * 6].label);
		print_str_lcd("\n");
		setTextColor_display(WHITE, BLACK);
	}
	display_on_lcd();
}

void show_menue()
{
	if (button1_pressed()) {
  		selectedItem = (selectedItem + 1) % menuItemCount;
	}
	if (button2_pressed()) {
  		set_state_auto();
	}
	if (button3_pressed()) {
 		handleSelection();
	}
	drawMenu();
}