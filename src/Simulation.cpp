#include "Simulation.h"

/**
 * functionDraw
 * @brief Draws out the points onto the window.
 * @param Pos points to draw out.
 * @param WindowTitle the title of the window.
 */
void functionDraw(std::vector<Vector2D>& Pos, std::string WindowTitle) {
	Window window(WindowTitle);

	Vector2D TPos(window.getWidth() / 2, window.getHeight() / 2); /// Origin of the Graph (Position transform)
	Vector2D TScale(10, -10); /// Scales by y and x from the Origin
	Vector2D TOffset(0, 0);

	drawGraphLines(TPos, TScale, window, TOffset);
	for (int i = 0; i < Pos.size(); i++) {
		drawPoint(TransformVector(TPos, TScale, Pos[i], TOffset), window);
	}

	std::cout << "Simulation Done!" << std::endl;

	while (!window.isClosed()) {
		SDL_RenderPresent(window.getRenderer());
		//window.pollEvents();

		/// Zooming in and out
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEWHEEL:
				if (event.wheel.y > 0) { /// Zooming in
					TScale.SetX(TScale.GetX() + 5);
					TScale.SetY(TScale.GetY() - 5);
				}
				else if (event.wheel.y < 0) { /// Zooming out
					if (TScale.GetX() > 5 && TScale.GetY() < -5) {
						TScale.SetX(TScale.GetX() - 5);
						TScale.SetY(TScale.GetY() + 5);
					}
				}
				/// Draw it
				window.clear();
				drawGraphLines(TPos, TScale, window, TOffset);
				for (int i = 0; i < Pos.size(); i++) {
					drawPoint(TransformVector(TPos, TScale, Pos[i], TOffset), window);
				}
				break;
			case SDL_KEYDOWN: /// Handling keydown events
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					TOffset.SetY(TOffset.GetY() + 10);
					break;
				case SDLK_DOWN:
					TOffset.SetY(TOffset.GetY() - 10);
					break;
				case SDLK_RIGHT:
					TOffset.SetX(TOffset.GetX() + 10);
					break;
				case SDLK_LEFT:
					TOffset.SetX(TOffset.GetX() - 10);
					break;
				}
				/// Draw it
				window.clear();
				drawGraphLines(TPos, TScale, window, TOffset);
				for (int i = 0; i < Pos.size(); i++) {
					drawPoint(TransformVector(TPos, TScale, Pos[i], TOffset), window);
				}
				break;
			case SDL_QUIT:
				window.close();
				break;
			}
				
		}
	}
	window.clear();
}

/**
 * runSim
 * @brief With given attributes, computes the points of projection of the body. Also draws it onto a window and saves it onto a .dat file.
 * @param b B is the magnetic field in Tesla.
 * @param q is the electric charge of the body (particle) in Coulomb.
 * @param m is the mass of the body.
 * @param time duration of the simulation in seconds.
 * @param frequency how many times in a second should the simulation tick.
 */
void runSim(double b, double q, double m, double time, double frequency) {
	Vector2D MagneticField(b, 0); /// Magnetic Field's Vector in Tesla
	Vector2D Lorentz(0, 0); /// Lorentz Force in Newton
	Vector2D Gravity(0, -9.81 * m); /// Gravitational force (with 9.81 m/s^2 acceleration) in Newton
	Vector2D CurrentNetForce(0, 0); /// Current Net Force in Newton
	Vector2D CurrentSpeed(0, 0); /// Speed of the Particle in m/s
	Vector2D CurrentAccel(0, 0); /// Acceleration of the Particle in m/s^2
	Vector2D OldAccel(0, 0); /// Previous Acceleration, needed for calculating the speed
	Vector2D CurrentPos(0, 0); /// Starting Position
	std::vector<Vector2D> Pos; /// Positions of the Particle

	Pos.push_back(CurrentPos);

	for (int i = 0; i < time * frequency; i++) {

		/// Calculating the Net Force and Lorentz Force
		/// Lorentz's Force Length is calculated, and then rotated by the Speedvector
		Lorentz = Vector2D(q * b * CurrentSpeed.GetLength(), 0);
		Lorentz.RotateDeg(CurrentSpeed.GetRotationDeg() - 270);
		CurrentNetForce = Gravity + Lorentz; /// A simple vector addition

		/// Calculating Velocity and Acceleration
		double two = 2;
		OldAccel = CurrentAccel;
		CurrentAccel = CurrentNetForce / m;
		CurrentSpeed += (OldAccel+CurrentAccel) / frequency / two;

		/// Calculating Position
		CurrentPos += CurrentSpeed / frequency;
		Pos.push_back(CurrentPos);
	}
	SaveSim(Pos); /// Saves the Simulation to "Simulation.dat"
	functionDraw(Pos, CreateFileName("Fizika_P11_Sim ")); /// Draws the Simulation to a Window
}

/**
 * TransformVector
 * @brief Transforms a vector with (scale, position offset) while it also can be offseted afterwards the transform.
 * @param pos original position of the point.
 * @param scale scale.
 * @param vec vector to do the position offset with.
 * @param Offset offset afterwards the transition.
 * @return transitioned and offseted point.
 */
Vector2D TransformVector(Vector2D pos, Vector2D scale, Vector2D vec, Vector2D Offset) {
	scale.SetX(scale.GetX() * scale.GetX());
	scale.SetY(scale.GetY() * scale.GetY() * (-1));
	return Vector2D(vec.GetX() * scale.GetX() - Offset.GetX() + pos.GetX(), vec.GetY() * scale.GetY() + Offset.GetY() + pos.GetY());
}

/**
 * CreateFileName
 * @brief Creates a file's name with the date and time in it to make it unique.
 * @param Title first name of the file.
 * @return final (probably unique) file name.
 */
std::string CreateFileName(std::string Title) {
	time_t now = time(0);
	tm TimeNow;
	localtime_s(&TimeNow, &now);
	std::stringstream FileNameStream;
	FileNameStream << Title;
	FileNameStream << TimeNow.tm_year + 1900;
	FileNameStream << "_";
	FileNameStream << TimeNow.tm_mon;
	FileNameStream << "_";
	FileNameStream << TimeNow.tm_mday;
	FileNameStream << " ";
	FileNameStream << TimeNow.tm_hour;
	FileNameStream << "_";
	FileNameStream << TimeNow.tm_min;
	FileNameStream << "_";
	FileNameStream << TimeNow.tm_sec;
	std::string FileNameString = FileNameStream.str();
	return FileNameString;
}

/**
 * SaveSim
 * @brief Saves the simulation onto a .dat file with a unique name.
 * @param Pos data of the simulated points.
 */
void SaveSim(std::vector<Vector2D> Pos) {
	std::string FileName(CreateFileName("Fizika_P11_Sim "));
	std::ofstream f;
	std::cout << FileName << std::endl;
	f.open(FileName + ".dat");
	int i = 0;
	while (i != Pos.size()) {
		f << Pos[i].GetX() << " " << Pos[i].GetY() << std::endl;
		i++;
	}
	f.close();
}