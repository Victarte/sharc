# Modules

ShArc is organized into the following four thematic modules.

---

## ShArc

The **ShArc** module is the main orchestrator. It coordinates initialization,
time-stepping, and finalization by delegating to all sub-modules.

**Role**: Coupling framework
**Source**: `src/ShArc/`
**Main class**: `ShArcModule`

---

## Two-Phase Flow

The **TwoPhaseFlow** module simulates two-phase flow in porous media (water/oil
or water/gas), including capillary pressure, relative permeability, and well
models.

**Sub-modules**:

| Sub-module | Interface | Description |
|-----------|-----------|-------------|
| BoundaryCondition | `IBoundaryManager` | Dirichlet and boundary value management |
| InitialCondition | `IInitialCondition` | Constant or expression-based initial states |
| PhysicalLaws | various | Capillary pressure, relative permeability (power law), fluid density |
| PhysicalSystem | `IPhysicalSystem`, `IVariableManager`, `ISystemBuilder` | System assembly and variable management |
| WellCondition | `IWellManager`, `WellIndexComputer` | Peaceman well index and well flow management |

**Source**: `src/TwoPhaseFlowSimulation/`

---

## CAWF

The **CAWF** module provides Finite Element Method (FEM) mechanics for
compaction, elasticity, and scalar PDEs.

**Sub-modules**:

| Sub-module | Description |
|-----------|-------------|
| **Elasticity** | Linear elastic deformation (Tria3, Tetra4, Quad4, Hexa8 elements), SYCL GPU backend |
| **Poisson** | Scalar elliptic PDE (steady-state diffusion, multi-element types) |
| **FEMUtils** | Shared utilities: DoF systems, BSR/CSR matrix formats, Gauss quadrature, GPU helpers |
| **DynamicMeshMng** | Dynamic mesh management for sedimentation/compaction |
| **Compaction** | Compaction modeling with sedimentary layers and gravity |

**Source**: `src/CAWF/`

---

## ExaDiBench

The **ExaDiBench** module provides benchmark cases for geometry computations on
meshes (volume, surface, center calculations) and mesh refinement.

**Source**: `src/ExaDiBench/`
**Main class**: `ExaDiBenchModule`

---

[Back to top](#modules)
