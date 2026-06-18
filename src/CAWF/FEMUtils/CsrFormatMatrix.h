// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2026 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*---------------------------------------------------------------------------*/
/* CsrFormatMatrix.h                                           (C) 2022-2026 */
/*                                                                           */
/* Container for Matrix using CSR format.                                    */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#ifndef ARCANEFEM_FEMUTILS_CSRFORMATMATRIX_H
#define ARCANEFEM_FEMUTILS_CSRFORMATMATRIX_H
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include <arcane/utils/FatalErrorException.h>
#include <arcane/utils/NumArray.h>

#include <arcane/VariableTypes.h>
#include <arcane/IItemFamily.h>

#include "FemUtils.h"
#include "CsrFormatMatrixView.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Arcane::FemUtils
{
/** AI generated: Forward declaration */
class DoFLinearSystem;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/** AI generated: Container for matrices in Compressed Sparse Row (CSR) format */
class CsrFormat
: public TraceAccessor
{
 public:

  /** AI generated: Constructs a CSR format matrix with a trace manager */
  explicit CsrFormat(Arcane::ITraceMng* tm)
  : TraceAccessor(tm)
  {
  }

 public:

  /** AI generated: Initializes the CSR matrix with DoF family, nnz, and row count */
  void initialize(IItemFamily* dof_family, Int32 nnz, Int32 nbRow, RunQueue& queue);

  /** AI generated: Adds a value to the specified (row, column) entry */
  void matrixAddValue(DoFLocalId row, DoFLocalId column, Real value)
  {
    if (row.isNull())
      ARCANE_FATAL("Row is null");
    if (column.isNull())
      ARCANE_FATAL("Column is null");
    if (value == 0.0)
      return;
    m_matrix_value(indexValue(row, column)) += value;
  }

  /** AI generated: Finds the linear index for a given (row, column) in the CSR storage */
  Int32 indexValue(DoFLocalId row, DoFLocalId column)
  {
    Int32 begin = m_matrix_row(row.localId());
    Int32 end = 0;
    if (row.localId() == m_matrix_row.extent0() - 1) {

      end = m_matrix_column.extent0();
    }
    else {

      end = m_matrix_row(row + 1);
    }
    for (Int32 i = begin; i < end; i++) {
      if (m_matrix_column(i) == column.localId()) {
        return i;
      }
    }
    return -1;
  }

  /** AI generated: Transfers CSR matrix values into a DoFLinearSystem */
  void translateToLinearSystem(DoFLinearSystem& linear_system, const RunQueue& queue);

  /**
   * @brief function to print the current content of the csr matrix
   *
   * @param fileName
   * @param nonzero if set to true, print only the non zero values
   */
  void printMatrix(std::string fileName);

  /** AI generated: Records a (row, column) coordinate during sparsity pattern assembly */
  void setCoordinates(DoFLocalId row, DoFLocalId column)
  {
    Int32 row_lid = row.localId();
    if (m_matrix_row(row_lid) == -1) {
      m_matrix_row(row_lid) = m_last_value;
    }
    m_matrix_column(m_last_value) = column.localId();
    m_last_value++;
  }

  /** AI generated: Sets the value of the specified (row, column) entry */
  void matrixSetValue(DoFLocalId row, DoFLocalId column, Real value)
  {
    m_matrix_value(indexValue(row, column)) = value;
  }

  /** AI generated: Returns a view of the matrix */
  CsrFormatMatrixView view();

 public:

  Int32 m_nnz = 0;
  // To become parallelizable, have all the index
  // inside a queue that would gradually pop ?
  // or link the idnex to the index of the core ?
  Int32 m_last_value = 0;
  NumArray<Int32, MDDim1> m_matrix_row;
  NumArray<Int32, MDDim1> m_matrix_column;
  NumArray<Real, MDDim1> m_matrix_value;
  //! Nombre de colonnes de chaque lignes.
  NumArray<Int32, MDDim1> m_matrix_rows_nb_column;
  IItemFamily* m_dof_family = nullptr;

  /** AI generated: Returns the value at the (row, column) coordinates */
  Int32 getValue(DoFLocalId row, DoFLocalId column)
  {
    return m_matrix_value(indexValue(row, column));
  }
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace Arcane::FemUtils

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif
