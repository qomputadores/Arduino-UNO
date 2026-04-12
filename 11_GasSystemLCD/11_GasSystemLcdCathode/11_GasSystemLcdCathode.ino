/*
 * Author: Iwan
 * Project: 11 Gas System Dynamic Cathode
 * Hardware: Common Cathode RGB LED + LCD I2C + MQ-2 Sensor
 * Description: Tactical User Interface where "Breathing" speed, 
 * color, and LCD messages indicate the atmospheric hazard level.
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// --- Hardware Mapping ---
#define GasSensorPin A0  // Analog input from MQ-2
#define RedPin 9         // Red channel PWM (Common Cathode)
#define GreenPin 10      // Green channel PWM (Common Cathode)
#define BluePin 11       // Blue channel PWM (Common Cathode)
#define BuzzerPin 5      // Alert output

// --- LCD Configuration ---
// Address 0x27 is standard for most PCF8574 I2C modules
LiquidCrystal_I2C Lcd(0x27, 16, 2); 

// --- Threshold Definitions ---
#define LowThreshold 150     // Calibration to Safe limit
#define WarningThreshold 400 // Safe to Warning limit
#define DangerThreshold 750  // Warning to Emergency limit

// --- Variable Definitions (UpperCamelCase) ---
int GasValue = 0;        // Current sensor reading
int Brightness = 0;      // PWM intensity for breathing effect
int FadeAmount = 5;      // Pulse step speed

void setup() {
  // Initialize digital pins as outputs
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);

  // Initialize LCD Module
  Lcd.init();
  Lcd.backlight();
  Lcd.setCursor(0, 0);
  Lcd.print("SYSTEM STARTING");
  delay(2000);
  Lcd.clear();
}

void loop() {
  // 1. Quantitative Data Acquisition
  GasValue = analogRead(GasSensorPin);

  // 2. Breathing Engine: Dynamic PWM Calculation
  Brightness = Brightness + FadeAmount;

  // Reverse pulse direction at limits (0-255)
  if (Brightness <= 0 || Brightness >= 255) {
    FadeAmount = -FadeAmount; 
  }

  // 3. LCD Quantitative Feedback
  Lcd.setCursor(0, 0);
  Lcd.print("GAS VALUE: ");
  Lcd.print(GasValue);
  Lcd.print("    "); // Clear ghost characters

  // --- 4. DYNAMIC INTERFACE LOGIC ---

  // LEVEL 4: DANGER (High concentration)
  if (GasValue >= DangerThreshold) {
    Lcd.setCursor(0, 1);
    Lcd.print("STATE: DANGER! ");
    
    analogWrite(RedPin, 255);    // Solid Red (No pulse for urgency)
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 0);
    tone(BuzzerPin, 2500);       // High-pitched continuous alarm
  }
  
  // LEVEL 3: WARNING (Moderate concentration)
  else if (GasValue >= WarningThreshold) {
    Lcd.setCursor(0, 1);
    Lcd.print("STATE: WARNING ");

    // Fast Pulse Speed
    FadeAmount = (FadeAmount > 0) ? 15 : -15; 
    
    analogWrite(RedPin, Brightness);       // Fast Red pulse
    analogWrite(GreenPin, Brightness / 4); // Dimmer Green to create Orange
    analogWrite(BluePin, 0);
    
    // Intermittent beep synchronized with brightness peak
    if(Brightness > 200) tone(BuzzerPin, 1000); 
    else noTone(BuzzerPin);
  }
  
  // LEVEL 2: SAFE (Low concentration)
  else if (GasValue >= LowThreshold) {
    Lcd.setCursor(0, 1);
    Lcd.print("STATE: SAFE    ");

    // Moderate Pulse Speed
    FadeAmount = (FadeAmount > 0) ? 5 : -5; 

    analogWrite(RedPin, 0);
    analogWrite(GreenPin, Brightness);     // Normal Green pulse
    analogWrite(BluePin, 0);
    noTone(BuzzerPin);
  }
  
  // LEVEL 1: STANDBY (Clean air)
  else {
    Lcd.setCursor(0, 1);
    Lcd.print("STATE: STANDBY ");

    // Slow/Languid Pulse Speed
    FadeAmount = (FadeAmount > 0) ? 2 : -2; 

    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, Brightness);      // Slow Blue pulse
    noTone(BuzzerPin);
  }

  // Refresh rate for PWM smoothness
  delay(30); 
}