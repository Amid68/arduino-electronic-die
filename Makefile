# @file Makefile
# @brief Build script for the electronic die project
# @author Ameed Othman
# @date 2024-10-31

# Microcontroller and programmer settings
MCU = atmega328p
F_CPU = 16000000UL
BAUD_RATE = 115200
PORT = /dev/cu.usbserial-110  # Update this to your Arduino's serial port

# Compiler and programming tools
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Compiler flags
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Iinclude -Iinclude/application -Iinclude/drivers
LDFLAGS = -mmcu=$(MCU)

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Source and object files
APP_SRC = $(wildcard $(SRCDIR)/application/*.c)
DRV_SRC = $(wildcard $(SRCDIR)/drivers/*.c)
SRC = $(APP_SRC) $(DRV_SRC)
OBJS = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Target binary
TARGET = $(BINDIR)/dice_roller

# Default rule
all: $(TARGET).hex

# Linking
$(TARGET).elf: $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Compiling
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Creating HEX file
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Uploading to the Arduino Uno R3
upload: $(TARGET).hex
	$(AVRDUDE) -V -F -c arduino -p $(MCU) -P $(PORT) -b $(BAUD_RATE) -D -U flash:w:$(TARGET).hex:i

# Cleaning up generated files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean upload
