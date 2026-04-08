# Parallel Implementation of the Lattice Boltzmann Method (LBM)

## Multi-threaded C++20 Solver for Lid-Driven Cavity Flow

### Overview

The objective of this project is the development of a custom-built computational engine in C++20 utilizing the LBMTau1 model. The project aims to simulate 2D fluid dynamics, specifically focusing on the lid-driven cavity benchmark.

### Project Scope

- **Manual parallelisation:** To implement explicit management of at least 2 threads and domain decomposition using synchronisation mechanisms and data consistency checks.

- **Verification of determinism:** To obtain bit-for-bit identical simulation results between sequential and parallel versions.

- **Numerical validation:** To verify the model’s reliability by comparing the velocity profile with reference data.

- **Convergence analysis:** To monitor residual error to objectively determine the attainment of steady state, following methodology described in the literature.

### Bibliography

* **Chen, S., & Doolen, G. D. (1998).** *Lattice Boltzmann method for fluid flows*.

* **Latt, J. (2007).** *Hydrodynamic limit of lattice Boltzmann equations*. 

* **He, X., & Luo, L. S. (1997).** *A priori derivation of the lattice Boltzmann equation from the continuous Boltzmann equation*. 

* **Guo, Z., Shi, B., & Wang, N. (2000).** *Lattice BGK model for incompressible Navier-Stokes equation*.
