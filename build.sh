#!/bin/bash

BUILD_DIR="build"
EXECUTABLE="tetris"
SRC_DIR="src"
CMAKE_OPTIONS="-DSDLTTF_VENDORED=ON -DSDLMIXER_VENDORED=ON"
OUT=""
verbose=false

while getopts "v" opt; do
  case $opt in 
    v)
      verbose=true
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
  esac
done

shift $((OPTIND -1))

if ! $verbose; then
  OUT=" > /dev/null 2>&1"
fi

if cmake -S . -B "$BUILD_DIR" $CMAKE_OPTIONS; then
  echo "-- CMake configuration successful"
else 
  echo "-- CMake configuration failed"
  exit 1
fi

if make -s -C "$BUILD_DIR"; then
  echo "-- Build successful"
else 
  echo "-- Build failed"
  exit 1
fi

if mv "$BUILD_DIR/$SRC_DIR/$EXECUTABLE" .; then
  echo "-- $EXECUTABLE moved to the current directory"
else 
  echo "-- Failed to move $EXECUTABLE"
  exit 1
fi
