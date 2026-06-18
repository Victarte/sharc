//
// Created by yousefs on 05/12/2022.
//

#ifndef WELLCONDITION_IWELLMANAGER_H
#define WELLCONDITION_IWELLMANAGER_H

#include "WellEnumerator.h"

#include "ArcRes/Entities/System.h"
#include "ArcGeoSim/Physics/Gump/Property.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/**
 * \ingroup TwoPhaseFlow
 * \aigenerated
 * \brief Interface for well condition management.
 *
 * Manages well boundary conditions for two-phase flow simulation,
 * including well index computation and flow rate management.
 * Supports enumeration over active wells.
 */
class IWellManager
{
public:

    /** \aigenerated Enumerator type for iterating over wells */
    typedef WellEnumerator Enumerator;

    /** \aigenerated Virtual destructor */
    virtual ~IWellManager() {}

public:

  /** \aigenerated Initializes well conditions: registers properties,
   *  creates variables, and populates at current time */
  virtual void init(ArcRes::System& system, Law::VariableCellFolder& domain) = 0;

  /** \aigenerated Updates well conditions at the current time */
  virtual void update(ArcRes::System& system) = 0;

  /** \aigenerated Returns an enumerator over the active wells */
  virtual Enumerator enumerator() const = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#define ENUMERATE_WELL(e, c) \
  for(IWellManager::Enumerator e = c; e.hasNext(); ++e)


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif //WELLCONDITION_IWELLMANAGER_H
