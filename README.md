# HJLLMS 
Major Project

This document serves to document high-level information about the practical implementation of C language to program a STM32F303 microcontroller to design and implement a proof-of-concept
technology for a 5-minute escape room experience.

___
___

## Group members, Responsibilities
1. Joel Pivetta | 520447488       
Exercise 1 : Safe Crack (servo peripheral)
2. Haz Salvesen     | 490480278       
Exercise 1 : Safe Crack (potentiometer, LED peripherals), Hardware, Documentation
3. Lachlan Irving   | 490627792      
Exercise 4 : Capacitive Touch, Minutes
4. Matlyda Hayne    | 520471933       
Exercise 3 : Sundial 
5. Samuel Richards  | 520482962       
Exercise 2 : Knocking, GUI, Exercise 4 : Capacitive Touch
6. Luis Sanabria    | 510432236       
Exercise 3 : Sundial
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
This experience includes a simulated vault cracking sequence which is realised through the interaction between an STM32F303 Discovery board, a potentiometer, a lock-picking robot's servo, and an LED light. The concept is centered around the notion of a vault with a dial lock. The dial, represented by the potentiometer, needs to be manipulated in a certain pattern to 'crack' the vault's code, similar to how a lock-picking robot would function. The STM32F303 Discovery board is the heart of the system, responsible for interfacing with the potentiometer and mimicking the movements of a lock-picking robot's servo.

## Subtasks
1. Interfacing with Potentiometer: The STM32F303 Discovery board must be programmed to read the analog inputs from the potentiometer, which represents the dial on the vault. The position of the dial is determined by the resistance of the potentiometer, which changes as it is turned.
2. Mimicking Lock-Picking Robot's Servo: Based on the analog inputs from the potentiometer, the board will simulate the actions of a lock-picking robot's servo. This includes rotating the dial to certain positions and pausing for a specified amount of time to mimic the process of 'feeling' for the correct combination.
3. Checking Combination: The board will be programmed to recognize specific sequences of movements as combinations. For example, if the dial moves to the right to 30, then left to 20, and finally right to 10, this could be recognized as a correct combination.
4. LED Light Activation: Once a correct combination is entered, the board will send a signal to light up the LED. This serves as a visual confirmation that the correct combination has been entered and the vault is 'unlocked'.

NB: Since the final task is an extension of this task, only the final task is shown, so R4 contains the actual string to be stepped through, whilst R5 holds each byte or character. The binary value of this register is then displayed in the 8 LEDs.
___

## Modularisation:
Numerous functions perform specific tasks, and follows an intuitive design with functions being delacred in ascending order. 
___

## Functions:
- setGPIO: Enables GPIOA and GPIOE for the button and LEDs, and sets GPIOE output.
- enableInterrupts: Configures and enables external interrupts for EXTI0.
- EXTI0_IRQHandler: Handles the EXTI0 interrupt by running the button press handler and resetting the interrupt.
- main: Sets GPIO, assigns the show_pattern function as the button press handler, enables interrupts, and enters an infinite loop.
- show_pattern: Displays an ASCII character pattern on the LEDs, cycling through the characters of the string "Michael" on each button press, and disables the button after the last character. By changing one comment code, it can also go back to the beginning of the string and show "Michael" again and again. 
___

## User Instructions
The program starts there are no lights on. If the input button is pressed, the board switches to the ASCII character stepping mode and then pressing the buttons steps through the ASCII character that is defined.
___

## Constraints & Limitations:
Limitation in scope: 
The code is specific to STM32F303 and may not be used with other hardware, limiting its adaptability. The code is written in C, however, and so is much more portable than assembly code. All that needs to be changed to make this code work with another device is to change the I/O definitions. 
Lack of scalability: 
The code was developed for the specific task of controlling eight LEDs, and modifications to the program will be required to handle different numbers of LEDs, restricting its scalability.
Input limitations: The program relies on a single input button to step through the ASCII characters, making it less user-friendly and less efficient in handling multiple inputs.
___

