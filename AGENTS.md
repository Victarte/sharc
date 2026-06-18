# ShArc - Agent Instructions

## What is this?

ShArc is a geoscience simulation application (porous media two-phase flow) built on the [Arcane framework](https://github.com/arcaneframework). It also includes CAWF (Compaction/Elasticity/FEM) capabilities and ExaDiBench benchmarks.

## Build system

Custom CMake build system via `common/ArcaneInfra/build-system/arcgeosim/`. Not vanilla CMake — uses macros like `createLibrary`, `createExecutable`, `generateCMakeLists`, `linkLibraries`, `commit`, `loadMeta`, `loadPackage`.

**Requires Arcane framework pre-installed.** The framework supplies Alien (linear algebra), Arccon, Arccore, Axlstar, and ArcGeoSim shared libraries. See `README.md` for full Ubuntu 22.04/24.04 install workflows.

To configure and build (after Arcane is installed):

```sh
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  -DARCANEFRAMEWORK_ROOT=/path/to/arcane/install \
  -DCMAKE_C_COMPILER=mpicc \
  -DCMAKE_CXX_COMPILER=mpic++
cmake --build build -j$(nproc)
```

Or use `./configure` (wrapper around `common/ArcaneInfra/bin/configure.new`).

## Project structure

- `src/ShArc/` — Main module (`ShArcModule.cc`/`.h`, `ShArc.axl`)
- `src/TwoPhaseFlowSimulation/` — Two-phase flow module
- `src/ExaDiBench/` — Benchmark module
- `src/CAWF/` — FEM/mechanics (Compaction, Elasticity, FEMUtils, Poisson)
- `src/Main/main.cc` — Entry point, links `ShArc.exe`
- `test/` — Tests per module (`.arc` case files, `ShArc.config`)
- `common/ArcaneInfra/` — Build infrastructure (git submodule)
- `common/ArcGeoSim/` — Shared geoscience framework (git submodule)

Source file registration is via `config.xml` + `libraries.xml` in each module, plus `generateCMakeLists()` in CMake.

## Key framework conventions

- **`.axl` files** — XML module descriptors (options, entry points, variables). Auto-generated historically via `createNew`.
- **`ShArc.config`** — XML time loop wiring (which modules, entry points for init/compute-loop/exit).
- **`.arc` files** — XML test case definitions (mesh, solvers, post-processing, validators).
- **GUMP models** (`.gump`) — Data model code generation (e.g., `TwoPhaseFlowSimulation/DataModel/ArcRes.gump`).
- **Code style**: tab-width 2, `-*- coding: utf-8-with-signature -*-`, SPDX-License-Identifier Apache-2.0.

## Tests

Custom Arcane CMake macros in `test/CMakeLists.txt`:

- `ARCANE_ADD_TEST_SEQUENTIAL(name config_file case_dir case_file)`
- `ARCANE_ADD_TEST_PARALLEL(name config_file case_dir case_file nproc)`
- `ARCANE_ADD_TEST_SEQUENTIAL_LONGTIME(name config_file case_dir case_file timeout)`

Run with:
```sh
ctest --test-dir build --timeout 300 --output-on-failure
```

Tests validate against reference values in `.arc` files using `SyntheticServiceValidator` (Mean + RelativeError + tolerance).

## CI

GitHub Actions in `.github/workflows/` (4 variants: IFPEN el8/el9 × foss/gimkl). 3-stage pipeline: Install Arcane → Install Sharc → Test Sharc.

Important env vars used in CI:
- `OMPI_ALLOW_RUN_AS_ROOT=1 OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1`
- `ARCANE_TEST_CLEANUP_AFTER_RUN=1`
- `CCACHE_COMPRESS=true CCACHE_MAXSIZE=5G`

## Quirks & gotchas

- Missing git submodule causes fatal error: `git submodule update --init` (for `common/ArcaneInfra/build-system`).
- Test timeouts: default 120s, long tests use 600s.
- Several tests gated on optional TARGETs: `hypre`, `trilinos`, `htssolver`, `ifpsolver`, `mcgsolver`, `mcgsolver::cuda`.
- SYCL support in CAWF (`Elasticity/FemModuleSYCL.cc`) — 4 backends: hipSYCL, IntelDPCPP, IntelSYCL, AdaptiveCpp.
- Some ExaDiBench tests are commented out (spe11c, pb, ring variants).
- Ref test output for TwoPhaseFlowSimulation: `RefUseCaseTwoPhaseFlow_DebugNewtonMatrix_1_1.txt` and `_Vector_1_1.txt`.
