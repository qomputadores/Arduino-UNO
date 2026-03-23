# Project: 05_UltrasonicSensor

## 1. Description
This project focuses on distance measurement using the **HC-SR04** sensor. We explore the physics of sound at a microscopic time scale (microseconds) and learn how to monitor and graph live data using the Arduino IDE's powerful communication tools.

## 2. Deep Dive: How the HC-SR04 "Sees"
The ultrasonic sensor works by emitting high-frequency sound waves that are inaudible to humans.



* **Trigger (The Transmitter):** This pin acts like a "speaker". When the Arduino sends a 10-microsecond pulse, the sensor shoots 8 bursts of ultrasound.
* **Echo (The Receiver):** This pin acts like a "microphone". It waits for the sound to hit an object and bounce back. 
* **The Physics of Sound:** Sound travels through air at approximately **340 meters per second**. In our code, we use **0.034 cm/μs**. 
* **Why divide by 2?** The time measured by the `pulseIn` function is the "round trip" (the time to go to the object PLUS the time to come back). To find the actual distance to the object, we must divide that result by two.

## 3. Programming Concept: Variable Memory Limits
In Arduino, we must choose the correct "data container" (variable) to avoid errors or "overflows".

| Type | Bits | Minimum Value | Maximum Value | Role in this Project |
| :--- | :--- | :--- | :--- | :--- |
| **int** | 16 | -32,768 | **32,767** | Stores the final distance in centimeters. |
| **long** | 32 | -2,147,483,648 | **2,147,483,647** | Stores the raw travel time in microseconds. |

## 4. Introduction to Serial Communication
Since the Arduino doesn't have a screen, we use the **Serial Port** to "talk" to the computer. 

### **A. Serial Monitor (The Text Interface)**
It shows you the raw data in a list format.
* **How to open:** Go to `Tools > Serial Monitor` or press `Ctrl + Shift + M`.
* **How to read it:** Ensure the speed is set to **9600 baud** (bottom right corner). You will see a stream of numbers representing the distance.

### **B. Serial Plotter (The Graphic Interface)**
It transforms numbers into a real-time moving graph.
* **How to open:** Go to `Tools > Serial Plotter` or press `Ctrl + Shift + L`.
* **How to use it:** The plotter looks for numbers and commas. In this project, you will see 5 lines:
    1.  **Distance (Dynamic):** Moves as you move your hand.
    2.  **Reference Lines (Static):** Fixed lines at 0, 5, 20, and 100 to help you judge distance visually without reading digits.

## 5. Hardware Requirements & Connections
* **Microcontroller:** Arduino Uno R3.
* **Sensor:** 1x HC-SR04 Ultrasonic Sensor.
* **Jumpers:** 4x Male-to-Male.

| Sensor Pin | Arduino Pin | Function |
| :--- | :--- | :--- |
| **VCC** | 5V | Power Supply |
| **Trig** | Pin 5 | Sends the pulse (Output) |
| **Echo** | Pin 6 | Listens for the rebound (Input) |
| **GND** | GND | Ground |

---
**This material is for classroom use only. Commercial distribution is strictly prohibited.**

**Author: Iwan**