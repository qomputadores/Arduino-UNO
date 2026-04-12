/*
 * Author: Iwan
 * Project: 11 Gas System Dynamic Anode
 * Hardware: Common Anode RGB LED + LCD I2C + MQ-2 Sensor
 * Description: Tactical User Interface using Inverse PWM Logic for 
 * Common Anode LEDs. LCD displays hazard levels and quantitative data.
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// --- Hardware Mapping ---
#define GasSensorPin A0  // Analog input from MQ-2
#define RedPin 9         // Red channel PWM (Common Anode)
#define GreenPin 10      // Green channel PWM (Common Anode)
#define BluePin 11       // Blue channel PWM (Common Anode)
#define BuzzerPin 5      // Alert output

// --- LCD Configuration ---
// Standard Address 0x27 for PCF8574 modules
LiquidCrystal_I2C Lcd(0x27, 16, 2); 

// --- Threshold Definitions ---
#define LowThreshold 150
#define WarningThreshold 400
#define DangerThreshold 750

// --- Variable Definitions (UpperCamelCase) ---
int GasValue = 0;        
int Brightness = 0;      
int FadeAmount = 5; 

void setup() {
  // Initialize control pins
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);

  // Initialize LCD Interface
  Lcd.init();
  Lcd.backlight();
  Lcd.setCursor(0, 0);
  Lcd.print("SYSTEM STARTING");
  delay(2000);
  Lcd.clear();
}

void loop() {
  // 1. Data Acquisition
  GasValue = analogRead(GasSensorPin);

  // 2. Breathing Engine Calculation
  Brightness = Brightness + FadeAmount;
  if (Brightness <= 0 || Brightness >= 255) {
    FadeAmount = -FadeAmount; 
  }

  /* * INVERSE LOGIC CALCULATION:
   * Common Anode LEDs are ON when the pin is LOW (0) and OFF when HIGH (255).
   */
  int InvBright = 255 - Brightness; // Maps 0-255 (Logic) to 255-0 (Hardware)
  int FullOff = 255;                // LED OFF for Common Anode
  int FullOn = 0;                   // LED MAX ON for Common Anode

  // 3. LCD Quantitative Display
  Lcd.setCursor(0, 0);
  Lcd.print("GAS VALUE: ");
  Lcd.print(GasValue);
  Lcd.print("    "); // Clear ghost digits

  // --- 4. DYNAMIC INTERFACE LOGIC ---

  // LEVEL 4: DANGER (Solid Red)
  if (GasValue >= DangerThreshold) {
    Lcd.setCursor(0, 1);
    Lcd.print("STATE: DANGER! ");

    analogWrite(RedPin, FullOn);    
    analogWrite(GreenPin, FullOff); 
    analogWrite(BluePin, FullOff);  
    tone(BuzzerPin, 2500);          
  }
  
  // LEVEL 3: WARNING (Fast Orange Breathing)
  else if (GasValue >= WarningThreshold) {
    Lcd.setCursor(0, 1);
    Lcd.print("STATE: WARNING ");

    FadeAmount = (FadeAmount > 0) ? 15 : -15; 
    
    analogWrite(RedPin, InvBright);                   // Pulse Red
    analogWrite(GreenPin, 255 - (Brightness / 4));    // Pulse Green dimmer for Orange
    analogWrite(BluePin, FullOff);  
    
    if(Brightness > 200) tone(BuzzerPin, 1000);
    else noTone(BuzzerPin);
  }
  
  // LEVEL 2: SAFE (Moderate Green Breathing)
  else if (GasValue >= LowThreshold) {
    Lcd.setCursor(0, 1);
    Lcd.print("STATE: SAFE    ");

    FadeAmount = (FadeAmount > 0) ? 5 : -5; 

    analogWrite(RedPin, FullOff);   
    analogWrite(GreenPin, InvBright); 
    analogWrite(BluePin, FullOff);  
    noTone(BuzzerPin);
  }
  
  // LEVEL 1: STANDBY (Slow Blue Breathing)
  else {
    Lcd.setCursor(0, 1);
    Lcd.print("STATE: STANDBY ");

    FadeAmount = (FadeAmount > 0) ? 2 : -2; 

    analogWrite(RedPin, FullOff);   
    analogWrite(GreenPin, FullOff); 
    analogWrite(BluePin, InvBright); 
    noTone(BuzzerPin);
  }

  // PWM Refresh rate
  delay(30); 
}