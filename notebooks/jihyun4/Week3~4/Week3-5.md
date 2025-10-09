# Auto-Adjusted Smart Lighting System  
### Week 3–5 Progress Report 

**Student:** Jihyun Seo  
**NetID:** jihyun4  

---
## 🗓 Week 3–5 Progress (Sep 22 – Oct 12)

### ✅ Breadboard Demonstration
- Completed a fully functional **breadboard prototype** integrating:
  - **ESP32 development board**  
  - **12 V → 5 V step-down converter**  
  - **Two LED strips (warm & cool)**  
  - **Logic-level N-MOSFETs** for PWM control  
  - **Photoresistor-based lux sensing** for brightness feedback  
- Verified stable operation and correct PWM dimming behavior.  
- Demonstrated real-time light adjustment responding to ambient brightness changes.

### 🧮 PCB Development
- Designed and fabricated the **first-round PCB (draft version)**.  
- Objective: check footprint alignments, net connections, and physical layout feasibility.  
- This early board may not be fully functional, but it serves as a proof-of-concept for further refinement.  

### ⚙️ Technical Challenges
- Major challenge: implementing **I²C communication** for the color sensor and **ADC readout** for the lux sensor at the breadboard stage.  
- Encountered unstable readings and communication errors, likely due to wiring noise and timing mismatches.  
- Plan: perform a detailed hardware review and debugging to stabilize sensor interfacing in upcoming weeks.

### 💡 System Design Exploration
- Began designing the **ESP32 bare-chip configuration** to replace the development board.  
- Considering **USB-to-UART circuit integration** for on-board programming and debugging.  
- Evaluating dif
