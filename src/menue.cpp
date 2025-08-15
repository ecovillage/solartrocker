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
#include "damper.h"
#include "storage.h"
#include "display.h"


MenuItem menuItems[] = {
	{"Automatik an", set_state_auto},
	{"Luefter aendern", change_luefter},
	{"Klappen aendern", change_klappen},
	{"Reset max Temp", reset_max_temp},
	{"Lueften", set_state_lueften},
	{"Heizen", set_state_heizen},
};

const int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);
int selectedItem = 0;

void set_selectedItem(int nb)
{
	selectedItem = nb;
}


void change_luefter()
{
	set_state_manuel();
	if (get_fan_state() == 0)
		fan_on();
	else
		fan_off();
}

void change_klappen()
{
	set_state_manuel();
	if (get_damper_state() == 0)
		open_damper();
	else
		close_damper();
}



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
	drawMenu();
	if (button1_pressed()) {
  		selectedItem = (selectedItem + 1) % menuItemCount;
	}
	if (button2_pressed()) {
  		set_modus_display(Display_Values);
	}
	else if (button3_pressed()) {
 		handleSelection();
	}
}