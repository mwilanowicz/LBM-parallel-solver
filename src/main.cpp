#include "Constants.hpp"
#include "Lattice.hpp"
#include <iostream>
#include <iomanip>

/*
File: main.cpp
Description: Entry point for D2Q9 LBM simulation
Author: Marcel Wilanowicz
Date: 2026-04-08
*/

int main() {
    std::cout << "Simulation width: " << LBM::Config::width << std::endl;
    std::cout << "Simulation height: " << LBM::Config::height << std::endl;
    std::cout << "Relaxation time (tau): " << LBM::Config::tau << std::endl;
    std::cout << "Number of time steps: " << LBM::Config::max_time_steps << std::endl;

    Lattice simulation;

    simulation.initialize();

    double m0 = 0.0;
    for (int y = 0; y < LBM::Config::height; ++y) {
        for (int x = 0; x < LBM::Config::width; ++x) {
            m0 += simulation.get_rho(x, y);
        }
    }
    std::cout << "Initial Mass: " << m0 << std::endl;

    for (int t = 1; t <= 1000; ++t) {
        simulation.time_step();

        if (t % 100 == 0) {
            double m = 0.0;
            for (int y = 0; y < LBM::Config::height; ++y) {
                for (int x = 0; x < LBM::Config::width; ++x) {
                    m += simulation.get_rho(x, y);
                }
            }
            std::cout << "Step: " << t << " | Mass: " << m << "\n";
        }
    }

    return 0;
}