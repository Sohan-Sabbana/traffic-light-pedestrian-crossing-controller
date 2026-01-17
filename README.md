# Arduino Traffic Light Controller with Pedestrian Interrupt

## Project Overview

This repository implements a dual-road traffic light control system using an Arduino Uno. The firmware is designed around a Finite State Machine (FSM) architecture to ensure predictable transitions between traffic phases. It features a non-blocking timing mechanism and utilizes hardware interrupts to handle pedestrian crossing requests asynchronously, prioritizing pedestrian safety without halting system operations.

## System Architecture

The control logic operates on five distinct states:

1. Road 1 Green: Primary road access.
2. Road 1 Yellow: Transition phase for Road 1.
3. All Red: Safety buffer clearing the intersection.
4. Road 2 Green: Secondary road access.
5. Road 2 Yellow: Transition phase for Road 2.

### Timing and Interrupts

- Non-Blocking I/O: The system uses millis() rather than blocking delay() functions. This allows the microcontroller to continuously poll inputs and maintain internal timers simultaneously.
- Interrupt Service Routine (ISR): The pedestrian button is attached to external interrupt pin 2. A falling edge trigger (button press) instantly flags a request variable, which dictates the logic flow of the main loop to shorten the current green cycle if necessary.

## Hardware Specifications

### Pin Configuration

| Component | Pin | Mode | Description |
| :--- | :--- | :--- | :--- |
| Red 1 | 3 | OUTPUT | Road 1 Red Signal |
| Yellow 1 | 4 | OUTPUT | Road 1 Yellow Signal |
| Green 1 | 5 | OUTPUT | Road 1 Green Signal |
| Red 2 | 8 | OUTPUT | Road 2 Red Signal |
| Green 2 | 9 | OUTPUT | Road 2 Green Signal |
| Button | 13 | INPUT_PULLUP | Pedestrian Request (Active Low) |

### Circuit Wiring

The circuit utilizes the Arduino's internal pull-up resistors for the input button to minimize external components.

- LEDs: Connected to respective digital pins with 220 ohm current-limiting resistors in series to Ground.
- Pushbutton: Connected between Pin 2 and Ground. No external pull-down or pull-up resistor is required.

## Deployment Instructions

1. Hardware Assembly: Wire the components according to the Pin Configuration table and the provided circuit diagram. Ensure the pushbutton connects Pin 2 to Ground directly.
2. Firmware Upload: Open the source code in the Arduino IDE, select the appropriate board and COM port, and upload the sketch.
3. Serial Monitoring: The system outputs state transition logs via the Serial interface. Set the Serial Monitor baud rate to 9600 to view these logs.

## Operational Logic

Upon initialization, the system defaults to Road 1 Green. The cycle proceeds based on defined time constants. If the pedestrian button is pressed while Road 1 is Green, the system registers the interrupt, overrides the remaining wait time, and initiates the transition to Road 1 Yellow, accelerating the cycle to allow the pedestrian crossing phase (implied during the traffic switch).
