# Game Controller

A Raspberry Pi Pico W based game controller that sends KY-023 joystick data over WiFi using FreeRTOS.

## Overview

This project implements a wireless game controller using a Raspberry Pi Pico W microcontroller. It reads analog input from a KY-023 joystick module and transmits the data over WiFi to a game server in JSON format using HTTP POST requests.

## Hardware Requirements

- Raspberry Pi Pico W
- KY-023 dual-axis joystick module with button
- USB cable for power

## Features

- **FreeRTOS-based multitasking**: Separate tasks for joystick reading, communication, and wifi connection handling/upkeeping
- **WiFi connectivity**: Connects to a configured WiFi network
- **Real-time joystick data**: Reads X/Y analog positions and button state
- **HTTP/JSON protocol**: Sends formatted data packets to a remote server
- **lwIP TCP/IP stack**: Network communication using lightweight IP

## Data Format

The controller sends HTTP POST requests with JSON payloads in the following format:

```
POST /data HTTP/1.1
Host: 192.168.1.121:8000
Content-Type: application/json
Content-Length: 114
Connection: close

{"device_id":"pico-joystick-01","x":float,"y":float,"button":bool,"timestamp":int}
```

### JSON Fields

- `device_id`: Unique identifier for the controller
- `x`: Normalized X-axis position (0.0 - 1.0)
- `y`: Normalized Y-axis position (0.0 - 1.0)
- `button`: Boolean state of the joystick button
- `timestamp`: Millisecond timestamp from device startup

## Project Structure

```
controller/
├── src/
│   ├── main.c              # Application entry point
│   ├── wifi.c/h            # WiFi connection and data transmission
│   ├── joystick.c/h        # KY-023 joystick reading (ADC)
│   ├── comm.c/h            # Communication protocol formatting
│   ├── system_state.c/h    # System state management
│   ├── config.h            # Configuration constants
│   ├── types.h             # Common type definitions
│   └── tasks/
│       ├── comm_task.c/h       # Communication task
│       ├── joystick_task.c/h   # Joystick sampling task
│       └── system_task.c/h     # System monitoring task
├── config/
│   └── FreeRTOSConfig.h    # FreeRTOS configuration
└── build/                  # Build output directory
```

## Configuration

Edit `src/config.h` to configure:

- **WiFi credentials**: `WIFI_SSID` and `WIFI_PASS`
- **Server settings**: `SERVER_IP` and `SERVER_PORT`
- **Joystick pins**: ADC pins for X/Y axes and button GPIO

## Building

This project uses CMake and the Pico SDK.

### Prerequisites

- Pico SDK installed (typically in `~/.pico-sdk/`)
- FreeRTOS kernel for Pico
- CMake and Ninja build system
- ARM GCC toolchain

### Compile

```bash
# Use the pre-configured build task
# In VS Code: Terminal → Run Task → Compile Project
```

Or manually:
```bash
ninja -C build
```

## Flashing

### USB Method (BOOTSEL)

1. Hold the BOOTSEL button on the Pico W
2. Connect USB cable
3. Release BOOTSEL (device appears as mass storage)
4. Run the flash task:

```bash
# In VS Code: Terminal → Run Task → Run Project
```

Or manually copy `build/controller_app.uf2` to the Pico drive.

### Debug Probe Method

Use the Flash task with OpenOCD and a debug probe (SWD connection).

## Usage

1. Configure WiFi credentials and server IP in `config.h`
2. Build and flash the firmware
3. Power on the Pico W
4. The controller will:
   - Initialize the WiFi module
   - Connect to the configured network
   - Start sending joystick data to the server
5. Monitor output via USB serial (115200 baud)

## Serial Output

The controller provides diagnostic output over USB CDC serial:

```
cyw43_arch_init succeeded
Connecting to WiFi...
Connected to WiFi successfully
IP: 192.168.1.xxx
Netconn created successfully
Connected to server 192.168.1.121:8000
```

## Dependencies

- **Pico SDK**: Raspberry Pi Pico C/C++ SDK
- **FreeRTOS**: Real-time operating system kernel
- **lwIP**: Lightweight TCP/IP stack
- **cJSON**: JSON parsing library (auto-fetched by CMake)

## License

-
