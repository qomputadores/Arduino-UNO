Project: 14Smart Indoor Climate Actuation

1. Description

This project simulates an industrial indoor environmental mitigation system. It monitors chemical toxic profiles via an MQ-2 sensor alongside thermal and moisture signals using a DHT11 module. Collected telemetry data is sequentially displayed across a 4-screen temporal multiplexing setup using an I2C LCD interface. Visual and acoustic safety states are handled via a hierarchical alert routine using an RGB LED and a buzzer. A 1-channel power relay is integrated as an automated hazard mitigation actuator: if either the ambient gas density or temperature parameters breach safety margins, the relay engages to activate an industrial exhaust fan to ventilate the zone while forcing a persistent priority emergency layout status screen on the hardware interface display.

2. Learning Objectives

Industrial Actuation: Understand electromechanical isolation by driving high-voltage power loads using 5V microcontrollers.
Combinational Hazard Assessment: Deploy logical OR operators to link chemical and thermal threat flags into a single automated safety response loop.
Temporal Interface Schedulers: Master the execution of rotating multi-screen display cycles using non-blocking millisecond counters with programmatic layout override traps.

3. How the "Actuation Logic" Works

The hardware monitoring framework parses the sensor input arrays and establishes a safety hierarchy based on the following environment parameters:

Environmental State | Sensor Triggers | RGB LED Visual Alert | Buzzer Acoustic | Relay Fan Status | LCD Display State
--- | --- | --- | --- | ---
Danger Level (Relay) | Gas >= 70% OR Temp >= 30C | Solid Red Light | Continuous 2500Hz Tone | ACTIVE (Ventilation ON) | Forced Emergency Screen
Danger Level (Moisture) | Hum >= 75% | Solid Red Light | Continuous 2500Hz Tone | Inactive (Ventilation OFF) | Standard Rotating Screens
Warning Level | Gas >= 15% OR Temp >= 24C OR Hum >= 60% | Orange Breathing Pulse | Muted | Inactive (Ventilation OFF) | Standard Rotating Screens
Safe Baseline | Default Operational Ranges | Green/Cyan Breathing Pulse | Muted | Inactive (Ventilation OFF) | Standard Rotating Screens

* Note on Relay Concomitance: The relay responds exclusively to thermal (Temp >= 30) and chemical (Gas >= 70%) threats. If the danger state is exclusively triggered by ambient moisture saturation (Hum >= 75% "Condens."), the alarm buzzer activates, but the power relay remains low to prevent pulling external humid air into the space.
* Note on Emergency Layout Trap: During a relay execution event, standard screen rotation freezes. The display locks onto Screen 4, printing text notifications confirming the active mitigation system operation. Normal screen rotation resumes automatically once parameters fall back inside nominal limits.

4. Hardware Requirements

Microcontroller: Arduino Uno R3.
Sensors/Inputs: 1x MQ-2 Gas Sensor Module, 1x DHT11 Climate Sensor Module.
Actuators/Outputs: 1x I2C 16x2 LCD Display Module, 1x 1-Channel 5V Relay Module, 1x RGB LED (Common Cathode), 1x Active Buzzer.
Resistors: 3x 220 Ω (for RGB color lines).
Protoboard & Jumpers.

5. Connection Details (Data Only)

Component | Arduino Pin | Role
--- | --- | ---
MQ-2 Gas Sensor | Pin A0 | Analog Output Signal Input
DHT11 Data Line | Pin 4 | Digital Signal I/O Channel
RGB LED Red Pin | Pin 9 | PWM Current Drive Output
RGB LED Green Pin | Pin 10 | PWM Current Drive Output
RGB LED Blue Pin | Pin 11 | PWM Current Drive Output
Active Buzzer (+) | Pin 5 | Acoustic Frequency Output
5V Relay Module | Pin 3 | Digital Actuator Command Output
I2C LCD SDA Line | Pin A4 | Serial Data Bus Line
I2C LCD SCL Line | Pin A5 | Serial Clock Bus Line

* Note for Common Anode Customization: Students executing this experiment using common anode RGB hardware profiles must invert output states inside the analogWrite declarations using subtraction mechanics (255 - Intensity).

6. Telemetry Display Sequences

The display scheduler monitors execution times via millis() and triggers a full screen refresh and clear every 3000ms using Sentence Case parameters:
* Screen 0: Initial station brand display ("Comfort station" / "By: Student Name").
* Screen 1: Chemical concentration values displayed alongside real-time risk evaluations (Safe/Warning/Danger).
* Screen 2: Real-time temperature readouts in Celsius with atmospheric indicators (Comfort/Normal/Hot).
* Screen 3: Relative ambient air moisture monitoring alongside environmental saturation alerts (Dry/Ideal/Condens.).
* Screen 4 (Priority Interrupt): Engaged strictly during active ventilation events, printing alert indicators ("Status: Emergency" / "Fan activated").

This material is for classroom use only. Commercial distribution is strictly prohibited.

Author: Iwan
