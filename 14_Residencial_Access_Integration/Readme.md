Project: 14 Residencial Access Integration

1. Description

This project simulates an advanced residential access checkpoint with two levels of tactical verification: proximity assessment and credential validation. It integrates an HC-SR04 ultrasonic sensor to measure a vehicle's distance in real time and a 3x4 matrix keypad matrix for password authentication. A 180-degree servo motor controls the residential gate, clearing it for linear horizontal traversal only when a correct 6-digit access code is verified.

2. Learning Objectives

System Integration: Combine complex input matrices, acoustic actuators, and motor controls into a single non-blocking logic flow.
State Lock Protocols: Implement code flag indicators to temporarily halt sensor acquisition while awaiting manual user input.
Hardware Optimization: Master the utilization of analog pins as high-stability digital inputs/outputs to maximize microcontroller resources.

3. How the "Access Logic" Works

The system shifts between 6 specific operational modes based on the real-time distance calculations of the approaching vehicle:

Mode | Distance | Visual Alert | Acoustic Alert | Gate Status
--- | --- | --- | --- | ---
Standby | > 100 cm | Blue Breathing Effect | Silent | Locked (0 deg)
Approach | 80 - 100 cm | Proportional Blue LED | Silent | Locked (0 deg)
Safe Zone | 50 - 80 cm | Blue-to-Green Crossfade | Silent | Locked (0 deg)
Warning | 20 - 50 cm | Green-to-Red Crossfade | Intermittent Beep | Locked (0 deg)
Checkpoint | 10 - 20 cm | Solid Red LED Alert | Silent (Awaiting Code) | Verification Lock
Secure Closing | < 10 cm | Fast Blinking Red / Police Siren | Emergency Sequence | Decremental Close (180 to 0)

* Note on Checkpoint Mode: Once the vehicle stops, the Serial Monitor requests the 6-digit code. Access Granted triggers a blinking Green light with high success tones and opens the gate to 180 degrees for 3 seconds. Access Denied triggers a fast blinking Red light with low error tones and resets the interface.
* Note on Secure Closing Protocol: Moving under 10 cm automatically engages Phase A (5 seconds of blinking Red light warning) followed by Phase B (5 seconds of slow motion servo descent with an alternating Red/Blue police siren effect using modulo arithmetic).

4. Hardware Requirements

Microcontroller: Arduino Uno R3.
Sensors/Inputs: 1x HC-SR04 Ultrasonic Sensor, 1x 3x4 Membrane Matrix Keypad.
Actuators/Outputs: 1x Micro Servo Motor SG90, 1x RGB LED (Common Cathode default), 1x Active Buzzer.
Protoboard & Jumpers.

5. Connection Details (Data Only)

Component | Arduino Pin | Role
--- | --- | ---
Ultrasonic Trig | Pin 7 | Output Trigger Pulse
Ultrasonic Echo | Pin 8 | Input Echo Reflection
RGB LED Red Channel | Pin 11 | PWM Intensity Control
RGB LED Green Channel | Pin 6 | PWM Intensity Control
RGB LED Blue Channel | Pin 5 | PWM Intensity Control
Active Buzzer (+) | Pin 3 | PWM / Frequency Tone Signal
Servo Motor Signal | Pin 9 | Dedicated Hardware PWM Control
Keypad Row 1 | Pin A0 | Digital Input Row Scanner
Keypad Row 2 | Pin A1 | Digital Input Row Scanner
Keypad Row 3 | Pin A2 | Digital Input Row Scanner
Keypad Row 4 | Pin A3 | Digital Input Row Scanner
Keypad Column 1 | Pin A4 | Digital Output Column Driver
Keypad Column 2 | Pin A5 | Digital Output Column Driver
Keypad Column 3 | Pin 4 | Digital Output Column Driver

* Note for Students with Common Anode LEDs: If you are using a Common Anode RGB LED instead of a Common Cathode, you must modify the parameters inside the SetLedHardware function to use subtraction math (255 - R, 255 - G, 255 - B) to prevent colors from appearing inverted.

6. Telemetry in Serial Monitor

To operate the security validation gate, open the Serial Monitor (Ctrl + Shift + M) at 9600 baud. The terminal will output system status changes. When the vehicle reaches the Checkpoint zone (10-20 cm), a secure input line will open. Type the 6-digit master key ("123456") to trigger the verification parameters.

This material is for classroom use only. Commercial distribution is strictly prohibited.
Author: Iwan