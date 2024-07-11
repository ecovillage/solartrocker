// Steuerung für Solartrocknung Vers. 1

#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BME280I2C.h>

// I/O
#define Relay1 6               // Relais für Lüfter (an/aus)
#define Relay2 7               // Relais für Klappenantrieb (Polarität wechselt)
#define ONE_WIRE_BUS 8         // Bus für Temperatursensoren Typ DS18B20
#define Switch1 3            // 1. Taste (noch nicht implementiert)
#define Switch2 4            // 2. Taste (noch nicht implementiert)
#define Switch3 5            // 3. Taste (noch nicht implementiert)

// Display
#define OLED_MOSI    9
#define OLED_CLK    10
#define OLED_DC     11
#define OLED_CS     12
#define OLED_RESET  13
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

OneWire oneWire(ONE_WIRE_BUS); 

DallasTemperature sensors(&oneWire);

BME280I2C bme;

void setup() {
  sensors.begin();
  Serial.begin(9600);
  
  pinMode(3, INPUT);                       //Taste 1
  pinMode(4, INPUT);                       //Taste 2
  pinMode(5, INPUT);                       //Taste 3
  pinMode(6, OUTPUT);                      //Relais 1
  pinMode(7, OUTPUT);                      //Relais 2

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  
  delay(100);

Wire.begin();

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

}


void loop() {

float temp(NAN), hum(NAN), pres(NAN);
   bme.read(pres, temp, hum);

//Relais Test
/*
digitalWrite(6, HIGH);
delay(1000);
digitalWrite(7, HIGH);
delay(1000);
digitalWrite(6, LOW);
delay(1000);
digitalWrite(7, LOW);
delay(100);
*/


// Temperatur messen
  sensors.requestTemperatures(); 
  int Temp1 = (int)(sensors.getTempCByIndex(0),(1));               //DS18B20 Sensor Nr.1
  // wenn mehrere Sensoren am 1W Bus sind sieht das so aus:
  // int Temp1 = (int)(sensors.getTempCByIndex(0),(2));
  // int Temp1 = (int)(sensors.getTempCByIndex(0),(3));
  // usw.


   {
     Serial.print (sensors.getTempCByIndex(0),(1));
     Serial.println (" °C");
     }

  {
    
    display.clearDisplay();
    display.setTextSize(1);             // 2 wäre größer...
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("DS: ");
    display.print(sensors.getTempCByIndex(0),(1));
    display.print((char)247);                        // degree symbol
    display.println("C");

delay(10);

    //display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 15);
    display.print("BMP: ");
    display.print(temp);
    display.print((char)247);                        // degree symbol
    display.println("C");

delay(10);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 30);
    display.print("BMP: ");
    display.print(hum);                               // Luftfeuchte
    display.print(" %RH");                        
    
delay(10);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 45);
    display.print("BMP: ");
    display.print(pres);                               // Luftdruck
    display.print(" mBar");     



  // Falls Du am unteren Bilschirm "Softkeys" basteln willst hier ein Beispiel:
  // Softkeys am unteren Displayrand
  /*
    display.setTextSize(2);
    display.setTextColor(BLACK, WHITE);              // Textfarbe invers
    display.setCursor(1, 49);
    display.print("ABC");
    display.setCursor(80, 49);
    display.print("1234");
    display.drawLine(0,49, 127, 49, WHITE);          // waagerechte Linie
    display.drawLine(0,50, 0, 63, WHITE);            // senkrechte Linie links
    display.drawLine(79,50, 79, 63, WHITE);          // senkrechte Linie rechts
*/

display.display();  
 } 
}                                                    // end loop
