// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2025 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*---------------------------------------------------------------------------*/
/* FemUtilsGlobal.h                                            (C) 2022-2025 */
/*                                                                           */
/* Defines types for FemUtils component.                                     */
/*---------------------------------------------------------------------------*/
#ifndef ARCANEFEM_FEMUTILS_FEMUTILSGLOBAL_H
#define ARCANEFEM_FEMUTILS_FEMUTILSGLOBAL_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "FemDoFsOnNodes.h"
#include <arcane/utils/ArcaneGlobal.h>

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Arcane::FemUtils
{

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/** AI generated: Forward declaration */
class CsrRowColumnIterator;
/** AI generated: Forward declaration */
class CsrFormatMatrixView;
/** AI generated: Forward declaration */
class CsrRow;
/** AI generated: Forward declaration */
class CsrFormat;
/** AI generated: Forward declaration */
class CsrRowColumnIndex;
/** AI generated: Forward declaration */
class IDoFLinearSystemFactory;
/** AI generated: Forward declaration */
class DoFLinearSystem;
/** AI generated: Forward declaration */
class IDoFLinearSystemImpl;
/** AI generated: Forward declaration */
class FemDoFsOnNodes;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/** AI generated: Legacy alias for CsrFormatMatrixView to maintain backward compatibility */
using CSRFormatView = CsrFormatMatrixView;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*!
 * \brief List of matrix elimination type
 */
enum class MatrixEliminationType : Byte
{
  //! No elimination
  None = 0,
  //! Row elimination
  Row = 1,
  //! RowColumn elimination
  RowColumn = 2,
};
/** AI generated: Constant for matrix elimination type: none */
static constexpr Byte ELIMINATE_NONE = static_cast<Byte>(MatrixEliminationType::None);
/** AI generated: Constant for matrix elimination type: row only */
static constexpr Byte ELIMINATE_ROW = static_cast<Byte>(MatrixEliminationType::Row);
/** AI generated: Constant for matrix elimination type: row and column */
static constexpr Byte ELIMINATE_ROW_COLUMN = static_cast<Byte>(MatrixEliminationType::RowColumn);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace Arcane::FemUtils

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif
