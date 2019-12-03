
This repo documents the solar and battery powered mesh nodes used by sudo mesh. These nodes provide high bandwidth internet connectivity backed by 4G LTE connections and are a separate project from the [disaster.radio](https://disaster.radio) nodes which are also solar+battery powered but does not route general purpose IP traffic to the internet.

We currently have two prototypes meant to test out two opposite extremes in terms of power consumption, weight and cost.

Currently both prototypes are designed to be pole-mounted though the $300 node is also designed to be suitable for strapping to a tree.

# The $300 node

This is our low-cost, light-weight prototype.

It sacrifices low build complexity to achieve the low cost and light weight. The primary components are:

* A Franklin R910 4G LTE wireless hotspot
* Four 3300 mAh li-ion batteries
* A flexible 50W ETFE solar panel
* A modified Sparkfun Sunny Buddy MPPT solar battery charger
* Two external omni-directional 4G LTE antennas
* Two semi-directional WiFi panel/patch antennas
* An aluminum frame for stabilization and mounting
* A weather-proofed aluminum box for the electronics

The Franklin R910 is a very low-power device, using less than 0.5 W with 4G LTE and WiFi active and a couple of connected WiFi clients. Maxing out the 4G bandwidth from one wifi-connected device takes about 1.5 W and maxing out with 10 devices all running internet speed tests takes about 4 W.

The battery capacity of this node is 3.7 V * 3.3 Ah * 4 = ~48.84 Wh

Now in actuality we're probably only going to get ~90% of that since we're not fully discharging to zero nor fully charging to max, since li-ion batteries can handle many more charge cycles when operated like this. If we assume an average usage of 2 W then that gives about 22 hours of usage with no charging at all:

(48.84 * 0.9) Wh / 2 W = ~22 hours

We're using a 50 W panel, which may seem oversized, but consider the shortest day of the year in Oakland, CA being (TODO check) 8 hours, that cuts the power input to 1/3 of total on time (actually less given no useful sun right at sunrise and sundown) and consider that it may be entirely cloudy for those 8 hours, which can reduce the input to 10 W. Include inefficiencies in the battery charging and discharging and now we're probably down to around 1.5 W  or less, and that's assuming the panel is mounted in an ideal location! It's also likely that the claimed 50 W of the panels we bought were a marketing fiction. We haven't actually tested them yet.

If we end up having too much power loss down-time we might do a couple of things:

* Intelligently shut-down during low-use hours (e.g. 2 to 6 am)
* Add more batteries and hope we don't get too many cloudy days in a row

# The $1k node

This prototype is completely built from off-the-shelf parts. Most of the build consists of bolting things together and configuring some software. Only one part of the build requires more than hand tools

ToDo list major components

