#!/bin/bash
# Clean all generated files

echo "Cleaning generated files..."

# Remove build directory contents
rm -rf build/*

# Recreate structure
mkdir -p build

echo "✓ Clean complete!"