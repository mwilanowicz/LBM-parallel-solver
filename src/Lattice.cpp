#include "Constants.hpp"
#include "Lattice.hpp"
#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

/*
File: Lattice.cpp
Description: Implementation of the Lattice class methods for LBM simulation and data export.
Author: Marcel Wilanowicz
Date: 2026-04-17
*/

void Lattice::initialize() {
    // Row-Major Order traversal for optimization
    for (int y = 0; y < LBM::Config::height; ++y) { // Iterate over rows first for sped up
        for (int x = 0; x < LBM::Config::width; ++x) { // Iterate over columns (elements of current row)
            size_t idx = map_idx(x, y); // Map 2D coordinates to 1D linear memory index
            for (int q = 0; q < LBM::Q; ++q) {
                // Equilibrium state at u=0, p=1 [Chen & Doolen, 1998, Eq. 22].
                f_old[q][idx] = LBM::w[q]; 
                f_new[q][idx] = LBM::w[q];
            }
        }
    }
}

void Lattice::save_vtk(int step) {
    std::filesystem::create_directory("outputs");
    std::string filename = "outputs/output_" + std::to_string(step) + ".vtk";
    std::ofstream file(filename);

    if (file.is_open() == false) {
        std::cerr << "Unable to open a file!" << std::endl;
        return;
    }

    file << "# vtk DataFile Version 3.0\n";
    file << "LBM_LidDrivenCavity_Output\n";
    file << "ASCII\n";
    file << "DATASET STRUCTURED_POINTS\n";
    
    // Dimensions: Width x Height x 1 (for 2D density is always 1)
    file << "DIMENSIONS " << LBM::Config::width << " " << LBM::Config::height << " 1\n";
    file << "ORIGIN 0 0 0\n";
    file << "SPACING 1 1 1\n\n";

    // Velocity vectors
    int num_points = LBM::Config::width * LBM::Config::height;
    file << "POINT_DATA " << num_points << "\n";
    file << "VECTORS velocity double\n";

    for (int y = 0; y < LBM::Config::height; ++y) {
        for (int x = 0; x < LBM::Config::width; ++x) {
            auto [ux, uy] = get_u(x, y);
            file << ux << " " << uy << " 0.0\n";
        }
    }

    // Density scalars
    file << "\nSCALARS density double 1\n";
    file << "LOOKUP_TABLE default\n";
    for (int y = 0; y < LBM::Config::height; ++y) {
        for (int x = 0; x < LBM::Config::width; ++x) {
            file << get_rho(x, y) << "\n";
        }
    }

    file.close();
}

void Lattice::save_csv(int step) {
    std::filesystem::create_directory("outputs");
    std::string filename = "outputs/output_" + std::to_string(step) + ".csv";
    std::ofstream file(filename);

    if (file.is_open() == false) {
        std::cerr << "Unable to open a file!" << std::endl;
        return;
    }

    file << "x,y,ux,uy\n";

    for (int x = 0; x < LBM::Config::width; ++x) {
        for (int y = 0; y < LBM::Config::height; ++y) {
            auto [ux, uy] = get_u(x, y);
            file << x << "," << y << "," << ux << "," << uy << "\n";
        }
    }

    file.close();
}
