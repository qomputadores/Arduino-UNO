/*
 * Author: Iwan
 * Project: 02 External Led Control
 * Learning Objective: To understand digital outputs and breadboard connectivity
 * using technical electronic terminology.
 */

/*
 * Connections via Breadboard:
 * 1. Jumper 1: Arduino Pin 2  -->  Breadboard (Column X).
 * 2. 220 Ohm Resistor: Bridge between Column X and Column Y.
 * 3. LED Anode (+): Inserted into Column Y (sharing node with resistor).
 * 4. LED Cathode (-): Inserted into Column Z (new node).
 * 5. Jumper 2: Column Z  -->  Arduino GND (completes the circuit).
 * Note: Components in the same column are electrically connected.
 */

#define ExternalLed 2 

void setup() {
  // Configure the digital pin as an output to allow current flow
  pinMode(ExternalLed, OUTPUT);
}

void loop() {
  // High logic level (5V): Current flows to the Anode
  digitalWrite(ExternalLed, HIGH);
  // Pause execution for 1000 milliseconds
  delay(1000);

  // Low logic level (0V): Stops the current flow
  digitalWrite(ExternalLed, LOW);
  // Pause execution for 1000 milliseconds
  delay(1000);
}