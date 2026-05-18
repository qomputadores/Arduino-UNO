/*
 * Author: Iwan
 * Project: 14 Residencial Access Integration
 * Learning Objective: Integrate matrix keypads, ultrasonic sensors, and servos 
 * into a single multi-stage security protocol using non-blocking state logic.
 */

/*
 * +-------------------------------------------------------------------------+
 * |                     TECHNICAL CONNECTION MAP (DATA ONLY)                |
 * +-----------------------+-------------------+-----------------------------+
 * |   HARDWARE COMPONENT  | ARDUINO PIN (UNO) |         PIN TYPE            |
 * +-----------------------+-------------------+-----------------------------+
 * |   Ultrasonic Trig     | D7                | Digital Output              |
 * |   Ultrasonic Echo     | D8                | Digital Input               |
 * |   RGB LED Red Anode   | D11 (PWM)         | Analog Output (PWM)         |
 * |   RGB LED Green Anode | D6 (PWM)          | Analog Output (PWM)         |
 * |   RGB LED Blue Anode  | D5 (PWM)          | Analog Output (PWM)         |
 * |   Active Buzzer (+)   | D3 (PWM)          | Analog Output (PWM / tone)  |
 * |   Servo Motor Signal  | D9 (PWM)          | Dedicated Hardware PWM      |
 * |   Keypad Row 1        | A0                | Analog used as Digital I/O  |
 * |   Keypad Row 2        | A1                | Analog used as Digital I/O  |
 * |   Keypad Row 3        | A2                | Analog used as Digital I/O  |
 * |   Keypad Row 4        | A3                | Analog used as Digital I/O  |
 * |   Keypad Column 1     | A4                | Analog used as Digital I/O  |
 * |   Keypad Column 2     | A5                | Analog used as Digital I/O  |
 * |   Keypad Column 3     | D4                | Digital I/O                 |
 * +-----------------------+-------------------+-----------------------------+
 */

#include <Servo.h>
#include <Keypad.h>

// --- Pin Definitions using Preprocessor Macros ---
#define TrigPin 7
#define EchoPin 8
#define RedPin 11   
#define GreenPin 6  
#define BluePin 5   
#define BuzzerPin 3 
#define ServoPin 9

// --- Keypad Configuration parameters ---
const byte ROWS = 4; // Four rows on the membrane keypad
const byte COLS = 3; // Three columns on the membrane keypad

// Character map matrix matching the physical 3x4 layout [cite: 1]
char Keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Physical pin mapping: Analog pins A0-A5 are configured as digital inputs/outputs
byte RowPins[ROWS] = {A0, A1, A2, A3}; 
byte ColPins[COLS] = {A4, A5, 4};

// Instantiate the Keypad object with the customized pin and matrix definitions
Keypad MatrixKeypad = Keypad(makeKeymap(Keys), RowPins, ColPins, ROWS, COLS);

// --- Security System Memory Registers ---
const char MasterPassword[7] = "123456"; // System authorization master key
char EnteredPassword[7];                 // Array buffer to store real-time keypresses
byte PasswordIndex = 0;                  // Tracker position for the array buffer

// --- Actuator & Sensor Global Objects ---
Servo GateServo;        // Instantiation of the servo control instance
long Duration;          // Holds the acoustic pulse round-trip travel time in microseconds
int Distance;           // Calculated real-time metric distance value in centimeters

// --- Interface State and PWM Variables ---
int BlueBrightness = 0;      // Dynamic counter for the standby pulsing effect
int FadeAmount = 5;          // Step modifier determining breathing fading speed
bool IsKeypadActive = false; // State flag behavior: locks ultrasonic sensor during authentication

void setup() {
  // Define peripheral pin operational directions
  pinMode(TrigPin, OUTPUT);  // Sends high-frequency ultrasound bursts
  pinMode(EchoPin, INPUT);   // Captures the returning acoustic echo bounce
  pinMode(RedPin, OUTPUT);   // Drives the Red channel of the RGB LED
  pinMode(GreenPin, OUTPUT); // Drives the Green channel of the RGB LED
  pinMode(BluePin, OUTPUT);  // Drives the Blue channel of the RGB LED
  pinMode(BuzzerPin, OUTPUT);// Drives current to the active alert buzzer
  
  // Attach servo communication link and force home position execution
  GateServo.attach(ServoPin);
  GateServo.write(0); // Initialize access gate barrier at CLOSED state (0 degrees)
  
  // Establish hardware terminal baud rate communication
  Serial.begin(9600);
  Serial.println("==================================================");
  Serial.println("     RESIDENTIAL SECURITY ACCESS SYSTEM ACTIVE    ");
  Serial.println("==================================================");
}

