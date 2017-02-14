/*
 * PlotGP.h
 *
 *  Created on: Feb 10, 2017
 *      Author: tim
 */

#ifndef PLOTTING_PLOTGP_H_
#define PLOTTING_PLOTGP_H_



/*
 * PlotGP.h
 *
 *  Created on: Jan 30, 2017
 *      Author: tim
 */


// apt-get install libgnuplot-iostream-dev



#include "gnuplot-iostream.h"
#include <string>
#include <vector>
#include <algorithm>
using std::vector;
using std::string;
using std::to_string;
using std::tuple;
using std::pair;



template <typename T>
class GPLimType
{
private:
	T value;
	bool isnone;
public:
	GPLimType()
	{
		this->value = (T)0;
		this->isnone = true;
	}
	GPLimType(T value)
	{
		this->value = value;
		this->isnone = false;
	}
	~GPLimType()
	{

	}
	operator T()
	{
		return this->value;
	}
	T operator =(T value)
	{
		this->value = value;
		this->isnone = false;
		return this->value;
	}
	T operator =(GPLimType<T> other)
	{
		this->value = other.value;
		this->isnone = other.isnone;
		return this->value;
	}
	bool is_none()
	{
		return this->isnone;
	}
};

template <typename X = double, typename Y = double>
class PlotGP {
private:
	vector<vector<X>> xranges;
	vector<vector<Y>> yranges;
	string xlabel;
	string ylabel;
	string title;
	pair<GPLimType<X>, GPLimType<X>> xlims;
	pair<GPLimType<Y>, GPLimType<Y>> ylims;
	bool auto_xmin, auto_xmax, auto_ymin, auto_ymax;


	static vector<tuple<X, Y>> make_pointwise(vector<X> & xvals, vector<Y> & yvals)
	{
		vector<tuple<X, Y>> points;
		size_t len = xvals.size();
		points.reserve(len);
		for(size_t i = 0; i < len; ++i)
		{
			points[i] = std::make_tuple(xvals[i], yvals[i]);
		}
		return points;
	}
	template <typename T>
	static void find_min(vector<T> vals,GPLimType<T> & current)
	{
		T minval;
		if(current.is_none())
		{
			minval = vals[0];
		}
		else
		{
			minval = (T)current;
		}
		size_t len = vals.size();
		for(size_t i = 0; i < len; ++i)
		{
			if(vals[i] < minval)
			{
				minval = vals[i];
			}
		}
		current = minval;

	}
	template <typename T>
	static void find_max(vector<T> vals,GPLimType<T> & current)
	{
		T maxval;
		if(current.is_none())
		{
			maxval = vals[0];
		}
		else
		{
			maxval = (T)current;
		}
		size_t len = vals.size();
		for(size_t i = 0; i < len; ++i)
		{
			if(vals[i] > maxval)
			{
				maxval = vals[i];
			}
		}
		current = maxval;

	}
	void rescale()
	{
		size_t numplots = this->xranges.size();
		if(auto_xmin)
		{
			PlotGP::find_min<X>(xranges[numplots - 1], xlims.first);
		}
		if(auto_xmax)
		{
			PlotGP::find_max<X>(xranges[numplots - 1], xlims.second);
		}
		if(auto_ymin)
		{
			PlotGP::find_min<Y>(yranges[numplots - 1], ylims.first);
		}
		if(auto_ymax)
		{
			PlotGP::find_max<Y>(yranges[numplots - 1], ylims.second);
		}
	}
public:
	PlotGP()
	{
		title = "X_vs_Y";
		xlabel = "";
		ylabel = "";
		xranges = vector<vector<X>>();
		yranges = vector<vector<Y>>();
		xlims = std::make_pair<GPLimType<X>, GPLimType<X>>(GPLimType<X>(), GPLimType<X>());
		ylims = std::make_pair<GPLimType<Y>, GPLimType<Y>>(GPLimType<Y>(), GPLimType<Y>());
		auto_xmin = true;
		auto_ymin = true;
		auto_xmax = true;
		auto_ymax = true;
	}
	virtual ~PlotGP()
	{

	}
	void set_xlabel(string label)
	{
		this->xlabel = label;
	}
	void set_ylabel(string label)
	{
		this->ylabel = label;
	}
	void set_title(string title)
	{
		this->title = title;
	}
	void set_xlims(X min, X max)
	{
		this->xlims = std::make_pair<X, X>(min, max);
		auto_xmin = false;
		auto_xmax = false;
	}
	void set_xmin(X min)
	{
		assert(min < xlims.second);
		this->xlims = std::make_pair<X, X>(min, xlims.second);
		auto_xmin = false;
	}
	void set_xmax(X max)
	{
		assert(max > xlims.first);
		this->xlims = std::make_pair<X, X>(xlims.first, max);
		auto_xmax = false;
	}
	void set_ylims(Y min, Y max)
	{
		this->ylims = std::make_pair<Y, Y>(min, max);
		auto_ymin = false;
		auto_ymax = false;
	}
	void set_ymin(Y min)
	{
		assert(min < xlims.second);
		this->ylims = std::make_pair<Y, Y>(min, ylims.second);
		auto_ymin = false;
	}
	void set_ymax(Y max)
	{
		assert(max > xlims.first);
		this->ylims = std::make_pair<Y, Y>(ylims.first, max);
		auto_ymax = false;

	}
	void add_plot(std::vector<X> xvals, std::vector<Y> yvals)
	{
		assert(xvals.size() == yvals.size());
		this->xranges.push_back(xvals);
		this->yranges.push_back(yvals);
		this->rescale();
	}

	void show_plots()
	{
		Gnuplot gp;
		gp << "set xrange [" + std::to_string(xlims.first) + ":" + std::to_string(xlims.second) + "]\n"
			  "set yrange [" + std::to_string(ylims.first) + ":" + std::to_string(ylims.second) + "]\n";
		if(not xlabel.empty())
		{
			gp << "set xlabel '" + xlabel + "';\n";
		}
		if(not xlabel.empty())
		{
			gp << "set ylabel '" + ylabel + "';\n";
		}
		if(not title.empty())
		gp << "set title '" + title + "';\n";
		size_t numplots = xranges.size();
		if(numplots == 1)
		{
			gp << "plot '-'  with lines;\n";
			gp.send1d(std::make_tuple(xranges[0], yranges[0]));

		}
		else
		{
			size_t i;
			gp << "plot ";
			for(i = 0; i < numplots - 1; ++i)
			{
				gp << "'-' with lines title '" + title + std::to_string(i) << "', ";
			}
			gp << "'-' with lines title '" + title + std::to_string(i);
			gp << "'\n";
			pair<vector<X>, vector<Y>> plot;
			for(i = 0; i < numplots - 1; ++i)
			{
				plot = std::make_pair(xranges[i], yranges[i]);
				gp.send1d(plot);
			}
			plot = std::make_pair(xranges[i], yranges[i]);
			gp.send1d(plot);


		}

	}
};


#endif /* PLOTTING_PLOTGP_H_ */
