#include "SimDraw.h"

void drawPoint(Vector2D P, Window& window, Vector2D Offset) {
	SDL_Rect pixel;
	pixel.x = P.GetX() - Offset.GetX();
	pixel.y = P.GetY() + Offset.GetY();
	pixel.w = 2;
	pixel.h = 2;
	SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(window.getRenderer(), &pixel);
	//SDL_RenderPresent(window.getRenderer());
}

void drawGraphLines(Vector2D pos, Vector2D scale, Window& window, Vector2D Offset) {
	SDL_SetRenderDrawColor(window.getRenderer(), 180, 180, 180, SDL_ALPHA_OPAQUE);

	scale.SetX(scale.GetX() * scale.GetX());
	scale.SetY(scale.GetY() * scale.GetY()* (-1));

	double GridSize = 10; /// Grid's size in pixel
	double vNum = window.getWidth() / 2 / GridSize / scale.GetY() * (-1); // Vertical Number

	int vDiv = 0; // Vertical Divide
	int vMul = 0; // Vertical Multiply
	int minThreshold = 4; // Minimum gridline number threshold
	int maxThreshold = 40; // Maximum gridline number threshold
	if (vNum > maxThreshold || vNum < minThreshold) {
		while(vNum < minThreshold || vNum > maxThreshold) {
			if (vNum > maxThreshold) {
				vNum /= 10;
				vDiv++;
			}
			if (vNum < minThreshold) {
				vNum *= 10;
				vMul++;
			}
		}
	}
	double xSpace = GridSize; // Space left in the x axis
	for (int i = 0; i < vDiv; i++) {
		xSpace = xSpace * 10;
	}
	for (int i = 0; i < vMul; i++) {
		xSpace = xSpace / 10;
	}

	/// Setting offsetX
	double finalOffsetX = Offset.GetX();
	while (abs(finalOffsetX) >= abs(xSpace * scale.GetY())) {
		if(finalOffsetX < 0)
			finalOffsetX += abs(xSpace * scale.GetY());
		else
			finalOffsetX -= abs(xSpace * scale.GetY());
	}

	/// Rendering Vertical Gridlines
	for (int i = -2; i < vNum + 2; i++) {
		double vx1 = pos.GetX() + i * xSpace * scale.GetY() - finalOffsetX;
		double vx2 = pos.GetX() + i * xSpace * scale.GetY() - finalOffsetX;
		double vy1 = 0;
		double vy2 = window.getHeight();
		SDL_RenderDrawLine(window.getRenderer(), vx1, vy1, vx2, vy2);
		vx1 = pos.GetX() - i * xSpace * scale.GetY() - finalOffsetX;
		vx2 = pos.GetX() - i * xSpace * scale.GetY() - finalOffsetX;
		SDL_RenderDrawLine(window.getRenderer(), vx1, vy1, vx2, vy2);
	}

	double hNum = window.getHeight() / xSpace; // Horizontal Number

	double ySpace = xSpace; // Space left in the y axis

	/// Setting offsetY
	double finalOffsetY = Offset.GetY();
	while (abs(finalOffsetY) >= abs(ySpace * scale.GetX())) {
		if (finalOffsetY < 0)
			finalOffsetY += abs(ySpace * scale.GetX());
		else
			finalOffsetY -= abs(ySpace * scale.GetX());
	}

	/// Rendering Horizontal Gridlines
	for (int i = -2; i < hNum + 2; i++) {
		double hx1 = 0;
		double hx2 = window.getWidth();
		double hy1 = pos.GetY() + i * ySpace * scale.GetX() + finalOffsetY;
		double hy2 = pos.GetY() + i * ySpace * scale.GetX() + finalOffsetY;
		SDL_RenderDrawLine(window.getRenderer(), hx1, hy1, hx2, hy2);
		hy1 = pos.GetY() - i * ySpace * scale.GetX() + finalOffsetY;
		hy2 = pos.GetY() - i * ySpace * scale.GetX() + finalOffsetY;
		SDL_RenderDrawLine(window.getRenderer(), hx1, hy1, hx2, hy2);
	}

	std::cout << std::setprecision(6) << "Grid Space:\nX = " << xSpace << "m (" << xSpace * scale.GetX() << " pixel)\nY = " << ySpace << "m (" << ySpace * scale.GetY() * (-1) << " pixel)" << std::endl;
	std::cout << "Grid Offset:\nX = " << Offset.GetX() << " pixel\nY = " << Offset.GetY() << " pixel" << std::endl << std::endl;
}