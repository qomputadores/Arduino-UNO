Project 11: Quantitative Gas Monitoring System (LCD I2C Integration)
1. Description
This project advances the atmospheric security interface by incorporating Quantitative Feedback. While the "Breathing" RGB LED provides a qualitative psychological alert through color and pulse frequency, the LCD 16x2 (I2C) delivers precise numerical data (Gas Value) and text-based status updates. Students will master the I2C communication protocol to manage complex visual data with minimal wiring.

2. Hardware Anatomy (Physics/Theory)
LCD 16x2 & I2C Protocol
I2C Architecture: Uses only two signal wires: SDA (Serial Data) and SCL (Serial Clock). This reduces the pin count from 16 to 2, optimizing the Arduino's I/O for other sensors.

Liquid Crystal Display: Uses light-modulating properties of liquid crystals. The built-in potentiometer on the I2C module must be adjusted to set the character contrast.

RGB LED Hardware Logic
This project includes support for both hardware variations:

Common Cathode (CC): Shared negative. Direct Logic: 255 = ON / 0 = OFF.

Common Anode (CA): Shared positive. Inverse Logic: 0 = ON / 255 = OFF.

Hierarchical Status Messages
The LCD is programmed to reflect the four atmospheric states:

Standby: Blue pulse + "STATE: STANDBY" (Sensor calibration).

Safe: Green pulse + "STATE: SAFE" (Normal operations).

Warning: Fast Orange pulse + "STATE: WARNING" (Gas detected).

Danger: Solid Red + "STATE: DANGER!" (Emergency threshold).

3. Library Methods
Lcd.init(): Initializes the I2C communication and the LCD controller.

Lcd.backlight(): Powers the internal LED for screen visibility.

Lcd.setCursor(col, row): Positions the data pointer (0-15 for columns, 0-1 for rows).

Lcd.print(data): Renders text or variables to the screen.

4. Power/Safety Protocols
I2C Address Check: Ensure the module address is correctly set in the code (usually 0x27 or 0x3F).

5V Power Rail: The LCD and MQ-2 sensor consume significant current; ensure the 5V rail is stable and shared correctly.

Contrast Adjustment: If no text is visible, rotate the I2C module's blue potentiometer until pixels appear.

Data Clearing: Use trailing spaces in Lcd.print() to erase ghost characters when values drop from 4 digits to 3.

5. Connection Table
+-----------------------+------------------+-------------------+
|   COMPONENT PIN       |   ARDUINO PIN    |      FUNCTION     |
+-----------------------+------------------+-------------------+
|   Mq2 Ao              |   A0             |  Analog Input     |
|   LCD SDA             |   A4 (SDA)       |  I2C Data Line    |
|   LCD SCL             |   A5 (SCL)       |  I2C Clock Line   |
|   RGB Red Pin         |   D9 (PWM)       |  Red Modulation   |
|   RGB Green Pin       |   D10 (PWM)      |  Green Modulation |
|   RGB Blue Pin        |   D11 (PWM)      |  Blue Modulation  |
|   Buzzer Signal (+/S) |   D5 (PWM)       |  Alert Output     |
+-----------------------+------------------+-------------------+

This material is for classroom use only. Commercial distribution is strictly prohibited.

Author: Iwan