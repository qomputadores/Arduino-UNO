# Project: 02_ExternalLedControl

## 1. Description
This project focuses on the physical logic of a **Breadboard**. Students will learn that vertical columns act as a single electrical node, allowing current to pass from one component to another without soldering.

## 2. Learning Objectives
* Understand Breadboard architecture (Vertical columns vs. Horizontal power rails).
* Differentiate between the **Anode** (Positive) and **Cathode** (Negative) terminals.
* Apply a current-limiting resistor to protect the circuit.

## 3. Hardware Requirements
* **Microcontroller:** Arduino Uno R3.
* **Breadboard:** 830 points.
* **LED:** 1x 5mm.
* **Resistor:** 1x 220 Ohm (Red-Red-Brown).
* **Jumpers:** 2x Male-to-Male.

## 4. Breadboard Circuitry & Connection Details
To create a functional circuit, components must share the same **Column** to be connected, or use different columns to remain isolated.

1. **Signal Input:** Connect a jumper from **Pin 2** to any empty **column** on the breadboard.
2. **Current Protection:** Place one terminal of the **resistor** in the **same column** as the jumper. Place the other terminal in a **different column**.
3. **LED Connection:** * Insert the **Anode** (+) into the **same column** where the resistor ends.
   * Insert the **Cathode** (-) into a **new, different column**.
4. **Closing the Circuit:** Connect a jumper from the **column of the Cathode** to the **GND** pin of the Arduino.

| Component | From | To | Connection Type |
| :--- | :--- | :--- | :--- |
| **Jumper 1** | Arduino Pin 2 | Column X | Signal Wire |
| **Resistor** | Column X | Column Y | Bridge / Protection |
| **LED Anode** | Column Y | LED (+) | Shared Node |
| **LED Cathode**| Column Z | LED (-) | Isolated Node |
| **Jumper 2** | Column Z | Arduino GND | Return Path |

## 5. Expected Behavior
The external LED will blink at 1-second intervals. If it fails, verify that the resistor and LED Anode share the **exact same vertical column**.

## 6. Code Syntax Explanation
* **#define ExternalLed 2:** Descriptive naming for the digital pin.
* **pinMode(ExternalLed, OUTPUT):** Configures the pin to deliver power.
* **digitalWrite(ExternalLed, HIGH/LOW):** Toggles the 5V state to complete or break the circuit.

---
**Author: Iwan**