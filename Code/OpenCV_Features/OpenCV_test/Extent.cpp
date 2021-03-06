#include "Extent.h"

Extent::Extent()
{
}

vector<string>& Extent::split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		if (!item.empty())
			elems.push_back(item);
	}
	return elems;
}

vector<string> Extent::split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

void Extent::ReplaceStringInPlace(std::string & subject, const std::string & search, const std::string & replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}
