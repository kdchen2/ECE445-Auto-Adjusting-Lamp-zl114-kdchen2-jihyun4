# Bi-Weekly Lab Notebook Entry: Weeks 5-6

## Week 5: Firmware Logic & Mechanical Housing
**Date Range:** October 13, 2025 – October 20, 2025

### 1. Objectives
* Submit the official Design Document.
* Implement the "Weighted Sensor Control" algorithm (Moving Average Filter).
* 3D print and fit-check the lamp housing.
* Order components for the PCB assembly (LEDs, headers, passives).

### 2. Work Record

#### 2.1 Firmware Implementation: Data Smoothing
We implemented the core filtering logic on the ESP32 to satisfy the "no flicker" requirement.
* **Algorithm:** We created a circular buffer of size 15 (`sample_sz = 15`) to store recent sensor readings.
* **Logic:**
    1.  Calculate average of the array: `get_avg()`.
    2.  Define a dynamic tolerance window based on the current average.
    3.  If a new reading is within tolerance, add it. If it is an outlier (noise), clamp it to the max allowed step size.
* **Code Snippet:**
    ```cpp
    float filter_val(int num, float avg, float tolerance) {
        float increment = tolerance * avg;
        float high = avg + increment;
        float low = avg - increment;
        // Logic to clamp 'num' between low and high
        return rtn_val;
    }
    ```
* **Testing:** We printed the output to the Serial Monitor. The values ramped up smoothly even when the input jumped instantly, confirming the logic works.

#### 2.2 Mechanical Prototyping
* **Task:** Printed a test mount for the LED strip and the base for the PCB.
* **Result:** The 3D printed housing holds the LED strip securely, but we need to adjust the mounting holes for the PCB in the base, as the dimensions were slightly off in the CAD model.

---

## Week 6: PCB Assembly & The Programming Failure
**Date Range:** October 20, 2025 – October 27, 2025

### 1. Objectives
* Assemble the partial prototype using the Round 1 PCB.
* Perform the "Second Breadboard Demo" (Verification of Control Loop).
* Test the manufactured PCB (Round 1).

### 2. Work Record


#### 2.1 Testing & Debugging (CRITICAL FAILURE)
We attempted to program the ESP32 on the PCB using an external USB-to-TTL adapter.
* **Issue:** The computer recognized the COM port, but the Arduino IDE/Espressif tools failed to upload: `A fatal error occurred: Failed to connect to ESP32: Timed out waiting for packet header`.
* **Investigation:** We probed the UART lines. Data was reaching the chip, but the ESP32 was not entering "Bootloader Mode."
* **Root Cause Analysis:** We failed to verify the strapping pin requirements for the ESP32-S3. To enter boot mode, **GPIO0** must be pulled LOW while **EN** (Reset) is toggled. Our external programmer header only connected TX, RX, and GND. We did not route DTR/RTS signals to control GPIO0/EN automatically, nor did we add physical buttons to do it manually.
* **Correction:** We cannot easily patch this on the current board. We must order a **Round 2 PCB** that integrates the CP2102 USB-to-TTL chip *on-board* with the correct auto-reset transistor logic (DTR/RTS).

#### 2.2 Breadboard Verification (Fallback)
Since the PCB could not be programmed, we performed the "Second Breadboard Demo" using the dev board setup.
* **Verification:** Demonstrated that the photoresistor circuit correctly dimmed the LEDs when a flashlight was shined on it. Verified the "Dark" vs "Daylight" current consumption using a multimeter.

### 3. Next Steps
* Redesign PCB (Round 3) to include a new Programmer.
* Prepare for Breadboard Demo 2.
