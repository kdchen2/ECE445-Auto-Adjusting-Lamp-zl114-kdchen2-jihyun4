# Bi-Weekly Lab Notebook Entry: Weeks 1-2

## Week 1: Project Proposal & Component Research
**Date Range:** September 15, 2025 – September 22, 2025

### 1. Objectives
* Finalize project idea: "Auto-Adjusted Smart Desk Lamp."
* Meet with TA (Zhuoer Zhang) to discuss feasibility.
* Draft and submit the Project Proposal and Team Contract.
* Select and order major components (ESP32, voltage regulator, sensors).
* Define high-level requirements (Lux targets, power efficiency).

### 2. Work Record

#### 2.1 Component Selection & Research
We determined the core components required to meet our requirements of 450 Lux output and color temperature adjustment (2700K–6500K).

* **Microcontroller:** Selected **ESP32-S3 (WROOM-1)**.
    * *Reasoning:* We need two ADC channels (one for the photoresistor/OPT101, one for internal monitoring) and I2C for the color sensor. The ESP32 also has high-resolution PWM (LEDC) needed for smooth dimming (Target: <2% change/sec).
* **Power Regulation:** Selected **LM723CN**.
    * *Reasoning:* We have a 12V DC input (for LEDs) but need 3.3V for logic. We chose the LM723 for precision regulation rather than a standard 7805/Linear regulator to ensure stable voltage for the sensors.
* **MOSFETs:** Selected **IRLZ24N**.
    * *Reasoning:* We need a logic-level MOSFET. The $V_{GS(th)}$ of the IRLZ24N is 1.0V–2.0V, which means our 3.3V ESP32 signal can fully saturate it. Standard IRF series MOSFETs might not fully turn on at 3.3V.

#### 2.2 Initial Schematic Planning
Started sketching the power flow. The system requires two voltage rails.

* **Rail A:** 12V Direct -> LED Strips (Warm & Cool) -> MOSFET Drain.
* **Rail B:** 12V -> LM723 Step-down -> 3.3V -> ESP32 & Sensors.



#### 2.3 Requirements Definition
Established the "High-Level Requirements" for the proposal:
1.  **Brightness:** Maintain desk brightness ±10% of target (450 Lux).
2.  **Smoothness:** Dimming rate limited to <2% per second (no flicker).
3.  **Efficiency:** Reduce power by >20% when daylight is detected.

### 3. References
* [ESP32-S3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)
* [IRLZ24N Datasheet](https://www.infineon.com/dgdl/Infineon-IRLZ24N-DataSheet-v01_01-EN.pdf)

* ## Week 2: Breadboard Prototyping & Voltage Regulation
**Date Range:** September 22, 2025 – September 29, 2025

### 1. Objectives
* Pass the Proposal Review.
* Build the 12V to 3.3V step-down circuit on a breadboard.
* Verify ESP32 PWM output using an oscilloscope.
* Test the initial color sensor (TCS34725) communication.

### 2. Work Record

#### 2.1 Voltage Regulator Construction (LM723)
We built the step-down circuit on the breadboard to power the ESP32 from the 12V adapter.

* **Design Equation:** The output voltage is determined by the internal reference voltage ($V_{ref} \approx 7.15V$) and the potential divider $R_1$ and $R_2$.
    $$V_{out} \approx V_{ref} \times \frac{R_2}{R_1 + R_2}$$
* **Testing:** Initially, the output was drifting. We added a filter capacitor ($C_{out} = 100 \mu F$) to the output to smooth transients.
* **Result:** Tuned resistors to achieve a stable **3.1V - 3.3V**. This is within the safe range for the ESP32 (3.0V - 3.6V).



#### 2.2 LED Control Logic (PWM)
We verified the PWM control for the LEDs. We are using the ESP32 `LEDC` peripheral.

* **Frequency Selection:** We chose **1 kHz**.
    * *Justification:* If frequency is too low (< 100Hz), flicker is visible. If too high, MOSFET switching losses increase. 1 kHz gives us good resolution with no visible flicker.
* **Resolution:** 16-bit resolution ($2^{16} = 65536$ steps).
    * This provides a step size of $\approx 0.0015\%$, well below the 2% smoothness requirement.

#### 2.3 Sensor Integration (First Pass)
Connected the **TCS34725** (Color Sensor) via I2C.
* **Pinout:** SDA -> GPIO 21, SCL -> GPIO 22.
* **Test:** Used Adafruit library to read RGB values. The sensor successfully returned values, but we need to write a function to convert RGB to Correlated Color Temperature (CCT).

#### 2.4 Issues & Debugging
* **Issue:** The initial plan used the **OPT101** analog light sensor. During preliminary testing with a flashlight, the sensor saturated (hit 3.3V rail) very quickly, at around 450 Lux.
* **Proposed Solution:** This sensor might be too sensitive for a desk lamp that needs to detect daylight. We are considering switching to a standard Photoresistor (LDR) voltage divider for better dynamic range. We will test this next week.

### 3. Next Steps
* Finalize the schematic for the Design Document.
* Test the Photoresistor as a replacement for OPT101.
* Draft the Design Document.
