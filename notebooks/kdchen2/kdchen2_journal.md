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

### Week 1-2 Progress Report (9/22/25-10/5/25)
---
#### Week 3:
- come up with validation tests for high level requirements:
  1. ±10% lux accuracy: Set a target lux and turn the lamp on. Measure the lux independently with a separate sensor (like mobile app) and verify it settles within  ±10% by 3 seconds.
  2. ≤ 2%/s transitions: Log duty cycle % over time during a change in brightness such as placing a box over the lamp. The slope must be ≤ 0.02 per second.
  3. ≥ 30% energy saving: Measure and compare power draw of 2 lamps in dark and light conditions over a set period of time: a control lamp without the ESP32 and smart adjustment, and the smart lamp. Show reduction ≥ 30%.
 
- present proposal to prof. Fiflet
- start investigating PWM and ADC on the ESP32


