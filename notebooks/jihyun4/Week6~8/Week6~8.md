# Auto-Adjusted Smart Lighting System  
**Week 6–8 Progress Report (Oct 13 – Oct 31, 2025)**  
**Student:** Jihyun Seo  **NetID:** jihyun4  

---

##  Overview
During Weeks 6–8, we focused on resolving the **ESP32 bare-chip programming issue**, verifying our **USB-to-UART download circuit**, and evaluating **light sensor options** for stable lux sensing.  
These weeks marked a transition from initial PCB verification toward a functional, standalone embedded system.

---

##  Hardware Progress

###  ESP32 Programming Success
We successfully implemented a working download circuit that allows direct programming of the ESP32 chip on our PCB using a **USB-to-UART (TTL) adapter**.

**Key connection detail:**

TX (USB-UART) ↔ RX (ESP32)
RX (USB-UART) ↔ TX (ESP32)


Earlier, we mistakenly connected TX→TX and RX→RX, preventing serial communication.  
After correcting the crossover connection, programming became stable and repeatable.
<img width="1415" height="935" alt="image" src="https://github.com/user-attachments/assets/0afff1e2-d8a4-41f7-95ae-b89fb9e8edcd" />
<img width="1495" height="921" alt="image" src="https://github.com/user-attachments/assets/6c41a0d4-5c04-4b63-b246-0385ed9e9089" />
<img width="1031" height="1141" alt="image" src="https://github.com/user-attachments/assets/f2a857f8-ce48-41e6-a400-70ee673a8e4f" />


---

###  PCB Version 1 Evaluation
First-round PCB arrived and was assembled.  
However, it failed to program due to the incorrect download circuit design.  

This board served as an important prototype for layout verification and physical fit.  

After confirming the programming fix, we redesigned the circuit and submitted the updated PCB order, expected to arrive in early November.

<img width="2398" height="1845" alt="image" src="https://github.com/user-attachments/assets/f9ab89c8-3516-487f-83f7-e37283a2581c" />

---

###  Sensor Exploration

#### 1. OPT101 Precision Lux Sensor
- Initially selected for its integrated photodiode + transimpedance amplifier design.  
- Found to be too sensitive to ambient light — output voltage saturates quickly under bright illumination.  
- Experimented with optical filtering (e.g., colored paper overlay) to limit light exposure and extend usable range.  
- Although highly accurate, it is costly (~ $10 /unit) and less tolerant to uncontrolled lighting conditions.  

#### 2. Photoresistor (LDR) Alternative
- Considered as a low-cost (~ $0.10) and robust alternative.  
- Provides smoother voltage variation under ambient light, though it’s non-linear and slower to respond than OPT101.  

**Discussion remains ongoing:**
- If OPT101’s dynamic range can be stabilized through filtering or calibration, it will remain the primary sensor.  
- Otherwise, the system may adopt an LDR-based design for simplicity and cost reduction.  

---

###  Summary of Achievements

| Category | Progress |
| ----------- | ----------- |
| Programming Interface | Fully functional using USB-to-UART (TX↔RX) |
| PCB Round 1 | Fabricated; verified layout; download circuit issue identified |
| PCB Round 2 | Not ordered |
| PCB Round 3 | Ordered with fixed download path |
| Sensor Testing | Compared OPT101 and photoresistor; analyzed trade-offs in accuracy and cost |

---

###  Next Steps (Week 9+)
- Receive and test second-round PCB with corrected programming interface.  
- Finalize sensor selection based on repeatability and ambient adaptability.  
- Begin firmware development for automatic brightness / CCT adjustment loop using stable sensor input.
