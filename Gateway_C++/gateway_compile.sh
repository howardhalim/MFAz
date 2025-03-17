#!/bin/bash
# Compile source files
g++ -I. bloom.c bloom_func.cpp api.cpp function.cpp miracl.a gateway.cpp -o gateway -lcurl

