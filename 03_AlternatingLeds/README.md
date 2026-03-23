# Project: 03_AlternatingLeds (Week 5)

## 1. Description
This project, corresponding to Week 5, demonstrates the control of two independent LEDs. The goal is to create an alternating sequence where only one LED is active at a time, teaching students about mutual exclusion in digital logic.

## 2. Learning Objectives
* Manage multiple `OUTPUT` pins in a single program.
* Understand the internal vertical connectivity (columns) of the Breadboard.
* Practice the use of independent resistors for multiple components.

## 3. Hardware Requirements
* **Microcontroller:** Arduino Uno R3.
* **Breadboard:** 830 points.
* **LEDs:** 1x Red, 1x Blue (Technical: 5mm).
* **Resistors:** 2x 220 Ohm (Red-Red-Brown).
* **Jumpers:** 3x Male-to-Male.

## 4. Breadboard Circuitry & Connection Details
Components must be placed in specific columns to ensure they share the electrical signal or remain isolated.

1. **Red LED Circuit:** Jumper from **Pin 2** to a column. A **220Ω resistor** bridges that column to another where the **Red Anode** is placed.
2. **Blue LED Circuit:** Jumper from **Pin 3** to a different column. A second **220Ω resistor** bridges to another column for the **Blue Anode**.
3. **Common Ground:** Both **Cathodes** connect to the breadboard's blue rail (-), which returns to the Arduino **GND**.

| Component | From | To | Connection Type |
| :--- | :--- | :--- | :--- |
| **Jumper 1** | Pin 2 | Column X | Red Signal |
| **Resistor 1** | Column X | Column Y | Red Protection |
| **Jumper 2** | Pin 3 | Column W | Blue Signal |
| **Resistor 2** | Column W | Column Z | Blue Protection |
| **Common GND** | Both Cathodes | Arduino GND | Return Path |

## 5. Expected Behavior
The Red and Blue LEDs will blink alternately every 200ms. If both are ON or OFF at the same time, check the `digitalWrite` logic in the loop.

## 6. Code Syntax Explanation
* **Multiple pinMode:** We initialize two separate pins to deliver 5V.
* **Alternating States:** By using `HIGH` for one pin and `LOW` for the other in each step, we create the alternating effect.

---
**Author: Iwan**