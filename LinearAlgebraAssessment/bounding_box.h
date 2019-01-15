#pragma once
class bounding_box
{
	double min_x_;
	double min_y_;
	double min_z_;
	double max_x_;
	double max_y_;
	double max_z_;

public:
	bounding_box(double min_x, double min_y, double min_z, double max_x, double max_y, double max_z) : 
		min_x_(min_x), min_y_(min_y), min_z_(min_z), max_x_(max_x), max_y_(max_y), max_z_(max_z)
	{
	}

	double min_x() const { return min_x_; }
	double min_y() const { return min_y_; }
	double min_z() const { return min_z_; }
	double max_x() const { return max_x_; }
	double max_y() const { return max_y_; }
	double max_z() const { return max_z_; }
};

