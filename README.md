MLNX/IoT: Internet of Things project
===

# Goal of the project:

Create a home sensing system for multiple applications, such as:

- Indoor temperature control
- Surveillance/Alarm system
- Domotic system
- Garden weather monitoring
- TBD

The system might be accesible to internet, so an autorized user may be able to login and monitor/control the system.

# Features

- Architecture:  ARM SoC (uP for the master, and uC for the slaves)
- Size:          No limitation for the master system. Slaves units: 30x55x85mm max aprox.
- Software:      Autonomous control system. Linux application / Web server on the master, Bare-metal on the slaves.
- Communication: Master/Slave 2.4GHz RF semi-duplex based on time slots
- Low-power:     Slave units based on button cell coin batteries. Target autonomy: 1 year

# Subdirectories:

* doc - Contains general documentation. Communication protocol description and detailed hw/sw specs.

* fw  - this is the firmware for the slave units
       
* sw  - this contains the Linux application and web server program for the Master unit.
        
* hw  - this directory contains hardware daughter boards and custom designs for the master/slave units.

# License

The MLNX/IoT project is released under the terms of the GNU Lesser General Public License (LGPL), version 3 or later.

# References 

[1]: http://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF51822        "nRF51822 - Nordic Semiconductor"


