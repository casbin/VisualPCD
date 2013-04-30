#include "JRacerInterface.h"
#include <iostream>
using namespace std;

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

JRacerInterface::JRacerInterface(string a_strIP, int a_iPort)
{
	strIP = a_strIP;
	iPort = a_iPort;
}

void JRacerInterface::openConnection()
{
	int result;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	racerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(racerSocket == INVALID_SOCKET)
	{
		cout << "Create racerSocket failed.\n";
		exit(0);
	}
	racerAddr.sin_family = AF_INET;
	racerAddr.sin_port = htons(iPort); 
	racerAddr.sin_addr.s_addr = inet_addr(strIP.c_str());
	result=connect(racerSocket, (SOCKADDR*) &racerAddr, sizeof(racerAddr));
	if(result == -1)
	{
		cout << "openConnection error: " << "Connect racer failed." << endl << endl;
		exit(0);
	}
}

void JRacerInterface::closeConnection()
{
	WSACleanup();
}

string JRacerInterface::readFromSocket()
{
	char c;

	wstring wstrResult;
	string strTemp = "";

	recv(racerSocket, &c, 1, 0);
	strTemp += c;

	while (c != 10)
	{
		recv(racerSocket, &c, 1, 0);
		if (c != 10)
		{
			strTemp += c;
		}
	}

	//const char* cBuffer = strTemp.c_str();
	//wchar_t wcBuffer[1024];
	//memcpy(wcBuffer, cBuffer, strTemp.length());
	//wcBuffer[strTemp.length()] = '\0';
	//wstrResult = wcBuffer;
	//return ws2s(wstrResult);

	return strTemp;
}

string JRacerInterface::sendCommand(string strCommand)
{
	strCommand += "\n";
	int status;

	//wstring wstrCommand = s2ws(strCommand);
	//const wchar_t* wcBuffer = wstrCommand.c_str();
	//char cBuffer[1024];
	//memcpy(cBuffer, wcBuffer, wstrCommand.length() * 2);
	//status = send(racerSocket, cBuffer, wstrCommand.length() * 2, 0);

	status = send(racerSocket, strCommand.c_str(), strCommand.length(), 0);

	if (status == -1)
	{
		cout << "Send command failed.\n";
	}
	string strResult = readFromSocket();
	return parseResult(strCommand, strResult);
}

string JRacerInterface::parseResult(string strCommand, string strResult)
{
	if (strResult[1] == 'o')
	{
		string strWarning = getWarningFromOK(strResult);
		if (strWarning != "")
			printWarning(strWarning);
		return "null";
	}
	else if (strResult[1] == 'e')
	{
		string strError = getError(strResult);
		return strError;
	}
	else if (strResult[1] == 'a')
	{
		vector<string> strAnsAndWar = getResultAndWarningFromAnswer(strResult);
		if (strAnsAndWar[1] != "")
		{
			printWarning(strAnsAndWar[1]);
		}
		return strAnsAndWar[0];
	}
	else
	{
		return "RACER MESSAGE: "+ strCommand + "; produced a RACER answer unknown: " + strResult;
	};
}

string JRacerInterface::getWarningFromOK(string strResult)
{
	string strWarning = "";
	int ini = strResult.find('"', 6);
	int fi = strResult.length() - 1;
	if (ini < fi - 1)
	{
		strWarning = strResult.substr(ini + 1, fi - ini - 1);
	}
	return strWarning;
}

void JRacerInterface::printWarning(string strWarning)
{
	for (int i = 0; i < strWarning.length(); i ++)
	{
		char c = strWarning[i];
		if (c == 9)
		{
			cout << endl;
		}
		else
		{
			cout << strWarning[i];
		}
	}
}

string JRacerInterface::getError(string strResult)
{
	string s;
	int iniMessage = strResult.find(' ', 7);
	int ini = strResult.find('"', iniMessage);
	int fi = strResult.find('"', ini + 1);
	s = (iniMessage + 1 < ini - 1)? strResult.substr(iniMessage + 1, ini - 1 - iniMessage - 1) : "";
	if ((iniMessage + 1 < ini - 1) && (ini + 1 < fi))
	{
		s = s + strResult.substr(ini + 1, fi - ini - 1);
	}
	return s;
}

vector<string> JRacerInterface::getResultAndWarningFromAnswer(string strResult)
{
	vector<string> s;
	int ini = strResult.find('"', 10);
	int fi = ini;
	bool esFinal = FALSE;
	while (!esFinal)
	{
		fi = strResult.find('"', fi + 1);
		esFinal = (strResult[fi -1] != '\\');
	}
	s.push_back(strResult.substr(ini + 1, fi - ini - 1));
	if (fi + 4 < strResult.length())
	{
		s.push_back(strResult.substr(fi + 3, strResult.length() - 1 - fi - 3));
	}
	else
	{
		s.push_back("");
	}
	return s;
}

/*
string JRacerInterface::WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen<= 0)
		return string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst)
		return string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	string strTemp(pszDst);
	delete [] pszDst;
	return strTemp;
}

string JRacerInterface::ws2s(wstring& inputws)
{ 
	return WChar2Ansi(inputws.c_str());
}

wstring JRacerInterface::Ansi2WChar(LPCSTR pszSrc, int nLen)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if (nSize <= 0)
		return NULL;
	WCHAR *pwszDst = new WCHAR[nSize+1];
	if ( NULL == pwszDst)
		return NULL;
	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;
	if (pwszDst[0] == 0xFEFF)
	{
		for(int i = 0; i < nSize; i ++)
		{
			pwszDst[i] = pwszDst[i+1];
		}
	}
	wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}
wstring JRacerInterface::s2ws(const string& s)
{
	return Ansi2WChar(s.c_str(), s.size());
}
*/