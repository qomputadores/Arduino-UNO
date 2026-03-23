/*
 * Author: Iwan
 * Project: 08 LCD I2C
 * Learning Objective: Master the I2C protocol and custom icon 
 * creation on a 16x2 LCD display.
 */

/*
 * +--------------------------------------------------------------+
 * |                HARDWARE CONNECTION DIAGRAM                   |
 * +-----------------------+------------------+-------------------+
 * |   COMPONENT (LCD)     |   ARDUINO PIN    |      NOTES        |
 * +-----------------------+------------------+-------------------+
 * |   VCC                 |   5V             |  Positive Rail    |
 * |   GND                 |   GND            |  Negative Rail    |
 * |   SDA (Serial Data)   |   A4             |  I2C Data Line    |
 * |   SCL (Serial Clock)  |   A5             |  I2C Clock Line   |
 * +-----------------------+------------------+-------------------+
 */

#include <Wire.h>               // Built-in library for I2C communication
#include <LiquidCrystal_I2C.h>  // External library for LCD I2C control

// Initialize LCD at address 0x27, with 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variable to define the speed of the scrolling animation
int timer = 200;

// Custom character bit-map: Heart Icon (5x8 pixel matrix)
// The '0b' prefix indicates binary format; 1 = Pixel ON, 0 = Pixel OFF
byte heart_icon[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,     
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup() {
  // Initialize the LCD controller hardware (HD44780 compatible)
  lcd.init();
  
  // Power up the LED panel background (Backlight)
  lcd.backlight();

  // Create the custom character and store it in CGRAM address 0
  lcd.createChar(0, heart_icon);

  // Position cursor at Column 0, Row 0 (Top row)
  lcd.setCursor(0, 0);
  lcd.print("Hello Noveno!");
  
  // Position cursor at Column 0, Row 1 (Bottom row)
  lcd.setCursor(0, 1);
  lcd.print("We ");
  
  // Write the raw byte of the icon stored at memory index 0
  lcd.write(0); 
  
  // Print the remaining text string
  lcd.print(" Robotics");
  
  // Initial delay to allow reading before animation starts
  delay(2000);
}

void loop() {
  // Loop to shift the entire buffer 16 positions to the left
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(timer);
  }

  // Loop to shift the buffer 16 positions back to the right
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayRight();
    delay(timer);
  }
}