---
title: ShArc Module
linkTitle: ShArc Module
---

The main orchestration module, defined in `src/ShArc/`.

## Responsibilities

- Initializes the simulation environment (geometry, time manager, expression manager)
- Manages service containers (physics, post-processing, validation)
- Handles time stepping loop
- Controls output period for post-processing
- Validates results at end of simulation via `IServiceValidator`

## Key files

| File | Role |
|------|------|
| `ShArc.axl` | Module descriptor |
| `ShArcModule.h` | Header |
| `ShArcModule.cc` | Implementation (372 lines) |
| `config.xml` | Source registration |

## Entry points

| Method | Phase | Description |
|--------|-------|-------------|
| `build()` | Build | Initialize services |
| `prepareInit()` | Init | Prepare data structures |
| `init()` | Init | Initialize simulation |
| `endInit()` | Init | Finalize initialization |
| `beginTimeStep()` | Compute-loop | Start of time step |
| `endTimeStep()` | Compute-loop | End of time step |
| `endSimulation()` | Exit | Validate and finalize |
