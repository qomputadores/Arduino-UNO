/*
 * Author: Iwan
 * Project: 01 Internal Blink
 * Learning Objective: To understand the basic structure of a sketch (setup and loop) 
 * and verify the communication between the computer and the Arduino board.
 */

/*
 * Connections:
 * Internal Led: Pin 13 (Built-in)
 * No external wiring required for this project.
 */

#define InternalLed 13 // Definition of the built-in LED pin using Upper CamelCase

void setup() {
  // Initialize the digital pin 13 as an output
  pinMode(InternalLed, OUTPUT);
}

void loop() {
  // Set the logic level to HIGH to turn the LED on
  digitalWrite(InternalLed, HIGH);
  delay(1000); // Wait for one second (1000 milliseconds)

  // Set the logic level to LOW to turn the LED off
  digitalWrite(InternalLed, LOW);
  delay(1000); // Wait for one second
}