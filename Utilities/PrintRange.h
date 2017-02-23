/*
 * Printing.h
 *
 *  Created on: Feb 19, 2017
 *      Author: tim
 */

#ifndef UTILITIES_PRINTING_H_
#define UTILITIES_PRINTING_H_
#include <string>
#include <boost/variant.hpp>

namespace print{
static const class PrintingOptions
{
public:
	size_t line_width = 8;
	size_t entry_width = 10;
	std::string indent = "";
	std::string delim = ",";
	std::pair<std::string, std::string> brackets = std::make_pair("[", "]");
} DEFAULT;
template <typename It>
class PrintRange
{

private:
	size_t line_width;
	size_t entry_width;
	std::string indent;
	std::string delim;
	std::pair<std::string, std::string> brackets;
public:

	PrintRange()
	{
		line_width = 8;
		entry_width = 10;
		indent = "";
		delim = ",";
		brackets = std::pair<std::string, std::string>("[", "]");

	}
	virtual ~PrintRange()
	{

	}
	void operator()(const It & begin, const It & end, size_t line_width = 8, std::string)
	{
		std::string out_string;
	}
};
}
#endif /* UTILITIES_PRINTING_H_ */
