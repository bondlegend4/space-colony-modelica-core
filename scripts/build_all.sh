#!/bin/bash
# Build all Modelica components

set -e

echo "Building all Modelica components..."
echo

# Find all .mo files in models directory
for model_file in models/*.mo; do
    # Extract component name (filename without extension)
    component_name=$(basename "$model_file" .mo)
    
    echo "========================================"
    echo "Building: $component_name"
    echo "========================================"
    
    # Build the component
    ./scripts/build_component.sh "$component_name"
    
    echo
done

echo "========================================"
echo "All components built successfully!"
echo "========================================"