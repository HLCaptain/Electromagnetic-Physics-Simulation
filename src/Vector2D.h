#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class Vector2D {
	double x;
	double y;
public:
	Vector2D(double x = 0, double y = 0) : x(x), y(y) { } /// Default Constructor
	~Vector2D() { } /// Default Destructor

	/// Getters, Setters
	void SetX(double nX) { x = nX; }
	void SetY(double nY) { y = nY; }
	double GetX() { return x; }
	double GetY() { return y; }

	
	double GetLength() {
		if (x == 0 && y == 0)
			return 0;
		return sqrt(exp2(abs(x)) + exp2(abs(y))); 
	}
	double GetRotationDeg() { /// Gets the rotation of the vector, gives back a Degree
		if (y == 0) { /// Checking if tangent exists
			if (x >= 0)
				return 90;
			else 
				return -90;
		}
		if ((atan2(y, x)) / M_PI * 180 >= 0) /// Checking cases
			return (atan2(y, x)) / M_PI * 180;
		return 360 + (atan2(y, x)) / M_PI * 180;
	}
	void RotateDeg(double deg) { /// Rotates Vector by Degree
		double NewX = x * cos(deg / 180 * M_PI) - y * sin(deg / 180 * M_PI);
		double NewY = x * sin(deg / 180 * M_PI) + y * cos(deg / 180 * M_PI);
		x = NewX;
		y = NewY;
	}

	///Operator things
	Vector2D operator+(Vector2D& rhs) { return Vector2D(rhs.GetX() + x, rhs.GetY() + y); }
	Vector2D operator/(double& rhs) { return Vector2D(x / rhs, y / rhs); }
	Vector2D operator*(double& rhs) { return Vector2D(x * rhs, y * rhs); }
	void operator+=(Vector2D rhs) {
		x += rhs.GetX();
		y += rhs.GetY();
	}
};

#endif // VECTOR2D_H
