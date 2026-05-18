/*
 * Author: Iwan
 * Project: 15 Smart Indoor Climate Actuation
 * Learning Objective: Analysis of multi-variable environmental signals, 
 * I2C communication protocol, and power relay automation control.
 */

/*
 * +-------------------------------------------------------------------------+
 * |                     TECHNICAL CONNECTION MAP (DATA ONLY)                |
 * +-----------------------+-------------------+-----------------------------+
 * |   HARDWARE COMPONENT  | ARDUINO PIN (UNO) |         PIN TYPE            |
 * +-----------------------+-------------------+-----------------------------+
 * |   MQ-2 Gas Sensor     | A0                | Analog Input Signal         |
 * |   DHT11 Data Line     | D4                | Digital Input/Output (I/O)  |
 * |   RGB LED Red Pin     | D9 (PWM)          | Analog Output (PWM)         |
 * |   RGB LED Green Pin   | D10 (PWM)         | Analog Output (PWM)         |
 * |   RGB LED Blue Pin    | D11 (PWM)         | Analog Output (PWM)         |
 * |   Active Buzzer (+)   | D5 (PWM)          | Analog Output (PWM / tone)  |
 * |   5V Relay Module     | D3                | Digital Output Command      |
 * |   I2C LCD SDA Line    | A4                | Dedicated I2C Data Bus      |
 * |   I2C LCD SCL Line    | A5                | Dedicated I2C Clock Bus     |
 * +-----------------------+-------------------+-----------------------------+
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
#define RelayPin 3

// --- Object Initialization ---
DHT DhtSensor(DhtPin, DhtType); 
LiquidCrystal_I2C Lcd(0x27, 16, 2); 

// --- Execution Control Variables ---
unsigned long PreviousMillis = 0; 
int ScreenMode = 0;               
int Brightness = 0;               
int FadeAmount = 5;               

void setup() {
  // Configuration of Pin Modes for actuators and relays
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(RelayPin, OUTPUT); // Configure relay pin as an output signal line
  
  // Force secure home state: ventilation fan starts completely OFF
  digitalWrite(RelayPin, LOW);

  // Peripheral activation sequences
  DhtSensor.begin(); 
  Lcd.init();        
  Lcd.backlight();   
  
  // Initial system diagnostic sequence
  Lcd.setCursor(0, 0);
  Lcd.print("Station ready"); // Sentence Case applied
  
  Lcd.setCursor(0, 1);
  Lcd.print("Booting system"); // Sentence Case applied
  
  // Establishment of hardware terminal baud rate communication
  Serial.begin(9600);
  Serial.println("==================================================");
  Serial.println("    POWER ELECTRONICS: INTEGRATED RELAY ACTIVE    ");
  Serial.println("==================================================");

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
  // Calculates real-time incremental steps for visual breathing effects
  Brightness = Brightness + FadeAmount;
  if (Brightness >= 255) {
    FadeAmount = -5; 
  }
  if (Brightness <= 0) {
    FadeAmount = 5;  
  }

  // --- 3. UI SCHEDULER (TEMPORAL MULTIPLEXING) ---
  // Rotates information screens every 3000ms without blocking processing lines
  unsigned long CurrentMillis = millis();
  
  // Dynamic override: Only advance screens if the relay is NOT active
  if (digitalWrite != HIGH) { 
    if (CurrentMillis - PreviousMillis >= 3000) {
      PreviousMillis = CurrentMillis;
      ScreenMode = ScreenMode + 1;
      if (ScreenMode > 3) { // Bounds limited to baseline screens (0 to 3)
        ScreenMode = 0;
      }
      Lcd.clear(); 
    }
  }

  // --- 4. HIERARCHICAL ALARM & ACTUATION LOGIC ---
  // LEVEL 1: DANGER STATE (Critical environmental thresholds breached)
  if (GasPercent >= 70 || Temp >= 30 || Hum >= 75) {
    analogWrite(RedPin, 255); // Solid Red alert behavior
    analogWrite(GreenPin, 0); 
    analogWrite(BluePin, 0);
    tone(BuzzerPin, 2500);    // Continuous high-pitch panic alarm
    
    // --- INTEGRATED AUTOMATION ACTUATOR CONTROL ---
    // Engage the electromechanical relay if danger comes from Gas density OR high Temperature
    if (GasPercent >= 70 || Temp >= 30) {
      digitalWrite(RelayPin, HIGH); // Contact NO Closed -> Exhaust Fan ON
      
      // UI Override: Force screen to Emergency state if it wasn't set yet
      if (ScreenMode != 4) {
        ScreenMode = 4;
        Lcd.clear();
      }
      Serial.println("[ALARM ACTUATION]: CRITICAL VENTILATION OVERRIDE LOCKED HIGH");
    } else {
      // If safety alarm is triggered strictly by moisture condensation, relay remains OFF
      digitalWrite(RelayPin, LOW); 
      if (ScreenMode == 4) { // Release override if shifting back from a relay event
        ScreenMode = 0;
        Lcd.clear();
      }
    }
  }
  // LEVEL 2: WARNING STATE (Medium environmental risk levels detected)
  else if (GasPercent >= 15 || Temp >= 24 || Hum >= 60) {
    analogWrite(RedPin, Brightness);       // Orange pulsing breathing output
    analogWrite(GreenPin, Brightness / 4); 
    analogWrite(BluePin, 0);
    noTone(BuzzerPin); 
    digitalWrite(RelayPin, LOW); // Contact NO Open -> Exhaust Fan OFF
    
    if (ScreenMode == 4) { // Safety clearance reset
      ScreenMode = 0;
      Lcd.clear();
    }
  }
  // LEVEL 3: SAFE Baseline State (All metrics operating inside nominal zones)
  else {
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, Brightness);     // Green dominant refreshing baseline pulse
    analogWrite(BluePin, Brightness / 10); 
    noTone(BuzzerPin); 
    digitalWrite(RelayPin, LOW); // Contact NO Open -> Exhaust Fan OFF
    
    if (ScreenMode == 4) { // Safety clearance reset
      ScreenMode = 0;
      Lcd.clear();
    }
  }

  // --- 5. SEQUENTIAL INFORMATION DISPLAY (Sentence Case) ---
  
  // Screen 0: Project Branding
  if (ScreenMode == 0) {
    Lcd.setCursor(0, 0);
    Lcd.print("Comfort station");
    Lcd.setCursor(0, 1);
    Lcd.print("By: Name");
  }

  // Screen 1: Chemical Density Percentage Tracking
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

  // Screen 2: Thermal Metric Readings
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

  // Screen 3: Ambient Moisture Density Tracking
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

  // Dynamic Screen 4: Active Mitigation Override Display (Sentence Case)
  if (ScreenMode == 4) {
    Lcd.setCursor(0, 0);
    Lcd.print("Status: Emergency");
    Lcd.setCursor(0, 1);
    Lcd.print("Fan activated");
  }

  delay(30); // Maintains system processing rhythm and uniform PWM transitions
}