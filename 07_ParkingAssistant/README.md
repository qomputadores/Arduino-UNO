# Project: 07_ParkingAssistant

## 1. Description
This project simulates a professional automotive parking assistant. It integrates the **HC-SR04** ultrasonic sensor to measure distance and provides real-time feedback through a traffic light system (LEDs) and an acoustic alarm (Buzzer).

## 2. Learning Objectives
* **System Integration:** Combine multiple inputs and outputs in a single logic flow.
* **Compound Conditionals:** Use `if`, `else if`, and `else` to manage different safety zones.
* **Telemetry Analysis:** Compare physical behavior (LEDs/Buzzer) with graphical data (Serial Plotter).

## 3. How the "Parking Logic" Works
The system is divided into three zones based on the measured distance:

| Zone | Distance | Visual Alert | Acoustic Alert |
| :--- | :--- | :--- | :--- |
| **Safe** | > 50 cm | Green LED ON | Silent |
| **Warning** | 20 - 50 cm | Yellow LED ON | Intermittent Beep |
| **Danger** | < 20 cm | Red LED ON | Continuous High Tone |



## 4. Hardware Requirements
* **Microcontroller:** Arduino Uno R3.
* **Sensor:** HC-SR04 Ultrasonic Sensor.
* **Outputs:** 3x LEDs (Green, Yellow, Red), 1x Active Buzzer.
* **Resistors:** 3x 220 $\Omega$ (for LEDs).
* **Protoboard & Jumpers.**

## 5. Connection Details
| Component | Arduino Pin | Role |
| :--- | :--- | :--- |
| **Ultrasonic Trig** | Pin 9 | Output Pulse |
| **Ultrasonic Echo** | Pin 10 | Input Echo |
| **Green LED** | Pin 2 | Safe Signal |
| **Yellow LED** | Pin 3 | Warning Signal |
| **Red LED** | Pin 4 | Danger Signal |
| **Buzzer** | Pin 5 | Acoustic Signal |

## 6. Telemetry in Serial Plotter
To view the graph, press `Ctrl + Shift + L`. You will see the **Distance** line moving between the **Safe (50)** and **Danger (20)** reference lines. This allows you to calibrate the sensor's precision visually.

---
**This material is for classroom use only. Commercial distribution is strictly prohibited.**

**Author: Iwan**
