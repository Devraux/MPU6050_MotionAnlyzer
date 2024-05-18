cmake_minimum_required(VERSION 3.27.4)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(MPU6050_MotionAnalyzer C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME} 
    main.c 
    mpu6050/mpu6050.c
    kalman_filter/kalman_filter.c
    ringbuffer/ringbuffer.c)
  
include_directories(mpu6050)
include_directories(ringbuffer)
include_directories(kalman_filter)



# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PRIVATE PARAM_ASSERTIONS_ENABLE_ALL=1)

target_link_libraries(${PROJECT_NAME} 
    pico_stdlib 
    hardware_i2c 
    hardware_gpio 
    hardware_uart
)