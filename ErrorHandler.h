#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <iostream>
#include <fstream>
using namespace std;

#define SCREEN_OUTPUT 1
#define FILE_OUTPUT 2

class ErrorHandler
{
public:
	ofstream* m_fileOut;

	streambuf* m_buffer;

public:
	ErrorHandler();
	ErrorHandler(string strFileLocation);

	void reportMessage(int iErrorCode);

	void setLogFile(string strFileLocation);
	void redirectTo(int iMode);
};
