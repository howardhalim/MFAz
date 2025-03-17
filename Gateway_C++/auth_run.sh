#!/bin/bash

# Assign arguments to variables
USERID="10001"
OP="read,write"
RESC="file1,file2"

# Run the program with the arguments
./auth_user "$USERID" "$OP" "$RESC"
