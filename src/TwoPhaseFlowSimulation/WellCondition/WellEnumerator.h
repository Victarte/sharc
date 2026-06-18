//
// Created by yousefs on 05/12/2022.
//

#ifndef NUMERICS_CONDITION_WELLENUMERATOR_H
#define NUMERICS_CONDITION_WELLENUMERATOR_H

#include "TwoPhaseFlowSimulation/BoundaryCondition/FolderEnumerator.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/**
 * \ingroup TwoPhaseFlow
 * \aigenerated
 * \brief Enumerator for iterating over well conditions.
 *
 * Extends FolderEnumerator for well-specific data, providing access
 * to well indices and flow flags in addition to folder and name.
 */
class WellEnumerator
  : public FolderEnumerator<Law::ContainerKind::PartialVariable,
                            Law::ItemKind::Cell>
{
private:

  /** \aigenerated Base class type */
  typedef FolderEnumerator<Law::ContainerKind::PartialVariable,
                           Law::ItemKind::Cell> Base;

public:

  /** \aigenerated Constructs the well enumerator */
  WellEnumerator(const Arcane::Array<Folder*>& folders,
                 const Arcane::StringArray& names,
                 const Arcane::Array<Arcane::PartialVariableCellReal*>& well_index,
                 const Arcane::ByteArray& is_flow)
    : Base(folders, names)
    , m_folders(folders)
    , m_well_index(well_index)
    , m_is_flow(is_flow) {}

  /** \aigenerated Copy constructor */
  WellEnumerator(const WellEnumerator& e)
    : Base(e)
    , m_folders(e.m_folders)
    , m_well_index(e.m_well_index)
    , m_is_flow(e.m_is_flow){}

  /** \aigenerated Access to the current folder (const) */
  const Folder& folder() const { return *(m_folders[index()]); }

  /** \aigenerated Access to the current folder (mutable) */
  Folder& folder() { return *(m_folders[index()]); }

  /** \aigenerated Returns the Peaceman well index for the current well */
  const Arcane::PartialVariableCellReal& wellIndex() const
  {
    return *m_well_index[index()];
  }

  /** \aigenerated Whether the current well is producing (flow) */
  bool isFlow() const
  {
    return m_is_flow[index()];
  }

private:

  /** \aigenerated List of folders for each well */
  const Arcane::Array<Folder*>& m_folders;

  /** \aigenerated List of well index variables for each well */
  const Arcane::Array<Arcane::PartialVariableCellReal*>& m_well_index;

  /** \aigenerated Array of flow flags per well */
  const Arcane::ByteArray& m_is_flow;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif /* NUMERICS_CONDITION_WELLENUMERATOR_H */
