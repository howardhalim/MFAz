#!/bin/bash
# Compile source files
g++ -I. bloom.c bloom_func.cpp api.cpp function.cpp gateway_rpi.cpp miracl.a rpi.cpp -o rpi -lcurl

