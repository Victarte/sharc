---
title: Elasticity
linkTitle: Elasticity
---

Linear elasticity solver based on Navier's equation, defined in `src/CAWF/Elasticity/`.

## Governing equation

Under small elastic deformation, the steady elastic deformation equation reads:

$$
-\nabla \cdot \sigma(\mathbf{x}) = \mathbf{f}(\mathbf{x}) \quad \mathbf{x}\in\Omega
$$

where $\sigma$ is the Cauchy stress tensor and $\mathbf{f}$ is the body force.

## Constitutive relation

For isotropic elastic materials, the stress tensor is:

$$
\sigma(\mathbf{x}) = \lambda (\nabla \cdot \mathbf{u}(\mathbf{x})) \mathbb{I} + \mu (\nabla\mathbf{u}(\mathbf{x}) + (\nabla\mathbf{u}(\mathbf{x}))^\text{T})
$$

where $\lambda$ and $\mu$ are Lamé parameters, and $\mathbf{u}$ is the displacement field.

Lamé parameters relate to Young's modulus $E$ and Poisson's ratio $\nu$:

$$
\lambda = \frac{E\nu}{(1+\nu)(1-2\nu)} \quad\quad \mu = \frac{E}{2(1+\nu)}
$$

## Strain tensor

$$
\varepsilon(\mathbf{u}) = \frac{1}{2}\left(\nabla\mathbf{u} + (\nabla\mathbf{u})^\text{T}\right)
$$

## Variational formulation

Find $\mathbf{u}^h \in V^h$ such that for all test functions $\mathbf{v}^h \in V^h$:

$$
\int_\Omega \sigma(\mathbf{u}^h) : \varepsilon(\mathbf{v}^h) \, d\Omega = \int_\Omega \mathbf{f} \cdot \mathbf{v}^h \, d\Omega + \int_{\partial\Omega_N} \mathbf{t} \cdot \mathbf{v}^h \, d\Gamma
$$

## Key files

| File | Role |
|------|------|
| `FemModule.axl` | Module descriptor |
| `FemModule.cc` | Implementation |
| `FemModule.h` | Header |
| `FemModuleSYCL.cc` | SYCL GPU backend (optional) |

## Options

| Option | Description |
|--------|-------------|
| `young-modulus` | Young's modulus $E$ |
| `poisson-ratio` | Poisson's ratio $\nu$ |
| `body-force` | Body force vector $\mathbf{f}$ |
| `boundary-conditions` | Dirichlet/Neumann BC specification |
| `linear-solver` | Linear solver backend |

## Supported solver backends

- Alien (default, CPU)
- Hypre (requires `TARGET_hypre`)
- PETSc (requires `TARGET_petsc`)
- SYCL GPU (requires SYCL backend: hipSYCL, IntelDPCPP, IntelSYCL, or AdaptiveCpp)
