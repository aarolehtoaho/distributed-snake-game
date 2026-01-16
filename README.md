# Distributed Game System
This is a distributed game system project that connects an embedded device, a backend service and a client application into one system. The goal of the project is to learn more about system design, backends, embedded devices, CI/CD and system integration.

<p align="center">
  <img src="https://github.com/user-attachments/assets/6fe54330-44ab-46db-a0fe-fa9a45a72fb4" width="25%" />
  <img src="https://github.com/user-attachments/assets/f609d849-7a80-4bec-9ce0-0637dd1bf761" width="28%" />
  <img src="https://github.com/user-attachments/assets/86d48930-14ba-405c-a4b8-639860113426" width="41%" />
</p>

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
- Database integration
- GitHub Actions CI/CD workflows

