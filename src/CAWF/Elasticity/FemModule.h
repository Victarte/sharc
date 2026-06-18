// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2025 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*---------------------------------------------------------------------------*/
/* FemModule.h                                                (C) 2022-2025  */
/*                                                                           */
/* FemModuleElasticity class definition.                                     */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#ifndef FEMMODULES_H
#define FEMMODULES_H
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include <arcane/utils/CommandLineArguments.h>
#include <arcane/utils/ParameterList.h>
#include <arcane/utils/ApplicationInfo.h>

#include <arcane/ITimeLoopMng.h>
#include <arcane/IMesh.h>
#include <arcane/IItemFamily.h>
#include <arcane/ItemGroup.h>
#include <arcane/ICaseMng.h>
#include <arcane/accelerator/core/IAcceleratorMng.h>
#include <arcane/accelerator/core/RunQueue.h>
#include <arcane/core/ItemTypes.h>
#include <arccore/base/ArccoreGlobal.h>
#include "arccore/base/NotImplementedException.h"

#include <alien/kernels/simple_csr/algebra/SimpleCSRLinearAlgebra.h>
#include <alien/kernels/simple_csr/algebra/SimpleCSRInternalLinearAlgebra.h>

#include <alien/ref/AlienRefSemantic.h>
#include <alien/ref/AlienImportExport.h>

#include <alien/arcane_tools/IIndexManager.h>
#include <alien/arcane_tools/indexManager/BasicIndexManager.h>
#include <alien/arcane_tools/indexManager/SimpleAbstractFamily.h>
#include <alien/arcane_tools/distribution/DistributionFabric.h>
#include <alien/arcane_tools/indexSet/IndexSetFabric.h>
#include <alien/arcane_tools/data/Space.h>

#include "CAWF/FEMUtils/IArcaneFemBC.h"
#include "CAWF/FEMUtils/IDoFLinearSystemFactory.h"
#include "CAWF/DynamicMeshMng/IDynamicMeshMng.h"

#include "Fem_axl.h"

#include "CAWF/FEMUtils/FemUtils.h"
#include "CAWF/FEMUtils/DoFLinearSystem.h"
#include "CAWF/FEMUtils/AlienDoFLinearSystem.h"
#include "CAWF/FEMUtils/FemDoFsOnNodes.h"
#include "CAWF/FEMUtils/BSRFormat.h"
#include "CAWF/FEMUtils/AlienBSRFormat.h"

#include "CAWF/FEMUtils/ArcaneFemFunctions.h"
#include "CAWF/FEMUtils/ArcaneFemFunctionsGpu.h"


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::FemUtils;

/*---------------------------------------------------------------------------*/
/**
 * \ingroup CAWF
 * \brief A module for finite element method.
 *
 * This class handles the initialization and computation for finite element
 * method (FEM) simulations, providing methods to  set  up and solve linear
 * systems, assemble FEM operators, and perform result checks.
 */
/*---------------------------------------------------------------------------*/

