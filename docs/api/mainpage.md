# ShArc

ShArc is a geoscience simulation application for **two-phase flow in porous media**, built on the [Arcane framework](https://github.com/arcaneframework). It couples flow, transport, and solid mechanics (compaction, elasticity) within a single time-loop via the CAWF mechanics modules, and provides benchmark cases through ExaDiBench.

---

## Architecture

```
┌──────────────────────────────────────────────────────────────┐
│                       ShArcModule                           │
│        ┌────────────┬──────────────┬──────────────┐         │
│        │            │              │              │         │
│        ▼            ▼              ▼              ▼         │
│  TwoPhaseFlow  CAWF/Elasticity  CAWF/Compaction  ExaDiBench│
│   (flow +      (FEM linear      (sedimentation,  (benchmark │
│    transport)    elasticity)      compaction)      cases)   │
└──────────────────────────────────────────────────────────────┘
```

### Modules

| Module | Description | Key Classes |
|--------|-------------|-------------|
| @ref ShArc | Main orchestrator coupling all sub-modules | @ref ShArcModule |
| @ref TwoPhaseFlow | Two-phase flow in porous media with capillary pressure, well models, and physical laws | @ref IBoundaryManager, @ref IInitialCondition, @ref IWellManager |
| @ref CAWF | FEM mechanics: elasticity, Poisson, compaction, dynamic meshes | @ref FemModuleElasticity, @ref FemModulePoisson, @ref CompactionModule |
| @ref ExaDiBench | Benchmark cases for geometry and mesh operations | @ref ExaDiBenchModule |

---

## Quick Start

### Prerequisites

- Arcane framework installed (see [Arcane installation guide](https://arcaneframework.github.io/arcane/devdoc/html/d7/d94/arcanedoc_build_install.html))
- MPI (mpicc/mpic++)
- CMake >= 3.20

### Build

```bash
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  -DARCANEFRAMEWORK_ROOT=/path/to/arcane/install \
  -DCMAKE_C_COMPILER=mpicc \
  -DCMAKE_CXX_COMPILER=mpic++
cmake --build build -j$(nproc)
```

### Run Tests

```bash
ctest --test-dir build --timeout 300 --output-on-failure
```

---

## Key Features

- **Two-phase flow**: water/oil or water/gas flow with capillary pressure (Brooks-Corey) and relative permeability (Corey law)
- **Well modeling**: Peaceman well indices for production/injection wells
- **FEM Linear Elasticity**: 2D/3D, Tria3/Tetra4/Quad4/Hexa8 elements, CPU and SYCL GPU backends
- **FEM Poisson**: scalar elliptic PDE solver for steady-state diffusion
- **Compaction modeling**: sedimentary layer deposition with gravity-driven compaction
- **Dynamic meshes**: mesh modification for sedimentation events
- **Benchmark cases**: geometry operations (volume, surface, center) and mesh refinement

---

## License

Apache 2.0 — CEA/IFPEN and Contributors.
