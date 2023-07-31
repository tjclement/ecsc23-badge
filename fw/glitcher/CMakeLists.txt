cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(hello_world
    main.c
    usb_descriptors.c
    cdc_sump.c
    adc.c
    output.c
)
add_definitions(-DPICO_DEFAULT_LED_PIN=26)
target_include_directories(hello_world PUBLIC
${CMAKE_CURRENT_LIST_DIR})

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello_world PUBLIC pico_stdlib pico_unique_id tinyusb_device tinyusb_board hardware_pio hardware_dma hardware_pwm)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello_world)
