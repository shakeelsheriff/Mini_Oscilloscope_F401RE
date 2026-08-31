# ==============================================================================
# Makefile for STM32F401RE Pure Bare-Metal Mini Oscilloscope
# ==============================================================================

TARGET = Mini_Oscilloscope_F401RE
BUILD_DIR = build

# Toolchain definitions
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# MCU Architecture Flags (Cortex-M4 with hardware Single Precision FPU)
MCU = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

# Include paths
INCLUDES = \
    -I. \
    -Idrivers/inc

# C Sources
SRCS = \
    main.c \
    startup/startup.c \
    drivers/rcc_driver.c \
    drivers/gpio_driver.c \
    drivers/usart_driver.c \
    drivers/adc_driver.c \
    drivers/timer_driver.c \
    drivers/systick.c \
    drivers/circular_buffer.c

# Compiler Flags
CFLAGS = $(MCU) $(INCLUDES) -O2 -g -Wall -Wextra -std=gnu11 \
         -ffunction-sections -fdata-sections -fno-builtin

# Linker Flags
LDSCRIPT = linker.ld
LDFLAGS  = $(MCU) -T$(LDSCRIPT) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref \
           -Wl,--gc-sections -nostartfiles

# Objects
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

# Default target
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex print_size

# Object compilation
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir $(subst /,\,$(dir $@)) 2>nul || cd .
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $< -o $@

# ELF Linking
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@echo [LD] $@
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

# Binary generation
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@echo [OBJCOPY] $@
	@$(OBJCOPY) -O binary $< $@

# HEX generation
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@echo [OBJCOPY] $@
	@$(OBJCOPY) -O ihex $< $@

# Create build directory
$(BUILD_DIR):
	@mkdir $(BUILD_DIR) 2>nul || cd .

# Print firmware size
print_size: $(BUILD_DIR)/$(TARGET).elf
	@echo ====================================================
	@$(SIZE) $(BUILD_DIR)/$(TARGET).elf
	@echo ====================================================

# Flash firmware using OpenOCD
flash: $(BUILD_DIR)/$(TARGET).elf
	@echo Flashing $(TARGET).elf via OpenOCD...
	openocd -f board/st_nucleo_f4.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

# Clean build artifacts
clean:
	@if exist $(BUILD_DIR) rd /s /q $(BUILD_DIR)
	@echo Cleaned build artifacts.

.PHONY: all clean flash print_size
