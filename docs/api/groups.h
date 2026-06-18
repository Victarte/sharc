// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2025 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/**
 * \defgroup ShArc ShArc
 * \brief Main coupling module for ShArc simulation
 *
 * The \b ShArc module orchestrates the coupling between all simulation
 * components. It manages the simulation lifecycle (build, init, time-step loop,
 * finalize), delegates to specialized sub-modules, and handles post-processing
 * and result validation.
 *
 * Interaction pattern:
 * - \ref ShArcModule::build() loads and configures sub-modules
 * - \ref ShArcModule::init() initializes mesh, geometry, and sub-modules
 * - The time-step loop calls each sub-module's compute methods
 * - \ref ShArcModule::endSimulation() finalizes and exports results
 *
 * Main class: \ref ShArcModule
 * Source: src/ShArc/
 */

/**
 * \defgroup TwoPhaseFlow Two-Phase Flow
 * \brief Two-phase flow simulation in porous media
 *
 * Simulation of two-phase (water/oil or water/gas) flow in porous media,
 * including capillary pressure, relative permeability, fluid density,
 * well models, and boundary conditions.
 *
 * Sub-module architecture:
 * - \b BoundaryCondition: manages Dirichlet and flux boundary conditions
 *   via \ref IBoundaryManager and \ref FolderEnumerator
 * - \b DataModel: system description using GUMP-generated models
 * - \b InitialCondition: sets up initial states via \ref IInitialCondition
 * - \b PhysicalLaws: constitutive models (\ref CapillaryPressureLaw,
 *   \ref RelativePermeabilityPowerLaw, \ref FluidDensityLaw, \ref ConstantLaw)
 * - \b PhysicalSystem: system assembly (\ref IPhysicalSystem,
 *   \ref IVariableManager, \ref ISystemBuilder)
 * - \b WellCondition: Peaceman well indexing (\ref WellIndexComputer,
 *   \ref IWellManager, \ref WellEnumerator)
 *
 * Main class: TwoPhaseFlowSimulationModule
 * Source: src/TwoPhaseFlowSimulation/
 */

/**
 * \defgroup CAWF CAWF
 * \brief Compaction, Elasticity, and FEM mechanics
 *
 * Finite Element Method modules for solid mechanics and scalar PDEs.
 * Supports 2D and 3D meshes with multiple element types (Tria3, Tetra4,
 * Quad4, Hexa8) and GPU acceleration via SYCL.
 *
 * Sub-modules:
 * - \b Elasticity: linear elastic deformation \f$\nabla\cdot\sigma = f\f$
 *   with Dirichlet, traction, and body-force BCs (\ref FemModuleElasticity)
 * - \b Poisson: scalar diffusion \f$-\nabla\cdot(k\nabla u) = f\f$
 *   (\ref FemModulePoisson)
 * - \b FEMUtils: shared linear algebra and assembly utilities
 *   (DoF systems, BSR/CSR matrices, Gauss quadrature, GPU helpers)
 * - \b DynamicMeshMng: dynamic mesh modifications for sedimentation
 *   (\ref ShArc::IDynamicMeshMng)
 * - \b Compaction: sedimentation and compaction with gravitational overburden
 *   (\ref CompactionModule)
 *
 * Main classes: \ref FemModuleElasticity, \ref FemModulePoisson, \ref CompactionModule
 * Source: src/CAWF/
 */

/**
 * \defgroup ExaDiBench ExaDiBench
 * \brief Benchmark simulation cases
 *
 * Benchmark cases for evaluating simulation performance and correctness.
 * Provides geometry computations (volume, surface area, centroid) on
 * various mesh types, plus mesh refinement benchmarks.
 *
 * Main class: \ref ExaDiBenchModule
 * Source: src/ExaDiBench/
 */
#ifndef SHARC_GROUPS_H
#define SHARC_GROUPS_H
#endif
