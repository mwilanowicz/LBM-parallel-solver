# Parallel Implementation of the Lattice Boltzmann Method (LBM)

## Overview

This project features a custom-built, computational engine in C++ utilizing the Lattice Boltzmann Method (LBM) in D2Q9 model. The solver simulates 2D fluid dynamics, specifically the classic Lid-Driven Cavity problem. 

The implementation has been scaled from a sequential baseline to a memory-distributed parallel architecture using **MPI (Message Passing Interface)**.

## Project Structure

```text
.
├── include
│   ├── Constants.hpp
│   └── Lattice.hpp
├── Makefile
├── README.md
├── schedule.md
├── src
│   ├── Lattice.cpp
│   ├── main_par.cpp
│   └── main_seq.cpp
└── test
    ├── assessment_100x100.ipynb
    ├── assessment_256x256.ipynb
    ├── assessment_512x512.ipynb
    └── test_lattice.cpp
```

## Features & Project Scope

* **Distributed Domain Decomposition:** 1D spatial partitioning into horizontal bands with halo exchange (`MPI_Sendrecv` / `MPI_Barrier` coordination).

* **Physical Validation:** Verified fluid dynamics against the established data (Ghia et al.) using centerline velocity profiles ($u_x, u_y$).

* **Parallel Bitwise Verification:** Spatial node-by-node identity ensuring bitwise reproducibility between sequential and parallel executions.

* **Scalability Benchmarking:** Performance tracking across various grid sizes ($100\times100$, $256\times256$, $512\times512$) for speedup, efficiency and overhead analysis.

## Quick Start

### Requirements

* MPI Library (OpenMPI)

* C++17/20 compliant compiler (GCC / Clang)

### Compilation & Execution

All commands must be run from the project root directory.

To compile and run the simulation, run:

```bash
# Compile the parallel solver
make main_par

# Run simulation using e.g 4 MPI processes
mpirun -np 4 ./main_par

# (Optionally) compile and run pure sequential version
make main_seq

```

---

## Literature

### Journal Articles

* **Chen, S., & Doolen, G. D. (1998).** Lattice Boltzmann method for fluid flows. *Annual Review of Fluid Mechanics*, 30, 329–364.
* **Ghia, U., Ghia, K. N., & Shin, C. T. (1982).** High-Re solutions for incompressible flow using the Navier-Stokes equations and a multigrid method. *Journal of Computational Physics*, 48(3), 387–411.
* **He, X., & Luo, L. S. (1997).** A priori derivation of the lattice Boltzmann equation from the continuous Boltzmann equation. *Physical Review E*, 55(6), R6333–R6336.

### Books

* **Krüger, T., Kusumaatmaja, H., Kuzmin, A., Shardt, O., Silva, G., & Viggen, E. M. (2017).** *The Lattice Boltzmann Method: Principles and Practice*. Springer International Publishing.
* **Mohamad, A. A. (2019).** *Lattice Boltzmann Method: Fundamentals and Engineering Applications with Computer Codes* (2nd ed.). Springer Nature.
