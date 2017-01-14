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
private:
	vector<string> fields;
	size_t n_fields;
public:
	StringTableEntry();
	StringTableEntry(const string &, string = " ");
	StringTableEntry(const vector<string> &);
	virtual ~StringTableEntry();
    size_t GetEntrySize(size_t index = 0);
	string ToString();
	string GetEntry(size_t index = 0);


};

#endif /* MISC_STRINGTABLEENTRY_H_ */
