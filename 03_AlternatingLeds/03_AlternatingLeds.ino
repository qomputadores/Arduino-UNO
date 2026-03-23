/*
 * Author: Iwan
 * Project: 03 Alternating Leds
 * Learning Objective: To control two external digital outputs simultaneously 
 * and create a visual alternating sequence using technical terminology.
 */

/*
 * Connections via Breadboard:
 * 1. Red LED Anode (+): Connected to Pin 2 via 220 Ohm resistor (Column X).
 * 2. Blue LED Anode (+): Connected to Pin 3 via 220 Ohm resistor (Column Y).
 * 3. Common Ground: Both Cathodes (-) connected to the GND rail of the breadboard.
 * Note: Components in the same column are electrically connected.
 */

#define RedLed 2
#define BlueLed 3

void setup() {
  // Configure both digital pins as outputs to provide voltage
  pinMode(RedLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
}

void loop() {
  // --- Sequence 1 ---
  // Turn Red LED ON and Blue LED OFF
  digitalWrite(RedLed, HIGH);
  digitalWrite(BlueLed, LOW);
  delay(200); // Wait 200 milliseconds

  // --- Sequence 2 ---
  // Turn Red LED OFF and Blue LED ON
  digitalWrite(RedLed, LOW);
  digitalWrite(BlueLed, HIGH);
  delay(200); // Wait 200 milliseconds
}
