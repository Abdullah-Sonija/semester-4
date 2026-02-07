#!/bin/bash

if [ "$#" ne -2 ]; then
  echo "Usage: $0 file1 file2."
  exit 1
fi

FILE1=$1
FILE2=$2

if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then
  echo "Error: One or both files do not exist."
  exit 1
fi

if cmp -s "$FILE1" "$FILE2"; then
  echo "The files are identical."
else
  echo "The files are different."
fi
