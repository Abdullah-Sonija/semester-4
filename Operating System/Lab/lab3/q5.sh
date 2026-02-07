#!/bin/bash

if [ -z "$1" ]; then
    echo "Error: Incorrect Folder path."
    exit 1
fi

source_folder="$1"

if [ ! -d "$source_folder" ]; then
    echo "Error: Source folder does not exist."
    exit 1
fi

current_date=$(date +%Y-%m-%d)
backup_folder="project_backup_$current_date"
mkdir -p "$backup_folder"

cp -r "$source_folder/." "$backup_folder/"

file_count=$(find "$source_folder" -type f | wc -l)

echo "Backup Completed."
echo "Folder Created: $backup_folder"
echo "Files backed up: $file_count"
