#!/bin/bash

# Assign arguments to variables
USERID="10001"
OP="read,write"
RESC="file1,file2"
HISTORY="granted_access_1720115341"
CHOICE="1"

# Run the program with the arguments
./user_timer "$USERID" "$OP" "$RESC" "$HISTORY" "$CHOICE"
