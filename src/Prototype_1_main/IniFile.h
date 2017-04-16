#ifndef _INIFILE_H_
#define _INIFILE_H_

#include "PreCompile.h"

class IniFile
{
public:
	IniFile(string &strFilePath);
	~IniFile();

	ifstream m_FileIn;
};

#endif