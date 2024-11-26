#!/bin/bash
# Compile source files
g++ -I. bloom.c bloom_func.cpp api.cpp function.cpp gateway.cpp miracl.a user_timer.cpp -o user_timer -lcurl

