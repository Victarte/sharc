// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2022 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*
 * Constant.h
 */

#ifndef CONSTANTLAW_H_
#define CONSTANTLAW_H_


#include "ArcGeoSim/Utils/Utils.h"

//=====================================================
/**
 * \ingroup TwoPhaseFlow
 * \aigenerated
 * \brief Constant-valued law.
 *
 * Returns a constant value for a physical property. Useful for
 * simple test cases where spatial or temporal variation is
 * not needed.
 */
class ConstantLaw
{
public :

  /** \aigenerated Constructs the law with zero value */
  ConstantLaw()
    : m_value(0.) {}
  
  /** \aigenerated Evaluates the constant value */
  void eval( Real& C ) const;
  
private :
  
  /** \aigenerated Constant value */
  Real m_value ;
  
public:

/** \aigenerated Sets the constant value */
void setParameters( const Real value  );

};


#endif /* CONSTANTLAW_H_ */