void loop() {
  // --- STEP 1: ULTRASONIC TELEMETRY DATA ACQUISITION ---
  // Generate a clean 10-microsecond trigger pulse to initiate the sensor cycle
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  // Read the pulse length reflection time; store raw data in microseconds
  Duration = pulseIn(EchoPin, HIGH);
  
  // Physics formula translation: Distance = (Time * Speed of Sound) / 2
  Distance = Duration * 0.034 / 2;

  // Local buffer allocation: Initialize all light channel intensities to zero
  int RedIntensity = 0;
  int GreenIntensity = 0;
  int BlueIntensity = 0;

  // --- STEP 2: STATE SELECTION ARCHITECTURE ---
  
  // STATE 1: STANDBY (No vehicle detected within perimeter boundaries)
  if (Distance > 100) {
    IsKeypadActive = false; // System baseline reset
    GateServo.write(0);     // Rigid lock enforcement at 0 degrees
    
    // Execute smooth math calculation for the Blue breathing pulse effect
    BlueIntensity = BlueBrightness;         
    BlueBrightness = BlueBrightness + FadeAmount; 
    
    // Reverse fade polarity automatically upon hitting intensity ceiling or floor
    if (BlueBrightness <= 0 || BlueBrightness >= 255) {
      FadeAmount = -FadeAmount;
    }
    noTone(BuzzerPin); // Ensure acoustic silencing
  } 
  
  // STATE 2: APPROACHING SECURITY CHECKPOINT (Vehicle enters 100cm boundary)
  else if (Distance <= 100 && Distance > 80) {
    IsKeypadActive = false;
    GateServo.write(0); // Gate stays locked down
    
    // Fade Blue proportional to distance: brighter as the car approaches 80cm
    BlueIntensity = map(Distance, 80, 100, 0, 255); 
    noTone(BuzzerPin);
  }
  
  // STATE 3: SAFE APPROACH SEGMENT (Transitioning from Blue into Green)
  else if (Distance <= 80 && Distance > 50) {
    IsKeypadActive = false;
    GateServo.write(0);
    
    // Linear Cross-fade logic: fades out Blue channel while intensifying Green
    BlueIntensity = map(Distance, 50, 80, 0, 255);  
    GreenIntensity = map(Distance, 50, 80, 255, 0); 
    noTone(BuzzerPin);
  }
  
  // STATE 4: CRITICAL PROXIMITY WARNING (Transitioning from Green into Red)
  else if (Distance <= 50 && Distance > 20) {
    IsKeypadActive = false;
    GateServo.write(0);
    
    // Linear Cross-fade logic: transitions illumination state from Green to Red
    GreenIntensity = map(Distance, 20, 50, 0, 255); 
    RedIntensity = map(Distance, 20, 50, 255, 0);   
    
    // Trigger acoustic warning bleep pulses synchronized with cycle rates
    tone(BuzzerPin, 1000, 20);             
  } 
  
  // STATE 5: INTERACTIVE SECURITY CHECKPOINT (Vehicle stopped at identification pad)
  else if (Distance <= 20 && Distance > 10) {
    RedIntensity = 255; // Static Solid Red alert meaning: STOP VEHICLE HERE
    noTone(BuzzerPin);
    
    // Flag validation check: prints prompt message exactly once upon entry
    if (!IsKeypadActive) {
      Serial.println("\n[SYSTEM]: VEHICLE STOPPED. Please input 6-digit access code:");
      PasswordIndex = 0;       // Buffer index flush
      IsKeypadActive = true;   // Engages software lock
    }
    
    // Delegate processor control execution to security authentication routine
    ExecuteSecurityCheck();
  }
  
  // STATE 6: PROTOCOL ENFORCEMENT: SECURE CLOSING (Activated under 10cm threshold)
  else {
    IsKeypadActive = false; // Disengage identification subroutines
    ExecuteSecureClosing(); // Initiate heavy-duty mechanical automated closure
  }

  // --- STEP 3: OUTPUT PERIPHERAL EXECUTION ---
  // Update hardware pin states using calculated PWM variables
  // Execution bypass: Ignored during manual code verification locks or closing loops
  if (Distance > 10 && !IsKeypadActive) {
    SetLedHardware(RedIntensity, GreenIntensity, BlueIntensity);
  }
  
  delay(30); // Establishes internal loop pacing and steady PWM transitions
}

