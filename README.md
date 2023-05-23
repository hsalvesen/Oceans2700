# Ocean's 2700
Major Project

This document serves to document high-level information about the practical implementation of C language to program a STM32F303 microcontroller to design and implement a proof-of-concept
technology for a 5-minute escape room experience.


# Escape Room Storyline: The Bank Heist
In the heart of the city lies an infamous bank, a fortress reputed for its invincible vault. Today, your team embarks on a daring mission: infiltrate the bank, crack the vault, secure the priceless artifact, and escape without leaving a trace. Precision is key, and silence is your weapon.

#### Exercise 1: Safe Crack

Your first challenge is to crack the vault. This is no ordinary vault; it boasts an antiquated dial lock system that demands meticulous manipulation. Your ally in this endeavor is a specialized bank heist robot, designed to decode the right combination to pick the lock. As the robot deciphers each part of the combination, an LED illuminates, signaling your progress. With the robot's help, you breach the vault and secure the coveted artifact.

#### Exercise 2: Report to Mission Control

With the artifact in your possession, it's crucial to inform mission control. Luckily, the heist robot is equipped with a unique communication channel. Your task is to interface with this system, encoding your message in Morse code. Each carefully tapped dot and dash confirms the successful extraction of the artifact.

#### Exercise 3: Hacking Police Radio Channel

But success has its echoes, and the authorities are now alerted to a possible breach. Their radio chatter buzzes urgently. Your next challenge is to hack into the police radio channel, creating a diversion. You have at your disposal a sundial-like device, outfitted with a magnetometer, which you use to distort the magnetic field and jam the radio signals. The police are successfully redirected, buying you some much-needed time.

#### Exercise 4: Exiting the Bank

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
Exercise 4 : Capacitive Touch, Minutes

4. Matylda Hayne    | 520471933       
Exercise 3 : Hacking Police Radio Channel (Sundial (magnetometer))

5. Samuel Richards  | 520482962       
Exercise 2 : Report to Mission Control (Knocking), GUI, Exercise 4 : Exiting the Bank (Capacitive Touch) 

6. Luis Sanabria    | 510432236       
Exercise 3 : Hacking Police Radio Channe (Sundial (LDRs))
___

## Roles
HJLLMS functioned like a start-up, forming a lateral hierachy, where each member was responsible for their own work, and there was no one overarching lead.
___
___

## Lab Minutes
Lab minutes are recorded as READMEs, located in the corresponding "minutes" folder
___
___


# Exercise 1 : Safe Crack

## High Level Overview:
This experience includes a simulated vault cracking sequence which is realised through the interaction between an STM32F303 Discovery board, a potentiometer, a lock-picking robot's servo, and an LED light. The concept is centered around the notion of a vault with a dial lock. The dial, represented by the potentiometer, rests on a Cartesian plane and needs to be manipulated in a certain pattern to 'crack' the vault's code, similar to how a lock-picking robot would function. The STM32F303 Discovery board is the heart of the system, responsible for interfacing with the potentiometer and mimicking the movements of a lock-picking robot's servo.

## Subtasks
1. Interfacing with Potentiometer: The STM32F303 Discovery board must be programmed to read the analog inputs from the potentiometer, which represents the dial on the vault. The position of the dial is determined by the resistance of the potentiometer, which changes as it is turned.
2. Mimicking Lock-Picking Robot's Servo: Based on the analog inputs from the potentiometer, the board will simulate the actions of a lock-picking robot's servo. This includes rotating the dial to certain positions and pausing for a specified amount of time to mimic the process of 'feeling' for the correct combination.
3. Checking Combination: The board will be programmed to recognise specific sequences of movements as combinations. For example, if the dial, on  moves to the right to 30 degrees, then left to 20 degrees, and finally right to 10 degrees, this could be recognized as a correct combination.
4. LED Light Activation: Once a correct combination is entered, the board will send a signal to light up the LED. This serves as a visual confirmation that the correct combination has been entered and the vault is 'unlocked'.

___

## Modularisation:
Numerous functions perform specific tasks, and follows an intuitive design with functions being delacred in ascending order.
___

