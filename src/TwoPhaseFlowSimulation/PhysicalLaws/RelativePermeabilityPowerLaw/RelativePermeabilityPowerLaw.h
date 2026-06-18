// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2022 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*
 * RelativePermeabilityPowerLaw.h
 */

#ifndef RELATIVEPERMEABILITYPOWERLAW_H_
#define RELATIVEPERMEABILITYPOWERLAW_H_

#include "ArcGeoSim/Utils/Utils.h"
#include <arcane/utils/ITraceMng.h>

//=====================================================
/**
 * \ingroup TwoPhaseFlow
 * \aigenerated
 * \brief Relative permeability power law (Corey-type).
 *
 * Computes wetting-phase relative permeability using the Corey
 * power-law model: \f$k_{rw}(S_w) \propto \bar{S}_w^\alpha\f$
 * where \f$\bar{S}_w = (S_w - S_{wi}) / (1 - S_{wi} - S_{gc})\f$,
 * with irreducible wetting saturation \f$S_{wi}\f$, residual
 * non-wetting saturation \f$S_{gc}\f$, and exponent \f$\alpha\f$.
 */
class RelativePermeabilityPowerLaw
{
public :
  
  /** \aigenerated Constructs the law with default parameters */
  RelativePermeabilityPowerLaw()
  {
    initParameters();
  }

  /** \aigenerated Evaluates relative permeability and its derivative
   *  \param Sw Wetting-phase saturation
   *  \param krw Relative permeability
   *  \param dkrw_dSw Derivative of krw wrt Sw */
  void eval( const Real Sw, Real& krw, Real& dkrw_dSw ) const;

  /** \aigenerated Sets the law parameters
   *  \param Swi Irreducible wetting saturation
   *  \param Sgc Residual non-wetting saturation
   *  \param alpha Power-law exponent */
  void setParameters( const Real Swi, const Real Sgc, const Real alpha );

private :

  /** \aigenerated Initializes parameters to default values */
  void initParameters();

  /** \aigenerated Computes normalized saturation \f$\bar{S}_w\f$
   *  and its derivative */
  Real computeSwBar( const Real Sw, Real& dSwBar_dSw ) const;

private :

  /** \aigenerated Irreducible wetting saturation */
  Real m_Swi;
  /** \aigenerated Residual non-wetting saturation */
  Real m_Sgc;
  /** \aigenerated Power-law exponent */
  Real m_alpha;
};

#endif /* RELATIVEPERMEABILITYPOWERLAW_H_ */
