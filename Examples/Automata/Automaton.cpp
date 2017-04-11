/*
 * Automoton.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: tim
 */

#include "Automaton.h"
#include <iostream>




double Automaton::density_ = Food::density_;
double Automaton::defaultMass_ = 2 *  Food::defaultMass_;


void Automaton::addMass(const double mass)
{
	mass_ += mass;
	radius_ = sqrt(mass_ / (density_ * M_PI));
}


Automaton::Automaton(double x, double y, StaticChromosome<12> chromosome):
		      Evolvable(chromosome, UniformRandomMutation(.1)),
			  Food(x, y, defaultMass_),
			  foodDist_(),
			  avoidDist_(),
			  pursueDist_()
{
	// default initialize everything and then load from chromosome.
	vel_ = {0, 0};
	radius_ = sqrt(mass_ / (density_ * M_PI));
	forceDirection_ = 0;
	force_ = 0;
	fitness_ = 0;
	setPointPos_ = {0, 0};
	loadFromChromosome();
}
void Automaton::loadFromChromosome()
{
	forcePID_ = PID<double>(double(chromosome_[0]),
							double(chromosome_[1]),
							double(chromosome_[2]));
	headingPID_ = PID<double>(double(chromosome_[3]),
							  double(chromosome_[4]),
							  double(chromosome_[5]));
	foodWeight_ = double(chromosome_[6]);
	avoidWeight_ = double(chromosome_[7]);
	pursueWeight_ = double(chromosome_[8]);

	foodDist_.setSigma(double(chromosome_[9]));
	avoidDist_.setSigma(double(chromosome_[10]));
	pursueDist_.setSigma(double(chromosome_[11]));
}

void Automaton::setToDefaults()
{
	mass_ = defaultMass_;
	vel_ = {0, 0};
	radius_ = sqrt(mass_ / (density_ * M_PI));
	forceDirection_ = 0;
	force_ = 0;
	fitness_ = 0;
	setPointPos_ = {0, 0};
}

Vec<double, 2> Automaton::getVelocity()
{
	return vel_;
}
Vec<double, 2> Automaton::getForceVector()
{
	return Vec<double, 2>({cosf(forceDirection_), sinf(forceDirection_)}) * force_;
}

void Automaton::updatePosition(double timeStep, double dragCoeff)
{


	// vector from current pos to desired pos
	auto diff = setPointPos_ - pos_;

	// distance from desired pos
	auto distErr = diff.norm();

	// angle from position to setpoint position
	auto spAng = diff.angleBetween(Vec<double, 2>({1, 0}));
	if(diff[1] < 0)
	{
		spAng = 2 * M_PI - spAng;
	}
	// angle of velocity vector
	auto velAng = vel_.angleBetween(Vec<double, 2>({1, 0}));
	if(vel_[1] < 0)
	{
		velAng = 2 * M_PI - spAng;
	}
	// error
	auto angErr = (spAng - velAng);
	// correct for any NaNs
	if(std::isnan(angErr))
	{
		angErr = 0;
	}
	// update PIDs
	forceDirection_ = headingPID_.update(angErr);
	force_ = forcePID_.update(distErr);
	// correct for any NaNs
	if(std::isnan(force_))
	{
		force_ = 0;
	}
	// throw in some drag force.
	auto forceVec = getForceVector();
	if(dragCoeff > 0)
	{
		forceVec -=  vel_ * (.5 * dragCoeff * M_PI * radius_ * radius_ * vel_.norm());
	}
	vel_ +=  forceVec * (timeStep / mass_);

	// update the position
	pos_ += vel_ * timeStep;

}
bool Automaton::canEat(const Automaton & other) const
{
	return (other.pos_ - pos_).norm() < radius_;
}
bool Automaton::canEat(const Food & food) const
{
	double dist = (food.pos_ - pos_).norm();
	return dist < radius_ or dist < food.getRadius();
}
void Automaton::eat(const Food & other)
{
	vel_ *= (mass_ / (mass_ + other.mass_));
	addMass(other.mass_);
}
void Automaton::eat(const Automaton & other)
{
	vel_ = (vel_ * mass_  + other.vel_ * other.mass_)/ (mass_ + other.mass_);
	addMass(other.mass_);

}

void Automaton::setFitness(double fitness) noexcept
{
	fitness_ = fitness;
}
double Automaton::getFitness()
{
	return fitness_ ;
}
void Automaton::setMass(double mass) noexcept
{
	mass_ = mass;
}
const Vec<double, 2> & Automaton::viewVelocity()
{
	return vel_;
}
void Automaton::setVelocity(double x, double y)
{
	vel_ = {x, y};
}



