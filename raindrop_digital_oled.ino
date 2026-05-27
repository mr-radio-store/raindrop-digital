/*
Raindrop module digital output on oled

1. Rain Sensor Module	Arduino	Notes
VCC	5V	Power supply
GND	GND	Ground
DO (digital out)	D2 (example)	HIGH when dry, LOW when wet
AO (analog out)	A0 (optional)	Returns analog moisture level
2. OLED wire connecction
OLED Pin	Arduino Uno / Mega
VCC	5V
GND	GND
SDA	A4 (Uno) / 20 (Mega)
SCL	A5 (Uno) / 21 (Mega)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define RAIN_SENSOR_DO_PIN 2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED display object (I2C address 0x3C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(RAIN_SENSOR_DO_PIN, INPUT);
  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not found"));
    while (true); // Stop if OLED fails
  }

  display.clearDisplay();
  display.setTextSize(1); // Small readable font
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Rain Sensor Ready");
  display.display();
  delay(2000);
}

void loop() {
  int isRaining = digitalRead(RAIN_SENSOR_DO_PIN);
  
  display.clearDisplay();                  // Clear screen
  display.setCursor(0, 10);                // Set position
  display.setTextSize(1);                  // Use small font
  display.setTextColor(SSD1306_WHITE);     // Ensure proper color

  if (isRaining == LOW) {
    display.println("Status: RAIN DETECTED");
    Serial.println("Water detected!");
  } else {
    display.println("Status: NO RAIN");
    Serial.println("No water detected.");
  }

  display.display();
  delay(2000);
}
