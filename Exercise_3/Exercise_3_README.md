# Exercise 3 : Radio Wave Interference:
## High Level Overview:
This experience includes a simulated 'Radio Wave detector and Jammer' experience, simulated through interfacing our STM32F303 Discovery board with a magnetometer module as well an ADC module reading from 8 difference ADC channels simultaneously. The experience flow is as follows: determine the correct "radio wave frequency band" by rotating a magnetic field around the magnetometer until it detects the correct orientation which is then displayed explicitly on the discovery board using LEDs, then jam the correct 'frequency band' using a 'broad wave emission device' (a bright torch) shinning on the correct LDR voltage devider circuit. The STM32F303 Discovery board interfaces with these external sensors manipulated by the user and controls the flow of the exercise. When the exercise is complete, the board will transmit a successful signal through its serial point to the host computer.

___

## Subtasks
1. Interfacing with GPIO for LED display: The STM32F303 Discovery board must be able to manipulate the state of its LEDs for communication purposes between the system flow and the user.
2. Interfacing with Magnetometer: Then Discovery board's integrated magnetometer must be activated, configured and read from to determine the board's bearing relative to its surrounding magnetic field. This magnetic field is produced by strong surrounding magnets which can be manipulated by the user. The raw reading recieved must be sorted into 8 bins to mirror the 8 chambers of interfaced ADCs and checked against the internally stored solution.
3. Interfacing with ADCs: The Discovery board must be able to recieve and process analog inputs for all 8 sectors containing seperate LDR voltage divider circuits simultaneously. It must then  tuned to determine which of these circuits have been triggered and compare that to an internally stored solution.
___

## Modularisation
XXXX
___

## Functions:
Some notable functions are:
- enable_clocks() & enableLED(): Enable the clocks and LED's on the STM board
- Channel Select functions:
	- ADC_select_CH2 (void): 
	- ADC_select_CH3 (void):
	- ADC_select_CH4 (void):
	- ADC_select_CH5 (void):
	- ADC_select_CH6 (void):
	- ADC_select_CH7 (void):
	- ADC_select_CH8 (void):
	- ADC_select_CH9 (void):
- shuffleArray(float array[], float degrees): Used when calculating average of previous magnetometer data, this specific funcion will move the data one place left in the array each cycle and add the new read in data as the last element. This ensures a moving average can be calculated.
- turnOnLED(int pos): Will turn on the LED on the display corresponding to the integer value it receives.
___
## User instructions:
1. Startup Program: Uploading code onto STM32F3 Discovery Board. Once the previous two challenges have been completed, this challenge will automatically begin.

2. Finding Correct Magnet Orientation: The LED display on the STM board will light up with 4 LED's. The LED's will stay in this state until the correct orientation of the magnetic field is present. 

3. Found correct Orientation: Once the orientation is found, the LED display will show the corresponding direction on the LED display (due to the LED display having a direction towards North, East, South, West). *NOTE that the program will not continue to the next stage until the correct orientation is found*

4. Shining a Light: Once the LED is displayed, the user will use the torch provided to shine a light into the corresponding direction in the box underneath. Inside the box are LDR's waiting to be triggered. *NOTE that ONLY the right LDR must be triggered to be completed*

5. Stages 1-4 will repeat 5 times with a random solution to be found.

6. Completion of the Exercise: When completed, all LED's will light up on the LED display.
___

## Constraints and Limitations:
Light and LDR sensitivity: The LDRs measure the surrounding light level letting us detect a change in light too (resulting in a changed resistance), which is what we are measuring in our challenge. It is necessary to calibrate the LDR sensitivity to the amount of light in the room testing in and the brightness of the light used. Additionally the LDRs can only meaninfully detect changes in light in a certain range meaning the surrounding environment must not be too bright for the system to function correctly.

Wiring Issues: As this exercise is heavily dependant on correct wiring, any wiring mishaps could cause this project to break and work erratically. Mishaps could include loose wiring, exposed wiring, or wires that have fallen out completely. Wires should be checked before each test to ensure accurate testing and a smooth run-through.

LDR Functionality: The LDRs are a major part of the second half of the challenge. Ensuring that ALL LDRs are correctly functioning is crucial for this project to be functional.

Magnetometer Position: The Magnetometer is positioned off-center on the STM but is positioned centered on the physical challenge colosseum. With research on magnetic fields and how magnetometers work, we discovered that having the magnetometer off-centre means that our readings may be slightly disrupted. However, as we're sorting the readings into 8 sections, it doesn't have an effect on the functionality as our readings dont need to be incredibly accurate.

