R2FX.ino
====

## Preface
Based on the excellent [Padawan360](https://github.com/dankraus/padawan360)
sketch by Dan Kraus, which was influenced by DanF's original [Padawan PS2](http://astromech.net/droidwiki/index.php?title=PADAWAN) control system.  A
lot changed from the original fork, only a few lines remain, too much change to
make sense keeping it as a fork since there likely won't be pull requests being
made. See for the original implementation of Xbox 360 based control.

## Intro
_Soon_

## Components

- #### Arduino Mega or Compatible Clone

- #### USB Shield
  Any board derived from the original [Circuits@Home](https://www.circuitsathome.com/products-page/arduino-shields) project should work.  All boards may differ slightly with which
  jumpers and headers are soldered if you order a knock off from Amazon or
  elsewhere.

  Also keep in mind, if you don't by the original (distribution of the board is
  a pain) to contribute to their awesome project that made this project possible.

- #### Xbox 360 Wireless USB Receiver

- #### Xbox 360 Wireless Controller
  Take it from your old Xbox. ;)

	**Note:** If you don't have these two, just buy a bundled set from Amazon,
  it's a bit cheaper.

- #### WAVTrigger
  Sourced from [SparkFun](https://www.sparkfun.com/products/13660)

- #### Sabertooth Motor Controller - Feet
	Depending on your motors you'll want a [Sabertooth 2x25](https://www.dimensionengineering.com/products/sabertooth2x25) or [2x12](https://www.dimensionengineering.com/products/sabertooth2x12).

- #### Syren Motor Controller - Dome
	[Syren 10](https://www.dimensionengineering.com/products/syren10)

- #### Amp and Speakers

- #### Optional Components
  ##### Voltage Sensor
  A small cheap [voltage sensor](https://www.amazon.com/Diymall-Voltage-Sensor-Dc0-25v-Arduino/dp/B00NK4L97Q) which connects to your main power and A2 and GND on your MEGA.

## Setup

### Controller LED Status

|LEDs Around Center Guide Button   |Description   |
|---|---|
| 4 Flashing/Blinking in Unison  | Looking for connection to receiver   |
| Rotating/Spinning pattern  | Connected to receiver. Foot motors disengaged  |
| Single LED Top Left - Steady  | Foot Motors Engaged. Speed 1  |
| Single LED Top Right - Steady  | Foot Motors Engaged. Speed 2  |
| Single LED Bottom Left - Steady   | Foot Motors Engaged. Speed 3  |
_Just like Dan's system_
