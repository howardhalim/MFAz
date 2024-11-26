#!/bin/bash
# Compile source files
g++ -I. bloom.c bloom_func.cpp api.cpp function.cpp gateway.cpp miracl.a user.cpp -o user -lcurl

