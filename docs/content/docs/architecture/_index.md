---
title: Architecture
linkTitle: Architecture
menu:
  main:
    weight: 30
---

ShArc is organized as a set of modules orchestrated by the Arcane framework.

## Module Architecture

```mermaid
graph TD
  subgraph "ShArc Modules"
    SHARC["src/ShArc/ Orchestrator"]
    SHARC --> TPF["src/TwoPhaseFlowSimulation/ Physics"]
    SHARC --> EXA["src/ExaDiBench/ Benchmarks"]
    SHARC --> CAWF["src/CAWF/ FEM"]
    TPF --> BC["BoundaryCondition"]
    TPF --> IC["InitialCondition"]
    TPF --> LAWS["PhysicalLaws"]
    TPF --> WELL["WellCondition"]
    CAWF --> FEMU["FEMUtils"]
    CAWF --> ELAS["Elasticity"]
    CAWF --> POIS["Poisson"]
    CAWF --> COMP["Compaction"]
  end
  subgraph "Arcane Framework"
    ARC["Arcane Core"] --> ALIEN["Alien Linear Algebra"]
    ARC --> AXL["Axlstar/AXL"]
  end
  SHARC --> ARC
```

## Build system

ShArc uses a custom CMake build system with macros like `createLibrary`, `createExecutable`, `generateCMakeLists`, `linkLibraries`, `commit`, `loadMeta`, and `loadPackage`. Source file registration is handled via `config.xml` and `libraries.xml` in each module, plus `generateCMakeLists()` in CMake.

## Data models

Data models are defined via GUMP (`.gump`) files, e.g. `TwoPhaseFlowSimulation/DataModel/ArcRes.gump`, which generate C++ code for variable definitions and service interfaces.
