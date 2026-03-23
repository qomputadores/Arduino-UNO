/*
 * Author: Iwan
 * Project: 07B Parking RGB Anode
 * Learning Objective: Dynamic Blue pulse with Inverse Logic (Anode).
 */

#define RED_PIN 11
#define GREEN_PIN 6
#define BLUE_PIN 5
#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 3

long duration;
int distance;

int blueBrightness = 255; // Starts at OFF for Anode
int fadeAmount = -5;      // Moves towards 0 (ON)

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  int redIntensity = 255;
  int greenIntensity = 255;
  int blueIntensity = 255;

  if (distance > 100) {
    // MODE: STANDBY (Dynamic Blue Pulse)
    blueIntensity = blueBrightness;
    blueBrightness = blueBrightness + fadeAmount;

    // Logic: In Anode, 0 is full ON, 255 is OFF
    if (blueBrightness <= 0 || blueBrightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    noTone(BUZZER_PIN);
  } 
  else if (distance <= 100 && distance > 50) {
    // Transition Blue to Green
    blueIntensity = map(distance, 50, 100, 255, 0);
    greenIntensity = map(distance, 50, 100, 0, 255);
    noTone(BUZZER_PIN);
  }
  else if (distance <= 50 && distance > 20) {
    greenIntensity = map(distance, 20, 50, 255, 0);
    redIntensity = map(distance, 20, 50, 0, 255);
    tone(BUZZER_PIN, 1000, 20); 
  } 
  else {
    redIntensity = 0;
    tone(BUZZER_PIN, 2000); 
  }

  analogWrite(RED_PIN, redIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
  analogWrite(BLUE_PIN, blueIntensity);

  delay(30);
}