## Testing Proceedures:
In order to check that the anticlockwise and clockwise functions worked as expected, different inputs for R1 and R2 were provided and it wasverified that only one LED was on at a given time. The selected LED moved either clockwise or anticlockwise around the circle of LEDs.
The ASCII to LED pattern mapping was tested and verified by checking that each ASCII character in the string provided in the code generates the expected LED pattern on the board.
The string stepping functionality was tested by pressing the input button and verifying that the LED pattern changes to the next ASCII character in the string.
The wraparound functions was checked by verifying that the binary bits are wrapped around when going clockwise or anticlockwise, and that the LED pattern was still correct.
___
___


# Exercise 2 - Serial Communication:

## High Level Overview:

Exercise 2 explores UART communication on the STM32 microcontroller, where UART is an asynchronous serial communication protocol that allows two devices to communicate without sharing clock information. The exercise is divided into four tasks:

1. Task 1 extends the serial module in week6-modular-design to include receiving serial data, and stores this data in a memory buffer. 
2. Sends data with a defined terminating character when the transmission is complete.
3. Replaces the serial receiving process with an interrupt based approach. 
4. Replaces the serial transmission process with an interrupt based approach.


___

## Modularisation
This section was designed to be modular by splitting it into multiple functions which can be individually called - e.g. the enableUSART, transmit_string, and receive_string functions.
___

## Functions
- enableUSART1: Enable GPIO C and USART1's clocks, set GPIO C to use UART as alternate function, set the baud rate and ready USART 1 for both receive and transmit
- enableInterrupts: Configures and enables external interrupts for EXTI0.
- enableLEDs: Enable clock for Port E (LEDs), get the most significant 16 bits of port mode register as that is where the mode for the LEDs are defined
- enableInterrupts: Generate an interrupt upon receiving data and set priority and enable interrupts
- USART1_EXTI25_IRQHandler: Allow main function to occur.

## User Instructions
The user needs to build and load the function onto the discovery board and load putty through their terminal at a baud rate of 115200. After that point when the user enters a string into putty the string is stored in a buffer and then transmitted back to putty so the user can see what they transmitted. A new line is also added. 
___

## Constraints and Limitations:
The system is constrained by the amount of USART ports available on the device, as well as the type of characters that can be sent over the USART bus. Additionally, when transmitting high amounts of data the USART protocol might not be fast enough or have enough error checking.
___

## Testing Procedure:

Since this system uses a real-time system, debugging using breakpoints is often not possible. Thus, most debugging was done by printing a lot of data to the serial port of the computer. Such as:

```
Hello40
Hello40
Hello40
Hello40
Hello40
```


This did make it quite difficult to debug when it was a serial issue, but all issues were eventually resolved. We used a list of testing strings which contained a variety of characters. We then made sure that when typed into one Serial Console, the input was mirrored in the Serial Console on the other computer.
___

# Exercise 3 - Hardware timer:

Exercise 3 focuses on creating a module that interfaces with hardware timers. The exercise contains two tasks:

1) a function in the timer module that triggers a callback function at regular intervals. The interval is set during the module initialisation process.

2) a function that triggers a one-time callback function after a specified delay in milliseconds. This function accepts the delay and the callback function pointer as inputs.
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


# Exercise 4 - Integration: 


## High Level Overview:
Exercise 4 serves as an integration exercise, combining most of the functions created in prior exercises. The main objective is to perform a sequence of operations on three STM32 discovery boards that are connected via UARTs. The task involves are:

a) When a button is pressed, trigger the transmission of a string containing a number(in ASCII) over serial.
b) When a string containing a number is received, incorporate a timer based delay before subtracting 1 from the number and transmitting to back to the source. The time delay should be equal the number received multiplied by 100ms (i.e. receive 8, wait for 800ms, 7 is 700ms, etc). When the number is zero, do not transmit.
c) When a number is received, turn on that many LED lights. If the number is larger than 8, turn on all lights for an even number, and no lights for an odd number.
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
