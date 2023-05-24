# Exercise 2 : Reporting to Mission Control

## High Level Overview:
This module involves the user tapping the IMU on the PTU to transmit an encoded morse-code message to mission control. The user must enter the correct code to continue.

___
## Subtasks
1.	Morse Code Translation: A predefined text message ("HEIST") must be manually converted, letter-by-letter into its corresponding Morse signal.
2.	Tapping in the correct message: the Morse code must be entered in by tapping the accelerometer. The number of taps must correspond to each respective letter.
3.	Confirming the Message: The board will compare the signal received by the accelerometer with the original, predefined word in Morse code. If they match, it means the message has been transmitted successfully.
Completion of the Exercise: After the correct sequence of Morse code has been entered, second rectangle on the GUI will light up green, signalling the completion of the second exercise.
___
## Modularisation
All modules have been separated into appropriate peripheral files, each with a respective .c file in the Source folder and a .h file in the Includes folder for the exercise (Exercise 2).
This reduces the main.c file to 12 lines, enabling portability, reusable, ease of reading through and ease of debugging.
There are 17 modules, including main.c. These are: gpio.c, gyro.c, i2c.c, knocking.c, main.c, peripherals.c, ptu_i2c.c, stm32fxx_hal_msp.c, stm32f3xx.it.c, syscalls.c, sysclock_config.c, sysmem.c, system_stm32f3xx.c, tim.c, usart.c, usb.c.
___

## Functions
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
Dashes - the Gyroscope is not able to detect dashes. Luckily, the first four letters of the word HEIST all only contain dots, and the last character is a single dash.
Movement - the system cannot be used while the servos are moving, or on a soft surface, as this creates vibrations which are falsely registered as taps.
___

## Testing Procedure:
Each section of the code was tested individually before the entire module was integrated and tested as a whole. 
Gyro - The gyro was tested by taking the values from it and graphing them. We then confirmed that the outputs correctly changed based on the movement of the system.
Knocking - The knocking system was set to print a character whenever a knock was registered. We then tested that it correctly received each knock and did not produce unwanted knocks.
Dots and Spaces - the desired spacing between dots and between spaces was tested on its own until a desired threshold value was found. 
USART - the usart bus was tested by printing characters to the bus and detecting them on a computer.
Integration - the entire system was tested to ensure it matched the desired output.
___
