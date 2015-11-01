#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include<algorithm>
using std::string;
using std::map;
using std::vector;
using std::stringstream;
using std::transform;
template <class T>
void convertFromString(T &value, const string &s) {
	stringstream ss(s);

	ss >> value;
}

template <class T>
string ConvertToString(T value) {
	stringstream ss;
	ss << value;
	return ss.str();
}

class CIniFile
{
	string filePath;
	string content;
	vector<string>lineContent;
	map<string, map<string, string> >mapSection;
public:
	CIniFile(string path);
	~CIniFile();

	string get(string section, string key, string _default);

	void set(string section, string key, string value);

	void save();
	void save(string path);

private:
	CIniFile(){}
	bool loadFile(string path);

};

