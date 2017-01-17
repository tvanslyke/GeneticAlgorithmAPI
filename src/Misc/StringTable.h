/*
 * StringTable.h
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#ifndef MISC_STRINGTABLE_H_
#define MISC_STRINGTABLE_H_
#include "StringTableEntry.h"
#include <vector>
#include <iostream>
using std::vector;
using std::ostream;
using std::cout;
class StringTable {

private:
	StringTableEntry heading;
	vector<StringTableEntry> entries;
	size_t num_fields;

	vector<size_t> GetFieldWidths();
public:
	StringTable();
	StringTable(size_t num_fields, size_t num_init_entries = 0);
	virtual ~StringTable();
	void SetHeading(StringTableEntry & heading);
	void SetHeading(const string & heading);
	void Append(const StringTableEntry & entry);
	void Append(const StringTableEntry && entry);
	void Append(string entry);
	void Display(ostream & output_stream = cout, string sep = string("    "));
};

#endif /* MISC_STRINGTABLE_H_ */
