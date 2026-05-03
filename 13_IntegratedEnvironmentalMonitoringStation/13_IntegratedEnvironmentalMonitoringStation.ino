/*
 * Author: Iwan
 * Project: 13 Indoor Climate Station
 * Learning Objective: Analysis of multi-variable environmental signals, 
 * I2C communication protocol, and acoustic/visual hierarchical control.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- Hardware Mapping and Peripheral Definitions ---
#define GasSensorPin A0  
#define DhtPin 4         
#define DhtType DHT11    
#define RedPin 9         
#define GreenPin 10      
#define BluePin 11       
#define BuzzerPin 5      

// --- Object Initialization ---
DHT DhtSensor(DhtPin, DhtType); 
LiquidCrystal_I2C Lcd(0x27, 16, 2); 

// --- Execution Control Variables ---
unsigned long PreviousMillis = 0; 
int ScreenMode = 0;               
int Brightness = 0;               
int FadeAmount = 5;               

void setup() {
  // Configuration of Pin Modes for actuators
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);

  // Peripheral activation sequences
  DhtSensor.begin(); 
  Lcd.init();        
  Lcd.backlight();   
  
  // Initial system diagnostic sequence
  Lcd.setCursor(0, 0);
  Lcd.print("Station ready"); // Sentence Case applied
  
  Lcd.setCursor(0, 1);
  Lcd.print("Booting system"); // Sentence Case applied
  
  // Stabilization period for sensor chemistry
  delay(3000); 
  Lcd.clear();
}

void loop() {
  // --- 1. QUANTITATIVE SIGNAL ACQUISITION ---
  int RawValue = analogRead(GasSensorPin); 
  int GasPercent = map(RawValue, 0, 1023, 0, 100); 
  float Temp = DhtSensor.readTemperature(); 
  float Hum = DhtSensor.readHumidity();      

  // --- 2. PULSE ENGINE (PWM NON-BLOCKING SIGNAL) ---
  Brightness = Brightness + FadeAmount;
  if (Brightness >= 255) {
    FadeAmount = -5; 
  }
  if (Brightness <= 0) {
    FadeAmount = 5;  
  }

  // --- 3. UI SCHEDULER (TEMPORAL MULTIPLEXING) ---
  unsigned long CurrentMillis = millis();
  if (CurrentMillis - PreviousMillis >= 3000) {
    PreviousMillis = CurrentMillis;
    ScreenMode = ScreenMode + 1;
    if (ScreenMode > 3) {
      ScreenMode = 0;
    }
    Lcd.clear(); 
  }

  // --- 4. HIERARCHICAL ALARM LOGIC (CATHODE & ACOUSTIC) ---
  if (GasPercent >= 70 || Temp >= 30 || Hum >= 75) {
    analogWrite(RedPin, 255); 
    analogWrite(GreenPin, 0); 
    analogWrite(BluePin, 0);
    tone(BuzzerPin, 2500); 
  }
  else if (GasPercent >= 15 || Temp >= 24 || Hum >= 60) {
    analogWrite(RedPin, Brightness);       
    analogWrite(GreenPin, Brightness / 4); 
    analogWrite(BluePin, 0);
    noTone(BuzzerPin); 
  }
  else {
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, Brightness);     
    analogWrite(BluePin, Brightness / 10); 
    noTone(BuzzerPin); 
  }

  // --- 5. SEQUENTIAL INFORMATION DISPLAY (Sentence Case) ---
  
  // Screen 0: Project Branding
  if (ScreenMode == 0) {
    Lcd.setCursor(0, 0);
    Lcd.print("Comfort station");
    
    Lcd.setCursor(0, 1);
    Lcd.print("By: Iwan");
  }

  // Screen 1: Gas Telemetry
  if (ScreenMode == 1) {
    Lcd.setCursor(0, 0);
    Lcd.print("Gas level: ");
    Lcd.print(GasPercent);
    Lcd.print("%");
    
    Lcd.setCursor(0, 1);
    if (GasPercent >= 70) {
      Lcd.print("Status: Danger");
    }
    else if (GasPercent >= 15) {
      Lcd.print("Status: Warning");
    }
    else {
      Lcd.print("Status: Safe");
    }
  }

  // Screen 2: Temperature Telemetry
  if (ScreenMode == 2) {
    Lcd.setCursor(0, 0);
    Lcd.print("Temp: ");
    Lcd.print(Temp);
    Lcd.print(" C");
    
    Lcd.setCursor(0, 1);
    if (Temp >= 30) {
      Lcd.print("Status: Hot");
    }
    else if (Temp < 24) {
      Lcd.print("Status: Comfort");
    }
    else {
      Lcd.print("Status: Normal");
    }
  }

  // Screen 3: Humidity Telemetry
  if (ScreenMode == 3) {
    Lcd.setCursor(0, 0);
    Lcd.print("Humidity: ");
    Lcd.print(Hum);
    Lcd.print("%");
    
    Lcd.setCursor(0, 1);
    if (Hum >= 75) {
      Lcd.print("Status: Condens.");
    }
    else if (Hum < 30) {
      Lcd.print("Status: Dry");
    }
    else {
      Lcd.print("Status: Ideal");
    }
  }

  delay(30); 
}