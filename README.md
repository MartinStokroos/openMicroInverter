# openMicroInverter ![ Fig. 0.](figures/oshw-logo-100-px.png  "oshw logo.")
### An open source hardware platform for experimenting with DC-to-AC conversion, power and energy metering and grid tie inverters.

### What is the openMicroInverter?
The *openMicroInverter*, or short *oμi*, is an **Arduino-UNO based** DC-to-AC power converter. The *oμi* platform is meant for doing experiments with power electronics and energy systems. The *oμi* is intended to work as:

1. DC-to-AC power inverter for off the grid applications,
2. AC power meter and energy metering device,
3. an inverter which phase-locks to the grid,
4. solar-inverter or inverter for energy storage systems and
5. a bi-directional power converter.

Why then using the 8-bit Arduino-UNO? Just because it is fun to squeeze the maximum out of it:-) Furthermore, this project shows the full capabilities of the TrueRMS Arduino library from my repositories. Applications i, ii and iii have been successfully realized so far...

This work is in progress.

### How does it work?
The converter topology of the *oμi* is a single-phase, single-step, transformer coupled power converter with a full-bridge inverter. This type of converter is not as efficient as a high frequency switching boost converter with DC-to-AC converter, but the *oμi* is simple to build and relatively safe to operate.

### The Hardware
There are two versions of the hardware. It are the development model and the final platform design. The development model has been used for the development of the software.
Please refer to the schematic diagrams to understand further explanation.

#### The openMicroInverter development model
A rapid prototype was created for software development. The development schematic is named *openMicroInverter_dev*.
A somewhat old H-bridge driver has been used for the design. It is the HIP4082, a medium voltage, medium frequency full-bridge driver distributed by *Renesas*.

to be continued...

#### The openMicroInverter hardware
This work is under development.

### Software Description
Arduino-UNO Pinout:

Pin | Function
--- | --------
A0 | scaled ac mains voltage biased on 2.5V DC. Full scale voltage is 350V peak-to-peak.
A1 | scaled ac inverter current biased on 2.5V DC. Full scale current is 5A peak-to-peak.
A2 | scaled ac inverter voltage biased on 2.5V DC. Full scale voltage is 350V peak-to-peak.
A3 | scaled battery current biased on 2.5V DC. Full scale current is .. A.
A4 | scaled battery voltage. Full scale voltage is .. V.
A5 | -
D2 | grid connect relay
D4 | debug pin
D6 | external reference voltage input for the comparator (ZCD).
D8 | inverter enable (high=on)
D7 | analog comparator input (AIN1) for zero-cross detection (ZCD) of the grid voltage. The analog comparator input is connected to A0.
D13 | Arduino LED as *PLL-locking* indicator

### The PowerSys library
This library contains modules used for power control. One basic function is the reference waveform generator. It is based on Direct Digital Synthesis and has special a feature for synchronizing the reference waveform with the grid frequency.

Explanation follows...

# Example Sketches
*Metering.ino*	-	This sketch is a power meter and energy metering example working with the *openMicroInverter_dev* hardware. The sketch contains the interrupt time base and ADC multiplexer, which will be used in future sketches.

