#!/bin/bash

if [ "$#" -ne 4 ]; then
  echo "Usage: $0 num1 num2 num3 num4"
  exit 1
fi

a=$1
b=$2
c=$3
d=$4

result=$((a * b * c * d))

echo "the product of $a, $b, $c, and $d is $result."
