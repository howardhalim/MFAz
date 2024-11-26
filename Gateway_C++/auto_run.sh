#!/bin/bash

# Assign arguments to variables
OP="read,write"
RESC="file1,file2"
HISTORY="granted_access_1720712851"
CHOICE="3"


# Run the program with the arguments
./user_auto "$OP" "$RESC" "$HISTORY" "$CHOICE"
