#include "stdafx.h"
#include "IniFile.h"
#include <fstream>
#include <regex>
#include <iostream>
using std::iostream;
using std::fstream;
using std::regex;


vector<string> RegexSearch(string src, string match)
{
	vector<string>ret;
	const std::regex pattern(match);

	std::string weekend = src;
	const std::sregex_token_iterator end; 

	for (std::sregex_token_iterator i(weekend.begin(), weekend.end(), pattern); i != end; ++i)

	{
		ret.push_back(*i);
		//std::cout << *i << std::endl;

	}
	return ret;
}

string trim(const string& str)
{
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos)
	{
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
	{
		return str.substr(pos, pos2 - pos +1);
	}
	return str.substr(pos);
}


CIniFile::CIniFile(string path) :filePath(path)
{
	loadFile(path);
}


CIniFile::~CIniFile() 
{
}

bool CIniFile::loadFile(string path)
{
	fstream _file;
	char buf[1024];
	_file.open(path, std::ios::in);
	if (_file){
		/*std::ostringstream tmp;
		tmp << _file.rdbuf();
		content = tmp.str();
		vector<string>ret = RegexSearch(content, "^\\s*\\[.*\\]\\s*$");
		for each (string var in ret)
		{
			std::cout << var << std::endl;
		}
		ret = RegexSearch(content, "^\\s*^[a-zA-z_].*=.*");
		for each (string var in ret)
		{
			std::cout << var << std::endl;
		}*/
		while (!_file.eof()){
			_file.getline(buf, sizeof(buf));
			string str(buf);
			transform(str.begin(), str.end(), str.begin(), tolower);
			lineContent.push_back(str);
		}
		string section;
		for (size_t i = 0; i < lineContent.size(); i++)
		{
			vector<string>ret = RegexSearch(lineContent[i], "^\\s*\\[.*\\]\\s*");
			if (ret.size()>0){
				vector<string>ses = RegexSearch(ret[0], "[^\\[\\]\\s]{1,}");
				if (ses.size() == 1)
				{
					section = ses[0];
					std::cout << "[" << section << "]" << std::endl;
					if (mapSection.find(section) == mapSection.end()){
						mapSection[section];
					}
				}
				
			}
			else{
				ret = RegexSearch(lineContent[i], "^\\s*^[^;#].*=[^;#]{1,}");
				if (ret.size()>0 && !section.empty()){
					vector<string>para = RegexSearch(ret[0], "[^=\t\r\n]+");
					if (para.size()==2)
					{
						para[0] = trim(para[0]);
						para[1] = trim(para[1]);
						mapSection[section][para[0]] = para[1];
						std::cout << para[0] <<"="<<para[1]<< std::endl;
					}

					
					
				}
			}
		}
		
	}
	return true;
}



void CIniFile::save()
{
	save(filePath);
}
void CIniFile::save(string path)
{
	fstream fs(path, fstream::out | std::ios_base::trunc);
	for (map<string, map<string, string> >::iterator it = mapSection.begin(); it != mapSection.end(); it++)
	{
		fs << "[" << it->first << "]" << std::endl;
		for (map<string, string>::iterator jit = it->second.begin(); jit != it->second.end(); jit++)
		{
			fs << jit->first << "=" << jit->second << std::endl;
		}
	}
}

string CIniFile::get(string section, string key, string _default)
{
	transform(section.begin(), section.end(), section.begin(), tolower);
	transform(key.begin(), key.end(), key.begin(), tolower);
	if (mapSection.find(section) != mapSection.end() && mapSection[section].find(key) != mapSection[section].end())
	{
		return mapSection[section][key];
	}
	else{
		return _default;
	}
}

void CIniFile::set(string section, string key, string value)
{
	transform(section.begin(), section.end(), section.begin(), tolower);
	transform(key.begin(), key.end(), key.begin(), tolower);
	mapSection[section][key] = value;
}