## Functions:
- angle_generation: Creates 5 randomised angles between 0 and 180 degrees based on current SysTick value.
```
for (uint32_t i = 0; i < 5; i++)
	{
		   predefined_angles_degrees[i] = (SysTick->VAL % 181); // generate a random number within the loop
    }
 ```
- angle_conversion: Converts angles generated into appropriate form to be recognised and interpretted by the potentiometer and the panning servo motor.
- state_machine: Enables a stepping through of each of the 5 lock combinations. 
- communicate: Communicates that the module has been completed to our GUI.

___

## User Instructions
1. Starting the Program: Upon uploading the code to the STM32F303 Discovery board, the escape room simulation will automatically start.

2. Servo Movements: The servo, representing the lock-picking robot, will begin at its origin point (90 degrees). It will then rotate towards its final angle before resetting back to 90 degrees. This cycle of movement will continue until the correct angle is entered via the lock dial, represented by the potentiometer, and held there for 3 seconds.

3. Entering the Correct Angle: As a user, you will manipulate the potentiometer to set the correct angle. The program has a small tolerance for accuracy, so it doesn't need to be exact.

4. LED Indication: Once you've set the potentiometer to the correct angle, a green LED on the Discovery board will turn on for 3 seconds before turning off. This serves as your signal that you've entered the correct angle on the lock dial.

5. Repeating the Process: The servo will then start moving towards the next predefined angle. You will need to repeat the process of setting the potentiometer to the correct angle for the new servo position. This cycle will continue until all 5 predefined angles have been entered correctly, in sequence.

Completion of the Exercise: After the correct sequence of angles has been entered, the servo will reset to 0 degrees and stop moving. The green LED will light up and stay on, signaling the successful completion of the exercise.

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
___
___


# Exercise 2 : Reporting to Mission Control

## High Level Overview:
This scenario involves an encoded message delivery operation simulated via interactions between the lock-picking robot and manual Morse code translation. The premise hinges on the idea of a message coded in Morse that needs to be relayed accurately by tapping on the robot's accelerometer. The GUI acts as a channel that can report back if the correct message has been sent and recieved by Mission Control

___
## Subtasks
1. Morse Code Translation: A predefined text message ("HEIST") must be manually converted, letter-by-letterm into its corresponding Morse signal.
2. Tapping in the correct message: the Morse code must be entered in by tapping the accelerometer. The number of taps must correspond to each respective letter. 
3. Confirming the Message: The board will compare the signal received by the accelerometer with the original, predefined word in Morse code. If they match, it means the message has been transmitted successfully, and the GUI will report this

___
## Modularisation
xxx
___

## Functions
- 

## User Instructions
xxx
___

## Constraints and Limitations:
xxx
___

## Testing Procedure:
xxx
___

# Exercise 3 - Radio Wave Interference:

xxx
___

## Subtasks
xxx
___

## Modularisation
Sub-exercises follow the general routine:
Initialise:
- Discovery board
- External hardware timer
Set parameters
- Check hardware timer count against a user specified delay value.

## Functions:
- enable_clocks: Enables required clocks for GPIO and TIM2.
- initialise_board: Initializes the LED pins on the board.
- timer_module_init: Initializes the timer module with a specified interval and regular interval callback.
- set_one_shot_callback: Sets a one-shot callback with a specified delay.
- TIM2_IRQHandler: Handles regular interval callbacks and one-shot callbacks for the TIM2 interrupt.
- regular_interval_cb: Toggles the LEDs as a regular interval callback function.
- one_shot_cb: Turns on all LEDs, waits for a certain time, and then turns them off as a one-shot callback function.
- main: Disables interrupts, enables required clocks, initializes the board, configures TIM2 timer, enables interrupts, initializes the timer module, sets a one-shot callback, and enters an infinite loop.
pressed: Detected when button is pressed -> checks if unpressed
unpressed: Detected button is unpressed from pressed -> restarts script with new settings
___
## User instructions:
A user can change the conditions of each delay script by changing either 2 saved values in any of the sub exercises: 
- timer_module_init(1000, regular_interval_cb); // Change regular callback time (in milliseconds)
- set_one_shot_callback(3000, one_shot_cb); // Change 1 shot CB begin time (in milliseconds)
With a PRESCALER value of 8 and multiplied by 1000, the DELAY value will be a delay in ns, then ms.
___

