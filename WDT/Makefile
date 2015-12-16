CC=avr-gcc
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
MCU=atmega328p
F_CPU=16000000UL

OBJCOPY=avr-objcopy
BIN_FORMAT=ihex

PORT=/dev/ttyUSB0
BAUD=115200
PROTOCOL=arduino
PART=m328p
AVRDUDE=avrdude -F -V

RM=rm -f

all: WatchDog.hex
	sudo $(AVRDUDE) -c$(PROTOCOL) -p $(PART) -P $(PORT) -b $(BAUD) -D -U flash:w:$<

compile: WatchDog.hex

WatchDog.hex: WatchDog.elf 
	 $(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@

WatchDog.elf: WatchDog.o 
	 $(CC) $(CFLAGS) -o $@ $<

WatchDog.o: WatchDog.c 
	 $(CC) $(CFLAGS) -c -o $@ $<

upload : 
	sudo $(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) $(BAUD) -U flash:w:WatchDog.hex

clean:
	$(RM) WatchDog.elf WatchDog.hex WatchDog.s WatchDog.o


