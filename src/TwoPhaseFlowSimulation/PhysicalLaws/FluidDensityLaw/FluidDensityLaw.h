// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2022 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*
 * FluidDensityLaw.h
 */

#ifndef FLUIDDENSITYLAW_H_
#define FLUIDDENSITYLAW_H_

#include "ArcGeoSim/Utils/Utils.h"
#include <arcane/utils/ITraceMng.h>

//=====================================================
/**
 * \ingroup TwoPhaseFlow
 * \aigenerated
 * \brief Fluid density law with linear expansion.
 *
 * Computes fluid density as a function of temperature and concentration
 * using the linear expansion model:
 * \f$\rho(T,C) = \rho_0 [1 - \beta_T (T - T_0) - \beta_C (C - C_0)]\f$.
 */
class FluidDensityLaw
{
public :

    /** \aigenerated Constructs the law with default parameters */
    FluidDensityLaw()
    {
        initParameters();
    }

    /** \aigenerated Evaluates density and its partial derivatives
     *  \param T Temperature
     *  \param C Concentration
     *  \param rho Density
     *  \param drho_dt Partial derivative wrt temperature
     *  \param drho_dc Partial derivative wrt concentration */
    void eval( const Real T, const Real C, Real& rho, Real& drho_dt, Real& drho_dc) const;

    /** \aigenerated Sets the law parameters
     *  \param rho0 Reference density
     *  \param betat Thermal expansion coefficient
     *  \param betac Concentration expansion coefficient
     *  \param t0 Reference temperature
     *  \param c0 Reference concentration */
    void setParameters( const Real rho0, const Real betat, const Real betac, const Real t0, const Real c0 );

private :

    /** \aigenerated Initializes parameters to default values */
    void initParameters();

private :

    /** \aigenerated Reference density */
    Real m_rho0;
    /** \aigenerated Thermal expansion coefficient */
    Real m_betat;
    /** \aigenerated Concentration expansion coefficient */
    Real m_betac;
    /** \aigenerated Reference temperature */
    Real m_t0;
    /** \aigenerated Reference concentration */
    Real m_c0;
};

#endif /* FLUIDDENSITYLAW_H_ */
