# Bi-Weekly Lab Notebook Entry: Weeks 3-4

## Week 3: Schematic Design & Breadboard Demo
**Date Range:** September 29, 2025 – October 6, 2025

### 1. Objectives
* Complete the Breadboard Demonstration for the TA.
* Finalize the full system schematic (Power, Control, LED subsystems).
* Finish and submit the official Design Document.
* Begin PCB layout.

### 2. Work Record

#### 2.1 Breadboard Demonstration
We successfully demonstrated the core functionality on the breadboard to the TA (Zhuoer Zhang).
* **Setup:** ESP32 connected to the TCS34725 color sensor and one LED strip via an IRLZ24N MOSFET.
* **Result:** We showed that the ESP32 could read I2C color data and adjust the LED brightness via PWM based on that data.
* **Feedback:** The TA approved the logic but emphasized ensuring the voltage regulator (LM723) is stable under the full load of two LED strips.

#### 2.2 Schematic Capture
We moved from hand-drawn sketches to the final CAD schematic.
* **Power Subsystem:** Designed the 12V $\to$ 3.3V step-down using the LM723CN. Calculated resistor values ($R_1, R_2$) to target 3.3V output.
* **LED Drivers:** Wired the Gate of the IRLZ24N MOSFETs to ESP32 GPIO pins. Added pull-down resistors (10k$\Omega$) to the Gates to prevent floating states during boot-up.
* **Sensor Interface:** Added headers for the OPT101 (analog) and TCS34725 (I2C).

<img width="1209" height="1041" alt="f46564ae80e5317ca2fc37477cfb7fe3" src="https://github.com/user-attachments/assets/0b458d69-508e-48ef-889c-52e82f3ca31d" />


#### 2.3 Design Document
Completed the Design Document, including the tolerance analysis for the PWM frequency (1 kHz) to prove it will be flicker-free. Submitted for review.

---

## Week 4: OPT101 Failure & PCB Order (Round 1)
**Date Range:** October 6, 2025 – October 13, 2025

### 1. Objectives
* Test the OPT101 light sensor (just received).
* Complete PCB Layout.
* Pass the PCB Design Review with the TA.
* Submit the Round 1 PCB Order.

### 2. Work Record

#### 2.1 Sensor Testing & The "OPT101 Issue"
We received the OPT101 photodiode and integrated it into the breadboard setup.
* **Test:** We shone a light source on the sensor to simulate daylight.
* **Observation:** The sensor output hit the maximum rail voltage (3.3V) extremely quickly. It saturated at approximately **450 Lux**.
* **Analysis:** This dynamic range is too small for a desk lamp application where daylight can easily exceed 1000+ Lux. The sensor cannot distinguish between "normal daylight" and "very bright sunlight."
* **Decision:** We decided to **abandon the OPT101**. We will replace it with a simple **Photoresistor (LDR)** circuit. The LDR has a wider resistance range in daylight, allowing us to distinguish brighter environments without clipping.

#### 2.2 PCB Layout (Round 1)
We routed the PCB based on the schematic.
* **Components:** Placed the ESP32-S3 module, the LM723 regulator, and the MOSFETs.
* **Trace Widths:** Used wider traces (20 mil+) for the 12V LED power rails to handle the higher current ($\approx 1A$). Used standard traces for signal lines.
* **Programming Interface:** We designed a header to connect an external USB-to-TTL programmer, assuming we could just hook up TX/RX/GND. *(Note: We suspect this might be tricky with the ESP32 boot mode strapping pins, but we will test it when the board arrives).*

#### 2.3 PCB Order
Passed the PCB audit with the TA and submitted the Gerber files for the first round of manufacturing.

<img width="483" height="465" alt="7e36629cc26fcbfe8f5c2987be4f4602" src="https://github.com/user-attachments/assets/cacfd271-628a-4d00-be17-e2afc5e1db34" />


### 3. Next Steps
* Wait for PCB arrival (approx. 1 week).
* Source a photoresistor and characterize its resistance vs. lux curve.
* Begin coding the "Moving Average" filter to handle sensor noise.
