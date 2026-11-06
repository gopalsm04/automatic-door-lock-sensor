# Automatic Door Lock Sensor (RFID-Based)

An Arduino-based door lock prototype that uses RFID card authentication. A valid card unlocks the door automatically and lights a green LED. An invalid card keeps the door locked and lights a red LED.

**Department of Electrical and Electronics Engineering, Shridevi Institute of Engineering and Technology, Tumakuru (VTU)**

## Overview
The user places an RFID card near the reader. The Arduino Uno compares the card against the authorised card ID. If it matches, the servo motor moves to unlock the door and the green LED glows. If it doesn't match, the door stays locked and the red LED glows. The 16x2 LCD shows the system status.

## Features
- RFID card-based authentication
- Automatic locking and unlocking using a servo motor
- Green LED for access granted, red LED for access denied
- 16x2 LCD status display

## Components
| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| RFID reader module [fill in: e.g. RC522] | Reads the RFID card |
| RFID cards | Authorised access keys |
| Servo motor | Locks and unlocks the door |
| 16x2 LCD display | Shows access status messages |
| Green LED | Indicates access granted (door unlocked) |
| Red LED | Indicates access denied (door locked) |

## How it works
1. The RFID reader scans the card brought near it.
2. The Arduino reads the card's unique ID and checks it against the stored authorised ID.
3. **Valid card:** the servo unlocks the door, the green LED glows and the LCD shows the status.
4. **Invalid card:** the door stays locked, the red LED glows and the LCD shows the status.

## Tools and technologies
- Arduino IDE, Embedded C/C++
- RFID interfacing, servo motor control, 16x2 LCD interfacing

## Team
-Gopal
-MD shahid
-Bi Bi Maryam
-MD Huzaifa

## Repository contents
- `code/` Arduino source code
- `images/` photos of the prototype
- `demo/` demo video (if available)

## Future improvements
- Add a keypad for two-factor access (card and PIN)
- Add a buzzer alert for repeated invalid attempts
- Store multiple authorised cards and log access times
- Add Wi-Fi alerts to the owner's phone
