# DJI C610 Dynomometer

## Summary
For more information on what a dynomometer is and what they're good for visit: https://build-its-inprogress.blogspot.com/search/label/Motor%20Dyno

This repo hosts the Arduino/Teensy firmware for a dynomometer built with two DJI C610 controllers and M2006 motors. A HP100 torque meter is used as the torque transducer. While the HP100 is relatively noisy, probably only resolving 1/100th Nm, it's about 1/10th the cost of a futek torque transducer that might normally be used in such a dyno setup.

## Electronics
* Teensy 4.0
* CAN transceiver
* HX711 breakout board
* 2x C610 motor controller
* 2x M2006 motors
* HP100 torque meter