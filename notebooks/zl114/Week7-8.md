# Bi-Weekly Lab Notebook Entry: Weeks 7-8

## Week 7: PCB Redesign & Breadboard Demo 2
**Date Range:** October 27, 2025 – November 3, 2025

### 1. Objectives
* Debug the Round 1 PCB failure (Hardware level).
* Redesign the schematic to include an on-board programmer.
* Perform Breadboard Demo 2 (Hardware Verification).

### 2. Work Record

#### 2.1 PCB Debugging & Redesign
Following the programming failure in Round 1, I revised the hardware design to eliminate the need for an external programmer.
* **New Component:** Added the **CP2102** USB-to-UART bridge chip directly to the schematic.
* **Auto-Reset Circuit:** Designed the hardware auto-reset logic using two NPN transistors (S8050). This allows the DTR and RTS signals from USB to automatically toggle the `EN` (Reset) and `GPIO0` (Boot) pins on the ESP32, enabling hands-free programming.
* **USB Interface:** Added a Micro-USB connector to the board, routing `D+` and `D-` differential pairs to the CP2102.
<img width="1230" height="1080" alt="f4cd1c361811157e95f6c09258ef32d6" src="https://github.com/user-attachments/assets/7698fdb0-a8e0-4334-9078-205dbc51c91c" />


#### 2.2 Breadboard Demo 2 (Hardware Verification)
Conducted the second formal demo to verify the analog performance of the LED drive circuit before finalizing the new PCB.
* **Thermal Test:** Ran the IRLZ24N MOSFETs at 100% duty cycle for 10 minutes.
    * *Observation:* The MOSFETs remained cool to the touch. This confirms that the 3.3V gate drive from the ESP32 is fully saturating the MOSFETs ($V_{GS} > V_{th}$), minimizing $R_{DS(on)}$ losses.
* **Voltage Stability:** Monitored the 12V rail on the oscilloscope while pulsing the LEDs.
    * *Result:* The voltage dip was minimal, confirming our power supply and bulk capacitors are sufficient for the load.

---

## Week 8: Final PCB Layout & Ordering
**Date Range:** November 3, 2025 – November 10, 2025

### 1. Objectives
* Complete the layout for the "Final Round" PCB (incorporating the CP2102 fix).
* Run Design Rule Checks (DRC).
* Submit the final PCB order.
* Submit Individual Progress Report.

### 2. Work Record

#### 2.1 Final PCB Layout
I finalized the routing for the new PCB design.
* **USB Routing:** Routed the USB differential pairs ($D+$, $D-$) parallel and close together to minimize impedance mismatch, though this is less critical at USB 2.0 speeds it is good practice.
* **Ground Planes:** Added a solid ground pour on both top and bottom layers to act as a heat sink for the voltage regulator and MOSFETs.
* **Footprint Verification:** Double-checked the footprint for the new CP2102 (QFN package) to ensure the thermal pad is grounded correctly.

#### 2.2 Pre-Order Verification (DRC)
Ran the electrical rule check (ERC) and design rule check (DRC) in the CAD software.
* **Errors Found:** Found two unrouted nets near the voltage regulator and a clearance violation on the USB connector pads.
* **Fix:** Rerouted the traces and adjusted the pad spacing.

#### 2.3 Submission
* Generated Gerber files.
* Submitted the order for the third/final manufacturing round.
* Completed the Individual Progress Report detailing the power subsystem design and the switch from OPT101 to Photoresistor.

<img width="1229" height="1161" alt="69456b2f03a09e8b7990e982ccc23063" src="https://github.com/user-attachments/assets/44561e92-5bd5-4825-9bf6-20845f7599ed" />


### 3. Next Steps
* Wait for final PCB delivery.
* Prepare for final assembly (soldering the QFN CP2102 will require flux and a heat gun).
