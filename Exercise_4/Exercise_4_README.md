# Exercise 4 : Capacitive Touch: 

## High Level Overview:
This scenario requires the heist robot to help you hack into a system of capacitive sensors in order to secure a safe exit out of the bank. Assuming that the robot has already been physically connected to the exit door, it will help you decipher the exit code combination that need to be manually inputted by the user in the correct sequence. The combination of LED colours displayed on the STM32F303 Discovery board’s LED’s will correlate with the colours of wires that must be simultaneously manually pressed. After this exercise has been completed, you will have escaped out the secret exit of the bank and seamlessly blend into the busy crowd with your stolen bounty intact. 
___

## Subtasks
1.	Observation of the LEDs: the code displayed on the STM32F303 by coloured LEDs must be observed.
2.	The corresponding wire or combination of wires on the physical module must be pressed.
3.	If the correct corresponding wires are pressed, the next sequence of LEDs will light up, and the task will continue.
Completion of the Exercise: After the correct sequence of capacitive touch entries have been made, the final rectangle on the GUI will light up green, signalling the completion of the final exercise.
___

## Modularisation:
All modules have been separated into appropriate peripheral files, each with a respective .c file in the Source folder and a .h file in the Includes folder for the exercise (Exercise 4).
This reduces the main.c file to 10 lines, enabling portability, reusable, ease of reading through and ease of debugging.
There are 14 modules, including main.c. These are: gpio.c, leds.c, main.c, peripherals.c, security_module.c stm32fxx_hal_msp.c, stm32f3xx.it.c, syscalls.c, sysclock_config.c, system_stm32f3xx.c, touch.c, tsc.c, usart.c, usb.c.
___

## Functions:
- init_peripherals() - This function initialised the STM board, HAL, and the various peripherals like i2c, USART, and the Touch Sensing Controller (TSC)
- run_security_module() - This function contains the main loop of the program - it generates a colour combination, displays it, then waits until the user inputs the correct combination, before repeating this a specified number of times
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
Number of wires - The module cannot have more than 8 wires as the STM32F3 has only 8 TSC groups. There are also only 4 colours of LEDs on the board, so we would have to start using external LEDS to have more than 4 colours.

___

## Testing Procedures:
- Individual Wires: Each wire was tested individually to determine a threshold of detection.
- All wires: All 16 combinations of wires begin pressed/not pressed to ensure the thresholds worked for all combinations.
- LEDs: the turn_on_colour and turn_off_colour functions were tested with each colour to ensure that all the LEDs worked and the function correctly toggles the right colour.
- Integration: The entire system was tested to ensure that it functioned as expected.
___

# GUI: 

## High Level Overview:
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
