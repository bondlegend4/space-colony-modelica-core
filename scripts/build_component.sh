#!/bin/bash
# Build a single Modelica component

set -e  # Exit on error

# OpenModelica compiler path (update this to match your installation)
# OMC="/Applications/OpenModelica/build_cmake/install_cmake/bin/omc"

# Check if omc exists
if [ ! -f "$OMC" ]; then
    echo "Error: OpenModelica compiler not found at: $OMC"
    echo "Please update the OMC variable in this script to point to your omc installation"
    echo ""
    echo "To find omc, try:"
    echo "  which omc"
    echo "  find /Applications -name omc -type f 2>/dev/null"
    exit 1
fi

COMPONENT_NAME=$1

if [ -z "$COMPONENT_NAME" ]; then
    echo "Usage: $0 <ComponentName>"
    echo "Example: $0 SimpleThermalMVP"
    exit 1
fi

MODEL_FILE="models/${COMPONENT_NAME}.mo"
BUILD_DIR="build/${COMPONENT_NAME}"

# Check if model exists
if [ ! -f "$MODEL_FILE" ]; then
    echo "Error: Model file not found: $MODEL_FILE"
    exit 1
fi

echo "Building component: $COMPONENT_NAME"
echo "Model file: $MODEL_FILE"
echo "Output directory: $BUILD_DIR"
echo "Using OMC: $OMC"

# Create build directory
mkdir -p "$BUILD_DIR"

# Change to build directory
cd "$BUILD_DIR"

# Copy model file temporarily
cp "../../$MODEL_FILE" .

# Generate C code using OpenModelica
echo "Generating C code..."
"$OMC" -s "${COMPONENT_NAME}.mo"

# Check if generation was successful
if [ ! -f "${COMPONENT_NAME}.c" ]; then
    echo "Error: C code generation failed!"
    exit 1
fi

# Remove the temporary model file
rm "${COMPONENT_NAME}.mo"

# Count generated files
C_FILES=$(ls -1 ${COMPONENT_NAME}*.c 2>/dev/null | wc -l)
H_FILES=$(ls -1 ${COMPONENT_NAME}*.h 2>/dev/null | wc -l)

echo "✓ Build successful!"
echo "  Generated $C_FILES C files"
echo "  Generated $H_FILES header files"
echo "  Output: $BUILD_DIR"