class FemModuleElasticity
: public ArcaneFemObject
, public ArcGeoSim::ICAWFMng::ITimeIterStateOp
{
 public:

  /** \aigenerated Constructs the elasticity module */
  explicit FemModuleElasticity(const ModuleBuildInfo& mbi)
  : ArcaneFemObject(mbi)
  , m_dofs_on_nodes(mbi.subDomain()->traceMng())
  , m_bsr_format(mbi.subDomain()->traceMng(), *(mbi.subDomain()->acceleratorMng()->defaultQueue()), m_dofs_on_nodes)
  {
    ICaseMng* cm = mbi.subDomain()->caseMng();
    cm->setTreatWarningAsError(true);
    cm->setAllowUnkownRootElelement(false);
  }

  /** \aigenerated Saves the old state for time stepping */
  void saveOldState();
  /** \aigenerated Reloads the old state for time stepping */
  void reloadOldState();
  /** \aigenerated Initializes the module */
  void init() override;
  /** \aigenerated Method called at the beginning of the simulation */
  void startInit() override;
  /** \aigenerated Computes the divergence of displacement at each iteration */
  void computeDivU() override;
  /** \aigenerated Executes the test case at each iteration */
  void test() override;
  /** \aigenerated Returns the module version */
  VersionInfo versionInfo() const override { return VersionInfo(1, 0, 0); }

  /** \aigenerated Updates the top boundary cell group for sedimentation */
  void _updateTopBoundary(CellGroup const& new_event);
  /** \aigenerated Performs a stationary (non-transient) solve */
  void _doStationarySolve();
  /** \aigenerated Defines the matrix sparsity pattern from element connectivities */
  template<typename ProfilerT>
  void _defineMatrixProfile(ProfilerT& profiler, ConstArrayView<Integer> allUIndex) ;
#ifdef ALIEN_USE_SYCL
  /** \aigenerated Defines the matrix profile on GPU accelerator */
  void _defineMatrixProfileAcc() ;
#endif
  /** \aigenerated Assembles the bilinear operator (stiffness matrix) */
  void _assembleBilinearOperator();
#ifdef ALIEN_USE_SYCL
  /** \aigenerated Assembles the bilinear operator on GPU accelerator */
  void _assembleBilinearOperatorAlienAcc() ;
#endif
  /** \aigenerated Assembles Dirichlet boundary conditions on GPU */
  void _assembleDirichletsGpu();

  /** \aigenerated Pre-processing computations before assembly */
  void _computePrePro();
  /** \aigenerated Post-processing computations after solve */
  void _computePostPro();

 private:

  /** \aigenerated Linear system (matrix + RHS + solution) */
  DoFLinearSystem m_linear_system;
  /** \aigenerated Degree-of-freedom mapping on mesh nodes */
  FemDoFsOnNodes m_dofs_on_nodes;
  /** \aigenerated Block sparse row matrix format for FEM assembly */
  BSRFormat m_bsr_format;
  /** \aigenerated Alien BSR format (optional, for external solvers) */
  AlienBSRFormat* m_alien_bsr_format = nullptr;
  /** \aigenerated Alien linear system implementation (optional) */
  Arcane::FemUtils::AlienDoFLinearSystemImpl* m_alien_linear_system = nullptr;

  /** \aigenerated DoF-to-DoF connection index array */
  UniqueArray<Integer> m_dof_dof_connection_index;
  /** \aigenerated DoF-to-DoF connection offset array */
  UniqueArray<Integer> m_dof_dof_connection_offset;

  /** \aigenerated Global body force vector */
  Real3 m_F;
  /** \aigenerated Young's modulus */
  Real E;
  /** \aigenerated Poisson's ratio */
  Real nu;

  /** \aigenerated Traction vector */
  Real3 t;
  /** \aigenerated Whether to apply body forces */
  bool m_applyBodyForce = false;

  /** \aigenerated Number of DoFs per node (2 for 2D, 3 for 3D) */
  Int8 m_dof_per_node;

  /** \aigenerated PETSc solver flags string */
  String m_petsc_flags;
  /** \aigenerated Matrix format type ("DOK", "BSR", "Alien-BSR-Acc") */
  String m_matrix_format = "DOK";

  /** \aigenerated Whether to assemble the linear system */
  bool m_assemble_linear_system = true;
  /** \aigenerated Whether to solve the linear system */
  bool m_solve_linear_system = true;
  /** \aigenerated Whether to perform cross-validation */
  bool m_cross_validation = false;
  /** \aigenerated Whether the mesh uses hex/quad elements */
  bool m_hex_quad_mesh = false;

  /** \aigenerated Current time step size */
  Real                           m_dt                    = 0. ;
  /** \aigenerated Current simulation time */
  Real                           m_time                  = 0. ;
  /** \aigenerated Current iteration number */
  int                            m_iter                  = 0 ;
  /** \aigenerated Maximum number of iterations */
  Integer                        m_max_iter              = 0 ;
  /** \aigenerated Gravitational acceleration */
  Real                           m_gravity               = 9.8;
  /** \aigenerated Top boundary z-coordinate */
  Real                           m_top_z                 = 0. ;
  /** \aigenerated Period between sedimentation events */
  Real                           m_event_period          = 0. ;
  /** \aigenerated Time of next sedimentation event */
  Real                           m_next_event_time       = 0. ;
  /** \aigenerated Current event index */
  Integer                        m_event_index           = 0 ;
  /** \aigenerated ID for new sediment layers */
  Integer                        m_new_layer_id          = 0 ;
  /** \aigenerated Whether the precice mesh has been updated */
  bool                           m_precice_mesh_is_updated = false;

  /** \aigenerated Array of sediment layer cell groups */
  UniqueArray<Arcane::CellGroup> m_layers ;
  /** \aigenerated Period for new layer events */
  Real                           m_layer_event_period    = 0. ;
  /** \aigenerated Time of current layer event */
  Real                           m_layer_event_time      = 0. ;
  /** \aigenerated Time of next layer event */
  Real                           m_next_layer_event_time = 0. ;
  /** \aigenerated UIDs of activated layers */
  UniqueArray<Int64>             m_activated_layers_uids;

  /** \aigenerated Parallel communication manager */
  IParallelMng*                  m_parallel_mng          = nullptr;
  /** \aigenerated Dynamic mesh manager for sedimentation */
  ShArc::IDynamicMeshMng*        m_dynamic_mesh_mng      = nullptr;
  /** \aigenerated CAWF manager */
  ArcGeoSim::ICAWFMng*           m_cawf_mng              = nullptr ;
  /** \aigenerated Geometry manager */
  IGeometryMng *                 m_geometry_mng          = nullptr;
  /** \aigenerated Geometry policy */
  NoOptimizationGeometryPolicy   m_geometry_policy ;
  /** \aigenerated Linear solver for the FEM system */
  Alien::ILinearSolver *         m_linear_solver         = nullptr;

  /** \aigenerated Retrieves material parameters (lambda, mu) for a cell group */
  void _getMaterialParameters(CellGroup const& cells);
  /** \aigenerated Solves the assembled linear system */
  void _solve();
  /** \aigenerated Assembles the linear operator (stiffness + BCs) */
  void _assembleLinearOperator();
  /** \aigenerated Validates results against reference values */
  void _validateResults();
  /** \aigenerated Updates time-dependent variables for next step */
  void _updateVariables();
  /** \aigenerated Initializes the BSR matrix format */
  void _initBsr();
  /** \aigenerated Initializes the Alien BSR matrix format */
  void _initAlienBsr();

  /** \aigenerated Applies body force contribution to the RHS */
  inline void _applyBodyForce(VariableDoFReal& rhs_values, const IndexedNodeDoFConnectivityView& node_dof);
  /** \aigenerated Applies traction contribution to the RHS */
  inline void _applyTraction(VariableDoFReal& rhs_values, const IndexedNodeDoFConnectivityView& node_dof);
  /** \aigenerated Applies Dirichlet BCs to the linear system */
  inline void _applyDirichlet(VariableDoFReal& rhs_values, const IndexedNodeDoFConnectivityView& node_dof);

  /** \aigenerated Computes the 6x6 element matrix for a 2D Tria3 element */
  RealMatrix<6, 6> _computeElementMatrixTria3(Cell cell);
  /** \aigenerated Computes the 12x12 element matrix for a 3D Tetra4 element */
  RealMatrix<12, 12> _computeElementMatrixTetra4(Cell cell);
  /** \aigenerated Computes the 8x8 element matrix for a 2D Quad4 element */
  RealMatrix<8, 8> _computeElementMatrixQuad4(Cell cell);
  /** \aigenerated Computes the 24x24 element matrix for a 3D Hexa8 element */
  RealMatrix<24, 24> _computeElementMatrixHexa8(Cell cell);
  /** \aigenerated Computes the gradient of displacement for a Hexa8 element */
  Real3 _computeElementGradientHexa8(Cell cell);
  /** \aigenerated Computes the divergence of displacement for a cell */
  Real _computeElementDiv(Cell cell);

  /** \aigenerated Assembles the bilinear operator on CPU for a given element type */
  template <int N>
  void _assembleBilinearOperatorCpu(const std::function<RealMatrix<N, N>(const Cell&)>& compute_element_matrix);

  /** \aigenerated Assembles the bilinear operator on GPU for a given element type */
  template <class FunctionT>
  void _assembleBilinearOperatorGpu(const FunctionT& compute_element_matrix);
};

template<typename ProfilerT>
void FemModuleElasticity::
_defineMatrixProfile(ProfilerT& profiler, ConstArrayView<Integer> allUIndex)
{
  ///////////////////////////////////////////////////////////////////////////
  //
  // DEFINE PROFILE
  //
  const Int32 dim = mesh()->dimension();
  auto node_dof(m_dofs_on_nodes.nodeDoFConnectivityView());
  ENUMERATE_ (Cell, icell, mesh()->allCells())
  {
    Cell cell = *icell;
    for (Node node1 : cell.nodes())
    {
      if (node1.isOwn())
      {
        for (Node node2 : cell.nodes())
        {
          for (Int32 i = 0; i < dim; ++i)
          {
            DoFLocalId dof1 = node_dof.dofId(node1, i);
            for (Int32 j = 0; j < dim; ++j)
            {
              DoFLocalId dof2 = node_dof.dofId(node2, j);
              profiler.addMatrixEntry(allUIndex[dof1.localId()], allUIndex[dof2.localId()]);
            }
          }
        }
      }
    }
  }
}

#endif
