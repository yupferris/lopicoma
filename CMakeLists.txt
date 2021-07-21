cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(lopicoma C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(lopicoma
    lopicoma.c
)

pico_generate_pio_header(lopicoma ${CMAKE_CURRENT_LIST_DIR}/fifo.pio)

pico_enable_stdio_uart(lopicoma 1)

pico_add_extra_outputs(lopicoma)

target_link_libraries(lopicoma pico_stdlib hardware_pio)
