###############################################################################
# Makefile for the project m8key
###############################################################################

## General Flags
PROJECT = m8key
MCU = atmega168
TARGET = m48key.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                                                                       -DF_CPU=20000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=m48key.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"G:\home\Documents\Projects\0-Electronics\OsuKB\osu-keyboard-v2\Prog\src\usbdrv" -I"G:\home\Documents\Projects\0-Electronics\OsuKB\osu-keyboard-v2\Prog\src\." 

## Objects that must be built in order to link
OBJECTS = main.o usbdrvasm.o usbdrv.o softPWM.o RGBLED.o speed.o WorkMode.o setup.o KeyScan.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) m48key.hex m48key.eep m48key.lss size

## Compile
usbdrvasm.o: ../usbdrv/usbdrvasm.s
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usbdrv.o: ../usbdrv/usbdrv.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

softPWM.o: ../softPWM.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

RGBLED.o: ../RGBLED.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

speed.o: ../speed.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

WorkMode.o: ../WorkMode.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

setup.o: ../setup.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

KeyScan.o: ../KeyScan.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) m48key.elf dep/* m48key.hex m48key.eep m48key.lss m48key.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

