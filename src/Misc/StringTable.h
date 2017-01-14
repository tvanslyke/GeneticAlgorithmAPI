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

using std::vector;

class StringTable {
private:
	vector<StringTableEntry> heading;
	vector<StringTableEntry> entries;
	size_t num_fields;
public:
	StringTable();
	StringTable(size_t num_fields, size_t num_init_entries = 5);
	virtual ~StringTable();
	void SetHeading(StringTableEntry & heading);
	void Append(StringTableEntry & entry);

};

#endif /* MISC_STRINGTABLE_H_ */
