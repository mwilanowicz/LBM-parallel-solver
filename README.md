# Parallel Implementation of the Lattice Boltzmann Method (LBM)

## Multi-threaded C++20 Solver for Lid-Driven Cavity Flow

### Overview

The objective of this project is the development of a custom-built computational engine in C++20 utilizing the LBM D2Q9 model. The project aims to simulate 2D fluid dynamics, specifically focusing on the lid-driven cavity benchmark.

### Project Scope

- **Manual parallelisation:** To implement explicit management of at least 2 threads and domain decomposition using synchronisation mechanisms and data consistency checks.

- **Verification of determinism:** To obtain bit-for-bit identical simulation results between sequential and parallel versions.

- **Numerical validation:** To verify the model’s reliability by comparing the velocity profile with reference data.

- **Convergence analysis:** To monitor residual error to objectively determine the attainment of steady state, following methodology described in the literature.

---

### Development Timeline

* **Stage 1 - Report I (26.03): Baseline Sequential Solver**
    * Design of the core D2Q9 solver architecture in C++20.
    * Execution of a physically correct single-threaded simulation.
    * Algorithm verification via mass conservation monitoring.
* **Stage 2 - Report II (16.04): Physical Validation & Boundary Conditions**
    * Implementation of "bounce-back" boundary conditions for walls.
    * Simulation of the Lid-Driven Cavity (LDC) test case.
    * Comparison of velocity profiles with reference literature data.
* **Stage 3 - Report III (07.05): Parallelism & Data Determinism**
    * Domain decomposition for two execution units (threads).
    * Implementation of synchronisation mechanisms to ensure data consistency.
    * Verification of determinism (sequential vs. parallel output identity).
* **Stage 4 - Report IV (21.05): Prototype Performance Analysis**
    * Execution time benchmarks for various grid sizes.
    * Evaluation of speedup achieved during the transition to multi-threading.
    * Formulation of conclusions regarding performance and future development.
* **Stage 5 - Finalization (28.05): Final Documentation**
    * Preparation of the final report summarizing research and programming results.
* **Stage 6 - Completion (11.06): Safety Buffer**
    * Time reserved for potential error corrections identified during final testing.

---

### Risk Analysis & Mitigation Strategies

#### 1. Numerical and Physical Risks
* **Computational Instability (Stage 2):**
    * **Risk:** Potential loss of simulation stability (numerical divergence) when attempting to resolve high-dynamics flows.
    * **Mitigation:** Continuous monitoring of input parameters and enforcing upper limits on maximum velocities within the system.
* **Mass Conservation Errors (Stage 2):**
    * **Risk:** Faulty boundary condition implementation resulting in unnatural mass increase or decrease.
    * **Mitigation:** Systematic verification of the total system density at every computational step.

#### 2. Implementation and Technical Risks
* **Parallel Processing Issues (Stage 3):**
    * **Risk:** Data synchronisation errors during domain decomposition leading to results diverging from the baseline version.
    * **Mitigation:** Deployment of synchronisation barriers and conducting rigorous comparison tests with the sequential version.
* **Low Code Efficiency (Stage 4):**
    * **Risk:** Unsatisfactory speedup after switching to two threads due to memory access latencies.
    * **Mitigation:** Utilisation of optimised data structures (Structure of Arrays - SoA) and hardware resource load analysis.

#### 3. Schedule Risks
* **Reference Data Divergence (Stages 2 & 4):**
    * **Risk:** Identification of significant differences between obtained results and literature data in the final project phase.
    * **Mitigation:** Inclusion of a dedicated time buffer (Stage 6) for model recalibration and additional physical accuracy verification.

---

### Bibliography

---

#### Journal Articles
* **Chen, S., & Doolen, G. D. (1998).** Lattice Boltzmann method for fluid flows. *Annual Review of Fluid Mechanics*, 30, 329–364.
* **Ghia, U., Ghia, K. N., & Shin, C. T. (1982).** High-Re solutions for incompressible flow using the Navier-Stokes equations and a multigrid method. *Journal of Computational Physics*, 48(3), 387–411.
* **He, X., & Luo, L. S. (1997).** A priori derivation of the lattice Boltzmann equation from the continuous Boltzmann equation. *Physical Review E*, 55(6), R6333–R6336.

---

#### Books
* **Mohamad, A. A. (2019).** *Lattice Boltzmann Method: Fundamentals and Engineering Applications with Computer Codes* (2nd ed.). Springer Nature.
* **White, F. M. (2011).** *Fluid Mechanics* (7th ed.). McGraw-Hill.
