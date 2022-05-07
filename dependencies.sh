#!/bin/sh
sudo apt-get update

echo "Installing ARM Cross Toolchain"
sudo apt-get remove binutils-arm-none-eabi gcc-arm-none-eabi
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo apt-get install gcc-arm-none-eabi
sudo apt-get install gdb-arm-none-eabi

echo "Installing pre-commit"
pip install pre-commit

# generate a sample config
pre-commit sample-config > .pre-commit-config.yaml

# activate pre-commit in a repository
pre-commit install
