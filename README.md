# IMS

`make` přeloží program
`make run` spustí 300 kroků (100 dní) simulace šíření ropy v Mexickém zálivu
výstup se ukládá do složky `out/` v podobě fotek ve formátu .ppn
pokud chcete spustit s grafickým oknem musíte si nainstalovat knihovnu `libsfml-dev` a v souboru Makefile zakomentovat řádek `CXXFLAGS += -DREMOVE_SFML` a odkomentovat řádek `LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system`

# IMS - Oil Spill Simulation

Authors: Matěj Vrba, Ondřej Bahounek  
Date: November 2023

## Overview

This project simulates the spread of an oil spill in the ocean using a cellular automaton model. The simulation is inspired by the Deepwater Horizon disaster of April 2010, one of the largest ecological catastrophes in modern history.

The model helps explore how various early-response strategies—such as the use of containment booms and oil skimmers—can limit environmental damage, especially the extent of oil reaching the coastline.

## Key Features

- 2D cellular automaton simulating horizontal diffusion of oil
- Realistic modeling of ocean currents
- Visual output using SFML
- Input maps for coastline and current directions

## Technologies Used

- C++ (standard library)
- SFML (for visualization)
- PNG textures (for input maps)

## Input Data

The simulation loads two PNG textures of the same size:
- **Coastline map**: Indicates land and sea areas
- **Ocean currents map**: Encodes the direction and strength of currents

## Model Details

The model simulates oil dispersion using:
- **Horizontal diffusion**: Based on concentration differences between neighboring cells
- **Ocean currents**: Oil is pushed in the direction and strength of local currents

Vertical factors such as evaporation and diffusion were ignored for simplicity, as oil mostly remains on the surface.

Wind was excluded due to its lower impact and the lack of reliable wind data.

For more detailed documentation and mathematical modeling, see the `dokumentace.pdf`

![sim](img.png)

## Running the Project

Run `make` to compile the program.

Run `make run` to execute 300 simulation steps (100 days) of oil spread in the Gulf of Mexico.

Output frames are saved in the `out/` folder as .ppn images.

If you want to run the simulation with a graphical window:
- Install the libsfml-dev library.
- In the Makefile, comment out the line:
    `CXXFLAGS += -DREMOVE_SFML`
and uncomment the line:
`LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system`