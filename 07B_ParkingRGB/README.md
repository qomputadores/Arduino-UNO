# Project: 07B_ParkingRGB (Advanced Signaling)

## 1. Description
This final version of the parking assistant introduces a **Dynamic Standby Mode**. When the sensor detects no immediate obstacles (> 100 cm), the LED pulses softly in **Blue**, indicating the system is active but at a safe distance.

## 2. Learning Objectives
* **Dynamic States:** Learn how to create a "Breathing LED" effect without stopping the rest of the code.
* **Variable Interaction:** Observe how the `blueIntensity` variable changes automatically in one mode and via `map()` in another.
* **Extended Logic:** Manage 4 distinct operational zones.

## 3. The "Pulse" Logic
When the distance is > 100 cm, we use a variable called `fadeAmount`. 
1. The code adds (or subtracts) a small amount to the `blueIntensity` in every loop.
2. When it reaches 255 (Max) or 0 (Min), it multiplies `fadeAmount` by -1 to reverse the direction.
3. This creates a smooth "breathing" effect.



## 4. Operational Zones Summary
* **> 100 cm:** Blue Pulse (Standby).
* **50 - 100 cm:** Blue to Green Gradient.
* **20 - 50 cm:** Green to Red Gradient (passes through Yellow).
* **< 20 cm:** Solid Red + High Pitch Alarm.

---
**Author: Iwan**