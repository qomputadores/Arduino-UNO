# Project: 01_InternalBlink

## 1. Description
This project is designed as the initial validation step for the Arduino Uno R3 hardware. It verifies the correct installation of the IDE, the communication through the USB port, and the operational state of the ATmega328P microcontroller by toggling the state of the built-in LED.

## 2. Software Installation & Setup
To ensure your workstation is ready, follow these steps:

1. **Download the IDE:** Get the latest version (Current: 2.3.5) from the official website:
   * [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. **Quick Selection Menu:** In Arduino IDE 2.x, use the **dropdown menu at the top center** of the interface. This allows you to select both the Board and the Port in one click.
3. **The "Unknown Board" Issue:** If the IDE shows the port (e.g., COM3) but identifies the board as **"Unknown"**, it is likely a generic version. You must manually select **"Arduino Uno"** from the board list.
4. **Drivers for Generic Boards (CH340):** If the board is not detected at all or remains "Unknown" despite manual selection, you may need the specific drivers for the CH340 chip (common in Chinese versions):
   * [CH340 Driver Download & Tutorial](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)

## 3. Learning Objectives
* Understand the basic structure of an Arduino sketch (setup and loop).
* Master the use of the `pinMode` and `digitalWrite` instructions.
* Identify the physical location of the built-in LED (Pin 13) on the board.

## 4. Hardware Requirements
* **Microcontroller:** Arduino Uno R3 (Original or Generic).
* **Connection:** USB Type-A to Type-B cable.
* **External Components:** None (Uses the on-board LED).

## 5. Connection Map
| Component | Arduino Pin | Notes |
| :--- | :--- | :--- |
| Internal LED | Pin 13 | Integrated into the PCB (labeled 'L') |

## 6. Expected Behavior
Upon successful firmware upload, the LED labeled **'L'** on the Arduino board will blink repeatedly. It will remain ON for 1 second and OFF for 1 second in a continuous cycle.

## 7. Code Syntax Explanation

### **The Main Functions**
Every Arduino program must contain exactly **one** `setup()` and **one** `loop()` function.
* **void setup():** Runs only once. Used to initialize pins.
* **void loop():** Runs repeatedly and infinitely. Contains the main logic.

### **Core Instructions**
* **pinMode(pin, mode):** Configures a pin as `INPUT` or `OUTPUT`. Here, Pin 13 is an `OUTPUT`.
* **digitalWrite(pin, value):** * `HIGH`: Sends 5V (ON).
    * `LOW`: Sends 0V (OFF).
* **delay(ms):** Pauses the program (1000 ms = 1 second).

---
**Author: Iwan**