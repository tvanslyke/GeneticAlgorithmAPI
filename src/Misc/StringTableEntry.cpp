/*
 * StringTableEntry.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#include "StringTableEntry.h"

vector<string> strip(const string & str, const string & sep = " ")
{
	vector<string> str_vec = vector<string>();
	size_t substr_start = 0;
	size_t substr_end;
	substr_end = str.find(sep);
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
	return str_vec;
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

StringTableEntry::StringTableEntry(const vector<string> & strvec)
{
	fields = vector<string>(strvec);
	n_fields = fields.size();
}

size_t StringTableEntry::GetEntrySize(size_t index)
{
	return (fields.at(index)).size();
}
string StringTableEntry::ToString()
{
	string out_str = "";
	out_str += fields[0] + " ";
	for(size_t i = 1; i < n_fields - 1; ++i)
	{
		out_str += fields[i] + " ";
	}
	out_str += fields[fields.size() - 1] + "\n";
	return out_str;
}
string StringTableEntry::GetEntry(size_t index)
{
	return string(fields.at(index));
}