// --- INTEGRATED SECURITY SUBROUTINES ---

void ExecuteSecurityCheck() {
  // Query matrix intersection scanner array register
  char KeyInput = MatrixKeypad.getKey();
  
  // Condition check: processes action only if a physical keypress event occurs
  if (KeyInput) {
    // Structural filter: completely ignores control keys '*' and '#' during input
    if (KeyInput != '*' && KeyInput != '#') {
      EnteredPassword[PasswordIndex] = KeyInput; // Store character into buffer
      PasswordIndex++;                           // Advance tracker pointer
      Serial.print("*");                         // Data protection masking character
      
      // Short interactive tactile frequency click confirmation tone
      tone(BuzzerPin, 1200, 50);
      
      // Evaluation barrier reached: exactly 6 characters compiled
      if (PasswordIndex == 6) {
        EnteredPassword[PasswordIndex] = '\0'; // Append crucial string null-terminator
        Serial.println(""); 
        
        // String comparison evaluation operation using strcmp()
        if (strcmp(EnteredPassword, MasterPassword) == 0) {
          Serial.println("[STATUS]: ACCESS GRANTED - OPENING RESIDENTIAL GATE");
          
          // Authentication success feedback sequence: Blinking Green Light
          for(int I = 0; I < 3; I++) {
            SetLedHardware(0, 255, 0); tone(BuzzerPin, 1500, 100); delay(150);
            SetLedHardware(0, 0, 0); delay(150);
          }
          
          GateServo.write(180);       // Actuate mechanical gate arm to full open limits
          SetLedHardware(0, 255, 0);  // Display solid success Green
          delay(3000);                // Structural pause allowing car to safely traverse clearance
          
        } else {
          Serial.println("[STATUS]: ACCESS DENIED - INCORRECT CODE");
          
          // Authentication failure feedback sequence: Fast Red Flash + Low Siren
          for(int I = 0; I < 5; I++) {
            SetLedHardware(255, 0, 0); tone(BuzzerPin, 500, 100); delay(100);
            SetLedHardware(0, 0, 0); delay(100);
          }
        }
        PasswordIndex = 0;       // Reset array pointer index for future inputs
        IsKeypadActive = false;  // Release software lock to re-enable ultrasonic scanning
      }
    }
  }
}

void ExecuteSecureClosing() {
  // PHASE A: 5-Second Blinking Red Warning Signal (10 cycles of 250ms ON + 250ms OFF)
  for (int I = 0; I < 10; I++) { 
    SetLedHardware(255, 0, 0);
    delay(250);
    SetLedHardware(0, 0, 0);
    delay(250);
  }

  // PHASE B: 5-Second Slow Motion Mechanical Descent (Siren Effect from 180 to 0 degrees)
  for (int Angle = 180; Angle >= 0; Angle--) {
    GateServo.write(Angle); // Relocate mechanical position index decrementally
    
    // Police Siren logic: alternate Red and Blue channels using the Modulo division remainder
    if (Angle % 2 == 0) {
      SetLedHardware(255, 0, 0); // Active high Red state
    } else {
      SetLedHardware(0, 0, 255); // Active high Blue state
    }
    // Execution velocity tuning: 27ms * 180 steps = 4860 milliseconds total duration
    delay(27); 
  }
  
  noTone(BuzzerPin);          // Terminate acoustic output lines
  SetLedHardware(255, 0, 0);  // Enforce secure solid red lockout state
  delay(2000);                // Protocol cooling cycle delay
}

void SetLedHardware(int R, int G, int B) {
  /*
   * INSTRUCTION FOR STUDENTS:
   * COMMON CATHODE (Default Kit): Use parameters directly (R, G, B).
   * COMMON ANODE Kit Alternative: Invert current fields using subtraction math:
   * analogWrite(RedPin, 255 - R); etc.
   */
  analogWrite(RedPin, R);
  analogWrite(GreenPin, G);
  analogWrite(BluePin, B);
}