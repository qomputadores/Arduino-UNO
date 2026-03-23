/*
 * Author: Iwan
 * Project: 06B RGB Led Rainbow Cathode
 * Learning Objective: Introduction to 'for' loops and 'random' functions.
 */

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

int timer = 10;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // randomSeed 'stirs' the random number generator using
  // electrical noise from an empty analog pin (A0).
  randomSeed(analogRead(0));
}

void loop() {
  // --- PHASE 1: RAINBOW (Automatic fade) ---
  // The 'for' loop repeats the code 256 times automatically.
  for (int i = 0; i <= 255; i++) {
    analogWrite(RED_PIN, 255 - i);
    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, 0);
    delay(timer);
  }

  // (Other color transitions follow the same 'for' logic)

  // --- PHASE 2: RANDOM STROBE (5 Seconds) ---
  // This loop runs 10 times. Each cycle is 500ms (250 ON + 250 OFF).
  // Total: 10 * 500ms = 5000ms = 5 Seconds.
  for (int count = 0; count < 10; count++) {
    // random(0, 256) picks a number between 0 and 255.
    analogWrite(RED_PIN, random(0, 256));
    analogWrite(GREEN_PIN, random(0, 256));
    analogWrite(BLUE_PIN, random(0, 256));
    delay(250);

    // Turn all OFF for the flashing effect
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
    delay(250);
  }
}