/*
 * PID.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tim
 */

#ifndef EXAMPLES_PID_H_
#define EXAMPLES_PID_H_
/**
 * Basic Proportional-Integral-Derivative controller.
 *
 * @author Timothy Van Slyke
 */
template <typename T>
class PID {

public:
	/** Default ctor. */
	PID() = default;


	/**
	 * Initialize with p, i, and d constants.
	 * @param p -  Proportional constant.
	 * @param i - Integral constant.
	 * @param d - Derivative constant.
	 */
	PID(const T & p, const T & i, const T & d): p_(p), i_(i), d_(d)
	{
		acc_ = T();
		save_ = T();
	}
	/**
	 * Update the PID's internal state and the control parameter.
 	 * @param error - the signed distance from the setPoint.
	 * @return the control parameter
	 */
	T update(const T & error)
	{
		auto diff = error - save_;
		save_ = error;
		acc_ += i_ * error ;
		return p_ * error + d_ * diff  + acc_;
	}
private:
	/** Proportional constant. */
	T p_;
	/** Integral constant. */
	T i_;
	/** Derivative constant. */
	T d_;
	/** Cumulative error buildup. */
	T acc_;
	/** Value of the previous error. */
	T save_;
};

#endif /* EXAMPLES_PID_H_ */
