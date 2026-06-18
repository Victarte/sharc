---
title: Installation
linkTitle: Installation
menu:
  main:
    weight: 10
---

ShArc depends on the [Arcane framework](https://github.com/arcaneframework), which provides Alien (linear algebra), Arccore, Arccon, Axlstar, and ArcGeoSim shared libraries.

## Prerequisites

### Ubuntu 22.04

```bash
sudo apt-get -y update
sudo apt install -y apt-utils build-essential iputils-ping python3 \
  git gfortran libglib2.0-dev libxml2-dev libhdf5-openmpi-dev \
  libparmetis-dev libunwind-dev dotnet6 cmake
sudo apt install -y libeigen3-dev libboost-all-dev googletest ninja-build
sudo apt install -y libhypre-dev libpetsc-real-dev
sudo apt install -y swig g++-12 gcc-12 nvidia-cuda-toolkit
```

### Ubuntu 24.04

```bash
sudo apt-get -y update
sudo apt install -y apt-utils build-essential iputils-ping python3 \
  git gfortran libglib2.0-dev libxml2-dev \
  libparmetis-dev libunwind-dev dotnet8 cmake
sudo apt install -y googletest ninja-build swig
sudo apt install -y libeigen3-dev libboost-all-dev libhdf5-openmpi-dev
sudo apt install -y libhypre-dev libpetsc-real-dev
```

## Build Arcane Framework

```bash
git clone https://github.com/arcaneframework/arcane.git
cd arcane
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  -DCMAKE_C_COMPILER=mpicc \
  -DCMAKE_CXX_COMPILER=mpic++
cmake --build build -j$(nproc)
cmake --install build --prefix /usr/local/arcane
```

## Build ShArc

```bash
git clone https://github.com/arcaneframework/sharc.git
cd sharc
git submodule update --init
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  -DARCANEFRAMEWORK_ROOT=/usr/local/arcane \
  -DCMAKE_C_COMPILER=mpicc \
  -DCMAKE_CXX_COMPILER=mpic++
cmake --build build -j$(nproc)
```

## Apptainer

An Apptainer definition file is available in `common/ArcaneInfra/containers/`. Build with:

```bash
apptainer build sharc.sif common/ArcaneInfra/containers/sharc.def
```

## Guix

A Guix package definition is available in `common/ArcaneInfra/guix/`. Install with:

```bash
guix package -f common/ArcaneInfra/guix/sharc.scm
```
