# Exercise 1 : Safe Crack

## High Level Overview:
This experience includes a simulated vault cracking sequence which is realised through the interaction between an STM32F303 Discovery board, a potentiometer, a lock-picking robot's servo, and an LED light. The concept is centered around the notion of a vault with a dial lock. The dial, represented by the potentiometer, rests on a Cartesian plane and needs to be manipulated in a certain pattern to 'crack' the vault's code, similar to how a lock-picking robot would function. The STM32F303 Discovery board is the heart of the system, responsible for interfacing with the potentiometer and mimicking the movements of a lock-picking robot's servo.

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
- adc(): Converts angles generated into appropriate form to be recognised and interpretted by the potentiometer and the panning servo motor.
- safecracker(): Enables a stepping through of each of the 5 lock combinations. 
- serial(): Communicates that the module has been completed to our GUI.
- usart(): enables communication to GUI
- Init_Peripherals(): initialises all necessary peripherals, defined elsewhere.
- run_safecracker(): begins infinite loop.

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

Power to STM32 Board: To ensure constant and correct power supply to the STM32 board, it's recommended that the computer used to upload the code be plugged into a charger. A lack of adequate power can lead to erratic behavior of the board and disrupt the escape room simulation.
___

## Testing Proceedures:
Directional Rotation Test: By providing different inputs via the potentiometer, we can test the lock-picking robot's servo ability to mimic both anticlockwise and clockwise rotations. Verification will involve ensuring that the servo's direction of rotation matches the potentiometer's movement.

LED Confirmation Test: The LED light should only activate upon entering a correct angle. Test this by providing a range of correct and incorrect inputs, and verifying that the LED lights up only for correct inputs.

Angle-to-Servo Mapping Test: To verify that each angle set via the potentiometer generates the expected servo movement, set predefined angles and observe the corresponding servo actions.

Sequence Stepping Test: Similar to string stepping functionality, we should test the system's ability to progress through the sequence of angles. After entering each correct angle, the system should move to the next step in the sequence. This can be tested by entering correct angles and verifying the progression to the subsequent servo positions.

Wraparound Test: Like the wraparound function for binary bits, the potentiometer's rotation should wrap around within the 0-180 degrees range. This can be tested by rotating the potentiometer beyond 180 degrees and verifying that the system correctly interprets this as a wraparound within the servo's range.

Finally, all of the modules were tested together to check for cohesive functionality. 

___
___
