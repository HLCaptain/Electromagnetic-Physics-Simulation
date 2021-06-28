#include <iostream>
#include <SDL.h>

#include "Simulation.h"

void GetInput(double& b, double& q, double& m, double& t) {
	std::cout << "Strength of the Magnetic Field (T) = ";
	std::cin >> b;

	std::cout << "Charge of the Particle (C) = ";
	std::cin >> q;

	std::cout << "Mass of the Particle (Kg) = ";
	std::cin >> m;

	std::cout << "Duration of the Simulation (s) = ";
	std::cin >> t;
}


int main(int argc, char **argv) { /// Arguments needed for SDL2

	double b; /// Magnetic field strength
	double q; /// Charge of particle
	double m; /// Mass of particle
	double t; /// Duration of the Simulation
	double f = 1000; /// Number of Ticks in 1 second

	std::cout << "Basic informations:" << std::endl;
	std::cout << "Gravity (m/(s^2)) = " << 9.81 << std::endl;
	std::cout << "Frequency (Hz) = " << f << std::endl << std::endl;
	GetInput(b, q, m, t);

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cerr << "Cannot Initialize SDL :(" << std::endl;
	}
	else {
		std::cout << "Simulation Running..." << std::endl;
		runSim(b, q, m, t, f);
	}

	return 0;
}