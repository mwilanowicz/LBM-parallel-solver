#pragma once
#include <array>

/*
File: Constants.hpp
Description: D2Q9 model constants and simulation parameters for Lattice Boltzmann Method.
Author: Marcel Wilanowicz
Date: 2026-04-08
*/

namespace LBM {
    // --------------- D2Q9 model constants (Compile-time) --------------- 
    // Discrete velocity vectors (e_i) for D2Q9 model [He & Luo, 1997, Eq. 17].
    inline constexpr int Q = 9; // Number of discrete velocity and distribution function directions
    inline constexpr std::array<int, Q> ex = {0, 1, 0, -1, 0, 1, -1, -1, 1}; // x-components of velocity vectors (ex_i)
    inline constexpr std::array<int, Q> ey = {0, 0, 1, 0, -1, 1, 1, -1, -1}; // y-components of velocity vectors (ey_i)
    /* Vortices are ordered as follows:

        6  2  5
        3  0  1
        7  4  8
    
        where:

        {0, 0}, // Rest vertex
        {1, 0}, // Right vertex
        {0, 1}, // Up vertex
        {-1, 0}, // Left vertex
        {0, -1}, // Down vertex
        {1, 1}, // Up-Right vertex
        {-1, 1}, // Up-Left vertex
        {-1, -1}, // Down-Left vertex
        {1, -1} // Down-Right vertex
    */

    // Weight scalars (w_i) as function distribution coefficients [He & Luo, 1997, Eq. 15]
    inline constexpr std::array<double, Q> w = { 
        4.0 / 9.0, // Rest vertex
        1.0 / 9.0, // Right vertex
        1.0 / 9.0, // Up vertex
        1.0 / 9.0, // Left vertex
        1.0 / 9.0, // Down vertex
        1.0 / 36.0, // Up-Right vertex
        1.0 / 36.0, // Up-Left vertex
        1.0 / 36.0, // Down-Left vertex
        1.0 / 36.0 // Down-Right vertex
    };

    // Speed of sound (squared) in the lattice (cs^2 = c^2 / 3, where c=1) [He & Luo, 1997, R6334]
    inline constexpr double cs2 = 1.0 / 3.0; 

    // ---------------  Simulation parameters (Compile-time) ---------------
    struct Config {
        
        // Kinematic viscosity: ν = (2τ − 1)/6, therefore τ must be > 0.5 for stability [Chen & Doolen, 1998, p.335].
        static constexpr double tau = 0.6; 

        static constexpr int width = 200; // Width of the simulation grid
        static constexpr int height = 100; // Height of the simulation grid
        static constexpr int max_time_steps = 10000; // Number of simulation time steps
    };
}
