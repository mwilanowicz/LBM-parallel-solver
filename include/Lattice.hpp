# pragma once
#include "Constants.hpp"
#include <array>
#include <vector>
#include <utility>

/*
File: Lattice.hpp
Description: Lattice class definition for Lattice Boltzmann Method simulation.
It utilizes SoA (Structure of Arrays) layout for distribution functions to optimize memory 
access.

Author: Marcel Wilanowicz
Date: 2026-04-08
*/

class Lattice {
private:
    // Distribution functions for each velocity direction (Structure of Arrays)
    std::array<std::vector<double>, LBM::Q> f_old; // Input Buffer (current state of the lattice)
    std::array<std::vector<double>, LBM::Q> f_new; // Output Buffer (result of computation for the next time step)

public:
    // Contructor for allocating 9 + 9 vectors of size (width * height) each (initially zeros)
    Lattice() {
        const size_t total_cells = LBM::Config::width * LBM::Config::height; // Total number of cells in the grid
        for (int i = 0; i < LBM::Q; ++i) {
            f_old[i].resize(total_cells, 0.0); // Initialize f_old with zeros
            f_new[i].resize(total_cells, 0.0); // Initialize f_new with zeros
        }
    }

    // Map (linearize) the index based on x and y coordinates of the lattice (row-major order) 
    // for quick memory access
    inline size_t map_idx(int x, int y) const {
        return static_cast<size_t>(y) * LBM::Config::width + x; 
    }

    // Swap the distribution function arrays for the next iteration
    void swap () {
        std::swap(f_old, f_new); 
    }

    // Test function to check memory allocation
    size_t get_component_size (int q) const {
        return f_old[q].size();
    }

    // Setter for writing access to f_new
    inline void set_f_new(int x, int y, int q, double val) {
        size_t idx = map_idx(x, y);
        f_new[q][idx] = val;
    }

    // Getter for reading access to f_old
    inline double get_f_old(int x, int y, int q) {
        int idx = map_idx(x, y);
        return f_old[q][idx];
    }

    // Initialization of the grid
    void initialize();

    // Getter for reading summed rho-value of current cell (total mass conservation) 
    // [Chen & Doolen, 1998, Eq. 3].
    inline double get_rho(int x, int y) {
        double rho = 0.0;
        size_t idx = map_idx(x, y); // Map 2D coordinates to 1D linear memory index
    
        for (int q = 0; q < LBM::Q; ++q) {
            rho += f_old[q][idx];
        }
        return rho;
    }

    // Getter for reading summed u-value of current cell (total momentum conservation)
    // [Chen & Doolen, 1998, Eq. 3].
    inline std::pair<double, double> get_u(int x, int y) {
        std::pair<double, double> u = {0.0, 0.0};
        double rho = 0.0;
        size_t idx = map_idx(x, y);
        for (int q = 0; q < LBM::Q; ++q) {
            rho += f_old[q][idx];
            u.first += f_old[q][idx] * LBM::ex[q];
            u.second += f_old[q][idx] * LBM::ey[q];
        }
        u.first = u.first / rho;
        u.second = u.second / rho;

        return u;
    }

    // The general form of the equilibrium distribution function [Chen & Doolen, 1998, Eq. 22].
    inline double get_equilibrium(int q, double rho, std::pair<double, double> u) const {
        return LBM::w[q] * rho * (
            1.0 
            + (LBM::ex[q] * u.first + LBM::ey[q] * u.second) / LBM::cs2 
            + ((LBM::ex[q] * u.first + LBM::ey[q] * u.second) 
            * (LBM::ex[q] * u.first + LBM::ey[q] * u.second)) / (2.0 * LBM::cs2 * LBM::cs2) 
            - (u.first * u.first + u.second * u.second) / (2.0 * LBM::cs2)
        );
    }

    // Performs a single discrete time step (delta t) of the LBM evolution.
    void time_step() {
        for (int y = 0; y < LBM::Config::height; ++y) {
            for (int x = 0; x < LBM::Config::width; ++x) {
                size_t idx = map_idx(x, y);

                double rho = 0.0;
                double ux = 0.0;
                double uy = 0.0;

                // Macroscopic (summed up) p,u values of the fluid [Chen & Doolen, 1998, Eq. 3].
                for (int q = 0; q < LBM::Q; ++q) {
                    // Fluid total mass conservation (left equation)
                    rho += f_old[q][idx]; 

                    // Fluid total momentum conservation (right equation)
                    ux += f_old[q][idx] * LBM::ex[q];
                    uy += f_old[q][idx] * LBM::ey[q];
                }

                // We devide by rho to get the actual u value
                std::pair<double, double> u = {ux / rho, uy / rho};

                // LBGK Collision & Streaming step [Chen & Doolen, 1998, Eq. 14].
                for (int q = 0; q < LBM::Q; ++q) {

                    // Right side of the equation
                    double f_eq = get_equilibrium(q, rho, u);
                    double f_coll = f_old[q][idx] - (1.0 / LBM::Config::tau) * (f_old[q][idx] - f_eq);
                    
                    // Left side of the equation (target position). Applied periodic boundary conditions using % operator)
                    int tx = (x + LBM::ex[q] + LBM::Config::width) % LBM::Config::width;
                    int ty = (y + LBM::ey[q] + LBM::Config::height) % LBM::Config::height;

                    // Time Step
                    f_new[q][map_idx(tx, ty)] = f_coll;
                }                
            }
        }
        swap();
    }
};
