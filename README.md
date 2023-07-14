# Ocean's 2700
### Major Project

This document serves to document high-level information about the practical implementation of C language to program a STM32F303 microcontroller to design and implement a proof-of-concept
technology for a 5-minute escape room experience. 

[![IMAGE Link to Live Demo](https://i.imgur.com/S9S9dgt.png)](https://www.youtube.com/watch?v=DRQaRWyRdBQ")
[![IMAGE Link to Exposition](https://i.imgur.com/x0ZxC2m.png)](http://www.youtube.com/watch?v=BdD9xIvt8MA "Ocean's 2700 Exposition")


# Escape Room Storyline: The Bank Heist
In the heart of the city lies an infamous bank, a fortress reputed for its invincible vault. Today, your team embarks on a daring mission: infiltrate the bank, crack the vault, secure the priceless artifact, and escape without leaving a trace. Precision is key, and silence is your weapon. View the videos above for an exposition of your task. 

### Exercise 1: Safe Crack

Your first challenge is to crack the vault. This is no ordinary vault; it boasts an antiquated dial lock system that demands meticulous manipulation. Your ally in this endeavor is a specialized bank heist robot, designed to decode the right combination to pick the lock. As the robot deciphers each part of the combination, an LED illuminates, signalling your progress. With the robot's help, you breach the vault and secure the coveted artifact.

### Exercise 2: Report to Mission Control

With the artifact in your possession, it's crucial to inform mission control. Luckily, the heist robot is equipped with a unique communication channel. Your task is to interface with this system, encoding your message in Morse code. Each carefully tapped dot and dash confirms the successful extraction of the artifact.

### Exercise 3: Hacking Police Radio Channel

But success has its echoes, and the authorities are now alerted to a possible breach. Their radio chatter buzzes urgently. Your next challenge is to hack into the police radio channel, creating a diversion. You have at your disposal a sundial-like device, outfitted with a magnetometer, which you use to distort the magnetic field and jam the radio signals. The police are successfully redirected, buying you some much-needed time.

### Exercise 4: Exiting the Bank

With the authorities temporarily misled, your escape path is clear, save for one last hurdle: a state-of-the-art security system operated by capacitive touch sensors. Your challenge is to discern the intricate pattern and cautiously navigate through it.

Undeterred, you deactivate the sensors and, with your team, make a swift exit, melting into the shadows just as the confused police return to the now silent bank. Your heist is a triumph: the priceless artifact is yours, and the legend of the impenetrable bank vault is no more.

___
___

## Group members, Responsibilities
1. Joel Pivetta | 520447488       
Exercise 1 : Safe Crack (servo peripheral), integration for Exercise 1 

2. Haz Salvesen     | 490480278       
Exercise 1 : Safe Crack (potentiometer, LED peripherals), Hardware, Documentation

3. Lachlan Irving   | 490627792      
Exercise 4 : Capacitive Touch ideation, Minutes

4. Matylda Hayne    | 520471933       
Exercise 3 : Hacking Police Radio Channel (Sundial (magnetometer))

5. Samuel Richards  | 520482962       
Exercise 2 : Report to Mission Control (Knocking), GUI, Exercise 4 : Exiting the Bank (Capacitive Touch) 

6. Luis Sanabria    | 510432236       
Exercise 3 : Hacking Police Radio Channe (Sundial (LDRs))
___

## Roles
HJLLMS functioned like a start-up, forming a lateral hierarchy, where each member was responsible for their own work, and there was no one overarching lead.
The responsibilities for each of the Exercises and subtasks are detailed above under Group Members.
___
___

## Minutes
Lab minutes and outside-of-lab minutes for meetings are recorded as READMEs, located in the corresponding "minutes" folder. Each is dated and includes goals, regular progress reporting and actionable.
___
___


# Exercise 1 : Safe Crack

## High-Level Overview:
This experience includes a simulated vault cracking sequence which is realised through the interaction between an STM32F303 Discovery board, a potentiometer, a lock-picking robot's servo, and an LED light. The concept is centred around the notion of a vault with a dial lock. The deal, represented by the potentiometer, rests on a Cartesian plane and needs to be manipulated in a certain pattern to 'crack' the vault's code, similar to how a lock-picking robot would function. The STM32F303 Discovery board is the heart of the system, responsible for interfacing with the potentiometer and mimicking the movements of a lock-picking robot's servo.

## Subtasks
1. Interfacing with Potentiometer: The STM32F303 Discovery board must be programmed to read the analog inputs from the potentiometer, which represents the dial on the vault. The position of the dial is determined by the resistance of the potentiometer, which changes as it is turned.
2. Mimicking Lock-Picking Robot's Servo: Based on the analog inputs from the potentiometer, the board will simulate the actions of a lock-picking robot's servo. This includes rotating the dial to certain positions and pausing for a specified amount of time to mimic the process of 'feeling' for the correct combination.
3. Checking Combination: The board produce a random sequence of combinations upon each reset. The servo will mimic the same end angle movement as the randomised combination sequence. For example, if the dial on the vault copies the servo and moves to the right to 30 degrees, then left to 20 degrees, and finally right to 10 degrees, this could be recognised as a correct combination.
4. LED Light Activation: Once a correct combination is entered, the board will send a signal to light up the LED. This serves as a visual confirmation that the correct combination has been entered and the vault is 'unlocked'.

Completion of Tasks: after this Exercise has been completed, the LED will remain on and the solenoid will activate, unlocking the vault and signalling the completion of this exercise. 

___

## Modularisation:
All modules have been separated into appropriate peripheral files, each with a respective .c file in the Source folder and a .h file in the Includes folder for the exercise (Exercise 1).
This reduces the main.c file to 10 lines, heavily simplifying it. This enables portability, reusability, ease of reading and ease of debugging.

There are 19 modules, including main.c. These are: adc.c, gpio.c, i2c.c, main.c, motor.c, peripherals.c, ptu_i2c.c, safecracker.c, serial.c, spi.c, stm32fxx_hal_msp.c, stm32f3xx.it.c, syscalls.c, sysclock_config.c, sysmem.c, system_stm32f3xx.c, tim.c, usart.c, usb.c.
___

## Functions:
Some notable functions are:
- motor: Creates 5 randomised angles between 0 and 180 degrees based on current SysTick value.
```
for (uint32_t i = 0; i < 5; i++)
	{
		   predefined_angles_degrees[i] = (SysTick->VAL % 181); // generate a random number within the loop
    }
 ```
- adc(): Converts angles generated into an appropriate form to be recognised and interpreted by the potentiometer and the panning servo motor.
- safecracker(): Enables stepping through of each of the 5 lock combinations. 
- serial(): Communicates that the module has been completed to our GUI.
- usart(): enables communication to GUI
- Init_Peripherals(): initialises all necessary peripherals, defined elsewhere.
- run_safecracker(): begins the infinite loop.

___
## Troubleshooting 

### Wiring
#### Servo
- PTU -> STM32
- GND -> GND
- PWM1 -> PA15

#### Potentiometer
GND -> GND
V_in -> 3.3V V_in
Input -> PA2 (Analog to Digital Conversion)

#### LED
GND -> 100 Ohm resistor -> GND
V_in -> PE7

#### Solenoid
GND -> Transistor 
V_in -> Transistor -> 5V DC
Transistor switch leg -> PE8


___

## User Instructions
1. Starting the Program: Upon uploading the code to the STM32F303 Discovery board, the escape room simulation will automatically start.

2. Servo Movements: The servo, representing the lock-picking robot, will begin at its origin point (90 degrees). It will then rotate towards its final angle before resetting back to 90 degrees. This cycle of movement will continue until the correct angle is entered via the lock dial, represented by the potentiometer, and held there for 3 seconds.

3. Entering the Correct Angle: As a user, you will manipulate the potentiometer to set the correct angle. The program has a small tolerance for accuracy, so it doesn't need to be exact.

4. LED Indication: Once you've set the potentiometer to the correct angle, a green LED on the Discovery board will turn on for 3 seconds before turning off. This serves as your signal that you've entered the correct angle on the lock dial.

5. Repeating the Process: The servo will then start moving towards the next predefined angle. You will need to repeat the process of setting the potentiometer to the correct angle for the new servo position. This cycle will continue until all 5 predefined angles have been entered correctly, in sequence.

Completion of the Exercise: After the correct sequence of angles has been entered, the servo will reset to 0 degrees and stop moving. The green LED will light up and stay on, signaling the successful completion of the exercise. This will be communicated to the GUI; the first of the four rectangles will light up green on the GUI.

Remember, the objective is to accurately follow the servo's movements with the lock dial (potentiometer), entering the correct sequence of 5 angles.
___

## Constraints & Limitations:
Wiring Issues: One potential limitation of this exercise is the instability of the wiring. The wires connecting the components can sometimes become loose, disrupting the communication between the potentiometer, servo, and STM32F303 Discovery board. If any malfunction is observed, it's advisable to check and fix the wiring connections before resetting and attempting the exercise again.

Servo Angle Limitation: The servo's rotation is constrained between 0 and 180 degrees. This limitation is inherent to the servo's physical properties and cannot be altered. As such, it's crucial to ensure that the angles coded in the program fall within this range.

Potentiometer Rotation: Unlike the servo, the potentiometer can rotate beyond 180 degrees. This discrepancy might cause confusion while attempting to match the potentiometer's position with the servo's angle. Users will need to mentally map the potentiometer's full rotation to the servo's 0 to 180-degree range.

Input Voltage Calibration: The potentiometer's calibration is another crucial aspect. The input voltage should be set to 3V to ensure accurate readings. Any deviation from this voltage might lead to incorrect detection of the dial position and hence, failure in unlocking the vault.

Power to STM32 Board: To ensure constant and correct power supply to the STM32 board, it's recommended that the computer used to upload the code be plugged into a charger. A lack of adequate power can lead to erratic behaviour of the board and disrupt the escape room simulation.

Solenoid: The solenoid lock requires 5V input to actuate. Because the SMT32F303 board is unable to supply 5V from one of its output pins, another 5V source is required. Fortunately, the robot has a 5V output pin, which can be controlled by using an NPN transistor (2n3904) as a switch, triggered by a STM32F303 pin (pin PE8).
___

## Testing Procedures:
Directional Rotation Test: By providing different inputs via the potentiometer, we can test the lock-picking robot's servo ability to mimic both anticlockwise and clockwise rotations. Verification will involve ensuring that the servo's direction of rotation matches the potentiometer's movement.

LED Confirmation Test: The LED light should only activate upon entering a correct angle. Test this by providing a range of correct and incorrect inputs, and verifying that the LED lights up only for correct inputs.

Angle-to-Servo Mapping Test: To verify that each angle set via the potentiometer generates the expected servo movement, set predefined angles and observe the corresponding servo actions.

Sequence Stepping Test: Similar to string stepping functionality, we should test the system's ability to progress through the sequence of angles. After entering each correct angle, the system should move to the next step in the sequence. This can be tested by entering correct angles and verifying the progression to the subsequent servo positions.

Wraparound Test: Like the wraparound function for binary bits, the potentiometer's rotation should wrap around within the 0-180 degrees range. This can be tested by rotating the potentiometer beyond 180 degrees and verifying that the system correctly interprets this as a wraparound within the servo's range.

Finally, all of the modules were tested together to check for cohesive functionality. 

___
___


# Exercise 2 : Reporting to Mission Control

## High-Level Overview:
This module involves the user tapping the IMU on the PTU to transmit an encoded morse-code message to mission control. The user must enter the correct code to continue.

___
## Subtasks
1.	Morse Code Translation: A predefined text message ("HEIST") must be manually converted, letter-by-letter into its corresponding Morse signal.
2.	Tapping in the correct message: the Morse code must be entered by tapping the accelerometer. The number of taps must correspond to each respective letter.
3.	Confirming the Message: The board will compare the signal received by the accelerometer with the original, predefined word in Morse code. If they match, it means the message has been transmitted successfully.
Completion of the Exercise: After the correct sequence of Morse code has been entered, the second rectangle on the GUI will light up green, signalling the completion of the second exercise.
___
## Modularisation
All modules have been separated into appropriate peripheral files, each with a respective .c file in the Source folder and a .h file in the Includes folder for the exercise (Exercise 2).
This reduces the main.c file to 12 lines, enabling portability, reusable, ease of reading through and ease of debugging.
There are 17 modules, including main.c. These are: gpio.c, gyro.c, i2c.c, knocking.c, main.c, peripherals.c, ptu_i2c.c, stm32fxx_hal_msp.c, stm32f3xx.it.c, syscalls.c, sysclock_config.c, sysmem.c, system_stm32f3xx.c, tim.c, usart.c, usb.c.
___

## Functions
Some notable functions are:
- init_peripherals() - This function initialises the board and its peripherals, like the USART module and i2c bus.
- detect_knock_pattern() - This function detects user knocks, checks them against the desired code, and returns when the code is entered correctly. It also prints characters to the USART1 bus whenever the user gets the code right or wrong, which are then interpreted by the GUI program.
- read_gyro() - This function reads the value of the specified axis of the gyroscope and returns it.


## User Instructions
1.	Upon system initialisation, the user is greeted with a message informing them that the communication lines have been jammed. 
2.	The user must determine how to spell out the word “H-E-I-S-T” in Morse code. A break in letters is represented by a pause of inputs greater than a duration of 1 second long.
3.	It is then up to the user to transmit “H-E-I-S-T” in Morse code: 

i.	• • • •,	 SPACE, 

ii.	•, 		 SPACE, 

iii.	• •, 		 SPACE, 

iv.	• • •,		 SPACE, 

v.	–, 		 *COMPLETE*.

to the Mission Control by tapping the combination on the head of the accelerometer board. Incorrect inputs will require the user to begin the sequence again.
4.	Upon completion of the module, a message will appear on the GUI congratulating the user.
___

## Constraints and Limitations:
- Dashes - the Gyroscope is not able to detect dashes. Fortunately, the first four letters of the word H-E-I-S-T all only contain dots in Morse code, and the last character is a single dash.

- Movement - the system cannot be used while the servos are moving, or on a soft surface, as this creates vibrations that are falsely registered as taps.
___

## Testing Procedure:
Each section of the code was tested individually before the entire module was integrated and tested as a whole. 
Gyro - The gyro was tested by taking the values from it and graphing them. We then confirmed that the outputs correctly changed based on the movement of the system.
Knocking - The knocking system was set to print a character whenever a knock was registered. We then tested that it correctly received each knock and did not produce unwanted knocks.
Dots and Spaces - the desired spacing between dots and between spaces was tested on its own until a desired threshold value was found. 
USART - the usart bus was tested by printing characters to the bus and detecting them on a computer.
Integration - the entire system was tested to ensure it matched the desired output.
___

# Exercise 3 : Radio Wave Interference:
## High-Level Overview:
This experience includes a simulated 'Radio Wave detector and Jammer' experience, simulated through interfacing our STM32F303 Discovery board with a magnetometer module as well an ADC module reading from 8 different ADC channels simultaneously. The experience flow is as follows: determine the correct "radio wave frequency band" by rotating a magnetic field around the magnetometer until it detects the correct orientation which is then displayed explicitly on the discovery board using LEDs, then jam the correct 'frequency band' using a 'broad wave emission device' (a bright torch) shinning on the correct LDR voltage divider circuit. The STM32F303 Discovery board interfaces with these external sensors manipulated by the user and controls the flow of the exercise. When the exercise is complete, the board will transmit a successful signal through its serial point to the host computer.

___

## Subtasks
1. Interfacing with GPIO for LED display: The STM32F303 Discovery board must be able to manipulate the state of its LEDs for communication purposes between the system flow and the user.
2. Interfacing with Magnetometer: Then Discovery board's integrated magnetometer must be activated, configured and read from to determine the board's bearing relative to its surrounding magnetic field. This magnetic field is produced by strong surrounding magnets which can be manipulated by the user. The raw reading received must be sorted into 8 bins to mirror the 8 chambers of interfaced ADCs and checked against the internally stored solution.
3. Interfacing with ADCs: The Discovery board must be able to receive and process analog inputs for all 8 sectors containing separate LDR voltage divider circuits simultaneously. It must then  be tuned to determine which of these circuits have been triggered and compare that to an internally stored solution.
___

## Modularisation
All modules have been separated into the respective .c files with a corresponding header file. The main file totals 9 lines with only the necessary functions for ease of readability, re-usability and ease of debugging. These files are named accordingly as: ADC_functions.c, board_config.c, calculation_functions.c, main.c, peripherals.c, and radio_interference.c. 
___

## Functions:
Some notable functions are:
- radio_interfere(): this is the function that calls the entire project. it contains the main overview of the Magnetometer and the ADC modules.
- mag_config(): this function sets the correct registers for reading and writing data and sets the magnetometer to continuously read in data.
- read_x_data(), read_y_data(), read_z_data(): these functions read the raw magnetometer data from the LSM303AGR magnetometer inside the STM32F3.
- calculate_degrees(): uses the x and y axis data from the magnetometer to calculate the angle using an arctan function. Due to the four quadrants (All Stations To Central), we have to adjust the data accordingly by adding 180 to data in quadrants 1 and 2 and adding 360 to the third quadrants data.
- calculate_average(): takes the most recent 10 data degree entries and averages them. it accounts for more incoming data using a shuffle function which means only the most recent data is used.
- check_solution(): compares the angle the magnetometer is looking at to the randomised solution, if correct, breaks the magnetometer loop and moves to the next internal module.
- poll_ADC(): this function will consistently check and re-initialise the LDRs to ensure they're ready to receive a change.
- check_match(): this function will cycle through the array of LDRs and the solution array and compare the values. In the solution array, only 1 value is 1 while all else is 0. The LDR array will contain the current LDR data, meaning that if the current LDR being looked at has a value of 1 in the array and the value in the solution is also equal to 1 at that index, the loop will break and the challenge is completed. Otherwise, it will continue cycling until a correct answer is inputted.

___
##Pin Out
- PA1: "North", ADC Channel 2
- PA2: "North East", ADC Channel 3
- PA3: "East", ADC Channel 4
- PF4: "South East", ADC Channel 5
- PC0: "South", ADC Channel 6
- PC1: "South West", ADC Channel 7
- PC2: "West", ADC Channel 8
- PC3: "North West", ADC Channel 9
- GND: Ground
- 3V: 3 Volts Power Supply

___
## User instructions:
1. Startup Program: Uploading code onto STM32F3 Discovery Board. Once the previous two challenges have been completed, this challenge will automatically begin.

2. Finding Correct Magnet Orientation: The LED display on the STM board will light up with 4 LEDs. The LEDs will stay in this state until the correct orientation of the magnetic field is present. 

3. Found correct Orientation: Once the orientation is found, the LED display will show the corresponding direction on the LED display (due to the LED display having a direction towards North, East, South, West). *NOTE that the program will not continue to the next stage until the correct orientation is found*

4. Shining a Light: Once the LED is displayed, the user will use the torch provided to shine a light in the corresponding direction in the box underneath. Inside the box are LDRs waiting to be triggered. *NOTE that ONLY the right LDR must be triggered to be completed*

5. Stages 1-4 will repeat 5 times with a random solution to be found.

6. Completion of the Exercise: When completed, all LEDs will light up on the LED display.
___

## Constraints and Limitations:
Light and LDR sensitivity: The LDRs measure the surrounding light level letting us detect a change in light too (resulting in a changed resistance), which is what we are measuring in our challenge. It is necessary to calibrate the LDR sensitivity to the amount of light in the room testing in and the brightness of the light used. Additionally, the LDRs can only meaningfully detect changes in light in a certain range meaning the surrounding environment must not be too bright for the system to function correctly.

Wiring Issues: As this exercise is heavily dependent on correct wiring, any wiring mishaps could cause this project to break and work erratically. Mishaps could include loose wiring, exposed wiring, or wires that have fallen out completely. Wires should be checked before each test to ensure accurate testing and a smooth run-through.

LDR Functionality: The LDRs are a major part of the second half of the challenge. Ensuring that ALL LDRs are correctly functioning is crucial for this project to be functional.

Magnetometer Position: The Magnetometer is positioned off-centre on the STM but is positioned centred on the physical challenge colosseum. With research on magnetic fields and how magnetometers work, we discovered that having the magnetometer off-centre means that our readings may be slightly disrupted. However, as we're sorting the readings into 8 sections, it doesn't have an effect on the functionality as our readings don't need to be incredibly accurate.

Power to STM32 Board: To ensure constant and correct power supply to the STM32 board, it's recommended that the computer used to upload the code be plugged into a charger. A lack of adequate power can lead to the erratic behaviour of the board and disrupt the escape room simulation.
___

## Test cases:
Magnetometer Readings: The first and largest test was to ensure that the magnetometer read data and it read it correctly. This was broken down into 4 major stages:

1. Read in non-zero and changing data: This process involved using the datasheet to confirm correct registers, correct functions, correct configuration values and using HAL. Multiple print statements were used to ensure that the values the magnetometer returned were non-zero. This was returned in milli gauss (mG) and displayed the strength of the magnetic field on the x, y, and z-axis of the magnetometer. As the magnetometer moved, we had to check that the values also changed. Once this was confirmed, we could move on to interpreting the results.
2. Graph data and interpret results: Using the Arduino Serial Plotter, each cycle of the program returned and printed the corresponding values for each axis. This change in values was plotted on a graph. This data was showing the strength of the magnetic fields present. Tests with things such as fridge magnets, whiteboard erasers, car keys and iPhones showed spikes in data as the field changed from the Earth's magnetic field to the closer one.
3. Calculating degrees from the data: Now that the data was accurately reading changes in magnetic fields, we could use the data to calculate what direction the magnetometer was facing based on a local magnetic field (we decided to use a local field as using the Earths proved to have too much interference and the field wasn't strong enough for our use). This was done by taking the x and y-axis data and using the inverse tan function to calculate the angle from the x-axis. Each quadrant of a coordinate graph would produce an angle, however, we had to ensure that we defined a reference point as angle 0 and measured from there, and adjusted the measurement accordingly. E.g. In quadrant 2 (stating that quadrant 1 is the top right quadrant and the quadrants move anti-clockwise), calculating the angle using inverse tan (giving a negative angle) means you then need to add 180 degrees. Similarly, in quadrant 3, you receive a positive result and also add 180. 
4. Displaying the data: The final step was to ensure that the STM LED display would correctly show the LED corresponding to the angle it was facing. 

Once these tests were completed and functioning correctly, the magnetometer could be implemented into the project.

ADC Segment:

1. Read an analog signal from one LDR: Shine a strong light on the LDR voltage divider circuit. This was temporarily configured to a STM32 Discovery board LED which was expected to light up when sufficient light was detected. This worked as expected.
2. Change sensitivity of ADC trigger threshold: Configure software sensitivity to high then shine a weak light over the LDR circuit. The circuit did not transmit a high enough voltage to trigger the discovery board's LED. This worked as expected.
3. Read from multiple ADC channels at once: Connect one LDR voltage divider circuit to one pin on the discovery board connected to a configured ADC channel. Configure for high sensitivity and shine a light on it. We configured each individual ADC channel to trigger its unique LED on the discovery board. Shining a light on the circuit activated the correct LED and when it was rewired to a different channel's pin, its respective LED turned on while the previous one turned off. This is as expected and demonstrates the ability to read from multiple channels.
4. Read from multiple LDR voltage divider circuits at once: Connect 8 LDR Voltage divider circuits to 8 unique channels configured for high sensitivity. Shine a torch on chosen LDRs and their respective LEDs assigned by software on the board should activate. This worked as expected.
5. Compare activated LDRs to an external solution array: An external solution array was created which corresponded to the desired states of each LDR voltage divider. These LDRs were activated simultaneously using a torch to see if the system would detect the current state of the LDRs to match the external solution. The match passed which locked the system. This was as desired

With these tests completed and functioning as expected, the ADC could be fully implemented into the rest of the project.

Light: One of the tedious tasks to test for was the light that shined on the LDRs. Our first test was with an iPhone flashlight. We discovered that this light was not enough to produce a change in the LDRs. Our two options were to create a larger hole to input light but that risked having light leak into the chambers, compromising the sensitivity of the LDRs. We decided on a torch that was much brighter than a phone light that will be given in the challenge alongside the other physical components.

Integrating the two parts: Our main test for integration was that the second half would not commence until the first half (finding the angle to shine in the light) was completed. We tested each LDR singularly to ensure that it does not show the completion screen without finding the correct magnet orientation.

___


# Exercise 4 : Capacitive Touch: 

## High-Level Overview:
This scenario requires the heist robot to help you hack into a system of capacitive sensors in order to secure a safe exit out of the bank. Assuming that the robot has already been physically connected to the exit door, it will help you decipher the exit code combination that needs to be manually inputted by the user in the correct sequence. The combination of LED colours displayed on the STM32F303 Discovery board’s LEDs will correlate with the colours of wires that must be simultaneously manually pressed. After this exercise has been completed, you will have escaped out of the secret exit of the bank and seamlessly blend into the busy crowd with your stolen bounty intact. 
___

## Subtasks
1.	Observation of the LEDs: the code displayed on the STM32F303 by coloured LEDs must be observed.
2.	The corresponding wire or combination of wires on the physical module must be pressed.
3.	If the correct corresponding wires are pressed, the next sequence of LEDs will light up, and the task will continue.
Completion of the Exercise: After the correct sequence of capacitive touch entries has been made, the final rectangle on the GUI will light up green, signalling the completion of the final exercise.
___

## Modularisation:
All modules have been separated into appropriate peripheral files, each with a respective .c file in the Source folder and a .h file in the Includes folder for the exercise (Exercise 4).
This reduces the main.c file to 10 lines, enabling portability, reusable, ease of reading through and ease of debugging.
There are 14 modules, including main.c. These are: gpio.c, LEDs.c, main.c, peripherals.c, security_module.c stm32fxx_hal_msp.c, stm32f3xx.it.c, syscalls.c, sysclock_config.c, system_stm32f3xx.c, touch.c, tsc.c, usart.c, usb.c.
___

## Functions:
Some notable functions are:
- init_peripherals() - This function initialised the STM board, HAL, and the various peripherals like i2c, USART, and the Touch Sensing Controller (TSC)
- run_security_module() - This function contains the main loop of the program - it generates a colour combination, displays it, and then waits until the user inputs the correct combination, before repeating this a specified number of times
- readTSC() - This function discharges, then starts a touch acquisition, before waiting until the acquisition is complete. This is necessary to get touch data.
- get_TSC_colours() - This function reads all the touch sensors, and compares them against their threshold, before returning a number whose bits represent the wires that are touched.

___

## User Instructions:
1.	Upon system initialisation, the user is greeted with a message informing them that all that is standing in their way is a maze of capacitive touch sensors to be deciphered by the robot and then manually inputted by the user.
2.	The user must observe the combination of LED lights that are lit on the STM32F303 board. 
3.	It is then up to the user to use both of their hands to manually press the correct entry of wires. If, for instance, the green and red LEDs are lit, then the green and red exposed wires must be pressed, simultaneously. 
4.	Upon completion of the module, a message will appear on the GUI congratulating the user on their escape.
___

## Constraints and Limitations:
The number of wires - The module cannot have more than 8 wires as the STM32F3 has only 8 TSC groups. There are also only 4 colours of LEDs on the board, so we would have to start using external LEDS to have more than 4 colours.

___

## Testing Procedures:
- Individual Wires: Each wire was tested individually to determine a threshold of detection.
- All wires: All 16 combinations of wires begin pressed/not pressed to ensure the thresholds worked for all combinations.
- LEDs: the turn_on_colour and turn_off_colour functions were tested with each colour to ensure that all the LEDs worked and the function correctly toggles the right colour.
- Integration: The entire system was tested to ensure that it functioned as expected.
___

# GUI: 

## High-Level Overview:
The GUI controls the overall flow of the program and provides feedback and instruction to the user.
___

## Subtasks
1.	Receive Serial messages from boards
2. 	Parse Serial inputs and update the GUI accordingly
3. 	Provide information to the user via the description box
___

## Modularisation:
The code has been separated into a main file, a GUI controller file, a UART controller file, and a general state machine file which contains the system logic.
___
