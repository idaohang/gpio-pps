gpio_ppd - allocate a gpio pin for platform PPS

parameters: pin - which gpio pin (raspi numbers, i.e. 18 is next to the UART)

This is to be used IN PLACE of the patch for arch/arm/bcm2708.c patch, 
where you have to recompile the kernel to change which pin.

You still need to enable (as modules) PPS support in the kernel.

(And need to recompile ntp with pps support and adjust the config).

The pikernomatic default now enables the kernel pps.
