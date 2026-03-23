/*
 * Author: Iwan
 * Project: 05 Ultrasonic Sensor
 * Learning Objective: Understanding micro-timing, sensor pin roles, 
 * and memory capacity of different variable types.
 */

#define TrigPin 5
#define EchoPin 6

/* * DATA TYPES CAPACITY (Real values):
 * 1. int (16-bit): Can store from -32,768 to 32,767. 
 * Perfect for 'Distance' (usually 2 to 400 cm).
 * 2. long (32-bit): Can store from -2,147,483,648 to 2,147,483,647.
 * Necessary for 'Duration' because sound time is measured in 
 * millionths of a second (microseconds).
 */
long Duration;
int Distance;

void setup() {
  Serial.begin(9600);

  // Trig (Trigger) is an OUTPUT because it sends the sound wave
  pinMode(TrigPin, OUTPUT);

  // Echo is an INPUT because it "listens" for the returning sound wave
  pinMode(EchoPin, INPUT);
}

void loop() {
  // --- TRIGGERING THE SONAR PULSE ---
  // We start with LOW to ensure a clean "silent" start
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);

  // We send a pulse for exactly 10 microseconds.
  // Why Microseconds? Because sound is so fast that we need
  // a scale 1,000,000 times smaller than a second to be precise.
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  // --- MEASURING THE ECHO ---
  // pulseIn measures the time (in microseconds) it takes for the
  // sound to bounce back. It waits for the Echo pin to go HIGH.
  Duration = pulseIn(EchoPin, HIGH);

  // --- CALCULATION ---
  // 0.034 is the speed of sound in cm per microsecond.
  // We divide by 2 because the sound traveled to the object AND back.
  Distance = Duration * 0.034 / 2;

  // --- VISUALIZATION (Serial Plotter Format) ---
  Serial.print("Distance:");
  Serial.print(Distance);
  Serial.print(",");
  Serial.print("Base_0:0,");
  Serial.print("Ref_5:5,");
  Serial.print("Warning_20:20,");
  Serial.print("Max_100:");
  Serial.println(100);

  delay(100);  // 0.1s pause to make the graph readable
}