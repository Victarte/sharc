// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2022 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/**
 * \file
 * \brief ShArc simulation entry point.
 * \aigenerated
 *
 * Initializes the Arcane framework with ShArc application info
 * and delegates to ArcGeoSim::main() for execution.
 */
#include "ArcGeoSim/Appli/Architecture/ArcGeoSimMain.h"

#ifdef ARCGEOSIM_USE_EXPORT
#include "ShArcDynamicLoading.h"
#endif

/**
 * \brief Main entry point for the ShArc simulation.
 * \aigenerated
 *
 * Sets up Arcane::ApplicationInfo with the name "ShArc" and version 1.0.0,
 * then hands control to the ArcGeoSim main loop.
 */
int main(int argc, char* argv[])
{ 
  Arcane::ApplicationInfo info(&argc,&argv,
                               "ShArc",
                               Arcane::VersionInfo(1,0,0));
  
  return ArcGeoSim::main(info);
}
