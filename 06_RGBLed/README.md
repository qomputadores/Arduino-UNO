# Project: 06_RGBLed

## 1. Description
This project focuses on the study of the RGB LED, a device capable of producing almost any color by mixing Red, Green, and Blue light. We explore the two electrical configurations (Common Cathode and Common Anode) and the logic required to create secondary colors.

## 2. Learning Objectives: Color Theory
An RGB LED follows the **Additive Color Model**. This means:
* **Primary Colors:** Red, Green, and Blue.
* **Secondary Colors:** Created by turning on two primary pins at the same time (e.g., Red + Green = Yellow).
* **White Light:** Created by turning on all three primary pins simultaneously.



[Image of additive color mixing diagram]


## 3. Understanding the Hardware: Anode vs. Cathode
The physical connection of the common (longest) pin changes how we "talk" to the LED:

| Type | Common Pin | Logic | Action to turn ON |
| :--- | :--- | :--- | :--- |
| **Common Cathode** | **GND** | Direct | `digitalWrite(pin, HIGH)` |
| **Common Anode** | **5V** | Inverse | `digitalWrite(pin, LOW)` |

## 4. Hardware Requirements
* **Microcontroller:** Arduino Uno R3.
* **Actuator:** 1x RGB LED (4 pins).
* **Resistors:** 3x 220 $\Omega$ resistors (Mandatory).
* **Jumpers:** Male-to-Male.

## 5. Connection Details
| RGB Pin | Color | Arduino Pin |
| :--- | :--- | :--- |
| **Pin 1** | Red (R) | Pin 9 |
| **Pin 2 (Longest)** | **Common** | **GND** (Cathode) or **5V** (Anode) |
| **Pin 3** | Green (G) | Pin 10 |
| **Pin 4** | Blue (B) | Pin 11 |

---
**This material is for classroom use only. Commercial distribution is strictly prohibited.**

**Author: Iwan**