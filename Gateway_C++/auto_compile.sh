#!/bin/bash
# Compile source files
g++ -I. bloom.c bloom_func.cpp api.cpp function.cpp gateway_auto.cpp miracl.a user_auto.cpp -o user_auto -lcurl

