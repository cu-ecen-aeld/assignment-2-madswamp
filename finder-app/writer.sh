#!/bin/bash

if [ $# -lt 2 ] 
then
    echo "Not enough arguments supplied, expected 2, found $#"
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

if ! mkdir -p "$(dirname "$1")"
then 
    echo "could not create directory"
    exit 1
fi

if ! echo "$2" > "$1"
then
    echo "could not create file"
    exit 1
fi

exit 0  