---
title: Tests
linkTitle: Tests
menu:
  main:
    weight: 50
---

ShArc uses a custom test system based on Arcane macros.

## Test runners

| Macro | Description |
|-------|-------------|
| `ARCANE_ADD_TEST_SEQUENTIAL(name config case_dir case_file)` | Sequential test |
| `ARCANE_ADD_TEST_PARALLEL(name config case_dir case_file nproc)` | Parallel test (MPI) |
| `ARCANE_ADD_TEST_SEQUENTIAL_LONGTIME(name config case_dir case_file timeout)` | Long-running test |

## Running tests

```bash
cmake --build build
ctest --test-dir build --timeout 300 --output-on-failure
ctest --test-dir build -R TwoPhaseFlowSimulation
```

## Validation

Tests validate against reference values in `.arc` files using `SyntheticServiceValidator`:
- Mean arithmetic comparison
- RelativeError tolerance
- AbsoluteError tolerance

## Two-Phase Flow Tests

Located in `test/TwoPhaseFlowSimulation/`.

| Test | Mesh | Solver |
|------|------|--------|
| `use-case-two-phase-flow` | 10x1x1 | PETSc SuperLU |
| `use-case-two-phase-flow-with-capillary-pressure` | 10x1x1 | BCGS |
| `use-case-two-phase-flow-debug-newton-matrix` | 10x1x1 | Debug |
| `use-case-two-phase-flow-ref` | 10x1x1 | Reference |

## CAWF Tests

### Elasticity (12 tests)
Linear elasticity verification problems with various boundary conditions and mesh types.

### Poisson (8 tests)
Poisson equation convergence tests on 2D and 3D meshes.

### Compaction (5 tests)
Compaction simulations with multi-layer configurations.

## ExaDiBench

Located in `test/ExaDiBench/`. Tests include cube3d, spe11c, pb, and ring mesh benchmarks.

## Large Scale Tests

Long-time tests with refined meshes and extended simulation times are available but not run by default.
