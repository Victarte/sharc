---
title: FAQ
linkTitle: FAQ
menu:
  main:
    weight: 40
---

# Frequently Asked Questions

## General

### What is ShArc?

ShArc is a geoscience simulation application for porous media two-phase flow, built on the Arcane framework. It simulates water/gas flow in geological porous media and includes FEM capabilities for geomechanics.

### Who develops ShArc?

ShArc is developed by **CEA** (Commissariat à l'énergie atomique) and **IFPEN** (IFP Energies nouvelles).

### What is the license?

Apache License, Version 2.0.

## Installation

### What are the system requirements?

Linux (Ubuntu 22.04 or 24.04 recommended), MPI, C++20 compiler, and the Arcane framework dependencies.

### Do I need a GPU?

No, ShArc runs on CPU. GPU support (CUDA/SYCL) is optional for accelerated solvers.

### How do I install linear solver backends?

Install the corresponding packages:
- Hypre: `apt install libhypre-dev`
- PETSc: `apt install libpetsc-real-dev`
- Trilinos: `apt install libtrilinos-*`

## Usage

### How do I run a simulation?

```bash
mpirun -np N ./build/src/Main/ShArc.exe case.arc
```

### What mesh formats are supported?

VT2 (VTK), MSH (Gmsh v4.1), IXM, and MHB formats.

### How do I visualize results?

Use **ParaView** to open VTKHDF output files in `output/depouillement/vtkhdfv2/`.

## Development

### How do I add a new module?

1. Create a `ModuleName.axl` descriptor
2. Implement the module class
3. Register in `config.xml`
4. Add to `ShArc.config` time loop
5. Register tests in `test/CMakeLists.txt`

### How do I run tests?

```bash
ctest --test-dir build --timeout 300 --output-on-failure
```
