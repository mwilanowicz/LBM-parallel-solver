import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
import re

''' 
File: benchmark.py
Description: Validation and visualization script for Lid-Driven Cavity LBM simulation.
Normalizes simulation data and compares centerline velocity profiles (u_x, u_y) against 
the Ghia et al. (1982) benchmark.

Author: Marcel Wilanowicz
Date: 2026-04-17
'''

# Config
H = 100
W = 100
U_LID = 0.1

def extract_step(p):
    match = re.search(r'output_(\d+)', p.name)
    if match:
        return int(match.group(1))
    else:
        return 0

def get_latest_output():
    path = Path("../outputs")
    files = list(path.glob("output_*.csv"))

    # If didn't find files
    if not files:
        return None, None
        
    # Get file with largest step value
    max_step_file = max(files, key=extract_step)
    step_num = extract_step(max_step_file)

    return max_step_file, step_num

def validate():
    target_file, step = get_latest_output()

    if not target_file:
        print("Error: Not found any files in 'outputs' directory.")
        return
    
    print(f"Reading data from: {target_file} (Step: {step})")

    # Reading data from simulation
    data = pd.read_csv(target_file)

    mid_x = (W - 1) // 2
    mid_y = (H - 1) // 2

    # Vertical profile for ux comparison
    v_line = data[data['x'] == mid_x].sort_values('y')

    # Horizontal profile for uy comparison
    h_line = data[data['y'] == mid_y].sort_values('x')

    # Normalizing the data (velocity profiles and dimension of the grid): 
    # we want dimensionless values for correct benchmark [Chen & Doolen, 1998, p.342].
    ux_norm = v_line['ux'] / U_LID
    y_norm = v_line['y'] / (H - 1)
    uy_norm = h_line['uy'] / U_LID
    x_norm = h_line['x'] / (W - 1)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

    # ------------ 1. Plotting vertical profile: ux(y) ------------

    # Simulation data
    ax1.plot(ux_norm, y_norm, 'b-', label='LBM Simulation Benchmark', linewidth=2)

    # Ghia data
    ax1.plot(ghia_ux, ghia_y, 'ro', label='Ghia et al. (1982) Reference', markersize=6)

    ax1.set_title(f"Vertical Profile $u_x$ (Step: {step})")
    ax1.set_xlabel("$u_x / u_{lid}$")
    ax1.set_ylabel("$y / H$")
    ax1.set_xlim([-1.0, 1.0])
    ax1.set_ylim([-0.1, 1.1])
    ax1.grid(True, which='both', linestyle='--', alpha=0.5)
    ax1.legend()

    # ------------ 2. Plotting horizontal profile: uy(x) ------------

    # Simulation data
    ax2.plot(uy_norm, x_norm, 'b-', label='LBM Simulation Benchmark', linewidth=2)

    # Ghia data
    ax2.plot(ghia_uy, ghia_x, 'ro', label='Ghia et al. (1982) Reference', markersize=6)

    ax2.set_title(f"Horizontal Profile $u_y$ (Step: {step})")
    ax2.set_xlabel("$u_y / u_{lid}$")
    ax2.set_ylabel("$x / W$")
    ax2.set_xlim([-1.0, 1.0])
    ax2.set_ylim([-0.1, 1.1])
    ax2.grid(True, which='both', linestyle='--', alpha=0.5)
    ax2.legend()

    plt.tight_layout()
    plt.show()

''' Results for u-velocity along Vertical Line through Geometric Center of Cavity 
[Ghia et al. p.398, Table I]'''
ghia_y =  [0.0000, 0.0547, 0.0625, 0.0703, 0.1016, 0.1719, 0.2813, 0.4531, 
           0.5000, 0.6172, 0.7344, 0.8516, 0.9531, 0.9609, 0.9688, 0.9766, 1.0000]

ghia_ux = [0.00000, -0.03717, -0.04192, -0.04775, -0.06434, -0.10150, -0.15662, -0.21090, 
           -0.20581, -0.14098, -0.01447, 0.17527, 0.55892, 0.61756, 0.68439, 0.75837, 1.00000]

''' Results for u-velocity along Vertical Line through Geometric Center of Cavity 
[Ghia et al. p.399, Table II]'''
ghia_x = [0.0000, 0.0625, 0.0703, 0.0781, 0.0938, 0.1563, 0.2266, 0.2344, 0.5000, 
          0.8047, 0.8594, 0.9063, 0.9453, 0.9531, 0.9609, 0.9688, 1.0000]

ghia_uy = [0.00000, 0.09233, 0.10091, 0.10890, 0.12317, 0.16077, 0.17507, 0.17527, 
           0.05454, -0.24533, -0.22445, -0.16914, -0.10313, -0.08864, -0.07391, -0.05906, 0.00000]

if __name__ == "__main__":
    validate()
