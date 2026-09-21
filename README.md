# 🚦 Smart Traffic Light Controller

An Arduino-based smart traffic light controller developed by **CASCADE-X**.

The project implements a **Finite State Machine (FSM)** for traffic light control, along with pedestrian request handling, button debouncing, non-blocking timing using `millis()`, and a buzzer-based pedestrian alert.

---

##  Team — CASCADE-X

| Member | Primary Responsibility |

| Gaurav Singh Chandel | Hardware Design & Integration |

| Anurag Kumar | Software & Embedded Logic |

---
##  Project Overview

This project simulates a smart traffic intersection using an **Arduino Uno**, three LEDs representing traffic signals, a pedestrian push button, and a buzzer.

The system operates normally through the traffic light sequence and can respond to a pedestrian crossing request when the button is pressed during the green-light phase.

The controller was designed using an **FSM-based approach** instead of relying entirely on blocking delays.

---
##  Features

- 🚦 Three-state traffic light control
- 🧠 Finite State Machine (FSM)
- 🚶 Pedestrian crossing request
- 🔘 Push-button input with debouncing
- ⏱️ Non-blocking timing using `millis()`
- 🔊 Buzzer alert during pedestrian crossing
- 🔌 Arduino Uno based implementation
- 🛠️ Breadboard-based hardware prototype

---

##  Hardware Components

- Arduino Uno
- Red LED
- Yellow LED
- Green LED
- 270 Ω resistors × 3
- Push button
- Piezoelectric buzzer
- Breadboard
- Jumper wires
- USB cable

---

##  Pin Configuration

| Component | Arduino Pin |

| Red LED | D8 |
| Yellow LED | D9 |
| Green LED | D10 |
| Buzzer | D11 |
| Pedestrian Button | D2 |

The pedestrian button uses Arduino's internal **INPUT_PULLUP** configuration, so no external pull-up resistor is required.

---

##  System Operation

### Normal Operation

The normal traffic sequence is:

RED (5s)
   ↓
YELLOW (5s)
   ↓
GREEN (7s)
   ↓
RED

## Pedestrian Request

If the pedestrian button is pressed while the light is GREEN:

GREEN (finish 7s)
        ↓
YELLOW (5s)
        ↓
RED
        ↓
PEDESTRIAN (5s + buzzer)
        ↓
GREEN

---

## FLOW STATE DIAGRAM

               ┌──────────────────┐
                                  ↓
        RED → YELLOW → GREEN ─────→ RED
                         │
                         │ Button Press
                         ↓
                   YELLOW_TO_RED
                         ↓
                        RED
                         ↓
                   PEDESTRIAN
                         ↓
                       GREEN

---

## Button Debouncing

Mechanical push buttons can produce multiple rapid electrical transitions when pressed or released. This phenomenon is known as switch bouncing.

To prevent a single physical press from being detected multiple times, the project implements software debouncing.

The controller:

Detects a raw button-state change.
Starts a debounce timer.
Waits until the signal remains stable for 50 ms.
Updates the stable button state.
Detects the HIGH-to-LOW transition as a valid button press.
Registers the pedestrian request only when the traffic light is in the GREEN state.

---

## Non-Blocking Timing

The project uses Arduino's millis() function instead of using delay() for the main control logic.

This allows the controller to:

Track state durations
Continuously monitor the push button
Handle buzzer timing
Perform multiple operations without blocking the main loop

---

## Pedestrian Crossing Mode

When a pedestrian request is detected during the GREEN state:

The GREEN state completes its 7-second duration.
The controller changes to YELLOW.
After 5 seconds, the traffic light changes to RED.
The pedestrian crossing state begins.
The traffic light remains RED.
The buzzer toggles every 500 ms.
The pedestrian crossing lasts for 5 seconds.
The buzzer turns off.
The pedestrian request is cleared.
The controller returns to GREEN.

---

## Concepts Used

Arduino GPIO

Digital Input and Output

INPUT_PULLUP

Finite State Machines

Button Debouncing

Edge Detection

Non-Blocking Timing

millis()

Embedded C/C++

Hardware-Software Integration

---

##  How to Run

Install the Arduino IDE.

Connect the Arduino Uno using a USB cable.

Open TRAFFIC_LIGHTS.ino.

Select Arduino Uno as the board.

Select the correct COM port.

Upload the program.

Connect the components according to the circuit diagram.

Power the Arduino and test the traffic light sequence.

Press the pedestrian button during GREEN to test pedestrian mode.

---

## PROJECT STATUS  

Completed.
The hardware prototype, embedded software, FSM-based control, pedestrian request handling, button debouncing, non-blocking timing, circuit schematic, and demonstration have been implemented and tested.

---

## 📄 License

This project is licensed under the MIT License. See the LICENSE file for details.
