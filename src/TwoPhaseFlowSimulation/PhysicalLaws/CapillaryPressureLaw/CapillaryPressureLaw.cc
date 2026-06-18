// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2022 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------

/*
 * CapillaryPressureLaw.cc
 *  Lois Physiques
 */

//-----------------------------------------------------------
// Loi de la pression capillaire
// Pc = Pe (Sw)^(-1/lambda)
//-----------------------------------------------------------

#include "FluidDensityLaw.h"

//=====================================================

/** AI comment: Evaluates capillary pressure Pc = Pe * Se^(-1/lambda) */
void CapillaryPressureLaw::eval( const Real S, Real& Pc, Real& dPc_dS ) const
{
    // Compute results

    Real dSe_dS;
    const Real Se   = computeSe( S, dSe_dS );
    Real alpha = - 1./m_lambda;
    if(Se)
    {
        Pc = m_Pe * pow(Se, alpha);
        dPc_dS = alpha * m_Pe * dSe_dS * pow(Se, alpha - 1);
    }
    else {
        Pc = 0.;        // infinity
        dPc_dS = 0.;    // -infinity
        // Se == 0    warning() <<"Sw is out of bounds in the evaluation of the capillary pressure law !";
    }
}

//=====================================================

/** AI comment: Computes effective saturation Se from saturation S and residual saturations */
Real CapillaryPressureLaw::computeSe( const Real S, Real& dSe_dS ) const
{

    Real Se = Arcane::math::min(1 - (S - m_Sr)/(1 - m_Sr_ref -m_Sr), 1.0);
    dSe_dS = - 1.0/(1 - m_Sr_ref -m_Sr);

    return Arcane::math::max(Se, 0.);

}

//=====================================================

/** AI comment: Sets capillary pressure law parameters: entry pressure, residual saturations, exponent */
void CapillaryPressureLaw::setParameters( const Real Pe, const Real Sr_ref, const Real Sr, const Real lambda  )
{
    // Set Parameters

    m_Pe = Pe;
    m_Sr_ref = Sr_ref;
    m_Sr = Sr;
    m_lambda = lambda;
}

//=====================================================

/** AI comment: Initializes capillary pressure parameters to default values */
void CapillaryPressureLaw::initParameters()
{
    // Init Parameters
    // Standard End Points
    const Real Pe    = 0;
    const Real Sr_ref   = 0;
    const Real Sr   = 0;
    const Real lambda = 1;

    // Set Parameters
    setParameters( Pe, Sr_ref, Sr, lambda );
}
