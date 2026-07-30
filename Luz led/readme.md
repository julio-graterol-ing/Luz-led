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

* **July 30, 2026 | Object-Oriented Firmware Modularization (Architecture Shift):** 

  **Project: Custom Multi-Subsystem Driver Refactoring.**  
  In this module, I executed a complete architectural refactoring of the concurrent multi-peripheral firmware. Moving away from a monolithic codebase, I applied Object-Oriented Programming (OOP) design patterns to abstract physical hardware devices into independent, standalone driver modules utilizing strict C++ Class encapsulation.

  * *The Bottleneck:* Maintaining a growing single-file (`main.cpp`) concurrent code structure makes the firmware unstable, extremely difficult to scale, prone to global variable scope pollution, and non-portable for 32-bit cross-compilation architectures.
  * *The Engineering Fix:* Isolated the software sub-systems into dedicated header/implementation pairs: `ClimateSensor` (`.h`/`.cpp`) for the DHT11 digital bus, `ServoMotion` (`.h`/`.cpp`) for the SG90 kinematics, and `DisplayCore` (`.h`/`.cpp`) for the 5461AS multiplexing matrix. All memory scopes were encapsulated using `private` visibility registers and communication handles. The master loop scheduler inside `main.cpp` was reduced to an unpolluted, production-grade template of **only 15 lines of code**, achieving maximum modular portability before migrating toward the ESP32 ecosystem.


* **July 28, 2026 | Asynchronous Multisystem Integration (The Core Engine):** 

  **Project: Real-Time Concurrent Multi-Periferal Station.**  
  Developed a multi-process asynchronous scheduling architecture utilizing an independent time-slicing method (`millis()`) to concurrently drive three hardware sub-systems with zero processing stalls. The design acts as a handcrafted lightweight RTOS (Real-Time Operating System) conceptual prototype, isolating background execution loops from high-speed peripheral refresh cycles.

  * *The Bottleneck:* Merging a 4-Digit 7-Segment multiplexed array (5461AS) with a digital DHT11 climate sensor and an analog Servo Motor (SG90) generated severe hardware timer collisions and pin starvation, causing segment flickering, sluggish motor response, and `NaN` communication drops over the `PORTC` bus.
  * *The Engineering Fix:* Executed a full hardware re-mapping by isolating the servo to pin `A0` and the DHT11 to pin `A4`. Implemented strict 6-byte string allocation formatting via `sprintf()` to prevent dangerous **Buffer Overflows** within the SRAM registers. The final firmware successfully drives smooth $180^\circ$ servo kinematics, reads active environmental values, and multi-plexes telemetry data every 3 seconds (`t  26` / `h  50`) with homogeneous brightness and zero processor delays.


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
├── include/
│   ├── Climate.h          # Custom climate sensor interface header
│   ├── DisplayCore.h      # Custom 5461AS display matrix control header
│   └── Motion.h           # Custom SG90 servo kinematics controller header
├── src/
│   ├── main.cpp           # Ultra-clean production software scheduler (15 lines)
│   ├── Climate.cpp        # Custom climate sensor implementation source
│   ├── DisplayCore.cpp    # Custom 5461AS multiplexing source code
│   └── Motion.cpp         # Custom SG90 servo positional execution code
├── historical_code/       # Protected baseline iterations of past exercises
├── platformio.ini         # Strict dependency registry & compiler flags
└── README.md              # Core engineering documentation

```

---
*Developed under professional firmware guidelines to demonstrate pre-university engineering competencies toward my career at Universidad Miguel Hernández (UMH).*
