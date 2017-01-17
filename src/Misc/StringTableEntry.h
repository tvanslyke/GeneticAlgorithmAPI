/*
 * StringTableEntry.h
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#ifndef MISC_STRINGTABLEENTRY_H_
#define MISC_STRINGTABLEENTRY_H_

#include <vector>
#include <cstdlib>
#include <string>

using std::vector;
using std::string;

class StringTableEntry {
	friend class StringTable;
private:
	vector<string> fields;
	size_t n_fields;
public:
	StringTableEntry();
	StringTableEntry(const string &, string sep = " ");
	StringTableEntry(const string && in_string, string sep = " ");
	StringTableEntry(const vector<string> &);
	virtual ~StringTableEntry();
    size_t GetEntrySize(size_t index = 0);
    size_t GetNumFields();
	string ToString(string sep = "     ");
	string ToString(vector<size_t> field_widths, string sep = "     ");
    size_t Display(string sep = " ");
    size_t Display(vector<size_t> field_widths, string sep = "     ");
	string GetField(size_t index = 0);
	string operator[](size_t);
};



#endif /* MISC_STRINGTABLEENTRY_H_ */
