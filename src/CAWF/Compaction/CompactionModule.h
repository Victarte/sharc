#pragma once

#include "CAWF/DynamicMeshMng/IDynamicMeshMng.h"

#include "Compaction_axl.h"

using namespace Arcane;

/**
 * \ingroup CAWF
 * \aigenerated
 * \brief Module for compaction and sedimentation simulation.
 *
 * CompactionModule models sediment deposition and compaction over time,
 * managing sedimentary layers, gravity-driven compaction, and dynamic
 * top boundary evolution. It handles layer events where new sediment
 * is added, and computes density and pressure evolution.
 */
class CompactionModule
: public ArcaneCompactionObject
, public ArcGeoSim::ICAWFMng::ITimeIterStateOp
{
 public:
  /** \aigenerated Index manager type for linear algebra */
  typedef Alien::ArcaneTools::BasicIndexManager IndexMangerType ;
  /** \aigenerated Pointer to index manager */
  typedef std::unique_ptr<IndexMangerType>      IndexMangerPtrType ;
  /** \aigenerated Space type for linear algebra */
  typedef Alien::ArcaneTools::Space             SpaceType ;
  /** \aigenerated Scalar index set type */
  typedef Alien::ArcaneTools::IIndexManager::ScalarIndexSet  ScalarIndexSetType ;

  /** \aigenerated Constructs the compaction module */
  CompactionModule(const Arcane::ModuleBuildInfo & mbi)
    : ArcaneCompactionObject(mbi){}

  /** \aigenerated Destructor */
  virtual ~CompactionModule() {};

public:
  /** \aigenerated Initializes the module and its data structures */
  void init();
  /** \aigenerated Runs the compaction test case */
  void test();

  /** \aigenerated Updates the top boundary after a sedimentation event */
  void updateTopBoundary(CellGroup const& new_event);
  /** \aigenerated Computes cell density from compaction state */
  void computeDensity();
  /** \aigenerated Computes cell pressure from overburden */
  void computePressure();
  /** \aigenerated Updates time-dependent variables for the next time step */
  void updateVariablesTN();

  /** \aigenerated Saves the current state for time step restart */
  void saveOldState() ;
  /** \aigenerated Reloads the previously saved state */
  void reloadOldState() ;

private :


  /** \aigenerated Current time step size */
  Real          m_dt = 0. ;
  /** \aigenerated Current simulation time */
  Real          m_time = 0. ;
  /** \aigenerated Current iteration number */
  int           m_iter = 0 ;
  /** \aigenerated Maximum number of iterations */
  int           m_max_iter = 0 ;


  /** \aigenerated Name of the top boundary group */
  String                         m_top_boundary_name     = "TopBoundary" ;
  /** \aigenerated Name of the bottom boundary group */
  String                         m_bottom_boundary_name  = "BottomBoundary" ;
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
  /** \aigenerated Linear solver for the compaction system */
  Alien::ILinearSolver *         m_linear_solver         = nullptr;

  /** \aigenerated Array of all DoF indices */
  Alien::UniqueArray<Integer>  m_allUIndex;



};

