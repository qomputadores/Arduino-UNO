/*
 * Author: Iwan
 * Project: 06B RGB Led Rainbow Anode
 * Learning Objective: Master PWM with Inverse Logic (Anode) 
 * using 'for' loops and 'random' functions.
 */

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

int timer = 10; 

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // We seed the random generator with noise from A0
  randomSeed(analogRead(0)); 
}

void loop() {
  // --- PHASE 1: RAINBOW (Inverse Logic PWM) ---
  
  // From Red to Yellow
  // Red stays ON (0), Green fades ON (255 down to 0)
  for (int i = 255; i >= 0; i--) {
    analogWrite(RED_PIN, 0); 
    analogWrite(GREEN_PIN, i); 
    analogWrite(BLUE_PIN, 255); 
    delay(timer);
  }

  // From Yellow to Green
  // Green stays ON (0), Red fades OFF (0 up to 255)
  for (int i = 0; i <= 255; i++) {
    analogWrite(RED_PIN, i); 
    analogWrite(GREEN_PIN, 0); 
    analogWrite(BLUE_PIN, 255); 
    delay(timer);
  }

  // From Green to Cyan
  // Green stays ON (0), Blue fades ON (255 down to 0)
  for (int i = 255; i >= 0; i--) {
    analogWrite(RED_PIN, 255); 
    analogWrite(GREEN_PIN, 0); 
    analogWrite(BLUE_PIN, i); 
    delay(timer);
  }

  // --- PHASE 2: RANDOM STROBE (5 Seconds) ---
  // 10 repetitions * 500ms (250 ON + 250 OFF) = 5 seconds
  for (int count = 0; count < 10; count++) {
    
    // Random color: 0 is bright, 255 is dark (Inverse)
    analogWrite(RED_PIN, random(0, 256));
    analogWrite(GREEN_PIN, random(0, 256));
    analogWrite(BLUE_PIN, random(0, 256));
    delay(250); 
    
    // Turn all OFF (In Anode, 255 is 5V, so no current flows)
    analogWrite(RED_PIN, 255);
    analogWrite(GREEN_PIN, 255);
    analogWrite(BLUE_PIN, 255);
    delay(250); 
  }
}