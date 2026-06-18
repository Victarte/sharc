// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2025 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*---------------------------------------------------------------------------*/
/* PASSMO : Performant Assessment for Seismic Site Modelling with finite-    */
/* element (FEM) numerical modelling approach                                */
/* Created by : E. Foerster                                                  */
/*---------------------------------------------------------------------------*/
/* GaussDoFsOnCells.h                                          (C) 2022-2025 */
/* Manage one or more Gauss points for FEM integration on Cells              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#ifndef GAUSSDOFSONCELLS_H
#define GAUSSDOFSONCELLS_H
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "FemUtils.h"
#include <arcane/ItemTypes.h>
#include <arcane/IndexedItemConnectivityView.h>
#include <arcane/IMesh.h>
//#include "MeshTensorVariable.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Arcane::FemUtils
{
/*!
 * \brief Manage one or more Gauss Points on Cells through the Arcane DoFs mechanism.
 *
 * Before using an instance of this class you need to call method
 * initialize().
 */
class GaussDoFsOnCells
{
  class Impl;

 public:

  /** AI generated: Constructs the Gauss point manager with a trace manager */
  explicit GaussDoFsOnCells(Arcane::ITraceMng* tm);
  /** AI generated: Destructor */
  ~GaussDoFsOnCells();

 public:

  GaussDoFsOnCells(const GaussDoFsOnCells&) = delete;
  GaussDoFsOnCells(GaussDoFsOnCells&&) = delete;
  GaussDoFsOnCells& operator=(GaussDoFsOnCells&&) = delete;
  GaussDoFsOnCells& operator=(const GaussDoFsOnCells&) = delete;

 public:

  /*!
   * \brief Initialize the instance.
   */
  void initialize(Arcane::IMesh* mesh, Arcane::Int32 max_nb_gauss_per_cell);

 public:

  /** AI generated: Returns the connectivity view from cells to their associated Gauss DoFs */
  [[nodiscard]] Arcane::IndexedCellDoFConnectivityView gaussCellConnectivityView() const;
  /** AI generated: Returns the Gauss DoF item family */
  [[nodiscard]] Arcane::IItemFamily* gaussFamily() const;
  /** AI generated: Returns the Gauss point shape function values variable */
  Arcane::VariableDoFArrayReal& gaussShape();
  /** AI generated: Returns the Gauss point shape function derivatives variable */
  Arcane::VariableDoFArrayReal3& gaussShapeDeriv();
  /** AI generated: Returns the Gauss point reference positions variable */
  Arcane::VariableDoFReal3& gaussRefPosition();
  /** AI generated: Returns the Gauss point Jacobian matrix variable */
  Arcane::VariableDoFReal3x3& gaussJacobMat();
  /** AI generated: Returns the Gauss point integration weights variable */
  Arcane::VariableDoFReal& gaussWeight();
  /** AI generated: Returns the Gauss point Jacobian determinant variable */
  Arcane::VariableDoFReal& gaussJacobian();
  /** AI generated: Returns the Gauss point law parameters variable */
  Arcane::VariableDoFArrayReal& gaussLawParam();
  /** AI generated: Returns the Gauss point law history parameters variable */
  Arcane::VariableDoFArrayReal& gaussLawHistoryParam();

/*  Arcane::VariableDoFArrayTensor2& gaussStress();
  Arcane::VariableDoFArrayTensor2& gaussStrain();
  Arcane::VariableDoFArrayTensor2& gaussStrainPlastic();*/
  /** AI generated: Returns the Gauss point stress variable */
  Arcane::VariableDoFArrayReal3x3& gaussStress();
  /** AI generated: Returns the Gauss point strain variable */
  Arcane::VariableDoFArrayReal3x3& gaussStrain();
  /** AI generated: Returns the Gauss point plastic strain variable */
  Arcane::VariableDoFArrayReal3x3& gaussStrainPlastic();
  /** AI generated: Returns the Gauss point tangent operator variable */
  Arcane::VariableDoFArrayReal3x3& gaussTangentOperator();

 private:

  Impl* m_p = nullptr;
};
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif //GAUSSDOFSONCELLS_H
