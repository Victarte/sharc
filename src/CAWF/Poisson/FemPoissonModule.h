// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2025 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*---------------------------------------------------------------------------*/
/* FemModule.h                                                 (C) 2022-2025 */
/*                                                                           */
/* FemModulePoisson class definition.                                               */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#ifndef FEMMODULES_H
#define FEMMODULES_H
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include <arcane/utils/CommandLineArguments.h>
#include <arcane/utils/PlatformUtils.h>
#include <arcane/utils/ParameterList.h>
#include <arcane/utils/ApplicationInfo.h>
#include <arcane/utils/ArcaneGlobal.h>
#include <arcane/utils/NumArray.h>

#include <arcane/ITimeLoopMng.h>
#include <arcane/IItemFamily.h>
#include <arcane/ItemGroup.h>
#include <arcane/ICaseMng.h>
#include <arcane/IMesh.h>

#include <arccore/base/NotImplementedException.h>

#include <arcane/accelerator/core/IAcceleratorMng.h>
#include <arcane/accelerator/VariableViews.h>

#include "CAWF/FEMUtils/IDoFLinearSystemFactory.h"
#include "CAWF/FEMUtils/ArcaneFemFunctionsGpu.h"
#include "CAWF/FEMUtils/ArcaneFemFunctions.h"
#include "CAWF/FEMUtils/DoFLinearSystem.h"
#include "CAWF/FEMUtils/FemDoFsOnNodes.h"
#include "CAWF/FEMUtils/IArcaneFemBC.h"
#include "CAWF/FEMUtils/BSRFormat.h"
#include "CAWF/FEMUtils/FemUtils.h"

#include "FemPoisson_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::FemUtils;
namespace ax = Arcane::Accelerator;

/*---------------------------------------------------------------------------*/
/**
 * \ingroup CAWF
 * \aigenerated
 * \brief Finite Element module for the Poisson (scalar elliptic) equation.
 *
 * Solves a steady-state diffusion problem using the Finite Element Method.
 * Supports multiple element types (Tria3, Tetra4, Quad4, Hexa8) with
 * CPU and GPU assembly backends.
 */
/*---------------------------------------------------------------------------*/

class FemModulePoisson
: public ArcaneFemPoissonObject
{
 public:

  /** \aigenerated Constructs the Poisson FEM module */
  explicit FemModulePoisson(const ModuleBuildInfo& mbi)
  : ArcaneFemPoissonObject(mbi)
  , m_dofs_on_nodes(mbi.subDomain()->traceMng())
  , m_bsr_format(mbi.subDomain()->traceMng(), *(mbi.subDomain()->acceleratorMng()->defaultQueue()), m_dofs_on_nodes)
  {
    ICaseMng* cm = mbi.subDomain()->caseMng();
    cm->setTreatWarningAsError(true);
    cm->setAllowUnkownRootElelement(false);
  }

  /** \aigenerated Method called at the beginning of the simulation */
  void startInit() override;
  /** \aigenerated Computes the solution at each iteration */
  void compute() override;
  /** \aigenerated Returns the module version */
  VersionInfo versionInfo() const override { return VersionInfo(1, 0, 0); }

  /** \aigenerated Assembles the bilinear operator (stiffness matrix) */
  void _assembleBilinearOperator();
  /** \aigenerated Assembles the linear operator on GPU */
  void _assembleLinearOperatorGpu();

 private:

  /** \aigenerated Block sparse row matrix format for assembly */
  BSRFormat m_bsr_format;
  /** \aigenerated Linear system (matrix + RHS + solution) */
  DoFLinearSystem m_linear_system;
  /** \aigenerated Degree-of-freedom item family */
  IItemFamily* m_dof_family = nullptr;
  /** \aigenerated DoF mapping on mesh nodes */
  FemDoFsOnNodes m_dofs_on_nodes;

  /** \aigenerated Source term value */
  Real f;

  /** \aigenerated PETSc solver flags */
  String m_petsc_flags;
  /** \aigenerated Matrix format type */
  String m_matrix_format = "DOK";

  /** \aigenerated Whether to assemble the linear system */
  bool m_assemble_linear_system = true;
  /** \aigenerated Whether to solve the linear system */
  bool m_solve_linear_system = true;
  /** \aigenerated Whether to perform cross-validation */
  bool m_cross_validation = false;
  /** \aigenerated Whether the mesh uses hex/quad elements */
  bool m_hex_quad_mesh = false;

  /** \aigenerated Performs a stationary (direct) solve */
  void _doStationarySolve();
  /** \aigenerated Retrieves material parameters from the case file */
  void _getMaterialParameters();
  /** \aigenerated Solves the assembled linear system */
  void _solve();
  /** \aigenerated Assembles the linear operator on CPU */
  void _assembleLinearOperatorCpu();
  /** \aigenerated Assembles the full linear operator (stiffness + BCs) */
  void _assembleLinearOperator();
  /** \aigenerated Updates time-dependent variables */
  void _updateVariables();
  /** \aigenerated Validates results against reference values */
  void _validateResults();

  /** AI comment: Computes the 3-node triangle element matrix */
  RealMatrix<3, 3> _computeElementMatrixTria3(Cell cell);
  /** AI comment: Computes the 4-node tetrahedron element matrix */
  RealMatrix<4, 4> _computeElementMatrixTetra4(Cell cell);
  /** AI comment: Computes the 4-node quadrilateral element matrix */
  RealMatrix<4, 4> _computeElementMatrixQuad4(Cell cell);
  /** AI comment: Computes the 8-node hexahedron element matrix */
  RealMatrix<8, 8> _computeElementMatrixHexa8(Cell cell);
  /** AI comment: Assembles the bilinear form using element matrix computation callback */
  template <int N>
  void _assembleBilinear(const std::function<RealMatrix<N, N>(const Cell&)>& compute_element_matrix);
};

#endif
