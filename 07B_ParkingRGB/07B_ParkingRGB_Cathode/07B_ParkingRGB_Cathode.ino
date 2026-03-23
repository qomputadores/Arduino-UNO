/*
 * Author: Iwan
 * Project: 07B Parking RGB Cathode
 * Learning Objective: Combine sensor-driven color mapping with 
 * a dynamic "breathing" effect (fading) for long distances.
 */

#define TRIG_PIN 9
#define ECHO_PIN 10
#define RED_PIN 11   
#define GREEN_PIN 6  
#define BLUE_PIN 5   
#define BUZZER_PIN 3 

long duration;
int distance;

// Variables for the Blue "Rainbow/Breathing" effect
int blueBrightness = 0;
int fadeAmount = 5; 

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
  // --- SENSOR READING ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  int redIntensity = 0;
  int greenIntensity = 0;
  int blueIntensity = 0;

  // --- LOGIC MODES ---
  
  if (distance > 100) {
    // MODE: STANDBY (Dynamic Blue Pulse)
    blueIntensity = blueBrightness;
    
    // Change brightness for the next frame
    blueBrightness = blueBrightness + fadeAmount;

    // Reverse direction at the limits
    if (blueBrightness <= 0 || blueBrightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    noTone(BUZZER_PIN);
  } 
  else if (distance <= 100 && distance > 50) {
    // MODE: SAFE (Transition Blue to Green)
    blueIntensity = map(distance, 50, 100, 0, 255);
    greenIntensity = map(distance, 50, 100, 255, 0);
    noTone(BUZZER_PIN);
  }
  else if (distance <= 50 && distance > 20) {
    // MODE: WARNING (Transition Green to Red)
    greenIntensity = map(distance, 20, 50, 0, 255);
    redIntensity = map(distance, 20, 50, 255, 0);
    tone(BUZZER_PIN, 1000, 20); 
  } 
  else {
    // MODE: DANGER (Solid Red)
    redIntensity = 255;
    tone(BUZZER_PIN, 2000); 
  }

  // Apply PWM values
  analogWrite(RED_PIN, redIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
  analogWrite(BLUE_PIN, blueIntensity);

  // Telemetry
  Serial.print("Dist:");
  Serial.print(distance);
  Serial.print(",");
  Serial.print("Blue_Pulse:");
  Serial.println(blueIntensity);

  delay(30); // Slightly faster for smoother blue fading
}