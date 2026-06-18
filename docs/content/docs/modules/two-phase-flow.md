---
title: Two-Phase Flow Simulation
linkTitle: Two-Phase Flow Simulation
---

The core physics module for simulating water/gas flow in porous media, defined in `src/TwoPhaseFlowSimulation/`.

## Governing equations

### Mass conservation

For each phase $\alpha$ (water and gas), the mass conservation equation is:

$$
\frac{\partial}{\partial t} (\phi \rho_\alpha S_\alpha) + \nabla \cdot (\rho_\alpha \mathbf{v}_\alpha) = q_\alpha
$$

where:
- $\phi$ is the porosity
- $\rho_\alpha$ is the phase density
- $S_\alpha$ is the phase saturation
- $\mathbf{v}_\alpha$ is the Darcy velocity
- $q_\alpha$ is the source/sink term

### Darcy's law

The phase velocity follows Darcy's law:

$$
\mathbf{v}_\alpha = -\frac{k_{r\alpha}}{\mu_\alpha} \mathbf{K} (\nabla p_\alpha - \rho_\alpha \mathbf{g})
$$

where:
- $\mathbf{K}$ is the permeability tensor
- $k_{r\alpha}$ is the relative permeability
- $\mu_\alpha$ is the phase viscosity
- $p_\alpha$ is the phase pressure
- $\mathbf{g}$ is the gravity vector

### Capillary pressure

$$ p_c(S_w) = p_n - p_w $$

### Saturation constraint

$$ S_w + S_n = 1 $$

## Features

- IMPES (Implicit Pressure Explicit Saturation) and fully implicit Newton-Krylov solvers
- Capillary pressure and relative permeability models
- Well models (production/injection)
- Parallel MPI execution with Hypre, PETSc, or Trilinos backends

## Sub-modules

- `BoundaryCondition/` — Boundary condition handling
- `InitialCondition/` — Initial condition setup
- `PhysicalLaws/` — Constitutive models (relative permeability, capillary pressure)
- `WellCondition/` — Well models

## Physical Laws

The `PhysicalLaws/` subdirectory provides a plugin system for relative permeability and capillary pressure models. Custom models can be added by implementing the corresponding service interface.

## ThermoChemicalConvection

A variant of the two-phase flow module that adds thermal and chemical convection effects, useful for simulation of convective mixing in geological storage.
