
# Secured Fan Speed Control Based on FreeRTOS

## Project Overview
This project implements a **Secured Fan Speed Control System** using **FreeRTOS** for multitasking. The user enters a password via UART, and once authenticated, the fan speed is controlled based on temperature readings from an **LM35 temperature sensor**. A **buzzer** alerts the user in case of an incorrect password, while an **LED** confirms correct password entry. FreeRTOS manages task scheduling for password authentication, fan control, and real-time monitoring.

Key components include:
- **Microcontroller**: ATMega32
- **Fan Motor**: Speed regulated based on temperature readings
- **Temperature Sensor**: LM35
- **Communication**: UART for password input
- **Actuators**: LEDs (for correct password indication), Buzzer (for wrong password alert)

## Features
- **Multitasking with FreeRTOS**: Efficient task scheduling for password authentication, temperature reading, fan speed control, and status indication.
- **Password Authentication**: The user enters a password via UART. A **buzzer** sounds for incorrect passwords, while an **LED** lights up for correct password entry.
- **Temperature-Based Fan Speed Control**: After authentication, the fan speed adjusts automatically based on the temperature detected by the LM35 sensor.
- **Simulated Setup**: Entire system is simulated using Proteus for testing and demonstration.

## Hardware Components
- **ATMega32 Microcontroller**
- **LM35 Temperature Sensor**: Reads ambient temperature to control fan speed.
- **Fan Motor**: Adjusts speed based on temperature readings.
- **LEDs**: Indicate correct password entry.
- **Buzzer**: Alerts the user in case of a wrong password.
- **UART**: Handles password transmission for security.

## Software Components
- **FreeRTOS**: Real-Time Operating System for task management and scheduling.
- **Proteus Simulation**: Used to simulate the entire system before hardware implementation.
- **Embedded C**: Programmed using Embedded C language for the ATMega32.

## Simulation Video
You can view the simulation video of the system in action [here](https://drive.google.com/file/d/1JK1its3ttEa8yt6YULbLtQiZt1vkM4KW/view?usp=drive_link).

## Source Code Structure

### `main.c`
This file contains the main entry point of the system. It initializes the FreeRTOS environment, sets up the hardware, and starts the task scheduler.

### `TaskHandler.c`
This file contains the task definitions and handlers for various components in the system, including:
- Task for password authentication via UART.
- Task for reading temperature from the LM35 sensor.
- Task for controlling fan speed based on temperature.
- Task for handling the buzzer and LED indicators.

### `TaskHandler.h`
This header file declares the task functions and shared variables used across tasks.

## Setup and Installation
1. **Clone the repository**:
    ```bash
    git clone https://github.com/Esraa-alii/Secured-Fan-Speed-Control-Based-on-FreeRTOS.git
    ```
2. **Proteus Simulation**:
   - Open the provided **Proteus** simulation file.
   - Ensure all necessary libraries are installed.
3. **Code**:
   - Compile and upload the code to the **ATMega32** microcontroller.
4. **Run Simulation**:
   - Launch the Proteus simulation to visualize the working system.

## Usage
- **Password Authentication**: Use UART to send a password. A **buzzer** will sound for incorrect entries, and an **LED** will light up for correct entries.
- **Temperature-Based Fan Control**: After successful authentication, the fan speed adjusts automatically based on the temperature detected by the LM35 sensor.
- **Status Indication**: LEDs and the buzzer provide real-time feedback on password entry.
- The system handles tasks concurrently using FreeRTOS.

## Future Enhancements
- Add remote control via Wi-Fi or Bluetooth.
- Integrate a mobile app for temperature monitoring and fan control.
- Expand the system to handle additional home appliances.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.
