/*
 * Author: Iwan
 * Project: 06 RGB Led Common Anode
 * Learning Objective: To understand the Inverse Logic of a Common Anode RGB LED 
 * and how to achieve color mixing by grounding the specific color pins.
 */

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

int timer = 1000;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // --- PRIMARY COLORS (In Anode, LOW = ON) ---

  // Red
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  delay(timer);

  // Green
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  delay(timer);

  // Blue
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  delay(timer);

  // --- MIXING FOR SECONDARY COLORS ---

  // Yellow (Red ON + Green ON)
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  delay(timer);

  // Cyan (Green ON + Blue ON)
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  delay(timer);

  // Magenta (Red ON + Blue ON)
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  delay(timer);

  // --- THE ULTIMATE MIX ---

  // White (All colors ON)
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  delay(timer);

  // OFF
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  delay(timer);
}