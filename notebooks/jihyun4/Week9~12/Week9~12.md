# Auto-Adjusted Smart Lighting System  
### Week 9–12 Progress Report  

**Student:** Jihyun Seo  
**NetID:** jihyun4  

---

## 🗓 Overview (Nov 3 – Dec 1)
These weeks focused on the final integration of the system, specifically transitioning from breadboard prototypes to the **final PCB assembly**, stabilizing the power regulation circuit, and making a critical hardware decision to switch sensor types. We also completed the **Mock Demo** with the TA and finalized the housing assembly during the Fall Break.

---

## 🛠 Hardware & PCB Progress

### 🔌 Third-Round PCB Assembly & Debugging
- **Fabrication & Assembly:** The third-round PCB was ordered and soldered. This version included the corrected programming interface (fixing the previous UART TX/RX and strapping pin issues).
- **Power Regulation Tuning:** - We integrated the **LM723CN voltage regulator** to step down 12 V to 3.3 V. 
  - *Issue:* The regulator initially showed instability and oscillation under load.
  - *Solution:* Iteratively tuned the external resistor network and output capacitors to dampen oscillations, ensuring a clean 3.3 V output for the ESP32 and sensors.

### 💡 Sensor Finalization (The Switch to LDR)
- **OPT101 Evaluation:** After receiving the OPT101 sensor, we conducted extensive breadboard testing.
  - *Result:* The sensor proved **too sensitive**, with output values changing dramatically and saturating quickly. Despite checking the datasheet and circuit design, we could not stabilize the readings for our application.
- **Decision:** We switched to a **Photoresistor (LDR)**.
  - *Outcome:* The LDR provided steady, reliable output and worked perfectly with the 3.3 V logic, allowing for smoother brightness control.

<img width="600" alt="PCB Assembly Placeholder" src="YOUR_IMAGE_LINK_HERE" />
*(Placeholder: Insert image of the final soldered PCB or the testing setup)*

---

## 💻 Firmware & Control Logic
- **Algorithm Validation:** - Integrated the new Photoresistor readings into the control loop.
  - Validated the **real-time adjustment algorithm** which now balances input from the color sensor (for CCT) and the LDR (for brightness).
- **Smoothing:** Implemented a moving-average filter and gamma correction to ensure brightness changes occur at a rate of less than 2% per second, preventing visible flickering.

---

## 📅 Timeline Summary

| Week | Activity |
| :--- | :--- |
| **Nov 3 – 10** | Ordered Round 3 PCB; finished individual progress reports. |
| **Nov 10 – 17** | Integrated sensors and LED circuits on the PCB. Validated real-time algorithms using both color and brightness data. |
| **Nov 17 – 24** | **Mock Demo:** Conducted with TA. Identified final circuit issues. Began assembling the full lamp housing and wiring. |
| **Nov 24 – Dec 1** | **Fall Break:** Soldered the final round PCB with added features. Prepared for the Final Demo. |

---

## ⚠️ Challenges & Resolutions

### 1. PCB Programming Interface
**Problem:** Our previous PCB revision failed because we underestimated the ESP32-S3 strapping pin requirements (GPIO0 and EN) needed to force bootloader mode, alongside the TX/RX routing issue.  
**Resolution:** The final PCB redesign successfully routed these ports to allow seamless code uploading via USB through the breadboard interface.

### 2. Sensor Sensitivity
**Problem:** The OPT101 was too volatile for the desk lamp environment.  
**Resolution:** Replaced with a simple Photoresistor (LDR), which met the requirements for maintaining target desk brightness (approx. 450 lux) with an error margin of less than 10%.

---

## 🚀 Next Steps (Finals Week)
- **Final Presentation:** Present the fully assembled Auto-Adjusted Smart Desk Lamp.
- **Documentation:** Submit the final paper, presentation slides, and lab notebook.
- **Checkout:** Complete lab checkout procedures.
