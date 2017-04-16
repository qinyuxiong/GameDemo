#include "IniFile.h"

IniFile::IniFile(string &strFilePath)
{
	m_FileIn.open(strFilePath.c_str(), ios::in);
	if (m_FileIn.is_open())
	{
		string strFileLine;
		while (!m_FileIn.eof())
		{
			getline(m_FileIn, strFileLine);
		}
	}
}