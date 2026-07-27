# 🚀 Advanced Firmware Engineering & Embedded Systems Portfolio

This repository contains an evolving, production-grade codebase detailing my transition from basic microcontroller scripting into asynchronous, non-blocking firmware design. All systems are developed in C++ using **PlatformIO** targeting the **ATmega328P** architecture (Elegoo Uno R3 setup).

---

## 🛠️ Core Engineering Methodologies Deployed

* **Asynchronous Time-Slicing (`millis()`):** 100% elimination of blocking delay routines (`delay()`) to ensure real-time multitasking execution loops.
* **Low-Level Hardware Diagnostic Tracing:** Experience bypassing missing component documentation through custom diagnostic firmware scripts to map raw hardware registers.
* **Current-Balance Calibration:** Designing robust schematic safety loops using individual segment current protection instead of single-digit saturation sinks.
* **Git Version Control Mastery:** Enforcing strict *Conventional Commits* standard (`feat:`, `docs:`) to trace real industrial release lifecycles.

---

## 📊 Technical Milestones & Architecture Evolution

### 📦 Phase 3: Multi-Digit Displays & Hardware Calibration (Latest Updates)
### 📦 Phase 3: Multi-Digit Displays & Hardware Calibration (Latest Updates)

* **July 27, 2026 | Custom Display Cascading Character Arrays:** 
  
  **Project: 4-Digit Multiplexed Array Exploration.**  
  In this module, I explored both bare-metal implementation and third-party library abstraction. First, I coded a custom multiplexing software engine from scratch using raw binary matrix mapping to understand pin routing and time-slice synchronization (`millis()`). Later, to optimize production and account for the non-sequential hardware pinout constraints of the 5461AS common-cathode display, I integrated the professional `SevSeg.h` library, managing advanced character array buffer operations (`setChars()`) for a clean cascading animation effect.

  * *The Bottleneck:* Integrated a 4-Digit 7-Segment screen (Model 5461AS) featuring a non-sequential, crossed internal pinout layout from the manufacturer.
  * *The Engineering Fix:* Designed a step-by-step diagnostic script to trace raw data ports, routed 4 strategic resistors directly on the segment nodes to balance the current, and implemented a custom **Asynchronous State Machine** with `SevSeg.h` and `.setChars()`. It delivers a clean, flicker-free cascading animation (`1...2...3...4` -> Blank -> `5...6...7...8`) without memory-hogging leading zeros.

* **July 23, 2026 | Parallel LCD & Climate Sensing Integration:** 
  * Built a standalone telemetry station combining a 16-pin parallel LCD1602 with a DHT11 climate sensor. Resolved bus corruption artifacts (ghosting/strange symbols) via software re-indexing and contrast tuning using an analog potentiometer.

### 📈 Phase 2: Sensor Telemetry & Asynchronous Subsystems
* **July 22, 2026 | Non-blocking Environmental Sensing Telemetry:** Integrated the DHT11 sensor to capture temperature and humidity variables using independent asynchronous intervals.
* **July 22, 2026 | Servo-Control System & Analog Hardware Mapping:** Developed a closed-loop control system utilizing an analog potentiometer to drive automated servo angles safely.
* **July 21, 2026 | Non-blocking Ultrasonic Radar System:** Deployed `NewPing` architectures to build an autonomous distance monitoring radar with continuous serial log readouts.
* **July 20, 2026 | Dynamic Blink Interval Modulation:** Hand-coded a state engine that reads analog input and updates the system ticker frequency in real time without halting execution.
* **July 19, 2026 | Analog Input Dimming Control:** Managed PWM duty-cycles to smoothly dim external loads based on real-time potentiometer telemetry.

### 🧱 Phase 1: Bare-Metal Basics & Digital Input/Output
* **July 18, 2026 | Digital Button Input & Dual-Ground Routing:** Designed an input pull-down interface with external debouncing stabilization and dual-ground electrical safety loops.
* **July 18, 2026 | 3-LED Traffic Light Sequence State Machine:** Modeled a basic sequential traffic routing loop using logical time boundaries.
* **July 17, 2026 | External LED Current Protection:** Calculated and deployed the first 220-ohm protective load loops to isolate physical microcontroller pins.
* **July 16, 2026 | Hand-Coded Morse SOS Signal Generator:** Designed a low-level structural blink algorithm executing precise timing arrays.
* **July 16, 2026 | Basic System Blink Initialization:** Verified basic compiler, framework, and board communication tools.

---

## 📂 Project Structure

```text
├── src/
│   └── main.cpp           # Active production firmware under development
├── historical_code/       # Protected baseline iterations of past exercises
├── platformio.ini         # Strict dependency registry & compiler flags
└── README.md              # Core engineering documentation
```

---
*Developed under professional firmware guidelines to demonstrate pre-university engineering competencies toward my career at Universidad Miguel Hernández (UMH).*
