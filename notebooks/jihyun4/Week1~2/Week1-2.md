# Auto-Adjusted Smart Lighting System

### Week 1–2 Progress Report (Sep 8–21, 2025)

| Student    | NetID   |
| ---------- | ------- |
| Jihyun Seo | jihyun4 |

---

## Project Overview

Designing a **smart desk lighting system** that automatically adjusts **brightness** and **correlated color temperature (CCT)** using an **ambient light sensor (lux)**, a **color sensor**, and an **ESP32**.
**Goal:** healthier, more comfortable indoor lighting that adapts to the environment.

> **Control Architecture Update:** We replaced LED drivers with **logic‑level N‑MOSFETs** (low‑side PWM switching) to modulate LED brightness directly. Two MOSFET channels (Warm, Cool) allow brightness and CCT mixing without dedicated DIM‑pin drivers.

---

## Week 1 Progress (Sep 8–14)

* **Literature Review & Ideation**

  * Identified problems with static desk lamps (eye strain, no adaptation to daylight).
  * Reviewed smart lighting strategies and CCT mixing approaches.
* **Initial Block Diagram**

  * Sensors → ESP32 → **MOSFET PWM Stages** → LED Channels
  * Subsystems defined: sensing, processing, actuation, power.
* **Component Exploration**

  * **MCU:** ESP32 (I²C + Wi‑Fi/BLE; LEDC PWM).
  * **Sensors:** Ambient Light Sensor (ALS) + RGB Color Sensor (I²C).
  * **Emitters:** Two LED channels: **Cool White** and **Warm White**.
  * **Actuation (updated):** Replace Mean Well LDD drivers with **logic‑level N‑MOSFETs** for low‑side PWM control per channel.

---

## Week 2 Progress (Sep 15–21)

### Hardware Design (MOSFET‑based)

* **I²C Bus**: ALS + Color sensor share SDA/SCL with proper pull‑ups.
* **LED Power Path (12 V)**:

  * **+12 V** → LED+ (strip or COB segment)
  * LED− → **MOSFET Drain**
  * **MOSFET Source** → GND
  * **Common Ground** between 12 V supply and ESP32
* **Gate Drive (ESP32 → MOSFET)**:

  * ESP32 **PWM (LEDC)**  → **Gate**
  * One MOSFET per channel (Warm, Cool)

* **Protection/Notes**:

  * Keep wiring short; add small **RC snubber** only if ringing is observed.
  * Select MOSFET with low **RDS(on)** at **VGS = 3.3 V** (true logic‑level).

```
12V+ ──> LED+  LED− ──> D  N‑MOSFET  S ──> GND
                       │
                 100 Ω │
ESP32 PWM ─────────── GATE
                       
               
```

### PWM & Control Logic

* **LEDC Setup**: 2 channels (Warm/Cool), **1–4 kHz** PWM (avoid visible flicker & audible buzz).
  Resolution: **10–13 bits** depending on chosen frequency.
* **Brightness Control**: Lux error → PI controller → total duty.
* **CCT Mix**: Color error → mixer sets Warm vs. Cool ratio.


### Why MOSFETs (vs. LED Drivers)

* **Simplicity & Size**: Fewer parts on the desk‑lamp prototype PCB.

