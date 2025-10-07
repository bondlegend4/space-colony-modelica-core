# space-colony-modelica-core
### Overview

Source of truth for all Modelica simulation components. Contains physics-based models compiled to C code for integration with Rust.

### Directory Structure

```
space-colony-modelica-core/
├── models/                 # Source Modelica (.mo) files
│   ├── SimpleThermalMVP.mo
│   ├── SolarPanel.mo      # Future
│   └── OxygenGenerator.mo # Future
├── build/                  # Generated C code (gitignored)
│   ├── SimpleThermalMVP/
│   │   ├── SimpleThermalMVP.c
│   │   ├── SimpleThermalMVP_model.h
│   │   ├── SimpleThermalMVP_functions.h
│   │   └── ... (21 generated files)
│   └── SolarPanel/        # Future
├── scripts/
│   ├── build_component.sh
│   ├── build_all.sh
│   └── clean.sh
├── .gitignore
└── README.md
```

### Available Components

#### SimpleThermalMVP

**Purpose**: Minimal viable thermal system for POC validation

**Inputs**:

- `heaterOn` (Boolean): Heater control signal

**Outputs**:

- `temperature` (Real, K): Current room temperature
- `heaterStatus` (Real): Heater status (0=off, 1=on)

**Parameters**:

- `roomCapacity = 1000.0` (J/K): Heat capacity
- `ambientTemp = 250.0` (K): Ambient temperature
- `heaterPower = 500.0` (W): Heater power when on
- `lossCoefficient = 2.0` (W/K): Heat loss coefficient

**Equations**:

```
roomCapacity * d(roomTemp)/dt = heating - losses
heating = heaterOn ? heaterPower : 0
losses = lossCoefficient * (roomTemp - ambientTemp)
```

### Building Components

#### Build a Single Component

```bash
./scripts/build_component.sh SimpleThermalMVP
```

**What it does**:

1. Copies the `.mo` file to `build/SimpleThermalMVP/`
2. Runs OpenModelica compiler (`omc -s`)
3. Generates ~21 C files and headers
4. Cleans up temporary files

**Output**:

- `SimpleThermalMVP.c` - Main simulation code
- `SimpleThermalMVP_model.h` - Data structures
- `SimpleThermalMVP_functions.h` - Function declarations
- `SimpleThermalMVP_*.c` - Subsystem implementations

#### Build All Components

```bash
./scripts/build_all.sh
```

Iterates through all `.mo` files in `models/` and builds each one.

#### Clean Generated Files

```bash
./scripts/clean.sh
```

Removes all files from `build/` directory.

### Adding a New Component

1. **Create the Modelica model**:

```bash
cat > models/SolarPanel.mo << 'EOF'
model SolarPanel
  "Solar power generation component"
  
  // Inputs
  input Real solarIrradiance "W/m²";
  input Boolean isDayTime;
  
  // Outputs
  output Real powerOutput "W";
  
  // Parameters
  parameter Real efficiency = 0.20;
  parameter Real area = 10.0 "m²";
  
equation
  powerOutput = if isDayTime then 
    solarIrradiance * area * efficiency 
  else 
    0.0;
end SolarPanel;
EOF
```

2. **Build it**:

```bash
./scripts/build_component.sh SolarPanel
```

3. **Commit only the source**:

```bash
git add models/SolarPanel.mo
git commit -m "Add SolarPanel component"
```

4. **Update FFI** (see modelica-rust-ffi documentation)

### Requirements

- OpenModelica v1.26.0 or later
- Standard Modelica library
- OpenIPSL library (for power systems)
- Bash shell (for build scripts)

### Integration

This repository is used as a **Git submodule** by `modelica-rust-ffi`. When you build components here, the Rust FFI layer automatically picks them up.

**Workflow**:

```bash
# Build component
cd space-colony-modelica-core
./scripts/build_component.sh SimpleThermalMVP

# FFI detects changes automatically
cd ../modelica-rust-ffi
cargo build
```

### Troubleshooting

**Problem**: `omc: command not found`

**Solution**: Update `scripts/build_component.sh` with your OpenModelica path:

```bash
OMC="/Applications/OpenModelica/build_cmake/install_cmake/bin/omc"
```

**Problem**: Build fails with missing libraries

**Solution**: Install required libraries via OpenModelica Package Manager:

```bash
omc
>> installPackage(Modelica);
>> installPackage(OpenIPSL);
```