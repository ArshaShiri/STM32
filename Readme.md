# Project Goal
This project aims to build a nubmer of drivers for **STM32F407 Discovery** using modern C++. 

## Table of Contents
* [Description](#description)
* [Requirements](#requirements)
* [Apps](#apps)
* [Build](#build)

## Description

## Requirements
* CMake
* clang-format
* pre-commit
* cmake-format
* ST-link

## Apps

## Build

To build the project run build.sh under `STM32F407Discovery`  
The following arguments can be passed to this script:  
* `-t` Build for the target. Build all the apps that are described in the [Apps](#apps) section.  
* `-h` Build for the host. This is used for running the unit tests.  
* `-a` Build for both the target and the host.  
* `-r` Rebuild.  
* `-d` Build in debug mode. By default, the build is in release mode.  

