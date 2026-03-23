/*
 * Author: Iwan
 * Project: 04B Buzzer Melody
 * Learning Objective: Advanced rhythmic control using tone/noTone 
 * with precise vertical instruction mapping for beginners.
 */

/*
 * Connections:
 * [Standard 3-Pin Module]
 * 1. VCC (+): Arduino 5V.
 * 2. GND (-): Arduino GND.
 * 3. Signal (S): Arduino Pin 4.
 */

#define ActiveBuzzer 4

void setup() {
  // Define Pin 4 as output for the buzzer signal
  pinMode(ActiveBuzzer, OUTPUT);
}

void loop() {
  // --- SHAVE AND A HAIRCUT ---

  // Note 1: Tun
  tone(ActiveBuzzer, 262); 
  delay(250);
  noTone(ActiveBuzzer);    
  delay(50); 

  // Note 2: Ta
  tone(ActiveBuzzer, 196); 
  delay(125);
  noTone(ActiveBuzzer);    
  delay(50);

  // Note 3: Ta
  tone(ActiveBuzzer, 196); 
  delay(125);
  noTone(ActiveBuzzer);    
  delay(50);

  // Note 4: Tun
  tone(ActiveBuzzer, 220); 
  delay(250);
  noTone(ActiveBuzzer);    
  delay(50);

  // Note 5: Tun (The longer pause before the end)
  tone(ActiveBuzzer, 196); 
  delay(250);
  noTone(ActiveBuzzer);    
  delay(250); 

  // --- THE FINAL "TUN-TUN" ---
  
  // First Tun
  tone(ActiveBuzzer, 247); 
  delay(250);
  noTone(ActiveBuzzer);    
  delay(100); // Critical silence to separate identical frequencies

  // Second Tun
  tone(ActiveBuzzer, 262); 
  delay(250);
  noTone(ActiveBuzzer);

  // Wait 3 seconds before repeating the melody
  delay(3000); 
}