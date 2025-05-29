# Smart Door Lock System  

## 📖 Project Overview  
Develop a secure smart door lock system using two ATmega32 microcontrollers, with password authentication, motion detection, and real-time alerts. The system features an HMI ECU with LCD and keypad, and a Control ECU with EEPROM, motor control, PIR sensor, and buzzer.

## 🎯 Objectives  
- Enable secure door access with password protection and motion detection.  
- Provide user interaction via LCD and keypad.  
- Store passwords in external EEPROM for reliability.  
- Control door motor with H-bridge circuit and provide alerts using a buzzer.  

## 💡 Features  
- **Password Protection:** Set and verify passwords stored in external EEPROM.  
- **LCD and Keypad:** User-friendly interface for entering and managing passwords.  
- **UART Communication:** Data exchange between HMI_ECU and Control_ECU.  
- **Motor Control:** Unlock/lock door using DC motor via H-bridge.  
- **PIR Sensor:** Motion detection to hold door open when someone is present.  
- **Buzzer Alerts:** Audible warnings for failed attempts and alerts.  
- **Password Management:** Users can change the password after verification.  
- **Security Lock:** Lockout for 1 minute after three incorrect password attempts.  

## 📚 Hardware Components  
- **HMI ECU:** ATmega32, 16x2 LCD, 4x4 Keypad  
- **Control ECU:** ATmega32, External EEPROM (24C16), Buzzer, H-bridge Motor Driver, DC Motor, PIR Sensor  

![Smart Door Lock System](https://github.com/user-attachments/assets/02b43357-c226-42f2-ac54-8032b051afcb)  

## 🚀 Operation Highlights  
- **Password Creation:** Enter and confirm a 5-digit password via LCD and keypad, stored securely in EEPROM.  
- **Main Options:** Use "+" to unlock door or "-" to change password.  
- **Door Unlocking:** Verify password, rotate motor to unlock door, hold motor as PIR sensor detects motion, then relock when clear.  
- **Password Change:** Verify password and update via LCD and keypad.  
- **Failed Attempts:** After three incorrect tries, activate buzzer, display error on LCD, and lock system for 1 minute.  
- **User Feedback:** LCD shows prompts and system status during operation.  

---  
