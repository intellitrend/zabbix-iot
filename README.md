# Example Zabbix IoT-Sensor from Zabbix Summit 2018

For details about the summit and the talk see [Zabbix Summit 2018](https://www.zabbix.com/zabbix_summit2018#overview) and [Better dress warm - IOT meets Zabbix](https://www.zabbix.com/zabbix_summit2018_agenda#day1_1630).


# About this repository

This repository shows how to build a simple IoT-Sensor based on [Espressif Systems ESP32](https://www.espressif.com/en/products/hardware/esp32/overview) that directly connects to a [Zabbix Server](https://www.zabbix.com) or Zabbix Proxy and can measure _temperature_, _air pressure_, _humidity_ and also the _RSSI_ of the Wi-Fi connection. It is a very basic demo application that will not receive further updates.

It includes:
* `/docs` - Schematic (Wiring). 
* `/src` - Demo Application (C++ to be used with [Arduino IDE](https://www.arduino.cc/en/Main/Software) or [Espressif's IDF](https://github.com/espressif/esp-idf)).
* `/zabbix` - Zabbix Template (requires Zabbix 3.0+)

The demo application contains a simple Zabbix Sender library, which is compatible with the "Zabbix Sender Protocol".


# Required Hardware

To build this sensor the following components are needed:

* __Microcontroller Espressif ESP32__. (either as a [module](https://www.espressif.com/en/products/hardware/modules) or as a [devKit](https://www.espressif.com/en/products/hardware/esp32-devkitc/overview)). Note: There are many vendors on the market, that sell different types of boards based on the ESP32.
* __Sensor Bosch BME280__. The [BME280 modul](https://www.bosch-sensortec.com/bst/products/all_products/bme280#tab_module_16_1_0) itself is really tiny (2.5mm*2.5mm) and hard to solder. Better use a breakout board like the [ADAfruit BME280](https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout)
* __2 LEDs with Resistors__: These are optional and can be used to signal the user what the sensor is doing. See the schematic in `/docs` and the code for how they are used.
* __PCB or Breadboard__: Either build your own PCB or use a [breadboard](https://en.wikipedia.org/wiki/Breadboard) to get started.
* __Micro USB cable__: To flash the software, one needs to connect via a serial port to the ESP32. When using a devKit type board, then these boards have a micro USB connector that provides a serial port for the PC next to the power-supply for the ESP32 itself. Depending on the chipset used, a driver will be needed.

# Required Development Software

To build a working firmware for the ESP32, the code must be cross-compiled. This can be done in a Windows or Linux environment. Basically there are 2 options.

## Beginner friendly

For beginners, the easiest is to use the [Arduino IDE](https://www.arduino.cc/en/Main/Software). This IDE is simple to configure and contains a library manager, that installs required libraries (like sensor libs) with just some clicks from the GUI. However, this IDE is not a full featured C/C++ IDE.

Download and install Arduino. Then follow the instructions to add support for the ESP32 environment. See the [arduino/esp32 respository](https://github.com/espressif/arduino-esp32) and specificially the [instructions for boards manager](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)

## Advanced user 

If you are more experienced and prefer to use an IDE like [Eclipse](https://www.eclipse.org/downloads/packages/), then this requires a lot more work to [setup the Espressif's IDF](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/eclipse-setup-windows.html)  (IoT development Kit) and to configure the various settings in Eclipse. Also, there is no menu driven library manager, thus libraries must be installed manually. 


# Setup the Application

All sources (except the external library) are located in the `/src` directory. The main application file is called `ZabbixIot.ino`.

## Arduino

Arduino uses a specific naming convention. The main file must have the same name as the project directory and must end with `.ino`. So in this case that would be the following structure: `ZabbixIot/ZabbixIot.ino`. To start, create a new directory `ZabbixIot` in the arduino sketch directory and copy the content of the repository /src directory into it.

_Note:_ Arduino does not allow to place  `.cpp` or `.h` in subdirectories. This is why all those files are located in the main source directory.

## IDF (Eclipse)

Using Eclipse with IDF or only the IDF, a file like `main.c` or `main.cpp` is expected.

Create a new ESP32 example project using the IDF tools and copy the content of `/src` into it. Then rename `ZabbixIot.ino` to `main.cpp`.

_Note:_ While the IDF is written in C, there are still a lot useful libraries out that are written in C++.


# Configure Application Settings

All relevant application settings are defined in `settings.h`. This includes the Zabbix configuration, Wi-Fi and measuring interval.

Per default, `measuring interval` is set to 60 seconds. This means the sensor will make a measurement and then go to sleep for 60 seconds. 


# Required Software Libraries 

Once the development environment is set, the application requires the following libraries:

* __BME280E Sensor__: [Adafruit_BME280_Library](https://github.com/adafruit/Adafruit_BME280_Library). 
* __ArduinoJson__: [ArduinoJson Library](https://arduinojson.org/v5/doc/installation/)


## Arduino
When using the Arduino IDE, simply install this libraries using the library manager.

## IDF (Eclipse)
When using Eclipse or IDF only, the setup depends on your build settings.


# Compile, Flash and Monitor

## Arduino

Setup Com-Port in Arduino IDE.

Select Compile from the menu, select flash from the menu. 

To view the output of the ESP32, select "Serial Monitor" from the menu.

## IDF (Eclipse)

Setup Com-Port by issuing `make menuconfig`. 

Then `make flash` and `make monitor` to see output.

# Support

We do not provide support for this repository. However we provide custom development for hardware and software. Contact us if you need assistance in your sensor project.