# Project: 04B_BuzzerMelody

## 1. Description
This project expands on the basic use of the Active Buzzer. We program the "Shave and a Haircut" rhythm, focusing on the critical importance of inter-note silences to ensure each note is perceived distinctly by the human ear.

## 2. Learning Objectives
* Understand that `tone()` requires a `delay()` to be audible before the next instruction.
* Learn to create "staccato" effects by inserting brief `noTone()` silences.
* Master the logic of sequential sound programming using vertical code structure.

## 3. Hardware Requirements
* **Microcontroller:** Arduino Uno R3.
* **Actuator:** 1x Active Buzzer (3-pin Module).
* **Jumpers:** Male-to-Female.

## 4. Connection Details
| Module Pin | Arduino Pin | Function |
| :--- | :--- | :--- |
| **VCC (+)** | 5V | Constant Power |
| **GND (-)** | GND | Ground Reference |
| **S / Signal** | Pin 4 | Control Signal |



## 5. Expected Behavior
The buzzer will play 7 distinct notes with a musical rhythm. The final two notes ("Tun-Tun") are separated by a 100ms silence to ensure they are heard as two separate pulses instead of one long sound.

## 6. Technical Explanation: Vertical Logic
In this project, we follow a strict vertical instruction flow:
1. **tone():** Starts the sound.
2. **delay():** Holds the program so the sound can be heard.
3. **noTone():** Stops the sound.
4. **delay():** Creates a small silence (gap) so the next note sounds fresh and separated.

---
**This material is for classroom use only. Commercial distribution is strictly prohibited.**

**Author: Iwan**