/*
 * Author: Iwan
 * Project: 07 Parking Assistant
 * Learning Objective: Integrated system using ultrasonic sensors, 
 * multi-stage visual alerts (LEDs), and acoustic feedback (Buzzer).
 */

// --- PIN DEFINITIONS ---
#define TRIG_PIN 9
#define ECHO_PIN 10
#define LED_GREEN 2
#define LED_YELLOW 3
#define LED_RED 4
#define BUZZER_PIN 5

// --- VARIABLES ---
// long (32-bit): For large numbers like microseconds
long duration; 
// int (16-bit): For smaller numbers like centimeters
int distance;  

void setup() {
  // Configured as OUTPUT because they send signals
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Configured as INPUT because it listens for the rebound
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize Serial Communication at 9600 bps
  Serial.begin(9600);
}

void loop() {
  // --- STEP 1: SENSOR TRIGGERING ---
  // We clean the pin and send a 10us pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // --- STEP 2: MEASURING & CALCULATING ---
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // --- STEP 3: DECISION LOGIC (If/Else) ---
  
  // STATE 1: SAFE (Distance > 50cm)
  if (distance > 50) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    noTone(BUZZER_PIN);
  } 
  // STATE 2: WARNING (Between 20cm and 50cm)
  else if (distance <= 50 && distance > 20) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
    tone(BUZZER_PIN, 1000, 50); 
  } 
  // STATE 3: DANGER (Distance < 20cm)
  else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER_PIN, 2000); 
  }

  // --- STEP 4: DUAL-MODE TELEMETRY ---
  // Format for Serial Plotter (Labels:Values)
  Serial.print("Dist:");
  Serial.print(distance);
  Serial.print(",");
  
  Serial.print("Safe_50:");
  Serial.print(50);
  Serial.print(",");
  
  Serial.print("Danger_20:");
  Serial.print(20);
  Serial.print(",");
  
  Serial.print("Ground:");
  Serial.println(0);
  
  // Stability delay
  delay(50); 
}