---
title: Quick Start
linkTitle: Quick Start
menu:
  main:
    weight: 20
---

This guide walks you through building ShArc and running your first simulation.

## 1. Build ShArc

Follow the [Installation]({{< relref "../installation" >}}) guide to build ShArc and its dependencies.

## 2. Set up a test case

ShArc uses `.arc` files as input (XML-based case definition). A minimal test case:

```xml
<?xml version="1.0"?>
<case code="ShArc" version="1.0">
  <mesh>
    <initialisation>
      <mesh-file>mesh-10x1x1.vt2</mesh-file>
    </initialisation>
  </mesh>
  <modules>
    <module name="ShArc" active="true">
      <post-processing>
        <output-period>1</output-period>
      </post-processing>
    </module>
  </modules>
</case>
```

Reference test cases are available in the `test/` directory.

## 3. Run the simulation

```bash
# With MPI
mpirun -np 4 ./build/src/Main/ShArc.exe test/case.arc

# Sequential
./build/src/Main/ShArc.exe test/case.arc
```

## 4. Visualize results

ShArc outputs results in VTK or VTKHDF format. Open with [ParaView](https://www.paraview.org/):

```bash
paraview output/depouillement/vtkhdfv2/simulation.hdf
```
