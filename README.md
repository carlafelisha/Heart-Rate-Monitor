## Heartbeat Hero Project README

---

#### Overview

The Heartbeat Hero project involves a series of Arduino files that work together to read and process heart rate data from a Pulse Sensor. The project displays heart rate information on an LCD screen and provides feedback based on the measured BPM (beats per minute). The files include code for handling interrupts, serial communication, and managing LCD display output. This was done in collaboration with my group members from BN2111 Biomedical Engineering Principles and Practice II.

#### Files Description

1. **`BN_sketch.ino`**

   **Purpose:** Main Arduino sketch for handling Pulse Sensor data, managing the LCD display, and providing feedback based on heart rate.

   **Key Features:**
   - **Pulse Sensor Setup:** Reads data from the Pulse Sensor connected to analog pin 0.
   - **LCD Display:** Shows messages and heart rate information using a LiquidCrystal library.
   - **Heartbeat Detection:** Displays a heart-shaped icon or messages based on BPM values.
   - **Variables:** Manages variables such as `BPM` (heart rate), `Signal` (raw sensor data), `IBI` (time between beats), and flags like `Pulse` and `QS` (Quantified Self).

   **Code Sections:**
   - Initialization (`setup()` function).
   - Main loop handling (`loop()` function).
   - LCD display updates and feedback messages.

2. **`AllSerialHandling.ino`**

   **Purpose:** Handles serial communication for different types of data output based on the `outputType` variable.

   **Key Features:**
   - **Data Output:** Supports multiple output modes:
     - **Processing Visualizer:** Sends data to Processing software for visualization.
     - **Serial Plotter:** Outputs data to the Arduino Serial Plotter.
   - **Serial Communication:** Sends data using specific symbols to indicate data types (e.g., 'S' for Signal, 'B' for BPM).

   **Code Sections:**
   - **`serialOutput()`:** Manages serial output based on the `outputType`.
   - **`serialOutputWhenBeatHappens()`:** Sends BPM and IBI data when a heartbeat is detected.
   - **`sendDataToSerial()`:** Helper function for sending formatted serial data.

3. **`interrupt.ino`**

   **Purpose:** Manages Timer2 interrupt service routine (ISR) for sampling the Pulse Sensor at a regular interval.

   **Key Features:**
   - **Timer Setup:** Configures Timer2 to trigger interrupts every 2 milliseconds.
   - **Pulse Detection:** Processes raw sensor data to detect heartbeats and calculate BPM.
   - **Data Management:** Maintains an array of the last ten IBI values for BPM calculation and handles peak/trough detection in the pulse waveform.

   **Code Sections:**
   - **`interruptSetup()`:** Configures Timer2 for regular sampling.
   - **`ISR(TIMER2_COMPA_vect)`:** Interrupt service routine for processing sensor data and calculating BPM.

4. **`Timer_interrupt_notes.ino`**

   **Purpose:** Provides notes and instructions on using different timers for Pulse Sensor sampling.

   **Key Features:**
   - **Timer Configurations:** Details Timer2, Timer1, and warnings about Timer0.
   - **Usage Notes:** Explains the impact of timer selection on other functionalities and libraries.

   **Code Sections:**
   - **Timer2 Configuration:** Default for Pulse Sensor, affects PWM on pins 3 and 11.
   - **Timer1 Configuration:** Alternative timer setup if Timer2 conflicts with other libraries.
   - **Timer0 Warning:** Advises against using Timer0 due to conflicts with core Arduino timing functions.

#### How to Use

1. **Upload Code:** Load `BN_sketch.ino` to your Arduino board. Ensure all files are in the same directory for proper integration.
2. **Configure Serial Output:**
   - Set the `outputType` variable in `BN_sketch.ino` to select the desired serial output mode.
3. **Connect Hardware:**
4. **Run and Test:**
   - Start the Arduino Serial Monitor or Serial Plotter to view the output.
   - Check the LCD display for heart rate information and feedback messages.

#### Additional Notes

- Ensure that Timer2 is not conflicting with other functionalities if using an Arduino board that supports PWM on pins 3 and 11.
- If using Timer1, adjust the `interruptSetup()` code accordingly and use the Timer1 ISR vector.
- Refer to `Timer_interrupt_notes.ino` for detailed information on timer configurations and potential conflicts.

---
