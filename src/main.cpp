#include "Constants.hpp"
#include "Lattice.hpp"
#include <iostream>
#include <iomanip>
#include <ios>

/*
File: main.cpp
Description: Entry point for D2Q9 LBM simulation
Author: Marcel Wilanowicz
Date: 2026-04-17
*/

int main() {
    std::cout << "Simulation width: " << LBM::Config::width << std::endl;
    std::cout << "Simulation height: " << LBM::Config::height << std::endl;
    std::cout << "Relaxation time (tau): " << LBM::Config::tau << std::endl;
    std::cout << "Lid Velocity: " << LBM::Config::u_lid << std::endl;
    std::cout << "Number of time steps: " << LBM::Config::max_time_steps << std::endl;

    Lattice simulation;

    simulation.initialize();

    // Initial mass
    double initial_mass = 0.0; 
    for (int y = 0; y < LBM::Config::height; ++y) {
        for (int x = 0; x < LBM::Config::width; ++x) {
            initial_mass += simulation.get_rho(x, y);
        }
    }
    std::cout << "\nInitial Mass: " << initial_mass << std::endl;

    for (int t = 1; t <= LBM::Config::max_time_steps; ++t) {
        simulation.time_step();

        // Mass monitoring (after 1000 steps each)
        if (t % 1000 == 0) {
            double current_mass = 0.0;
            for (int y = 0; y < LBM::Config::height; ++y) {
                for (int x = 0; x < LBM::Config::width; ++x) {
                    current_mass += simulation.get_rho(x, y);
                }
            }

            // Computing relative error
            double rel_error = std::abs(current_mass - initial_mass) / initial_mass;

            std::cout << "Step: " << std::setw(6) << t 
            << " | Mass: " << std::fixed << std::setprecision(8) << current_mass 
            << " | Rel. Error: " << std::scientific << std::setprecision(3) << rel_error
            << "\n";
        }
    }

    // Export simulation data
    simulation.save_vtk(LBM::Config::max_time_steps);
    simulation.save_csv(LBM::Config::max_time_steps);

    return 0;
}