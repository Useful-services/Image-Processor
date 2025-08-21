#!/bin/bash

echo "Building Backend Image Processor..."

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

echo "Configuring with CMake..."
cmake ..

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

echo "Building project..."
make

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build completed successfully!"
echo "Executable: build/MAIN"

cd .. 