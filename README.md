# Distributed Game System
This is a distributed game system project that connects an embedded device, a backend service and a client application into one system. The goal of the project is to learn more about system design, backends, embedded devices, CI/CD and system integration.

## Overview
The system consists of three main components:
- Embedded Device
  -  Raspberry Pi Pico W + FreeRTOS
  -  Reads joystick (KY-023) position and button press.
  -  Sends input data to the backend over wifi using HTTP POST
- Backend
  - Receives input data from the device by POST request
  - Processes game logic and state in background task
  - Responds with game state to GET requests
- Client
  - Connects to the backend
  - Requests game state with HTTP GET
  - Displays game state
 
## Project TODO:
- Implement client
- Containerize backend
- Database integration
- GitHub Actions CI/CD workflows
