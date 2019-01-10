#include "space_ship.h"
#include "math_class.h"

void space_ship::pitch(float degrees)
{
	math_class::rotate_x(matrix_, degrees, yaw_, roll_);
	add_degrees(pitch_, degrees);
}

void space_ship::yaw(float degrees)
{
	math_class::rotate_y(matrix_, degrees, pitch_, roll_);
	add_degrees(yaw_, degrees);
}

void space_ship::roll(float degrees)
{
	math_class::rotate_z(matrix_, degrees, pitch_, yaw_);
	add_degrees(roll_, degrees);
}

void space_ship::add_degrees(float& action, float degrees)
{
	if (action + degrees > 360)
	{
		const float rest = action + degrees - 360;
		action = rest;
	}
	else if (action + degrees < 0)
	{
		const float rest = action + degrees;
		action = 360 + rest;
	}
	else
	{
		action += degrees;
	}
}
