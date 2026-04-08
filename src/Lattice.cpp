#include "Constants.hpp"
#include "Lattice.hpp"

/*
File: Lattice.cpp
Description: Implementation of the Lattice class methods for LBM simulation.
Author: Marcel Wilanowicz
Date: 2026-04-08
*/

void Lattice::initialize() {
    // Row-Major Order traversal for optimization
    for (int y = 0; y < LBM::Config::height; ++y) { // Iterate over rows first for sped up
        for (int x = 0; x < LBM::Config::width; ++x) { // Iterate over columns (elements of current row)
            size_t idx = map_idx(x, y); // Map 2D coordinates to 1D linear memory index
            for (int q = 0; q < LBM::Q; ++q) {
                // Equilibrium state at u=0, p=1 [Chen & Doolen, 1998, Eq. 22].
                f_old[q][idx] = LBM::w[q]; 
            }
        }
    }
}
