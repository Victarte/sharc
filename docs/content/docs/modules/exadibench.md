---
title: ExaDiBench
linkTitle: ExaDiBench
---

Mesh geometry benchmark module for exascale co-design, defined in `src/ExaDiBench/`.

## Features

- Mesh export formats: VTK, MSH, IXM
- Mesh refinement (isotropic)
- Geometry computation: volume, surface, center
- Internal data storage via `ItemGroupMap`

## Key files

| File | Role |
|------|------|
| `ExaDiBench.axl` | Module descriptor |
| `ExaDiBenchModule.cc` | Implementation (315 lines) |
| `MeshbMeshReaderService.cc` | `.mhb` mesh format reader |

## Options

| Option | Description |
|--------|-------------|
| `export-format` | Output format (VTK/MSH/IXM) |
| `refine-level` | Mesh refinement level |
| `factor` | Scaling factor |
| `geometry-service` | Geometry computation service |

## Test configurations

| Test | Mesh | Description |
|------|------|-------------|
| `bench-cube3d` | `cube3D1.vt2` | 3D cube mesh benchmark |
| `bench-spe11c` | `spe11c.vtk` | SPE11c benchmark (commented out) |
| `bench-pb` | — | PB geometry benchmark |
| `bench-ring` | — | Ring mesh benchmark |
