---
title: Poisson
linkTitle: Poisson
---

Poisson equation FEM solver, defined in `src/CAWF/Poisson/`.

## Governing equation

The Poisson equation in 2D:

$$
\frac{\partial}{\partial x}\left(\frac{\partial u}{\partial x}\right) + \frac{\partial}{\partial y}\left(\frac{\partial u}{\partial y}\right) = f \quad \forall (x,y) \in \Omega
$$

or in compact form:

$$
\nabla^2 u = f \quad \forall (x,y) \in \Omega
$$

## Variational formulation

The FEM weak form reads: find $u^h \in H^1_0(\Omega)$ such that:

$$
-\int_{\Omega} \nabla u^h \cdot \nabla v^h \, d\Omega + \int_{\partial\Omega_N} (\bar{q} \cdot \mathbf{n}) v^h \, d\Gamma + \int_{\Omega} f v^h \, d\Omega = 0 \quad \forall v^h \in H^1_0(\Omega)
$$

## Boundary conditions

- **Dirichlet**: $u = u_D \quad \forall (x,y) \in \partial\Omega_D$
- **Neumann**: $\nabla u \cdot \mathbf{n} = q_N \quad \forall (x,y) \in \partial\Omega_N$

## Key files

| File | Role |
|------|------|
| `FemPoisson.axl` | Module descriptor |
| `FemPoissonModule.cc` | Implementation |
| `FemPoissonModule.h` | Header |

## Options

| Option | Description |
|--------|-------------|
| `source-term` | Right-hand side $f$ |
| `dirichlet-boundary` | Dirichlet BC value $u_D$ |
| `neumann-boundary` | Neumann BC flux $q_N$ |
| `linear-solver` | Solver backend configuration |
