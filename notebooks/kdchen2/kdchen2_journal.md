# Kevin Chen, kdchen2

### Week 1-2 Progress Report (9/8/25-9/21/25)
---
#### Week 1:
- clarify high level diagram for sensor and board placement
- assist in preparing proposal pptx: double check components and their availability
- order ESP32 early

#### Week 2:
- set up ESP-IDF on personal device
- begin following ESP32 tutorials
- successfully flash ESP32 with GPIO tutorial

### Week 3-4 Progress Report (9/22/25-10/5/25)
---
#### Week 3:
- come up with validation tests for high level requirements:
  1. ±10% lux accuracy: Set a target lux and turn the lamp on. Measure the lux independently with a separate sensor (like mobile app) and verify it settles within  ±10% by 3 seconds.
  2. ≤ 2%/s transitions: Log duty cycle % over time during a change in brightness such as placing a box over the lamp. The slope must be ≤ 0.02 per second.
  3. ≥ 30% energy saving: Measure and compare power draw of 2 lamps in dark and light conditions over a set period of time: a control lamp without the ESP32 and smart adjustment, and the smart lamp. Show reduction ≥ 30%.
 
- present proposal to prof. Fiflet
- start investigating PWM and ADC on the ESP32
- could not figure out how to manually link esp32 to i2c color sensor in ESP-IDF; could only read its device ID register
- adding the color sensor manufacturer's libraries to ESP-IDF was also not viable- too many dependencies upon dependencies to manually go through
- understanding both how ESP-IDF and the color sensor manufacturer's libraries handle i2c to reverse engineer communication is too much of a time cost to justify
  
  Due to being unable to use the color sensor in ESP-IDF, I will be switching to arduino IDE for the rest of the project for the sake of time. This way I can use the color sensor manufacturer's library to handle i2c communication.

- the color sensor is able to communicate to the esp32 using arduino ide

#### Week 4:
Objective: Create smooth dimming algorithm that responds to lux sensor

Current Set-Up:
- currently working with photo resistor + 10k resistor in series as a lux sensor and a single LED, since our lux sensor has not arrived yet and the connections on the LED strips are delicate and hard to transport
  - LED PWM is currently directly connected to the 'lux sensor' output in the code found in "week4_code/sketch_sep26a.ino"
  - the smoothness of our dimming/brightening algorithm can be determined by observing the LED's change in brightness

- created filtering algorithm for sensor data filtering for the lux sensor so that rapid changes in lux sensor data would be rejected:
  1. create an array for sensor values
  2. compare current sensor reading to the average of the data in the sensor values array +/- some percent of tolerance (our desired rate of change)
  3. if the current sensor reading is greater than or equal to the average + tolerance, then rotate in average + tolerance into the array; if the current sensor reading is less than or equal to the average - tolerance, then rotate in average - tolerance
  4. use the average of the sesnor data array for our LED PWM output
- algorithm works well with small tolerance values like 0.2 
  - the sensor does not produce rapid changes when the environment conditions change suddenly (like waving a hand over it)
  - the LED adjusts smoothly when the sensor is held in darkness over a long time
- algorithm has inherent gamma adjustment due to the nature of average values increasing non-linearly, offsetting the human (logarithmic) perception of lux and appearing linear
  - for large values the real tolerance value, which affects adjumsent rate, becomes much larger than the real tolerance for small values: (1 + tolerance)*1000 > (1 + tolerance)*10

### Week 5-6 Progress Report (10/6/25-10/19/25)
---
#### Week 5:
Objective: Confirm algorithm works with actual LED strips used for the lamp

- needed to adjust tolerance value to 0.02 for smoothness with the LED strips

- presented our breadboard with the filtering algorithm during the breadboard demo

- wrote initial algorithm for auto adjusting to target lux and color temperature, did not implement yet- see "week5_code/sketch_sep26a.ino" lines 72-98

- our proposed lux sensor arrived, however we cureently cannot get any output from it


#### Week 6:
Objective: Implement auto adjusting to target lux and color temperature

- worked on design document
- made a physical 'lamp head' using a paper towel roll and staples, wire connections for LED strips are now secured to the lamp head and are more resilient in transport

- initial algorithm did not work well and resulted in oscillation effects and unintended behavior
  - wrote a new algorithm for auto adjusting- see "week6_code/sketch_sep26b.ino"

Current Set-Up:
- still using photo resistor as lux sensor due to being unable to make our official color sensor work
- both lux sensor and color sensors are connected and are giving readings to the esp32
- both warm and cool LED strips are connected and independantly powered and will need to be independantly driven
- target lux and temp are currently set by a temporary ADC pin and 4 resistor voltage divider

New auto adjusting algorithm:
Prerequisite: convert rgb data to a value between 0 and 4096 similar to the adc output, temp- 0 = cool and 4096 = warm
1. set range window for which pwm output to can be adjusted based on the target lux
2. directly modify pwm output using color sensor data temp and target temp while limiting adjustment based on target lux and sensor lux
   - if the lux sensor detects a bright environment, the window is scaled down; vice versa
   - if the target lux is large, the window is linearly shifted right (like from 0-2048 to 400-2448)
3. double check if the output is within range for lux 
4. feed output through the filtering algorithm discussed earlier

- despite sensor data being smoothed out by the filtering algorithm, the adjustment algorithm does not result in a smooth change in LED PWM- however it was resolved by putting the output through the filtering algorithm
- the algorithm otherwise works and produces expected behavior, however it is difficult to test due to having to tie together multiple sensors
- we will need to empirically decide our set target temperatures and lux for the different modes of the lamp

### Week 7-8 Progress Report (10/20/25-11/2/25)
---
#### Week 7:
Objective: Update code to work with our proposed lux sensor

- partners were able to get the lux sensor to read values from environment
- will use a spare esp32 and new arduino project to test sensor sensitivity



