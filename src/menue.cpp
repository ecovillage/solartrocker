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
	print_str_lcd("-- MENUE --\n\n");
	for (int i = 0; i < menuItemCount; i++) {
		if (i == selectedItem)
			setTextColor_display(BLACK, WHITE);
		else
			setTextColor_display(WHITE, BLACK);
		print_str_lcd(menuItems[i].label);
		print_str_lcd("\n");
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