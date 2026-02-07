#!/bin/bash

if [ -z "$1" ]; then
	echo "Error: No directory specified."
	echo "Usage: $0 <directory_path>"
	exit 1
fi

target_dir="$1"

if [ ! -d "$target_dir" ]; then
	echo "Error: '$target_dir' is not a valid directory"
	exit 1
fi

dir_name=$(basename "$target_dir")

archive_name="${dir_name}_archive.tar.gz"

tar -czvf "$archive_name" "$target_dir"

if [ $? -eq 0 ];then
	echo "Success! Archive created. $archive_name"
else
	echo "Error: Failed to create archive."
	exit 1
fi