Power to STM32 Board: To ensure constant and correct power supply to the STM32 board, it's recommended that the computer used to upload the code be plugged into a charger. A lack of adequate power can lead to the erratic behavior of the board and disrupt the escape room simulation.
___

## Test cases:
Magnetometer Readings: The first and largest test was to ensure that the magnetometer read in data and it read it in correctly. This was broken down into 4 major stages:

1. Read in non-zero and changing data: This process involved using the datasheet to confirm correct registers, correct functions, correct configuration values and using HAL. Multiple print statements were used to ensure that the values the magnetometer returned were non-zero. This was returned in milli gauss (mG) and displayed the strength of the magnetic field on the x, y, and z axis of the magnetometer. As the magnetometer moved, we had to check that the values also changed. Once this was confirmed, we could move on to interpreting the results.
2. Graph data and interpret results: Using the Arduino Serial Plotter, each cycle of the program returned and printed the corresponding values for each axis. This change in values was plotted on a graph. This data was showing the strength of the magnetic fields present. Tests with things such as fridge magnets, whiteboard erasers, car keys and iPhones showed spikes in data as the field changed from the Earth's magnetic field to the closer one.
3. Calculating degrees from the data: Now that the data was accurately reading in chnages in magnetic fields, we could use the data to calculate what direction the magnetometer was facing based on a local magnetic field (we decided to use a local field as using the Earths proved to have too much interference and the field wasn't strong enough for our use). This was done by taking the x and y-axis data and using the inverse tan function to calculate the angle from the x-axis. Each quadrant of a coordinate graph would produce an angle, however, we had to ensure that we defined a reference point as angle 0 and measured from there, and adjusted the measurement accordingly. E.g. In quadrant 2 (stating that quadrant 1 is the top right quadrant and the quadrants move anti-clockwise), calculating the angle using inverse tan (giving a negative angle) means you then need to add 180 degrees. Similarly, in quadrant 3, you receive a positive result and also add 180. 
4. Displaying the data: The final step was to ensure that the STM LED display would correctly show the LED corresponding to the angle it was facing. 

Once these tests were completed and functioning correctly, the magnetometer could be implemented into the project.

ADC Segment:

1. Read an analog signal from one LDR: Shine a strong light on LDR voltage divider circuit. This was temporarily configured to a STM32 Discovery board LED which was expected to light up when sufficient light was detected. This worked as expected.
2. Change sensitivity of ADC trigger threshold: Configure software sensitivity to high then shine a weak light over LDR circuit. The circuit did not transmit a high enough voltage to trigger the discovery board's LED. This worked as expected.
3. Read from multiple ADC channels at once: Connect one LDR voltage divider circuit to one pin on the discovery board connected to a configured ADC channel. Configure for high sensitivity and shine a light on it. We configured each individual ADC channel to trigger their unique LED on the discovery board. Shining a light on the circuit activated the correct LED and when it was rewired to a different channel's pin, its respective LED turned on while the previous one turned off. This is as expected and demonstrates the ability to read from multiple channels.
4. Read from multiple LDR voltage divider circuits at once: Connect 8 LDR Voltage divider circuits to 8 unique channels configured for high sensitivity. Shine a torch on chosen LDRs and their respective LEDs assigned by software on the board should activate. This worked as expected.
5. Compare activated LDRs to an external solution array: An external solution array was created which corresponded to the desired states of the each LDR voltage divider. These LDRs were activated simultaneously using a torch to see if the system would detect the current state of the LDRs to match the external solution. The match passed which locked the system. This was as desired

With these tests completed and functioning as expected, the ADC could be fully implemented into the rest of the project.

Light: One of the tedious tasks to test for was the light that shined on the LDRs. Our first test was with an iPhone flashlight. We discovered that this light was not enough to produce a change in the LDRs. Our two options were to create a larger hole to input light but that risked having light leak into the chambers, compromising the sensitivity of the LDRs. We decided on a torch that was much brighter than a phone light that will be given in the challenge alongside the other physical components.

Integrating the two parts: Our main test for integration was that the second half would not commence until the first half (finding the angle to shine in the light) was completed. We tested each LDR singularly to ensure that it does not show the completion screen without finding the correct magnet orientation.

___
