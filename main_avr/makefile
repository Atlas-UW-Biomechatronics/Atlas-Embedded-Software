CC     = avr-gcc
CPP    = avr-cpp
COPY   = avr-objcopy
SIZE   = avr-size
PROG   = avrdude
DUMP   = avr-objdump 

MCU    = atmega328p
CFLAGS = -mmcu=$(MCU) -std=c11 -Wall -Wextra -finline-functions

BUILDDIR = build

OBJS = $(addprefix $(BUILDDIR)/, main.o pins.o led.o )

all: $(BUILDDIR) $(BUILDDIR)/main.hex

%.hex: %.elf
	$(COPY) -O ihex -R .eeprom $< $@

$(BUILDDIR)/main.elf: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: %.c 
	$(CC) -Os -DF_CPU=16000000UL $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir $(BUILDDIR)

clean:
	rm -f $(BUILDDIR)/*

size:
	$(SIZE) $(BUILDDIR)/main.elf

#  make send - program firmware on device
send: $(BUILDDIR)/main.hex
	$(PROG) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$<

list: $(BUILDDIR)/main.lst

$(BUILDDIR)/main.lst: $(BUILDDIR)/main.elf
	$(DUMP) -S $< > $@