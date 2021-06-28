#ifndef SIMDRAW_H
#define SIMDRAW_H

#include "WindowSDL.h"
#include "Vector2D.h"
#include <iomanip>

/// Drawing a Point to the Graph
void drawPoint(Vector2D P, Window& window, Vector2D Offset = Vector2D(0, 0));

void drawGraphLines(Vector2D pos, Vector2D scale, Window& window, Vector2D Offset = Vector2D(0, 0));





#endif // SIMDRAW_H



