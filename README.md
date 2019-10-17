# openMicroInverter 
#![ Fig. 0.](figures/oshw-logo-100-px.png  "oshw logo.")
## An open source hardware platform for experimenting with DC-to-AC conversion, power and energy metering and grid tie inverters

### What is the openMicroInverter?
The *openMicroInverter* or open Micro-Inverter, abbreviated as oUI, is an Arduino-UNO based DC-to-AC power converter. The oUI platform is meant to do experiments with power electronics and energy systems. This board is intended to work as:

1. a DC-to-AC power inverter for off grid applications
2. an AC power meter and energy metering device
3. an inverter which phase-locks to the grid voltage
4. as solar-inverter or inverter for energy storage systems.
5. as a bi-directional power converter.

Why then using the 8-bit Arduino-UNO? Just because it is fun to squeeze the maximum out of it:-) Furthermore, this project shows the full capabilities of the TrueRMS Arduino library from this repository. Applications i, ii and iii have been successfully realized so far...

This work is still in progress...

### How does it work?
The oUI power converter topology is a single-phase, single-step, transformer coupled power converter with a full H-bridge inverter/rectifier. This type of converter is not as efficient as a high frequency switching combination of a boost converter plus DC-to-AC converter, but the oUI is simple to build and relatively safe to operate.


