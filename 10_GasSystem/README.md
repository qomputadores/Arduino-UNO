# Project 10: Dynamic Atmospheric Security UI (Variable Speed Fade)

## 1. Description
This project focuses on advanced User Experience (UX) design for embedded systems. The system communicates the urgency of gas concentration through the **frequency of the breathing effect**. Students will learn to manipulate PWM timing dynamically, creating a psychological hierarchy of alerts: slow for standby, moderate for safety, fast for warning, and static-high for danger.

## 2. Hardware Anatomy (Physics/Theory)

### RGB LED Architecture & Identification
The longest pin is the common terminal. Connectivity depends on the internal semiconductor structure:
* **Common Cathode (CC):** Shared negative terminal. Connect to GND. Uses Direct Logic (PWM 255 = Max Brightness).
* **Common Anode (CA):** Shared positive terminal. Connect to 5V. Uses Inverse Logic (PWM 0 = Max Brightness, PWM 255 = OFF).

### Dynamic Fade Frequency (The "Breathing" Speed)
The variable FadeAmount determines how much the brightness changes in each loop cycle (30ms).
* **Blue (Languid):** Low step value (+/- 2). Creates a calm pulse suitable for standby or sensor warm-up.
* **Green (Normal):** Moderate step (+/- 5). Indicates stable and safe operation.
* **Orange (Agitated):** High step (+/- 15). Generates visual tension, alerting of an increasing gas trend.
* **Red (Critical):** Step becomes irrelevant as the LED stays at 100% duty cycle for maximum visibility and immediate reaction.

### Buzzer Varieties
* **Raw Component:** Must be connected with correct polarity (Positive to D5).
* **Buzzer Module:** Use the Signal (S) pin to D5. Supports 1000Hz and 2500Hz frequencies for tone distinction.

## 3. Library Methods
* analogWrite(pin, value): Modulates the LED brightness via Pulse Width Modulation.
* tone(pin, frequency): Generates audible square waves for the alarm.
* analogRead(pin): Samples the MQ-2 analog voltage output.

## 4. Power/Safety Protocols
1. **PWM Pin Check:** RGB control MUST be connected to pins 9, 10, or 11 (marked with ~).
2. **Current Limits:** 220 Ohm resistors are mandatory for each color channel.
3. **Common GND:** Ensure the Buzzer and Sensor share the same Ground rail as the Arduino.
4. **Calibration Window:** The Blue "Standby" state is ideal for the 60-second MQ-2 preheating period.

## 5. Connection Table
+-----------------------+------------------+-------------------+
|   COMPONENT PIN       |   ARDUINO PIN    |      FUNCTION     |
+-----------------------+------------------+-------------------+
|   Mq2 Ao              |   A0             |  Analog Input     |
|   RGB Common (Long)   |   5V / GND       |  Power Reference  |
|   RGB Red Pin         |   D9 (PWM)       |  Red Modulation   |
|   RGB Green Pin       |   D10 (PWM)      |  Green Modulation |
|   RGB Blue Pin        |   D11 (PWM)      |  Blue Modulation  |
|   Buzzer Signal (+/S) |   D5 (PWM)       |  Alert Output     |
+-----------------------+------------------+-------------------+

---
**This material is for classroom use only. Commercial distribution is strictly prohibited.**

**Author: Iwan**