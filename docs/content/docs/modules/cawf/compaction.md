---
title: Compaction
linkTitle: Compaction
---

Geomechanical compaction module, defined in `src/CAWF/Compaction/`.

## Features

- Models subsurface compaction under surface loads
- Supports multi-layer geometries
- Uses Alien linear algebra directly
- Can couple with CAWF for evolutive meshes

## Key files

| File | Role |
|------|------|
| `Compaction.axl` | Module descriptor |
| `CompactionModule.cc` | Implementation (~730 lines) |
| `CompactionModule.h` | Header |

## Options

| Option | Description |
|--------|-------------|
| `surface-density` | Surface load density |
| `compressibility` | Material compressibility |
| `layers` | Layer geometry |
| `linear-solver` | Solver configuration |
