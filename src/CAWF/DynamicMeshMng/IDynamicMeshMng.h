#pragma once

namespace ShArc
{
/**
 * \ingroup CAWF
 * \aigenerated
 * \brief Interface for dynamic mesh management.
 *
 * Handles mesh modifications during sedimentation events, such as
 * adding new cell layers and updating mesh connectivity.
 */
class IDynamicMeshMng
{
public:
  /** \aigenerated Default constructor */
  IDynamicMeshMng(){}
  /** \aigenerated Virtual destructor */
  virtual ~IDynamicMeshMng(){}

  /** \aigenerated Initializes the dynamic mesh manager */
  virtual void init() = 0 ;
  /** \aigenerated Updates the mesh for a new sedimentation event */
  virtual void updateNewEvent() = 0 ;
};
}
