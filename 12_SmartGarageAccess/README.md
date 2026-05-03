# Project 12: Smart Garage Access with Security Protocol

### Description
This project focuses on the implementation of an automated infrastructure system that integrates distance sensing with mechanical actuation and advanced safety signaling. Designed for eighth-grade students, the system simulates a professional garage door controller. It utilizes an ultrasonic sensor to monitor vehicle proximity and a servo motor to manage physical access. The core pedagogical objective is the execution of a multi-stage security protocol: a 5-second preventive warning phase followed by a 5-second synchronized closing sequence. This project transitions from simple reactive logic to complex, time-managed industrial automation.

### Hardware Anatomy (Physics/Theory)
*   **Ultrasonic Wave Propagation (HC-SR04):** The sensor operates on the principle of Time-of-Flight (ToF). It emits an ultrasonic burst (40kHz) that travels through the air, reflects off an object, and returns to the receiver. The distance is calculated using the constant speed of sound ($343 m/s$ in dry air at $20°C$).
*   **Pulse Width Modulation (PWM) Actuation:** The Servo motor and the RGB LED utilize PWM to translate digital signals into analog-like behavior. For the servo, a specific pulse width (typically between 1ms and 2ms) determines the angular position of the internal gears. For the RGB LED, the duty cycle of the PWM signal controls the average voltage delivered to each internal diode (Red, Green, Blue), allowing for color mixing and intensity transitions.
*   **Common Cathode Configuration:** The RGB LED used in this project shares a single ground (GND) pin. Light emission is achieved by sending a positive voltage (HIGH/PWM) to the specific anode pins for each color channel.
*   **Acoustic Transduction:** The active buzzer converts electrical energy into mechanical vibrations at a fixed resonant frequency to provide immediate auditory feedback during warning states.

### Library Methods
*   **Servo.h:**
    *   `attach(pin)`: Assigns the PWM-capable pin to the servo object and initializes the timer interrupts.
    *   `write(angle)`: Sends the command to move the internal potentiometer to a specific degree (0 to 180).
    *   `read()`: Returns the last commanded value of the servo's position.

### Instructions
1.  **System Initialization:** The microcontroller sets the initial gate position to 0° (Closed) and begins the standby "breathing" effect on the Blue LED channel.
2.  **Detection & Access:** When the HC-SR04 detects an object within 100cm, the `GateServo` moves to 90° (Open). The RGB LED maps the distance to a color gradient (Blue -> Green -> Yellow -> Red).
3.  **Security Trigger:** If the distance remains at 10cm or less, the system exits the parking mode and enters the `SECURE CLOSING` protocol.
4.  **Phase A (Warning):** The system executes a 5-second countdown. The Red LED channel blinks at 2Hz (250ms intervals) to signal an imminent mechanical movement.
5.  **Phase B (Closing):** A `for` loop decrements the servo angle from 90° to 0° over 5 seconds. Within the loop, the RGB LED toggles between Red and Blue (Siren Effect) using the modulo operator to ensure visual synchronization without blocking the processor.
6.  **Lockdown:** Once at 0°, the buzzer is silenced, and the LED remains solid Red until the object clears the safety threshold.

### Power/Safety Protocols
*   **Current Sink Management:** Since the Servo, RGB LED, and Buzzer operate simultaneously, the total current draw may approach the limits of the Arduino's 5V regulator. A stable external power source or high-quality USB connection is required.
*   **Common Ground (GND) Rail:** All components MUST share a common ground to prevent signal floating, which causes erratic servo behavior and ultrasonic noise.
*   **Signal Isolation:** The Trigger and Echo pins are kept on digital pins 7 and 8 to avoid interference with the native PWM timers used by the LED (5, 6, 11) and Servo (9).

### Connection Table
| COMPONENT      | ARDUINO PIN | NOTES                                      |
|----------------|-------------|--------------------------------------------|
| Trig (HC-SR04) | 7           | Digital Output (Trigger Pulse)             |
| Echo (HC-SR04) | 8           | Digital Input (Echo Timing)                |
| Red Pin (RGB)  | 11          | PWM Output (Common Cathode)                |
| Green Pin (RGB)| 6           | PWM Output (Common Cathode)                |
| Blue Pin (RGB) | 5           | PWM Output (Common Cathode)                |
| Buzzer         | 3           | Digital Output (Active Alarm)              |
| Servo Signal   | 9           | Native PWM Output (Gate Control)           |

This material is for classroom use only. 
Commercial distribution is strictly prohibited.
Author: Iwan. 