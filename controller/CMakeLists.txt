cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(APP_NAME controller) 
set(MAIN_TARGET controller_app)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(${APP_NAME} C CXX ASM)

pico_sdk_init()

# Pull in FreeRTOS
include(FreeRTOS_Kernel_import.cmake)

# Include config only for FreeRTOS target. 
target_include_directories(FreeRTOS-Kernel INTERFACE
${CMAKE_CURRENT_LIST_DIR}/config)

# Fetch cJSON library
include(FetchContent)
FetchContent_Declare(
  cjson
  GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
  GIT_TAG v1.7.17
)
set(ENABLE_CJSON_TEST OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cjson)

add_executable(${MAIN_TARGET}
    src/main.c
    src/config.h
    src/joystick.c
    src/comm.c
    src/wifi.c
    src/system_state.c
    src/tasks/joystick_task.c
    src/tasks/comm_task.c
    src/tasks/system_task.c
)

target_include_directories(${MAIN_TARGET} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/src/tasks
    ${cjson_SOURCE_DIR}
)

target_link_libraries(${MAIN_TARGET}
    pico_stdlib
    hardware_adc
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
    cjson
)

# Include libraries necessaries to control the WiFi.
if (PICO_CYW43_SUPPORTED)
    target_link_libraries(${MAIN_TARGET} pico_cyw43_arch_lwip_sys_freertos)
endif()

#Support for stdio (printf, fwrite, puts...) via usb or UART. 
pico_enable_stdio_usb(${MAIN_TARGET} 1)
pico_enable_stdio_uart(${MAIN_TARGET} 0)

# Create different output files
pico_add_extra_outputs(${MAIN_TARGET})
