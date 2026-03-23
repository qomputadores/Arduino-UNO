/*
 * Author: Iwan
 * Project: 07_Gas_Sensor_MQ2
 * Learning Objective: Interface an MQ-2 gas sensor to create a 
 * multi-level atmospheric alert system (Visual and Audible).
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
 * |   LedGreen (Anode)    |   D2             |  With 220 Ohm Res |
 * |   LedYellow (Anode)   |   D3             |  With 220 Ohm Res |
 * |   LedRed (Anode)      |   D4             |  With 220 Ohm Res |
 * |   BuzzerPin (+)       |   D5             |  Piezo Actuator   |
 * +-----------------------+------------------+-------------------+
 */

// --- Preprocessor Directives ---
#define GasSensorPin A0  // Analog input for MQ-2 sensor
#define LedGreen 2       // Pin for Safe status LED
#define LedYellow 3      // Pin for Warning status LED
#define LedRed 4         // Pin for Danger status LED
#define BuzzerPin 5      // Pin for Audible alarm

// --- Threshold Definitions ---
#define WarningThreshold 300 // Initial alert level
#define DangerThreshold 700  // Critical alert level

// --- Variable Definitions ---
int GasValue = 0;             // Stores the raw analog reading

void setup() {
  // Set digital pins as outputs for the alert system
  pinMode(LedGreen, OUTPUT);  
  pinMode(LedYellow, OUTPUT); 
  pinMode(LedRed, OUTPUT);    
  pinMode(BuzzerPin, OUTPUT); 

  // Initialize all outputs to OFF state
  digitalWrite(LedGreen, LOW);
  digitalWrite(LedYellow, LOW);
  digitalWrite(LedRed, LOW);
  noTone(BuzzerPin);
}

void loop() {
  // Read the analog signal from the MQ-2 sensor (0 to 1023)
  GasValue = analogRead(GasSensorPin);

  // --- Logic Decision Tree for Atmospheric Safety ---

  // LEVEL 3: DANGER (High concentration of gas/smoke)
  if (GasValue >= DangerThreshold) {
    digitalWrite(LedGreen, LOW);
    digitalWrite(LedYellow, LOW);
    digitalWrite(LedRed, HIGH);
    tone(BuzzerPin, 2000);    // Continuous high-pitch tone for emergency
  }
  // LEVEL 2: WARNING (Moderate concentration detected)
  else if (GasValue >= WarningThreshold && GasValue < DangerThreshold) {
    digitalWrite(LedGreen, LOW);
    digitalWrite(LedYellow, HIGH);
    digitalWrite(LedRed, LOW);
    
    // Intermittent beep logic for caution
    tone(BuzzerPin, 1000);
    delay(500);
    noTone(BuzzerPin);
    delay(500);
  }
  // LEVEL 1: SAFE (Air quality within normal limits)
  else {
    digitalWrite(LedGreen, HIGH);
    digitalWrite(LedYellow, LOW);
    digitalWrite(LedRed, LOW);
    noTone(BuzzerPin);        // Ensure silence in safe state
  }

  // Brief delay to stabilize the Analog-to-Digital conversion
  delay(100); 
}