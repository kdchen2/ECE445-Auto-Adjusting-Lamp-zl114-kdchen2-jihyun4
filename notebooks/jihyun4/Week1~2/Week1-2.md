# Auto-Adjusted Smart Lighting System  
### Week 1–2 Progress Report

| Student    | NetID   |
|------------|---------|
| Jihyun Seo | jihyun4 |

---


---

## Project Overview
Designing a **smart desk lighting system** that automatically adjusts **brightness** and **color temperature** using **ambient light sensors**, **color sensors**, and an **ESP32 microcontroller**.  
Goal: provide healthier, more comfortable indoor lighting by adapting to the environment.

---

## Week 1 Progress
- **Literature Review & Ideation**
  - Identified issues of static desk lamps (eye strain, no adaptation to daylight).
  - Reviewed existing smart lighting approaches and limitations.
- **Initial Block Diagram**
  - Sensors → ESP32 → LED Drivers → LEDs
  - Defined subsystems: sensing, processing, actuation, power.
- **Component Selection**
  - **ESP32** chosen as main controller (I²C + Wi-Fi/Bluetooth).
  - Candidate sensors: **Ambient Light Sensor (ALS)** + **RGB Color Sensor**.
  - **Meanwell LDD-L series LED drivers** selected for constant-current control.
- **LED Choice**
  - Using **Cree J-Series LEDs (6V config)**.
  - Dual-channel LEDs (Cool White + Warm White) for brightness & color control.

---

## Week 2 Progress
- **Hardware Design**
  - Sensors connected via shared **I²C bus** (SDA/SCL).
  - LED driver wiring defined:
    - DC Adapter → LED Drivers (Vin)
    - ESP32 PWM → DIM pins
    - LED outputs isolated per channel.
- **System Drawing**
  - Schematic showing:
    - **DC Adapter → LED Drivers → Warm/Cool LEDs**
    - **ESP32 → PWM (DIM) → LED Drivers**
    - **ESP32 → I²C → Sensors**
- **Control Logic**
  - ESP32 reads sensors:
    - Ambient light → adjusts **overall brightness**.
    - Color sensor → adjusts **Warm vs Cool ratio**.
  - PWM channels configured on ESP32 for dual-driver control.

---

## Repository Contents
- `Week1_Overview.pptx` — Slides: problem definition, block diagram, component selection.  
- `Week2_Drawing.png` — System wiring & control diagram.  
- `Week1-2.md` — This progress summary.

---

## Next Steps
- Prototype I²C communication with ALS + Color Sensor.  
- Implement PWM control for dual LED drivers.  
- Develop firmware loop: **dynamic brightness + color temperature control**.  

---
