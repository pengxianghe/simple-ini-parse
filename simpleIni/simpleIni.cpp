// simpleIni.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "IniFile.h"
#include<iostream>
#include<Windows.h>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SetCurrentDirectory(_T("C:/Users/hex/Documents/Visual Studio 2013/Projects/simpleIni/simpleIni"));
	CIniFile iniFile("setup.ini");
	iniFile.save("setup1.ini");

	string section = "light";
	string str;
	float f1;
	str = iniFile.get(section, "float", "");
	convertFromString(f1, str);
	cout << "float=" << f1 << endl;
	double d1;
	str = iniFile.get(section, "double", "");
	convertFromString(d1, str);
	cout << "double=" << d1 << endl;
	bool bl;
	iniFile.get(section, "bool", "");
	convertFromString(bl, str);
	cout << "bool=" << bl << endl;
	int  i1;
	iniFile.get(section, "int", "");
	convertFromString(i1, str);
	cout << "int=" << i1 << endl;
	
	str=iniFile.get("light", "string", string(""));
	cout << "string=" << str << endl;
	return 0;
	
}

