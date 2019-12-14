

all: watchdog.ihex

watchdog.ihex: watchdog
	avr-objcopy -j .text -j .data -O ihex watchdog watchdog.ihex

watchdog: watchdog.c
	avr-gcc -Wall -O3 -mmcu=atmega328p -o watchdog watchdog.c

hello_world.ihex: hello_world
	avr-objcopy -j .text -j .data -O ihex hello_world hello_world.ihex

hello_world: hello_world.c
	avr-gcc -Wall -O3 -mmcu=atmega328p -o hello_world hello_world.c

clean:
	rm -f watchdog watchdog.ihex hello_world hello_world.ihex

upload: watchdog.ihex
	avrdude -P /dev/ttyUSB0 -c arduino -p m328p -b 19200 -U flash:w:watchdog.ihex

upload_hello_world: hello_world.ihex
	avrdude -P /dev/ttyUSB0 -c arduino -p m328p -b 19200 -U flash:w:hello_world.ihex
