/*
 * StringTable.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#include "StringTable.h"


using std::cout;
using std::endl;

StringTable::StringTable() {
	// TODO Auto-generated constructor stub
	heading = StringTableEntry();
	entries = vector<StringTableEntry>();
	num_fields = 0;
}


StringTable::StringTable(size_t num_fields, size_t num_init_entries)
{
	this->num_fields = num_fields;
	this->heading = StringTableEntry();
	this->entries = vector<StringTableEntry>(num_init_entries);
}

StringTable::~StringTable() {
	// TODO Auto-generated destructor stub
}


void StringTable::SetHeading(StringTableEntry & heading)
{
	this->heading = heading;
}
void StringTable::SetHeading(const string & heading)
{
	StringTableEntry cpy = StringTableEntry(heading);
	this->heading = cpy;
}
void StringTable::Append(const StringTableEntry & entry)
{
	StringTableEntry cpy = StringTableEntry(entry);
	this->entries.push_back(entry);
}
void StringTable::Append(const StringTableEntry && entry)
{

	StringTableEntry cpy = StringTableEntry(entry);
	this->entries.push_back(entry);
}

void StringTable::Append(string entry)
{
	StringTableEntry new_entry = StringTableEntry(entry);
	this->entries.push_back(new_entry);
}

/*
 *  Return vector of 'size_t's indicating the longest string lengths
 *  in each column of the table.
 */
vector<size_t> StringTable::GetFieldWidths()
{
	vector<size_t> field_widths = vector<size_t>(num_fields, 0);
	size_t num_entries = field_widths.size();
	size_t this_size;
	for(size_t i = 0; i < num_entries; ++i)
	{
		for(size_t j = 0; j < num_fields; ++j)
		{
			this_size = entries[i].GetEntrySize(j);
			if(this_size > field_widths[j])
			{
				field_widths[j] = this_size;
			}
		}
	}
	if(heading.GetNumFields())
	{
		for(size_t j = 0; j < num_fields; ++j)
		{
			this_size =	heading.GetEntrySize(j);
			if(this_size > field_widths[j])
			{
				field_widths[j] = this_size;
			}
		}
	}
	return field_widths;
}

/*
 *  Print out each
 */
void StringTable::Display(ostream & output_stream, string sep)
{
	vector<size_t> widths = this->GetFieldWidths();
	size_t num_entries = entries.size();
	StringTableEntry this_entry;
	if(this->heading.GetNumFields())
	{
		heading.Display(widths, sep);
	}
	for(size_t i = 0; i < num_entries; ++i)
	{
		this_entry = entries.at(i);
		this_entry.Display(widths, sep);
	}
}



















