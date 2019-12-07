
The R910 cannot be configured to turn itself on when the battery has been charged back up. Since we can't guarantee that the battery will never drop below the level that causes the R910 to turn off we need an external device to turn the R910 back on.

The external watchdog needs to periodically check if the R910 is off and battery voltage is high enough for it to be turned back on, then turn the R910 back on by simulating a power button press and hold.

The watchdog should preferably be a 1.8 V logic level device for a few reasons:

* It needs to run on a supply voltage between 3.1 and 4.2 V
* It needs to detect the 1.8 V on voltage of the R910
* We might in the future want it talk to the R910 over serial

It probably still could be a 3.3 V device since they can often operate on a bit less than 3.3 V, but it could get tight with a 3.1 V supply and a voltage regulator which probably needs at least 0.2 volts difference, leaving us with 2.9 V. Detecting 1.8 V is also not hard on a 3.3 V device, it just requies a support component or two. Lower voltage doesn't necessarily mean less power consumption here since we're using a voltage regulator (though we could use something more efficient if it becomes an issue).

# 1.8 V arduino

Here's [a guide](https://www.iot-experiments.com/arduino-pro-mini-1mhz-1-8v/) for how to reprogram a 3.3 V arduino pro mini to 1.8 V. It will work for any Atmega 328P. The guide uses a purpose-built ISP to low-level program the arduino but the simpler solution is to use another 3.3 V arduino as the programmer using the ArduinoISP method.

## Programming an Arduino as ISP

To program an Arduino as an ISP the easiest way is by using the official Arduino IDE. Simply go to File -> Examples -> 11.ArduinoISP -> ArduinoISP. Then uncomment the line:

```
// #define USE_OLD_STYLE_WIRING
```

Then upload the sketch to your 3.3 V capable Arduino. This will now be your ISP.

Here's how to hook up your ISP to the soon-to-be 1.8 V arduino.

ISP <-> 1.8 V Arduino:

* Pin 10 <-> RST
* GND <-> GND
* VCC <-> VCC
* Pin 11 <-> Pin 11
* Pin 12 <-> Pin 12
* Pin 13 <-> Pin 13

You're now ready to program the 1.8 V device via the Arduino as ISP.

## Re-programming the e-fuses

To change the 3.3 V Arduino Pro Mini into a 1.8 V device we'll need to reprogram the e-fuses.

The [Engbedded AVR Fuse Calculator](http://www.engbedded.com/fusecalc) is really useful for figuring out how to set fuses on AVR devices. Otherwise consult the datasheet.

Here are the fuse settings we used.

Fuse Low Byte (FSL):

* Don't divide clock by 8: CKDIV8=1
* Clock output off: CKOUT=1
* Slowest startup time at 65 ms: SUT=10
* Enable the internal oscillator at 128 kHz: CKSEL=0011

So FSL is 11100011 or 0xE3

Fuse High Byte (FHB):

* Disable boot reset vector since we don't use a bootloader: BOOTRST=1
* Everything else at defaults

Sp HFB is 0xDB

Extended Fuse Byte (EFB):

* Disable brown-out detection: BODLEVEL=111

So EFB is 11111111 or 0xFF

Here's the `avrdude` command-line to program the e-fuses:

```
avrdude -P /dev/ttyUSB0 -c avrisp -p m328p -b 19200 -U lfuse:w:<0xE3>:m -U hfuse:w:<0xDB>:m -U efuse:w:<0xFF>:m
``

# Compiling the watchdog program

ToDo

# Uploading the watchdog program

To program the sketch:

```
avrdude -P /dev/ttyUSB0 -c avrisp -p m328p -b 19200 -U flash:w:watchdog.hex
```

# Accessing 1.8 V when R910 is off

Unfortunately only the direct battery voltage seems to be accessible outside of the cans when the device is off so we need to use a separate 1.8 V regulator.

# Turning on R910 electrically

The on button seems to be the only place where an electrical connection for turning the device on is exposed. When looking at the side of the PCB with the button, with the "WIFI 1" text right side up, the button is at the top left. It has four attachment points. The top two and bottom left pads are all ground. The bottom right pad is the pin that needs to be tied to ground to turn on the device. It needs to be tied to ground for several seconds or the boot process will halt.

None of the exposed pads on either side of the PCB seem to be connected to the "turn on" pad, so unfortunately we have to solder to the tiny pin right next to the button.

## Detecting if the R910 is on

There are a bunch of pads to the top right on the same side of the PCB as the "WIFI 1" text. The fifth pad from the top left is 1.8 V when the device is on and 0 V when it is off.