## Constraints and Limitations:
Both DELAY and PRESCALER values are unsigned 32 bit values (in the case of using TIMx_ARR, it can only be 32 bits using TIM_2 which is used in this exercise), as such the script will not function outside these parameters (e.g. a negative value).
___

#### Test cases:
1. Implement delay (without visual indicator)
    1. The test parameters include: a delay value of 10, prescaler of 8000. When stepping through code, code is delayed until the hardware timer CNT value exceeds 10 before proceeding with an infinite loop. This is as expected
    2. The test parameters include: a delay value of 5000, prescaler of 8000. When stepping through code, code is delayed until the hardware timer CNT value exceeds 5000 before proceeding with an infinite loop. This is as expected
    3. The test parameters include: a delay value of 0, prescaler of 8000. When stepping through code, code is not delayed and proceeds with the infinite loop. This is as expected.
2. Implement delay (without visual indicator) + button input changes prescaler value
    1. The test parameters include: a delay value of 5000, prescaler of 8000. When code is run, a pattern on LEDs turns on. After 5 seconds the pattern alternates to all on is off, all off is on. This occurs every 5 seconds. This is expected
    2. The test parameters include: a delay value of 5000, prescaler of 4000. When code is run, a pattern on LEDs turns on. After 2.5 seconds the pattern alternates to all on is off, all off is on. This occurs every 2.5 seconds. This is expected
    3. The test parameters include: a delay value of 5000, prescaler of 16000. When code is run, a pattern on LEDs turns on. After 10 seconds the pattern alternates to all on is off, all off is on. This occurs every 10 seconds. This is expected
    4. The test parameters include: a delay value of 5000, prescaler of 4000. When code is run, a pattern on LEDs turns on. Initially after 2.5 seconds the pattern alternates to all on is off, all off is on. This occurs every 2.5 seconds until a user button is pressed. The delay will then increase to 5.0 seconds. Pressing the button 2 more times on top of this increases delay to 10 seconds. This is expected.
3. Implement delay with ARPE and ARR 
    1. The test parameters include: a delay value of 5000, prescaler of 8000. When code is run, a pattern on LEDs turns on. After 5 seconds the pattern alternates to all on is off, all off is on. This occurs every 5 seconds. This is expected
    2. The test parameters include: a delay value of 5000, prescaler of 4000. When code is run, a pattern on LEDs turns on. After 2.5 seconds the pattern alternates to all on is off, all off is on. This occurs every 2.5 seconds. This is expected
    3. The test parameters include: a delay value of 5000, prescaler of 16000. When code is run, a pattern on LEDs turns on. After 10 seconds the pattern alternates to all on is off, all off is on. This occurs every 10 seconds. This is expected
___
___


# Exercise 4 - Capacitive Touch: 


## High Level Overview:


___

## Subtasks
xxx

___

## Modularisation:
The code was split up into several functions, for example a transmit_char function and an enableUSART function. This allowed the code to be reused from previous tasks and in multiple places in code.
___

## Functions:
- enableUSART1: Enable GPIO C and USART1's clocks, set GPIO C to use UART as alternate function, set the baud rate and ready USART 1 for both receive and transmit
- enableInterrupts: Signify that the external interrupt should occur on the rising edge, enable interrupts from EXTI0 and set priority and enable interrupts
- EXTI0_IRQHandler: Run the intended functionality for the interrupt and then resets interrupt.
- sendAscii: Utilises the functions from part 2 to transmit containing an integer to putty.
___

## User Instructions:
The code needs to be built and Putty opened at a abud rate of 115200. When the button is pushed a numerical string is sent to putty. 
___

## Constraints and Limitations:
The system is constrained as the button cannot be pressed while the delay is still occuring. This was not mentioned in the assignment notification, and it would take significant time and additional knowledge that we do not have.
___

## Testing Procedures:
To test the integration process, each board's LED patterns can be observed to see if they match the expected output. 
The UART transmission and reception can be checked by monitoring the transmitted and received characters on a computer terminal program. 
The delay function can be tested with different parameter values to ensure that the delay time is variable. 
Boards Each pair of boards (1-2, 2-3, 1-3) can be tested individually when all three are not available.
___
