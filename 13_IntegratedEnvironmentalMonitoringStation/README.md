# Project 13: Integrated Environmental Monitoring Station

### Description
Technical implementation of a multi-parameter station for indoor environmental analysis. This project processes chemical (MQ-2) and thermodynamic (DHT11) variables, converting raw analog and digital data into standardized percentages. The system architecture utilizes a non-blocking scheduler to cycle information on an I2C LCD using Sentence Case for improved readability. It features a hierarchical alarm protocol using PWM signal modulation on an RGB LED and a piezoelectric buzzer for acoustic alerts.

### Hardware Anatomy (Physics/Theory)
*   **DHT11 Digital Technology:** Unlike analog thermistors, the DHT11 is a composite sensor that includes a resistive-type humidity measurement component and an NTC temperature measurement component. It features an internal 8-bit microcontroller that performs the analog-to-digital conversion and transmits data via a specialized single-bus digital protocol.
*   **Single-Bus Digital Protocol:** The sensor communicates through a sequence of voltage pulses. A complete data transmission is 40 bits long: 16 bits for humidity data, 16 bits for temperature data, and 8 bits for parity (checksum) to ensure data integrity. The duration of the "High" signal determines whether a bit is a 0 or a 1.
*   **Piezoelectric Transduction:** The buzzer operates by vibrating a ceramic disk via oscillating electrical signals. A frequency of 2500Hz is used for high-priority alerts due to its high audibility.
*   **ADC Noise Floor:** Real-world sensors capture a baseline signal from ambient gases. Mapping the 10-bit resolution ($0$ to $1023$) to $0-100\%$ allows students to observe the "Noise Floor" (approx. $10\%$), proving that environmental air is never absolute $0$.
*   **I2C Serial Communication:** A synchronous protocol using SDA and SCL lines. It allows addressing the LCD controller to display characters using only two digital pins.

### Library Methods
*   **DHT.readTemperature():** Triggers the digital handshake and timing-sensitive pulse acquisition to decode the thermal state into Celsius.
*   **DHT.readHumidity():** Executes the data packet request to capture the relative humidity percentage from the sensor's internal register.
*   **tone(pin, frequency):** Generates a square wave of the specified frequency on the digital pin to drive the buzzer.
*   **LiquidCrystal_I2C.print():** Transmits the ASCII characters to the LCD controller buffer.
*   **map(value, 0, 1023, 0, 100):** Linear transformation of the raw ADC range into a percentage for user-centric telemetry.

### Instructions
1.  **Digital Initialization:** The `DhtSensor.begin()` method must be called within the setup stage to synchronize the microcontroller's internal timers with the sensor's transmission rate.
2.  **Data Acquisition Timing:** Due to the internal processing time of the DHT11, readings should not be requested more frequently than once every 2 seconds to avoid "NaN" (Not a Number) errors.
3.  **Telemetry Rotation:** Observe the LCD to verify the real-time status of Gas, Temperature, and Humidity in Sentence Case.
4.  **Alarm Hierarchy:** Emerald indicates safe conditions; Amber signals caution; Crimson and a 2500Hz tone represent critical environmental risks.

### Power/Safety Protocols
*   **Pull-up Resistor Requirement:** The DHT11 data line requires a pull-up resistor (typically 5kΩ to 10kΩ) to keep the signal HIGH during standby, although many modules include this resistor on their PCB.
*   **I/O Current Management:** Ensure the piezoelectric buzzer does not exceed the $40mA$ limit of the microcontroller's digital pins to prevent hardware damage.
*   **Shared Ground (GND):** All peripheral ground connections must be tied to a common rail to prevent floating voltages and signal corruption.

### Connection Table
| COMPONENT      | ARDUINO PIN | NOTES                                      |
|----------------|-------------|--------------------------------------------|
| MQ-2 (Gas)     | A0          | Analog Input (Calibrated Map)              |
| DHT11 (Data)   | 4           | Digital Input (Single-Bus Protocol)        |
| Red Pin (RGB)  | 9           | PWM Output (Common Cathode)                |
| Green Pin (RGB)| 10          | PWM Output (Common Cathode)                |
| Blue Pin (RGB) | 11          | PWM Output (Common Cathode)                |
| Buzzer         | 5           | Digital Output (Acoustic Feedback)         |
| SDA (LCD)      | A4          | I2C Data                                   |
| SCL (LCD)      | A5          | I2C Clock                                  |

This material is for classroom use only. 
Commercial distribution is strictly prohibited.
Author: Iwan.