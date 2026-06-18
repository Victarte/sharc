---
title: Development
linkTitle: Development
menu:
  main:
    weight: 60
---

## Contributing

1. Fork the repository on GitHub
2. Create a feature branch from `main`, `dev/cea`, or `dev/ifpen`
3. Make your changes
4. Run tests locally with `ctest`
5. Submit a Pull Request

## Branches

| Branch | Purpose |
|--------|---------|
| `main` | Stable release |
| `dev/cea` | CEA development |
| `dev/ifpen` | IFPEN development |
| `dev/numpex-exadi` | NumeX/ExaDi development |

## Coding Conventions

- **Tab width**: 2 spaces
- **Encoding**: `utf-8-with-signature`
- **License header**: Apache 2.0
- **Naming**: CamelCase classes, camelCase methods
- **C++ standard**: C++20

## CI/CD Pipeline

ShArc uses GitHub Actions with 4 workflow variants:

| Workflow | Toolchain | OS |
|----------|-----------|----|
| `ifpen_el8_foss-2021b` | OpenMPI/GCC | EL8 |
| `ifpen_el8_gimkl-2021b` | Intel MPI | EL8 |
| `ifpen_el9_foss-2021b` | OpenMPI/GCC | EL9 |
| `ifpen_el9_gimkl-2021b` | Intel MPI | EL9 |

### Pipeline stages

1. `arcane-install`: Build Arcane framework
2. `sharc-install`: Build ShArc
3. `sharc-test`: Run `ctest`

### Triggers

Push/PR to `main`, `dev/cea`, `dev/ifpen`, `dev/ci_ifpen`, `dev/numpex-exadi`.

### Docs

Documentation is built with Hugo and docsy. The built site is deployed to GitHub Pages from the `gh-pages` branch.
