# **Project Overview:**
This smart door control system is designed with two microcontrollers, one acting as the
Human-Machine Interface (HMI_ECU) and the other as the Control Unit (Control_ECU). Users
interact with the system using an LCD and keypad to enter passwords, which are verified and
stored using external EEPROM. The door is controlled by an H-bridge circuit connected to a
motor, and the system includes a PIR sensor for motion detection, a buzzer for alarms, and
password-protected access to system options like door unlocking and password changing.

 # **Features:**
### 1. **Password Protection:**
- Users can set and verify a password stored in external EEPROM.

### 2. **LCD and Keypad Interface:**
- Allows easy interaction for entering and managing passwords.
  
### 3.  **UART Communication:**
-  HMI_ECU sends and receives data to and from Control_ECU via UART.

### 4. **EEPROM Storage:**
-  Passwords and system data are stored securely in an external EEPROM.

### 5. **Motorized Door Control:**
-  The door is unlocked/locked using a motor driven by an Hbridge.

### 6. **Buzzer Alert:**
- The buzzer is activated for failed password attempts and system alerts.
  
### 7. **PIR Motion Sensor:**
- Detects motion to trigger door operations.
  
### 8. **Password Change Option:**
- Users can change the password after verification.
  
### 9. **Security Lock:**
- System locks for one minute if the password is entered incorrectly three times consecutively.


# **Hardware Components:**
### **HMI ECU:**
 1. 16x2 LCD in 8-bit mode.
 2. Keypad (4x4) mode.

### **Control ECU:**
1. External EEPROM (24C16).
2. Buzzer.
3. H-bridge Motor Driver.
4. Motor (for Door Control).
5. PIR Motion Sensor.

![Screenshot 2024-12-04 190517](https://github.com/user-attachments/assets/02b43357-c226-42f2-ac54-8032b051afcb)



# **Operation Description:**
### **Step 1 (Create a System Password):**
- The LCD should display “Please Enter Password”.
- Enter a password consists of 5 numbers, Display * in the screen for each number.
- Press enter button (choose any button in the keypad as enter button).
- Ask the user to re-enter the same password for confirmation by display this message “Please re-enter the same Pass”:
- Enter a password consists of 5 numbers, Display * in the screen for each number.
- Press enter button (choose any button in the keypad as enter button).
- HMI_ECU should send the two passwords to the Control_ECU through the UART.
- If the two passwords are matched then the system has a password now and save it inside the EEPORM and go to Step 2.
- If the two passwords are unmatched then repeat step 1 again.

### **Step 2 (Main Options):**
- The LCD will always display the main system option "+" to open the door and "-" to cahngethe paswword.

### **Step 3 (Open Door "+"):**
- The LCD should display “Please Enter Password”.
- Enter the password then press enter button (choose any button in the keypad as enter button).
- HMI_ECU should send the Password to the Control_ECU and it should compare it with the one saved in the EEPROM.
- if two passwords are matched:
   - rotates motor for 15-seconds CW and display a message on the screen “Door is Unlocking”
   - hold the motor as the PIR sensor Detected Their Motion and Display “Wait for people to Enter”.
   - rotates motor for 15-seconds A-CW and display a message on the screen “Door is Locking” when the PIR is No longer Detect Motion

### **Step 4 (Change Password "-"):**
- The LCD should display “Please Enter Password”.
- Enter the password then press enter button (choose any button in the keypad as enter button).
- HMI_ECU should send the Password to the Control_ECU and it should compare it with the one saved in the EEPROM.
- if two passwords are matched then repeat Step 1.

### **Step 5:**
- if the two passwords are unmatched at step 3 (+ : Open Door) or step 4 (- : Change Password)
- Ask the user one more time for the password.
- The LCD should display “Please Enter Password”.
- Enter the password then press enter button (choose any button in the keypad as enter button).
- HMI_ECU should send the password to the Control_ECU and it should compare it with the one saved in the EEPROM.
- if two passwords are matched then open the door or change the password in steps 3 and 4.
- If the two passwords are not matched again then ask the user one last time for the password.
- if two passwords are matched then open the door or change the password in steps 3 and 4.
- If the two passwords are not matched for the third consecutive time, then:
   - Activate Buzzer for 1-minute.
   - Display error message on LCD for 1 minute.
   - System should be locked no inputs from Keypad will be accepted during this time period.
   - Go to Step 2 the main options again
