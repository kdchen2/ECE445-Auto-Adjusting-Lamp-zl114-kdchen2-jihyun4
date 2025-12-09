# Bi-Weekly Lab Notebook Entry: Weeks 9-10

## Week 9: Final PCB Assembly & Signal Validation
**Date Range:** November 10, 2025 – November 17, 2025

### 1. Objectives
* Assemble the Final Round PCB (Round 3).
* Verify power rails and signal integrity on the new board.
* Validate sensor hardware integration (I2C and Analog lines)
* Prepare hardware for the Mock Demo.

### 2. Work Record

#### 2.1 Final PCB Assembly
Received the final bare PCBs and proceeded with assembly.
* **Component Soldering:**
    * Soldered the **CP2102** (USB-to-UART bridge). This was the most challenging part due to the QFN package. Used a heat gun and solder paste to ensure the thermal ground pad made proper connection.
    * Soldered the Micro-USB connector, ensuring the anchor tabs were fully wetted for mechanical strength.
    * Populated the ESP32-S3, LM723 regulator, and IRLZ24N MOSFETs.

#### 2.2 Hardware Validation
Before powering the ESP32, I performed continuity and voltage checks.
* **Power Rails:**
    * Applied 12V DC. Measured **3.28V** on the 3.3V rail. Stable.
    * Verified 0V on Ground planes.
* **Programming Interface Test:**
    * Connected the board to a laptop via USB. The computer successfully recognized the CP2102 COM port.
    * *Success:* The auto-reset circuit (transistor logic) worked correctly, allowing code upload without manual button presses. This resolves the critical failure from Round 1.

#### 2.3 Sensor & LED Integration
* **I2C Bus:** Checked the SCL/SDA lines on the oscilloscope. Verified clean square waves with the on-board pull-up resistors (4.7k$\Omega$).
* **Photoresistor:** Measured the voltage at the ADC pin divider. verified it swings between ~0.5V (Dark) and ~2.8V (Flashlight), confirming the dynamic range is correct for the ADC.

<img width="1059" height="861" alt="4036c0eb8c0a145431275929e71d1012 2" src="https://github.com/user-attachments/assets/b26d6165-c0f2-4d3d-b57d-cffcc10ad70f" />
<img width="948" height="897" alt="402e5bd1f28151126fd10fc653b2994b" src="https://github.com/user-attachments/assets/5f4a8a94-52bc-4b24-b755-ef7112e7f4d4" />


---

## Week 10: Mock Demo & Final Assembly
**Date Range:** November 17, 2025 – November 24, 2025

### 1. Objectives
* Conduct Mock Demo with TA (Zhuoer Zhang).
* Address any hardware feedback from the demo.
* Begin full mechanical assembly (Lamp Housing).

### 2. Work Record

#### 2.1 Mock Demo Performance
Presented the hardware to the TA.
* **Demonstration:** Showed the PCB powering up from the 12V wall adapter and driving both LED channels.
* **Feedback:** The hardware operation was stable. The TA advised adding strain relief to the wires connecting the LED strip to the PCB to effectively prevent them from snapping off during the final assembly.

#### 2.2 Final Assembly: Lamp Housing
Started integrating the electronics into the 3D-printed housing.
* **Wiring:**
    * Routed the 4-wire LED cable (12V, Warm_GND, Cool_GND) through the lamp arm channel.
    * Twisted the wires to reduce electromagnetic interference (EMI).
* **PCB Mounting:**
    * Secured the PCB into the base using M3 screws.
    * The fit was tight near the USB port; filed down the plastic opening slightly to allow the cable to plug in fully.
* **Sensor Placement:**
    * Glued the Photoresistor and Color Sensor to the top-facing openings of the base to ensure unobstructed view of the ambient light.

#### 2.3 Circuit Fixes / Improvements
* **Strain Relief:** Added hot glue around the wire-to-board solder joints for the LED strips and power jack to prevent mechanical stress fatigue.
* **Thermal Check:** Ran the lamp at full brightness inside the enclosed base for 20 minutes. The base got warm but not hot, confirming that the ground plane is acting as a sufficient heatsink for the MOSFETs inside the plastic enclosure.

### 3. Next Steps
* Final polish of the hardware (cable management).
* Prepare for the Final Demo after Fall Break.
