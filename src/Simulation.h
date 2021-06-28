#ifndef SIMULATION_H
#define SIMULATION_H

#include <math.h>

#include "SimDraw.h"
#include "WindowSDL.h"
#include "Vector2D.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <sstream>

/// Draws the points
void functionDraw(std::vector<Vector2D>& Pos, std::string WindowTitle = "Fizika P11 Szorgalmi");

/// Runs the simulation
void runSim(double b, double q, double m, double time, double frequency);

/// Transforms a point by 2 vectors
Vector2D TransformVector(Vector2D pos, Vector2D scale, Vector2D vec, Vector2D Offset = Vector2D(0, 0));

/// Saves Simulation to a .dat file
void SaveSim(std::vector<Vector2D> Pos);

/// Creates the file's name with the actual date
std::string CreateFileName(std::string FileName);





#endif // SIMULATION_H