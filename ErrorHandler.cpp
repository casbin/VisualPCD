#include "ErrorHandler.h"

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

ErrorHandler::ErrorHandler()
{
	m_buffer = NULL;
}

ErrorHandler::ErrorHandler(string strFileLocation)
{
	m_buffer = NULL;
	m_fileOut = new ofstream(strFileLocation.c_str());
}

void ErrorHandler::reportMessage(int iErrorCode)
{
	cout << "There is an error!" << endl;
}

void ErrorHandler::setLogFile(string strFileLocation)
{
	m_fileOut = new ofstream(strFileLocation.c_str());
}

void ErrorHandler::redirectTo(int iMode)
{
	if (iMode == SCREEN_OUTPUT)
	{
		if (m_buffer != NULL)
			cout.rdbuf(m_buffer);
	}
	else if (iMode == FILE_OUTPUT)
	{
		m_buffer = cout.rdbuf(m_fileOut->rdbuf());
	}
}
