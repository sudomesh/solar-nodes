
These are notes on the first $300 solar node prototype.

# Bill of Materials

TODO finish this

* Sparkfun Sunny Buddy MPPT solar battery charger 
* A 10k B=3380 NTC thermistor for Sunny Buddy thermal safety cut-off
* 4 Panasonic NCR18650B 3200 mAh li-ion batteries
* Custom aluminum heatsink
* Aluminum case 
* L and U shaped lengths of aluminum channel (was it 1/2" ? TODO)
* Various nuts, bolts and machine screws
* Thermal paste
* Thermal glue
* Thin stranded wire for soldering directly to SMD IC pin
* 1 set of solar panel plugs (TODO what are they called)
* ~1 foot of thick'ish cable for connecting to solar panel plugs
* Outdoor long-lasting silicone for sealing case

# Tools used

TODO finish this

* Soldering iron
* Glue gun
* Hand-held drill
* Files: Round and flat
* Something to cut sheets of aluminum
* Welder TIG AC/DC
* Beefy drill press or mill
* Drills (TODO which sizes)

For the first prototype the case and battery heatsink were custom-made by cutting, drilling and welding aluminum. For future iterations the plan is to use an off-the-shelf aluminum case and a less overbuilt battery heatsink

# Solar panel

Our prototype uses [this Renogy flexible 50 W ETFE panel](https://www.ebay.com/itm/RICH-SOLAR-50W-80W-100W-Mono-Flexible-Solar-Panel-12V-PV-Power-RV-Boat-ETFE/142823107329) which cost $80. One nice thing about it is that it's made in India rather than China, at least according to the labeling.

You can find cheaper [$50 panel that probably aren't actually 50 W](https://www.ebay.com/itm/50W-Dual-12V-5V-USB-Solar-Power-Panel-Car-Boat-Battery-Charger-50A-Controller/293177993583) but eh they could be and we haven't even tested the one we got.

# Battery protection circuit

We already have thermal protection and our charge controller is incapable of exceeding the max current on our 4-battery pack while the sunny buddy is set to max 4 V so we don't have to worry about over-temperature, over-current or over-voltage. The Franklin R910 has built-in under-voltage protection and definitely can't pull more current from the batteries than they can deliver, so we're pretty good on pretection over all but we should have an extra protection circuit in case something goes wrong.

First we got [these combined battery holder and protection circuits](https://www.ebay.com/itm/4Pcs-Battery-Holder-Case-for-Li-ion-3-6V-3-7V-18650-17670-Cell-1S1P-w-PCM-Inside/221234396554) but haven't used them for the first prototype due to concerns about contact using only mechanical pressure (sparking) and difficuly of thermally coupling the batteries while in the holders. 

We'll definitely test that solution out, but we ended up with the aluminum block instead for the first prototype so we got [this module](https://www.ebay.com/itm/1S-5A-3-7V-18650-BMS-Li-ion-lithium-Lipo-Battery-Circuit-PCB-Protection-Boar-TDO/233381371171) instead.

[This one](https://www.ebay.com/itm/6-12A-3-7V-PCB-BMS-Protection-Board-for-18650-Li-ion-Lithium-LiPo-Battery-C-BnIJ/233387320866) might be good if we need more amperage in the future.

# batteries

We're using Panasonic NCR18650B 3300 mAh batteries bought from [Li-ion Wholesale](https://liionwholesale.com/collections/batteries/products/panasonic-ncr18650b-battery-genuine-tested-6-8a-3400mah-flat-top-wholesale-lot?variant=1076987260).

# External watchdog

The R910 will shut itself down on low battery and there is no way to make it turn itself back on when the battery charge level comes back up.

We're building a small external watchdog which will operate in low power sleep mode most of the time, then wake up periodically to check the battery voltage and whether the system is on. If voltage is high enough and the system is off then it should toggle the on "button" for a few seconds to turn the system back on.

We're using an Arduino Pro Mini 3.3 V reprogrammed with an ISP (without a bootloader) to operate at 1.8 V and 128 kHz. It is powered by a 1.8 V regulator. This will allow it to operate on the full range of possible battery voltages (~ 3.0 to 4.2 V) while being able to talk to the R910 at its native logic level of 1.8 V.

Here's [a guide](https://www.iot-experiments.com/arduino-pro-mini-1mhz-1-8v/) for how to reconfigure an Arduino for 1.8 V operation. The guide shows how to do do it using a dedicated ISP, but it's just as easy to do with an arduino that has been programmged with the ArduinoISP sketch.

Note that at this point it doesn't matter whether it's an Arduino since we're not using the bootloader. All we need is an Atmega 328P (or similar) and we aren't even using the external oscillator nor the 3.3 or 5 V regulator on the dev boards.

Here's a really nice [http://www.engbedded.com/fusecalc](Atmel AVR E-fuse calculator)

# WiFi antennas

The first prototype uses two 2.4 GHz 14 dBi panel antennas with RP-SMA connectors for ~$13 each [from ebay](https://www.ebay.com/itm/New-Directional-Antenna-WiFi-Extender-Panel-2-4-GHz-14dbi-High-Gain-Long-Range/192858084948). These are the most common type of antenna that show up if you search for `2.4 GHz 14 dBi panel antenna`. Preliminary testing gave us a 10 dBi gain (testing two R910 units side by side, one with two of these and one with normal antennas).

We also bought two 5.8 GHz 14 dBi panel antennas with RP-SMA connectors for $9.60 each [from ebay](https://www.ebay.com/itm/5-8G-14db-Aerial-High-Gain-Panel-Antenna-for-FPV-5-8Ghz-TX-RX-2016-New-C6Q3/142925180377). These come without an enclosure and have not yet been tested. The advantage is the much smaller physical size due to the higher frequency.

# Batteries

The R910 has three battery contacts, and one is likely for communication with a thermal probe or something more intelligent. However, looking at the `/sys` filesystem it looks like it's not capable of reading a battery temperature with the official battery plugged in. In any case it doesn't complain if the third contact is connected or not so we're not using it.

We're using four Panasonic NCR18650B in parallel. For the first prototype we've drilled holes in a block of aluminum and slid them in there with some thermal grease, then insulated with kapton tape, welded the batteries together with a battery welder and again sealed with kapton tape. The aluminum block is meant as heat sink but is super overkill.

# Charge controller

We're using a Sparkfun Sunny Buddy as the solar battery charge controller. Mostly because it was the only thing we could get reasonably quickly and from a somewhat trustworthy vendor that has a decent chip on it. It uses the LT3652 MPPT-capable 2 A chip. Unfortunately their design is kinda annoying with the following shitty "features":

* 4.0 V output instead of 4.2 V
* Thermal probe pin from LT3652 not brought out on board
* Current limited to 450 mA

We changed the sense resistor according to the LT3652 datasheet to allow the max 2 A power and soldered directly to the chip to connect a thermal probe. The 4.0 V output actually turns out to work for us.

We should make our own board with a higher-powered version of the LT3652 since modifying and paying for these just doesn't make sense (they're like $26 + shipping).

## Verifying min and max charge

The Sparkfun Sunny Buddy outputs only 4 V (measured). This is not specified anywhere but is confirmed by one of the reviews on sparkfun.com (a positive review at that). This is odd as you'd want 4.2 V to fully charge a Li-ion battery, though of course charging to 100% is not always advisable, especially if you want a decent battery lifetime. Charging between e.g. 10% and 90% will make your battery life for more charge cycles.

Looking at the Panasonic NCR18650B battery spec sheet (the batteries we used in our build) it looks like there is very close to zero capacity in the 4.2 to 4.0 V range if either the discharge rates are 1C or more or at tempereatures below freezing (probably even at temeratures higher than 0 but we don't have exact data). There is a bit of capacity at 0.5 C to 0.2 discharge rates. Looks like about 100 mAh for 0.5 C and 300 mAh for 0.2 C. So by charging only to 4.0 V we loose between 0% and 8.8% of the total capacity depending on discharge rate and temperature. If we assume 0.5 to 4 W power draw that equates to between about 0.3 C and 0.03 C. That means we're probably loosing around 10% at the top which is ideal.

The R910 shuts off at 3.1 V (verified experimentally by watching serial console while slowly lowering input voltage) so it looks like we'll loose about 200 mAh or less at the bottom.

## Adding thermal probe to LT3652

According to LT3652 datasheet we need a 10k B=3380 NTC thermistor.

When voltage drops below 0.29 V (T > 40 C) or above 1.36 (T < 0 C) then charging shuts down. We could add another resistor in serial to get the max temp closer to 45 C but maybe 5 C is a good margin.

Digikey has [this one](https://www.digikey.com/product-detail/en/murata-electronics/NXRT15XH103FA1B040/490-7167-ND/3900399).

The last 3 digits in the manufacturer model number is just length of the wire leads.

Attach to the NTC pin and ground. It sources 50 microamps.

Jake gave me a NTC103 (labelled TDC310) which has a beta value of 4100 so 5175 ohm at 40 C compared to 5810 Ohm at 40 C on the appropriate thermistor:

I used a resistor in series which I measured to 660 Ohm so 5835 Ohm at 40 C which comes out to 0.29175 which is very much close enough to spec. This means that it will shut off at very close to 40 C but also at around 4.7 C instead of 0 C.

## Setting current limit to max on the sunny buddy

Add resistor at R_sen (which is in parallel to R1).

```
Max current = 0.1/((0.22 * R_sen) / (0.22 + R_sen))
```

Max current with no resistor at R_sen = 450 mA.

Absolute max for the LT3652 is 2 A.

R_sen value for 2 A max is 0.0648 Ohm. Rounding to 0.065 gets us just below 2 A.

## Other charge controllers

I ordered some of [these TI BQ24650 based models](https://www.ebay.com/itm/BQ24650-MPPT-Solar-Panel-Lithium-Lead-acid-Battery-Charging-Board-Controller-5A/183785610819)  but they're taking 4-6 weeks to ship.

[This one](https://www.ebay.com/itm/Wal-Front-1Pc-Solar-Panel-Controller-Charging-Module-Bq24650-5A-Mppt-Solar-Pane/123935030586) also looks interesting.

Didn't order [this one](https://www.waveshare.com/solar-power-manager.htm). It's interesting but uses the CN3791 which we've tried and verified isn't actually MPPT (you adjust it manually to set the power point).

We ordered and ended up using the [Sparkfun Sunny Buddy](https://www.sparkfun.com/products/12885) because we could get it very quickly from digikey and it was likely to work.

# Outdoor case

Minimum probably:

1" depth but will be super tight with antenna plugs sticking up.
It will work if we only use angled antenna connectors and pigtails.

4G hotspot is 4 1/4" so that's minimum for one dimension. Let's call it width.
The solar charge controller should fit on top of the hotspot within the 1" depth.
If we put the battery side by side with the hotspot (long dimensions touching)  then 5 1/2" height is enough, barely, but 6" would be better. We wouldn't be fitting any N-type connectors in the case wall. Should be room for RP-SMA though.

If we put them side by side with short dimensions touching then 3" by 8" would be just barely enough. We wouldn't be fitting any N-type connectors in the case wall. Should be room for RP-SMA though.

If we put the hotspot on top of the battery then 2" depth would work with angle TS-9 connectors. Other dimensions would be minimum 4 1/4" by 2 6/8". That's again without room for an N-type connector through the wall. Should be room for RP-SMA though. 108 * 70 * 50 mm


