// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2022 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*
 * CapillaryPressureLaw.h
 */

#ifndef CAPILLARYPRESSURELAW_H_
#define CAPILLARYPRESSURELAW_H_

#include "ArcGeoSim/Utils/Utils.h"
#include <arcane/utils/ITraceMng.h>

//=====================================================
/**
 * \ingroup TwoPhaseFlow
 * \aigenerated
 * \brief Brooks-Corey capillary pressure law.
 *
 * Computes capillary pressure \f$P_c(S)\f$ as a function of wetting-phase
 * saturation, using the Brooks-Corey model with entry pressure,
 * residual saturations, and pore-size distribution index.
 * Parameters: entry pressure \f$P_e\f$, reference residual \f$S_{r,ref}\f$,
 * residual saturation \f$S_r\f$, and pore-size index \f$\lambda\f$.
 */
class CapillaryPressureLaw
{
public :

    /** \aigenerated Constructs the law with default parameters */
    CapillaryPressureLaw()
    {
        initParameters();
    }

    /** \aigenerated Evaluates capillary pressure and its derivative
     *  \param S Wetting-phase saturation
     *  \param Pc Capillary pressure
     *  \param dPc_dS Derivative of Pc with respect to S */
    void eval( const Real S, Real& Pc, Real& dPc_dS ) const;

    /** \aigenerated Sets the law parameters
     *  \param Pe Entry pressure
     *  \param Sr_ref Reference residual saturation
     *  \param Sr Residual saturation
     *  \param lambda Pore-size distribution index */
    void setParameters( const Real Pe, const Real Sr_ref, const Real Sr, const Real lambda );

private :

    /** \aigenerated Initializes parameters to default values */
    void initParameters();

    /** \aigenerated Computes effective saturation <br>
     *  \f$S_e = (S - S_r) / (1 - S_r - S_{r,ref})\f$ <br>
     *  and its derivative */
    Real computeSe( const Real S, Real& dSe_dS ) const;

private :

    /** \aigenerated Entry pressure */
    Real m_Pe;
    /** \aigenerated Reference residual saturation */
    Real m_Sr_ref;
    /** \aigenerated Residual saturation */
    Real m_Sr;
    /** \aigenerated Pore-size distribution index */
    Real m_lambda;
};

#endif /* CAPILLARYPRESSURELAW_H_ */
