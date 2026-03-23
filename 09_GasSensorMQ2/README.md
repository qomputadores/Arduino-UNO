# Project 09: Atmospheric Monitoring and Industrial Safety System (MQ-2)

## 1. Description
This project focuses on Environmental Monitoring and Industrial Safety Electronics. The objective is to interface an MQ-2 gas sensor with the Arduino to detect the presence of combustible gases (LPG, Propane, Hydrogen) or smoke. The system translates physical gas concentrations into a processable numerical scale, establishing a three-tier alert system using independent visual indicators (LEDs) and an audible alarm (Buzzer) based on calibrated safety thresholds.

## 2. Hardware Anatomy (Physics/Theory)
The MQ-2 is an electrochemical sensor that operates using a sensitive layer of Tin Dioxide (SnO2).
* Chemical Sensing: The sensor includes an internal heating element. In clean air, oxygen is adsorbed on the SnO2 surface, trapping electrons and resulting in high electrical resistance.
* The Detection Process: When combustible molecules contact the heated sensor surface, they react with the adsorbed oxygen, releasing electrons back into the material. This significantly increases conductivity.
* Signal Conversion: This physical change in conductivity is output as an analog voltage (0V-5V). The Arduino's 10-bit ADC then maps this voltage to a digital value between 0 and 1023.

## 3. Library Methods
This project utilizes core hardware abstraction methods from the Arduino framework:
* analogRead(pin): Queries the internal ADC to retrieve the 10-bit resolution value from the sensor's output.
* pinMode(pin, mode): Defines the I/O direction for the LED indicators and the alarm system.
* digitalWrite(pin, state): Sets the logic level for the visual status LEDs.
* tone(pin, frequency): Generates a PWM-based square wave to drive the Piezo element at specific frequencies.
* noTone(pin): Immediately stops the frequency generation on the specified pin to silence the alarm.

## 4. Power/Safety Protocols
1. Preheating Period: The internal chemical reactions within the MQ-2 require the sensor to reach a specific temperature. Accurate data is only available after a 60-second stabilization phase.
2. Current Management: The heater consumes approximately 150mA. To prevent brownouts, the sensor must be powered directly from the breadboard rails, ensuring a dedicated 5V supply.
3. Common Ground: Maintaining a unified GND reference is mandatory to ensure the stability of the analog signal reading.

## 5. Connection Table
+-----------------------+------------------+-------------------+
|   COMPONENT PIN       |   ARDUINO PIN    |      FUNCTION     |
+-----------------------+------------------+-------------------+
|   Mq2 Vcc             |   5V             |  Power (Red Rail) |
|   Mq2 Gnd             |   GND            |  Ground (Blue Rail)|
|   Mq2 Ao              |   A0             |  Analog Input     |
|   LedGreen (Anode)    |   D2             |  Output (Digital) |
|   LedYellow (Anode)   |   D3             |  Output (Digital) |
|   LedRed (Anode)      |   D4             |  Output (Digital) |
|   BuzzerPin (+)       |   D5             |  Output (PWM)     |
+-----------------------+------------------+-------------------+

---
**This material is for classroom use only. Commercial distribution is strictly prohibited.**

**Author: Iwan**