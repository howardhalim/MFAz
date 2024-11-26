#!/bin/bash
# Compile source files
g++ -I. bloom.c bloom_func.cpp api.cpp function.cpp gateway.cpp miracl.a auth_user.cpp -o auth_user -lcurl

