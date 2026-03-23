/*
 * Author: Iwan
 * Project: 04_ActiveBuzzer
 * Learning Objective: To control an acoustic actuator using tone/noTone 
 * and understanding frequency-based digital signals.
 */

/*
 * Connections:
 * [Option A: Standalone Component]
 * 1. Anode (+): Pin 4.
 * 2. Cathode (-): GND.
 * * [Option B: 3-Pin Module]
 * 1. VCC (+): Arduino 5V (Constant power for the internal oscillator).
 * 2. GND (-): Arduino GND.
 * 3. Signal (S / I/O): Arduino Pin 4 (Control signal).
 */

#define ActiveBuzzer 4

void setup() {
  // Configures the pin to send the square wave signal
  pinMode(ActiveBuzzer, OUTPUT);
}

void loop() {
  /* * tone(pin, frequency):
   * This function triggers a square wave of a specific frequency (Hertz).
   * It uses the Arduino's internal timers to toggle the pin HIGH and LOW 
   * hundreds or thousands of times per second.
   */
  tone(ActiveBuzzer, 1000); 
  delay(500); // Sound duration

  /* * noTone(pin):
   * This function explicitly stops the wave generation on the pin.
   * Unlike digitalWrite(LOW), it ensures the internal timer is released
   * and the pin returns to a 0V state without residual pulses.
   */
  noTone(ActiveBuzzer);
  delay(1000); // Silence duration
}
