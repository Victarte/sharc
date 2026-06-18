---
title: CAWF (FEM)
linkTitle: CAWF (FEM)
---

# CAWF — Compaction/Elasticity/FEM

CAWF is a finite element library for geomechanical simulation, defined in `src/CAWF/`.

## Components

```mermaid
graph TD
  FEMU["FEMUtils"] --> ELAS["Elasticity"]
  FEMU --> POIS["Poisson"]
  FEMU --> COMP["Compaction"]
  ELAS --> LS["Linear System"]
  POIS --> LS
  COMP --> LS
  LS --> ALIEN["Alien"]
  LS --> HYPRE["Hypre"]
  LS --> PETSC["PETSc"]
  LS --> SYCL["SYCL GPU"]
```

| Sub-module | Description |
|------------|-------------|
| [FEMUtils]({{< relref "fem-utils" >}}) | Core FEM library (DOF management, matrices, quadrature) |
| [Elasticity]({{< relref "elasticity" >}}) | Linear elasticity solver based on Navier's equation |
| [Poisson]({{< relref "poisson" >}}) | Poisson equation FEM solver |
| [Compaction]({{< relref "compaction" >}}) | Geomechanical compaction solver |
| [DynamicMeshMng]({{< relref "dynamic-mesh" >}}) | Dynamic mesh adaptation service |

## Backends

Linear solvers can use Alien (default), Hypre, PETSc, or SYCL GPU backends depending on configuration.
