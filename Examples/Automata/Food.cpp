/*
 * Food.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: tim
 */

#include "Food.h"


Food::Food(double x, double y, double mass):
    mass_(mass), radius_(sqrt(mass_ / (density_ * M_PI)))
{
	pos_ = {x, y};
}
void Food::setPosition(double x, double y) noexcept
{
	pos_ = {x, y};
}

Vec<double, 2> Food::getPosition()
{
	return pos_;
}
const Vec<double, 2> & Food::viewPosition()
{
	return pos_;
}
double Food::getMass() const noexcept
{
	return mass_;
}
bool Food::operator<(const Food & other)
{
	return mass_ < other.mass_;
}


double Food::getRadius() const noexcept
{
	return radius_;
}
void Food::pack(std::ostream & out) const
{
	out.write(reinterpret_cast<const char *>(&pos_[0]), sizeof(pos_[0]));
	out.write(reinterpret_cast<const char *>(&pos_[1]), sizeof(pos_[1]));
	out.write(reinterpret_cast<const char *>(&radius_), sizeof(radius_));
}

double Food::defaultMass_ = 10.0;
double Food::density_ = 1.0;
