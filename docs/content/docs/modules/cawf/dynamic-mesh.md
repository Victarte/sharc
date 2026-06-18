---
title: Dynamic Mesh Management
linkTitle: Dynamic Mesh Management
---

Dynamic mesh management service, defined in `src/CAWF/DynamicMeshMng/`.

## Features

- Dynamic mesh adaptation and evolution
- Multiple mesh format support
- Event-driven mesh operations
- Optional preCICE coupling for multi-physics

## Key files

| File | Role |
|------|------|
| `DynamicMeshMng.axl` | Service descriptor |
| `DynamicMeshMngService.cc` | Implementation |
| `IDynamicMeshMng.h` | Service interface |

## Options

| Option | Description |
|--------|-------------|
| `mesh` | Input mesh file |
| `format` | Mesh format |
| `event` | Mesh operation events |
