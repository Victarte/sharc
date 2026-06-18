---
title: FEM Utilities
linkTitle: FEM Utilities
---

Core FEM library in `src/CAWF/FEMUtils/` (48 files). Provides foundational components for all CAWF solvers.

## Components

| Component | Description |
|-----------|-------------|
| `DoFLinearSystem` | Degrees of freedom management |
| `CsrFormatMatrix` | CSR sparse matrix format |
| `BSRFormat` | Block sparse row format |
| `AlienBSRFormat` | Alien-backed BSR format (CPU + SYCL) |
| `FemDoFsOnNodes` | Node-based DoF numbering |
| `FemBoundaryConditions` | Dirichlet/Neumann BC handling |
| `GaussQuadrature` | Gauss integration points and weights |
| `ArcaneFemFunctions` | Utility functions for FE computations |

## Linear system factories

| Factory | Backend |
|---------|---------|
| `FemLinearSystemFactory_Aleph` | Aleph solver |
| `FemLinearSystemFactory_Alien` | Alien solver |
| `FemLinearSystemFactory_Hypre` | Hypre (requires hypre) |
| `FemLinearSystemFactory_PETSc` | PETSc (requires PETSc) |
| `FemLinearSystemFactory_SequentialBasic` | Sequential direct solver |

## SYCL support

GPU-accelerated variants with SYCL backends are available for supported linear algebra operations.
