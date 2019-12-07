
This is information for the $300 solar node protype specific to the R910 and Sprint 4G LTE subscription.

# External watchdog

See `external_watchdog/README.md`

# Antennas

## Antenna connectors

We think the R910 hotspot uses MS162 antenna connectors. There's a github repo that claims they use TS9, and it's possible to get TS9 to fit with a bunch of work but it really doesn't seem like the right connector. MS162 is also a very snug fit but less so than TS9 and it stays on a lot better + the MS162 plugs are long enough to fit through the plastic of the case which is not quite the case with the TS9 plugs we've tried.

There is a seller on ebay called `wifi_expert` who sells MS162 pigtails to pretty much any antenna connector you can imagine, and they use RG316 cable and are based in California.

The R910 has six connectors total:

* Two dedicated to B41
* Two shared for B25 and B26
* Two for WiFi

The WiFi can be set to either 2.4 GHz or 5.8 GHz and also both at the same time. It's unclear if it has separate radios for the two (according to `iw phy` it doesn't) but either way they share the same antennas.

## 4G LTE

Sprint uses the following 4G LTE channels in the U.S:

* B26 - 859-894 MHz
* B25 - 1930-1995 MHz
* B41 - 2496-2670 MHz

It looks like most of their towers in the East Bay use all three frequencies.

There are TWO Sprint towers within a block of People's Park and they support all three frequencies.

Before we realized the R910 connectors probably aren't TS9 we ordered [this from ebay](https://www.ebay.com/itm/35dBi-4G-LTE-Booster-Ampllifier-MIMO-Antenna-TS9-Telstra-Optus-for-Huawei-ZTE/302680390516) and [one of these](https://www.ebay.com/itm/4G-3G-Antenna-28dbi-SMA-TS9-for-USB-LTE-Modem-MiFi-Mobile-WiFi-Router-Hotspot-US/254331707508). The dBi ratings on those are definitely completely fake and we haven't yet tested them to see how they actually work.

Currently our prototype is using [these N-type Omni-directional antennas from ltefix](https://ltefix.com/shop/antennas/4g-lte-antennas/omni-directional/700-2700mhz-terminal-3-5dbi-4dbi-4g-lte-omni-antenna-vertical-n-male/).

We're connecting them using [https://www.ebay.com/itm/RG316-N-Female-Bulkhead-Angle-to-MS162-Male-Angle-Coax-RF-Cable-USA-Ship/133141212174](these pigtails).

Since we're connecting them to band 41 only it would be better to use 2500 to 2700 MHz antennas but no-one really sells those. We should maybe just make those ourselves or trim some 2.4 GHz antennas a bit.
