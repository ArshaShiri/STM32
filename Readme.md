# Project Goal
This project aims to build a nubmer of drivers for **STM32F407 Discovery** using modern C++. 

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
The `-p` argument followed by the app's name should pass to the script.

