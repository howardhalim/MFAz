#!/bin/bash

# Assign arguments to variables
USERID="10001"
OP="read,write"
RESC="file1,file2"
HISTORY="granted_access_1720115237"

# Run the program with the arguments
./user "$USERID" "$OP" "$RESC" "$HISTORY"
