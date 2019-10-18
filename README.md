# openMicroInverter ![ Fig. 0.](figures/oshw-logo-100-px.png  "oshw logo.")
### An open source hardware platform for experimenting with DC-to-AC conversion, power and energy metering and grid tie inverters

### What is the openMicroInverter?
The *openMicroInverter*, or short *omui*, is an **Arduino-UNO based** DC-to-AC power converter. The omui platform is meant for doing experiments with power electronics and energy systems. The *omui* is intended to work as:

1. DC-to-AC power inverter for off the grid applications,
2. AC power meter and energy metering device,
3. an inverter which phase-locks to the grid,
4. solar-inverter or inverter for energy storage systems and
5. a bi-directional power converter.

Why then using the 8-bit Arduino-UNO? Just because it is fun to squeeze the maximum out of it:-) Furthermore, this project shows the full capabilities of the TrueRMS Arduino library from my repositories. Applications i, ii and iii have been successfully realized so far...

This work is in progress...

### How does it work?
The converter topology of the *omui* is a single-phase, single-step, transformer coupled power converter with a full H-bridge inverter/rectifier. This type of converter is not so efficient as a high frequency switching boost converter plus DC-to-AC converter combination, but the *omui* is simple to build and relatively safe to operate.

### The Hardware
Please refer to the schematic of the *omui* to understand further explanation.

### Software Description

### The PowerSys library
This library contains some modules used for power control. One of its functions is the waveform reference generator. it is based on Direct Digital Synthesis and has special features for synchronizing the reference waveform to the grid voltage.

