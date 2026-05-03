/*
 * Author: Iwan
 * Project: 12 Smart Garage Access
 * Learning Objective: Master multi-state logic, synchronized motor control, 
 * and safety signaling protocols using non-blocking delays.
 */

#include <Servo.h>

// --- TECHNICAL CONNECTION DIAGRAM ---
// | COMPONENT      | ARDUINO PIN | NOTES                                      |
// |----------------|-------------|--------------------------------------------|
// | Trig (HC-SR04) | 7           | Output trigger for ultrasonic sound waves  |
// | Echo (HC-SR04) | 8           | Input to measure travel time of sound waves|
// | Red Pin (RGB)  | 11          | PWM pin for red channel (Common Cathode)   |
// | Green Pin (RGB)| 6           | PWM pin for green channel (Common Cathode) |
// | Blue Pin (RGB) | 5           | PWM pin for blue channel (Common Cathode)  |
// | Buzzer         | 3           | Active buzzer for acoustic feedback        |
// | Servo Signal   | 9           | Native PWM for high-stability motor control|
// +----------------+-------------+--------------------------------------------+

// Pin definitions using #define for memory efficiency
#define TrigPin 7
#define EchoPin 8
#define RedPin 11   
#define GreenPin 6  
#define BluePin 5   
#define BuzzerPin 3 
#define ServoPin 9

// Global object and variables
Servo GateServo;        // Create a servo object to control the motor
long Duration;          // Variable to store the travel time of sound pulses
int Distance;           // Variable to store the calculated distance in cm

// Variables for the Blue "Breathing" standby effect
int BlueBrightness = 0; // Current PWM value for the blue LED
int FadeAmount = 5;     // Step size for increasing/decreasing brightness

void setup() {
  // Configure pin modes for sensors and actuators
  pinMode(TrigPin, OUTPUT);  // Sensor sends out the pulse
  pinMode(EchoPin, INPUT);   // Sensor receives the bounce (echo)
  pinMode(RedPin, OUTPUT);   // Control red light intensity
  pinMode(GreenPin, OUTPUT); // Control green light intensity
  pinMode(BluePin, OUTPUT);  // Control blue light intensity
  pinMode(BuzzerPin, OUTPUT);// Control acoustic alarm
  
  // Attach the servo and set initial position
  GateServo.attach(ServoPin);
  GateServo.write(0);        // Initialize the gate in the CLOSED position (0 deg)
  
  // Start serial communication for telemetry monitoring
  Serial.begin(9600);
}

void loop() {
  // --- STEP 1: ULTRASONIC SENSOR READING ---
  // Send a 10-microsecond pulse to trigger the sensor
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  // Measure the duration of the incoming pulse in microseconds
  Duration = pulseIn(EchoPin, HIGH);
  
  // Calculate distance: Time * Speed of Sound / 2 (for the return trip)
  Distance = Duration * 0.034 / 2;

  // Initialize LED intensity variables to 0 (off) in every loop cycle
  int RedIntensity = 0;
  int GreenIntensity = 0;
  int BlueIntensity = 0;

  // --- STEP 2: LOGICAL CONTROL MODES ---
  
  // MODE 1: STANDBY - No object detected near the gate
  if (Distance > 100) {
    GateServo.write(0);                    // Ensure gate is closed
    BlueIntensity = BlueBrightness;         // Apply current breathing brightness
    BlueBrightness = BlueBrightness + FadeAmount; // Update brightness for next loop
    
    // Reverse fading direction when limits (0 or 255) are reached
    if (BlueBrightness <= 0 || BlueBrightness >= 255) {
      FadeAmount = -FadeAmount;
    }
    noTone(BuzzerPin);                     // Silence the buzzer
  } 
  
  // MODE 2: ACCESS - Vehicle detected within 100cm (Door starts opening)
  else if (Distance <= 100 && Distance > 80) {
    GateServo.write(90);                   // Open the gate (90 degrees)
    BlueIntensity = map(Distance, 80, 100, 0, 255); // Dynamic blue light based on distance
    noTone(BuzzerPin);
  }
  
  // MODE 3: SAFE - Entry in progress (Transition Blue to Green)
  else if (Distance <= 80 && Distance > 50) {
    GateServo.write(90);                   // Keep gate open
    BlueIntensity = map(Distance, 50, 80, 0, 255);  // Fade out blue
    GreenIntensity = map(Distance, 50, 80, 255, 0); // Fade in green
    noTone(BuzzerPin);
  }
  
  // MODE 4: WARNING - Vehicle getting closer (Transition Green to Red)
  else if (Distance <= 50 && Distance > 20) {
    GateServo.write(90);                   // Keep gate open
    GreenIntensity = map(Distance, 20, 50, 0, 255); // Fade out green
    RedIntensity = map(Distance, 20, 50, 255, 0);   // Fade in red
    tone(BuzzerPin, 1000, 20);             // Beep at 1000Hz for 20ms
  } 
  
  // MODE 5: DANGER - Stopping zone reached (Gate stays open for parking)
  else if (Distance <= 20 && Distance > 10) {
    GateServo.write(90);                   // Keep gate open for final maneuver
    RedIntensity = 255;                    // Solid red alert
    tone(BuzzerPin, 2000);                 // Constant high-pitch alarm
  }
  
  // MODE 6: PROTOCOL: SECURE CLOSING - Activation at < 10cm threshold
  else {
    // FASE A: 5-Second Security Warning (Blinking Red Light)
    // 10 cycles of 500ms (250ms ON + 250ms OFF) = 5 seconds
    for (int i = 0; i < 10; i++) { 
      analogWrite(RedPin, 255);            // Red ON
      analogWrite(GreenPin, 0);
      analogWrite(BluePin, 0);
      delay(250);
      analogWrite(RedPin, 0);              // Red OFF
      delay(250);
    }

    // FASE B: 5-Second Slow Closing (Siren Effect + Smooth Motion)
    // Decrementing from 90 to 0 degrees to close slowly
    for (int Angle = 90; Angle >= 0; Angle--) {
      GateServo.write(Angle);              // Move servo to the specific current degree
      
      // Police Siren logic: Alternates Red and Blue using Modulo operator
      if (Angle % 2 == 0) {
        analogWrite(RedPin, 255);          // Red ON
        analogWrite(BluePin, 0);           // Blue OFF
      } else {
        analogWrite(RedPin, 0);            // Red OFF
        analogWrite(BluePin, 255);         // Blue ON
      }
      // 55ms per degree * 90 degrees = 4950ms (~5 seconds total)
      delay(55); 
    }
    
    // Final Locked State configuration
    noTone(BuzzerPin);                     // Stop sound
    analogWrite(RedPin, 255);              // Set LED to solid red (Secure)
    analogWrite(BluePin, 0);
    delay(2000);                           // Short pause to finalize protocol
  }

  // --- STEP 3: OUTPUT EXECUTION ---
  // Apply calculated PWM intensities to the RGB LED pins
  // (Note: This is skipped during the Secure Closing for-loops)
  if (Distance > 10) {
    analogWrite(RedPin, RedIntensity);
    analogWrite(GreenPin, GreenIntensity);
    analogWrite(BluePin, BlueIntensity);
  }

  // --- STEP 4: TELEMETRY AND DEBUGGING ---
  Serial.print("Dist:");
  Serial.print(Distance);
  Serial.print(" cm | Status: ");
  // Ternary operator to print current state in the serial monitor
  Serial.println(Distance <= 10 ? "PROTOCOL ACTIVE" : "OPERATIONAL");

  delay(30); // Global delay for loop stability and smooth pulse effect
}
