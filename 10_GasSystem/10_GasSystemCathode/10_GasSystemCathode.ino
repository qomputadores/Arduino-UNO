/*
 * Author: Iwan
 * Project: 10 Gas System Dynamic Cathode
 * Learning Objective: Implement a Tactical User Interface where "Breathing" 
 * speed and color indicate the atmospheric hazard level.
 */

/*
 * +--------------------------------------------------------------+
 * |                HARDWARE CONNECTION DIAGRAM                   |
 * +-----------------------+------------------+-------------------+
 * |   COMPONENT           |   ARDUINO PIN    |      NOTES        |
 * +-----------------------+------------------+-------------------+
 * |   Mq2 Vcc             |   5V             |  Power Rail       |
 * |   Mq2 Gnd             |   GND            |  Ground Rail      |
 * |   Mq2 Ao (Analog Out) |   A0             |  Analog Input     |
 * |   RGB Cathode (Long)  |   GND            |  Common Negative  |
 * |   Red Anode Pin       |   D9 (PWM)       |  Pin with ~ mark  |
 * |   Green Anode Pin     |   D10 (PWM)      |  Pin with ~ mark  |
 * |   Blue Anode Pin      |   D11 (PWM)      |  Pin with ~ mark  |
 * |   Buzzer (+) or (S)   |   D5 (PWM)       |  Component or Mod |
 * +-----------------------+------------------+-------------------+
 */

// --- Preprocessor Directives (#define) ---
#define GasSensorPin A0  // Analog input from MQ-2
#define RedPin 9         // Red channel PWM
#define GreenPin 10      // Green channel PWM
#define BluePin 11       // Blue channel PWM
#define BuzzerPin 5      // Alert output

// --- Threshold Definitions ---
#define LowThreshold 150     // Threshold for Standby to Safe
#define WarningThreshold 400 // Threshold for Safe to Warning
#define DangerThreshold 750  // Threshold for Emergency

// --- Variable Definitions ---
int GasValue = 0;        // Variable to store raw sensor data
int Brightness = 0;      // Current intensity of the LED (0-255)
int FadeAmount = 5;      // Speed of the pulse (Changed dynamically)

void setup() {
  // Set all control pins as outputs
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
}

void loop() {
  // 1. Read the gas concentration (0 to 1023)
  GasValue = analogRead(GasSensorPin);

  // 2. Breathing Engine: Adjust the brightness pulse
  Brightness = Brightness + FadeAmount;

  // Reverse the fade direction at the limits
  if (Brightness <= 0 || Brightness >= 255) {
    FadeAmount = -FadeAmount; 
  }

  // --- 3. DYNAMIC INTERFACE LOGIC ---

  // LEVEL 4: DANGER (High concentration)
  if (GasValue >= DangerThreshold) {
    analogWrite(RedPin, 255);    // Solid Red (No pulse for maximum urgency)
    analogWrite(GreenPin, 0);    // Green OFF
    analogWrite(BluePin, 0);     // Blue OFF
    tone(BuzzerPin, 2500);       // High-pitched continuous emergency tone
  }
  
  // LEVEL 3: WARNING (Moderate concentration)
  else if (GasValue >= WarningThreshold) {
    // Increase speed: FadeAmount is 15 (Fast pulse)
    FadeAmount = (FadeAmount > 0) ? 15 : -15; 
    
    analogWrite(RedPin, Brightness);       // Red pulses fast
    analogWrite(GreenPin, Brightness / 4); // Green pulses dimmer for Orange
    analogWrite(BluePin, 0);               // Blue OFF
    
    // Sync intermittent beep with the peak of the pulse
    if(Brightness > 200) tone(BuzzerPin, 1000); 
    else noTone(BuzzerPin);
  }
  
  // LEVEL 2: SAFE (Low concentration)
  else if (GasValue >= LowThreshold) {
    // Normal speed: FadeAmount is 5 (Moderate pulse)
    FadeAmount = (FadeAmount > 0) ? 5 : -5; 

    analogWrite(RedPin, 0);             // Red OFF
    analogWrite(GreenPin, Brightness);  // Green pulses normally
    analogWrite(BluePin, 0);            // Blue OFF
    noTone(BuzzerPin);                  // No sound in safe state
  }
  
  // LEVEL 1: STANDBY (Clean air/Calibration)
  else {
    // Slow speed: FadeAmount is 2 (Languid pulse)
    FadeAmount = (FadeAmount > 0) ? 2 : -2; 

    analogWrite(RedPin, 0);             // Red OFF
    analogWrite(GreenPin, 0);           // Green OFF
    analogWrite(BluePin, Brightness);   // Blue pulses slowly
    noTone(BuzzerPin);                  // System is calm
  }

  // Time between steps (Controls the smoothness of the PWM)
  delay(30); 
}