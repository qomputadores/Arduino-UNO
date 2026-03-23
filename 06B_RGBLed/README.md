# Project: 06B_RGBLed (PWM, Loops & Randomness)

## 1. Description
This project introduces **PWM (Pulse Width Modulation)** to control light intensity. Instead of just turning colors ON or OFF, we learn how to create millions of colors by rapidly pulsing electricity.

## 2. Technical Concept: What is PWM?
Arduino pins are digital, meaning they can only output **0V (LOW)** or **5V (HIGH)**. They cannot output 2.5V. So, how do we dim an LED?

We use **PWM**. Instead of a constant voltage, the Arduino turns the pin ON and OFF hundreds of times per second. 
* If the pin is ON 50% of the time, the LED looks half-bright.
* If it's ON 10% of the time, it looks very dim.



### **The relationship between PWM and `analogWrite()`**
In code, we use `analogWrite(pin, value)` to control this pulsing. The "value" goes from **0 to 255**:
* **0:** The pin is always OFF (0% Duty Cycle).
* **127:** The pin is ON half the time (50% Duty Cycle).
* **255:** The pin is always ON (100% Duty Cycle).

## 3. New Concept: The `for` Loop (The Counter)
The `for` loop is our "automatic counter". It allows us to transition through the 256 levels of PWM smoothly without writing 256 lines of code.

`for (int i = 0; i <= 255; i++)`

1. **Start:** `i` begins at 0.
2. **Check:** Is `i` less than or equal to 255?
3. **Action:** Run the code inside (change the LED brightness).
4. **Step:** Add 1 to `i` and repeat until it reaches 255.



## 4. Randomness and Entropy
* **`random(0, 256)`:** Picks a random PWM value for each color.
* **`randomSeed(analogRead(0))`:** This is the "starter" for randomness. Since an empty analog pin (A0) acts like an antenna picking up electromagnetic noise, we use that unpredictable "noise" to ensure the colors are different every time you turn the device on.

## 5. Hardware Requirements & Connections
* **Microcontroller:** Arduino Uno R3.
* **Pins used:** 9, 10, and 11 (Notice the **~** symbol next to them; it means they are **PWM-capable**).

| RGB Pin | Function | Arduino Pin |
| :--- | :--- | :--- |
| **Pin 1** | Red (R) | **Pin 9 (~)** |
| **Pin 2** | **Common** | GND / 5V |
| **Pin 3** | Green (G) | **Pin 10 (~)** |
| **Pin 4** | Blue (B) | **Pin 11 (~)** |

---
**This material is for classroom use only. Commercial distribution is strictly prohibited.**

**Author: Iwan**