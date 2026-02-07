#!/bin/bash

if [ -z "$1" ]; then
	echo "Error: No number provided."
	exit 1
fi
number=$1
square=$((number*number))
echo "The square of the $number is $square."

