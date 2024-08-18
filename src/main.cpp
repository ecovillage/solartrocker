#include <Arduino.h>
#include "fan.h"
#include "damper.h"
#include "lcd.h"
#include "bme280.h"
#include "display.h"
#include "ds18B20.h"
#include "buttons.h"
#include "storage.h"
#include "data.h"
#include "damper_logic.h"

void setup()
{	
	Serial.begin(9600);
	fan_setup();
	BME280_setup();
	damper_setup();
	lcd_setup();
	buttons_setup();
}

void loop()
{
	if (button1_pressed())
	{
		if (damper_state() == 0)
			open_damper();
		else
			close_damper();
		delay(200);
	}
	if (button2_pressed() == 1)
	{
		if (fan_state() == 0)
			fan_on();
		else
			fan_off();
		delay(200);
	}
	if (button3_pressed() == 1)
	{
		set_modus(read_modus() + 1);
		delay(200);
	}
	if (!check_humidity())
		check_fan_neccessary();
	display_values();
	collect_data();
	delay(100);
}

// // Taster-Test


// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// // I/O
// #define PIN_BUTTON1 3
// #define PIN_BUTTON2 4
// #define PIN_BUTTON3 5


// // Display
// #define OLED_MOSI    9
// #define OLED_CLK    10
// #define OLED_DC     11
// #define OLED_CS     12
// #define OLED_RESET  13
// #define SCREEN_WIDTH 128      // OLED display width, in pixels
// #define SCREEN_HEIGHT 64      // OLED display height, in pixels

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


// void setup() {
  
//   pinMode(PIN_BUTTON1, INPUT_PULLUP);
//   pinMode(PIN_BUTTON2, INPUT_PULLUP);
//   pinMode(PIN_BUTTON3, INPUT_PULLUP);

//   display.begin(SSD1306_SWITCHCAPVCC);
//   display.clearDisplay();
// }


// void loop() 
// {

// if (digitalRead(PIN_BUTTON1) == LOW) {  // Wenn auf der Eingangsleitung des Tasters1 HIGH anliegt ...
    
//   	print_str_lcd("Taster 1:   ");
// }
// else
// {display.clearDisplay();

// }
// display.display();
// if (digitalRead(PIN_BUTTON2) == LOW) {  // Wenn auf der Eingangsleitung des Tasters1 HIGH anliegt ...
    
//    print_str_lcd("Taster 2:   ");
// }
// else
// {display.clearDisplay();

// }
// display.display();
// if (digitalRead(PIN_BUTTON3) == LOW) {  // Wenn auf der Eingangsleitung des Tasters1 HIGH anliegt ...
    
//     print_str_lcd("Taster 3:   ");
// }
// else
// {display.clearDisplay();
//     }
//   display.display(); 
// }


