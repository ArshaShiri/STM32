# Project Goal
This project aims to build a number of drivers for **STM32F407 Discovery** using modern C++. 

## Table of Contents
* [Description](#description)
* [Requirements](#requirements)
* [Apps](#apps)
* [Build](#build)
* [Flash](#flash)

## Description

## Requirements
* CMake
* clang-format
* pre-commit
* cmake-format
* ST-link

## Apps
* [led](#led)
* [ledButton](#ledbutton)
* [ledButtonInterrupt](#ledbuttoninterrupt)
* [spi](#spi)
* [spiInterrupt](#spiinterrupt)
* [i2c](#i2c)

#### led
This app makes the green LED blink. This app tests the GPIO drivers. A software timer is used to control the blinking frequency.

#### ledButton
This app toggles the green LED by pressing the user button on the board. A software timer is used to debounce the button. The program registers the button press in an infinite loop by reading the pin associated with the user button.

#### ledButtonInterrupt
In terms of functionality, this app is similar to [ledButton](#ledbutton) app. The main difference is that the button press is registered via an interrupt instead of an infinite loop.

#### spi
#### spiInterrupt
#### i2c

## Build

To build the project run `build.sh` script under `STM32F407Discovery`  
The following arguments can be passed to this script:  
* `-t` Build for the target. Build all the apps that are described in the [Apps](#apps) section.  
* `-h` Build for the host. This is used for running the unit tests.  
* `-a` Build for both the target and the host.  
* `-r` Rebuild.  
* `-d` Build in debug mode. By default, the build is in release mode.  

## Flash
To flash the apps described in the [Apps](#apps) section, run the `load.sh` script under `STM32F407Discovery`  
The `-p` argument followed by the app's name should be passed to the script as a command line argument.

