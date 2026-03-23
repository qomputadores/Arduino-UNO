/*
 * Author: Iwan
 * Project: 10 Gas System Anode
 * Learning Objective: Implement Dynamic Speed Breathing using Inverse 
 * PWM Logic for Common Anode RGB LEDs.
 */

#define GasSensorPin A0  
#define RedPin 9         
#define GreenPin 10      
#define BluePin 11       
#define BuzzerPin 5      

#define LowThreshold 150
#define WarningThreshold 400
#define DangerThreshold 750

int GasValue = 0;        
int Brightness = 0;      
int FadeAmount = 5; 

void setup() {
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
}

void loop() {
  GasValue = analogRead(GasSensorPin);

  // Update brightness step
  Brightness = Brightness + FadeAmount;
  if (Brightness <= 0 || Brightness >= 255) {
    FadeAmount = -FadeAmount; 
  }

  /* * INVERSE LOGIC CALCULATION:
   * Since Anode is at 5V, 255 (HIGH) stops current = LED OFF.
   * 0 (LOW) allows full current = LED FULL ON.
   */
  int InvBright = 255 - Brightness; // Maps 0-255 to 255-0
  int FullOff = 255;                // Value to ensure channel is OFF
  int FullOn = 0;                   // Value to ensure channel is MAX ON

  // STATE 4: DANGER (Static Red)
  if (GasValue >= DangerThreshold) {
    analogWrite(RedPin, FullOn);    // Max brightness (Red)
    analogWrite(GreenPin, FullOff); // Channel OFF
    analogWrite(BluePin, FullOff);  // Channel OFF
    tone(BuzzerPin, 2500);          // High-pitch alarm
  }
  // STATE 3: WARNING (Fast Orange Breathing)
  else if (GasValue >= WarningThreshold) {
    FadeAmount = (FadeAmount > 0) ? 15 : -15; // Set fast speed
    analogWrite(RedPin, InvBright);           // Pulse Red
    analogWrite(GreenPin, 255 - (Brightness / 4)); // Pulse Green dimmer
    analogWrite(BluePin, FullOff);  
    if(Brightness > 200) tone(BuzzerPin, 1000);
    else noTone(BuzzerPin);
  }
  // STATE 2: SAFE (Moderate Green Breathing)
  else if (GasValue >= LowThreshold) {
    FadeAmount = (FadeAmount > 0) ? 5 : -5; // Set normal speed
    analogWrite(RedPin, FullOff);   
    analogWrite(GreenPin, InvBright);       // Pulse Green
    analogWrite(BluePin, FullOff);  
    noTone(BuzzerPin);
  }
  // STATE 1: STANDBY (Slow Blue Breathing)
  else {
    FadeAmount = (FadeAmount > 0) ? 2 : -2; // Set slow speed
    analogWrite(RedPin, FullOff);   
    analogWrite(GreenPin, FullOff); 
    analogWrite(BluePin, InvBright);       // Pulse Blue
    noTone(BuzzerPin);
  }

  delay(30); 
}