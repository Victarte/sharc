// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2022 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------

/*
 * ConstantLaw.cc
 *
 *  Lois Physiques Geoxim
 */

//-----------------------------------------------------------
// Loi contante
// C = C()
//-----------------------------------------------------------

#include "ConstantLaw.h"

//=====================================================

/** AI comment: Returns the constant value */
void ConstantLaw::eval( Real& C) const
{
  C = m_value;
}

//======================================================

/** AI comment: Sets the constant law value */
void ConstantLaw::setParameters( const Real value)
{
  // Set parameters
  m_value = value;
}
