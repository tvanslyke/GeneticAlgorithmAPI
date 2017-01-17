/*
 * StringTableEntry.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#include "StringTableEntry.h"
#include <iostream>
#include "vector_utils.h"

using std::cout;
using std::endl;

vector<string> strip(const string & str, const string & sep = " ")
{
	vector<string> str_vec = vector<string>();
	size_t substr_start = 0;
	size_t substr_end;
	substr_end = str.find(sep);
	if(!substr_end)
	{
		substr_start = str.find_first_not_of(sep, substr_end);
		substr_end = str.find(sep, substr_start);
	}
	while(substr_end != string::npos)
	{
		str_vec.push_back(str.substr(substr_start, substr_end - substr_start));
		substr_start = str.find_first_not_of(sep, substr_end);
		if(substr_start == string::npos)
		{
			return str_vec;
		}
		substr_end = str.find(sep, substr_start);
	}
	substr_end = str.size();
	string last_line = str.substr(substr_start, substr_end - substr_start);
	if(last_line.size())
	{
		str_vec.push_back(last_line);
	}

	return str_vec;
}
size_t StringTableEntry::GetNumFields()
{
	return this->n_fields;
}



StringTableEntry::StringTableEntry() {
	// TODO Auto-generated constructor stub
	fields = vector<string>();
	n_fields = 0;
}

StringTableEntry::~StringTableEntry() {
	// TODO Auto-generated destructor stub
}



StringTableEntry::StringTableEntry(const string & in_string, string sep)
{
	fields = strip(in_string, sep);
	n_fields = fields.size();
}

StringTableEntry::StringTableEntry(const string && in_string, string sep)
{

	fields = strip(string(in_string), sep);
	n_fields = fields.size();
}

StringTableEntry::StringTableEntry(const vector<string> & strvec)
{
	fields = vector<string>(strvec);
	n_fields = fields.size();
}

size_t StringTableEntry::GetEntrySize(size_t index)
{

	if(n_fields > index){

		return (fields.at(index)).size();}
	else
		return 0;
}
string StringTableEntry::ToString(string sep)
{
	string out_str = "";
	if(fields.size())
	{
		out_str += (fields[0] + sep);

		for(size_t i = 1; i < n_fields - 1; ++i)
		{
			out_str += (fields[i] + sep);
		}
		out_str += fields[fields.size() - 1];
	}
	return out_str;
}

string StringTableEntry::ToString(vector<size_t> field_widths, string sep)
{

	size_t this_width;
	string line = "";
	string this_field;
	size_t num_entries_to_use = field_widths.size();
	num_entries_to_use = num_entries_to_use > n_fields ? n_fields : num_entries_to_use;
	for(size_t  i = 0; i < num_entries_to_use; ++i)
	{
		this_field = fields[i];
		this_width = this_field.size();
		line += this_field;
		if(field_widths[i] > this_width)
		{
			line += string(field_widths[i] - this_width, ' ');
		}
		line += (i != num_entries_to_use - 1 ? sep : string(""));
	}
	return line;

}

string StringTableEntry::GetField(size_t index)
{
	if(fields.size() > index)
		return string(fields.at(index));
	else
		return string("");
}
string StringTableEntry::operator[](size_t index)
{
	return string(fields[index]);
}


size_t StringTableEntry::Display(string sep)
{
	cout << this->ToString(sep) << endl;
}
size_t StringTableEntry::Display(vector<size_t> field_widths, string sep)
{
	cout << this->ToString(field_widths, sep) << endl;
}




