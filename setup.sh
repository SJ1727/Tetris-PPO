#!/bin/bash

set -e 

echo "-- Initilizing Git submodules..."
cd $(dirname "$0")/
cat .gitmodules | \
while true; do
    read module || break
    read line; set -- $line
    path=$3
    read line; set -- $line
    url=$3
    
    echo $path
    if [ -d "$path" ]; then
      echo "$path already exists. Skipping clone."
    else
      echo "Cloning $module into $path..."
      git clone --filter=blob:none $url $path --recursive
    fi
done

# Setting up external libraries
echo "-- Downloading external libraries"
external_libraries=("SDL_ttf" "SDL_mixer" "SDL_image")

for lib in "${external_libraries[@]}"; do
  downloaded=false
  for folder in "vendor/$lib"/*/; do
    if [ "$(ls -A "$folder")" ]; then
      downloaded=true
      break 
    fi
  done

  if ! $downloaded; then 
    echo "Setting up vendor/$lib"
    vendor/$lib/external/download.sh
  else
    echo "vendor/$lib has already been setup"
  fi
done

# Create build directory
if [ ! -d "build" ]; then
  mkdir build
fi
