##!/bin/sh

# install it with pip
pip install pre-commit

# generate a sample config (you'll want to modify it)
pre-commit sample-config > .pre-commit-config.yaml

# activate pre-commit in a repository
pre-commit install
