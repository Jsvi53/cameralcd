#THIS FILE IS AUTO GENERATED FROM THE CAMERALCD! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.14)

# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_ST_FLASH, st-flash)
set(CMAKE_ST_INFO, st-info)

# project settings
project(CAMERALCD  C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)



set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
# add macro definition
# add_definitions(-DUSE_HAL_DRIVER -DSTM32F103xE -DUSE_STDPERIPH_DRIVER -DSTM32F103_HD -DSTM32F10X_HD)
add_definitions(-DUSE_HAL_DRIVER -DSTM32F103xE)

# get sources
file(GLOB_RECURSE SRC_LIST
    "Core/Src/*.c"
)

file(GLOB_RECURSE CMSIS_RTOS_V2 "Middlewares/Third_Party/FreeRTOS/Source/*.c")  # aux_source_directory("Middlewares/Third_Party/FreeRTOS/Source" CMSIS_RTOS_V2)
# replace Drivers folder sources files by the generate Makefile
set(SRC_LIST1
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c"
)
list(APPEND SRC_LIST ${CMSIS_RTOS_V2})
list(APPEND SRC_LIST ${SRC_LIST1} "startup_stm32f103xe.s")

# set include directories
set (INCLUDE_DIRS
    "Core/Inc"
    "Drivers/CMSIS/Device/ST/STM32F1xx/Include"
    "Drivers/CMSIS/Include"
    "Drivers/STM32F1xx_HAL_Driver/Inc"
    "Drivers/STM32F1xx_HAL_Driver/Inc/Legacy"
    "Middlewares/Third_Party/FreeRTOS/Source/include"
    "Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2"
    "Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3"
)

# add executable, .elf or .hex
add_executable(${PROJECT_NAME}.elf ${SRC_LIST} ${LINKER_SCRIPT})
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${INCLUDE_DIRS})

# compile option
set(CPU_FLAGS "-mcpu=cortex-m3" "-mthumb")
set(OPT_FLAGS "-Og")
set(DEBUG_FLAGS "-g -gdwarf-2")
set(C_DEFS "-DUSE_HAL_DRIVER" "-DSTM32F103xE")

target_compile_options(${PROJECT_NAME}.elf PRIVATE ${CPU_FLAGS} ${OPT_FLAGS} ${C_DEFS})
if(DEBUG)
    target_compile_options(${PROJECT_NAME}.elf PRIVATE ${DEBUG_FLAGS})
endif()

# set linker script
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F103ZETx_FLASH.ld")

# 链接选项
target_link_options(${PROJECT_NAME}.elf PRIVATE
    ${CPU_FLAGS}
    -specs=nano.specs
    -specs=nosys.specs
    -T${LINKER_SCRIPT}
    -Wl,-Map=${BUILD_DIR}/${CAMERALCD}.map,--cref
    -Wl,--gc-sections
)

# generate hex and bin files
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    # COMMAND ${CMAKE_ST_FLASH} --connect-under-reset erase
    # COMMAND ${CMAKE_ST_INFO} --probe
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${BUILD_DIR}/${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${PROJECT_NAME}.elf> ${BUILD_DIR}/${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Generating HEX and BIN files and calculating size"
    # VERBATIM
)

# clean
add_custom_target(clean_all COMMAND ${CMAKE_COMMAND} -E remove_directory ${BUILD_DIR})

