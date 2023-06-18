#!/bin/bash

# Get a list of all files with _bonus 
files=$(ls *_bonus*)

# Iterate over the list of files
for file in $files; do
  echo $file
  new_file_name=${file%"_bonus.c"}".c"
  echo $new_file_name
  mv "$file" "$new_file_name"
done
