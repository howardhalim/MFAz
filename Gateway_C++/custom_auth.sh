#!/bin/bash
# Compile source files
g++ -I. -Wall -D_FILE_OFFSET_BITS=64 bloom.c bloom_func.cpp api.cpp function.cpp gateway_auto.cpp miracl.a custom_auth.cpp -o custom_auth -lcurl `pkg-config fuse --cflags --libs`

