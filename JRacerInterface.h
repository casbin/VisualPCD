#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
#include <winsock2.h>
#include <vector>

using namespace std;

class JRacerInterface
{
public:
	string strIP;
	int iPort;

	WSADATA wsaData;
	SOCKET racerSocket;
	SOCKADDR_IN racerAddr;

public:
	JRacerInterface(string a_strIP, int a_iPort);
	void openConnection();
	void closeConnection();

	string readFromSocket();
	string sendCommand(string strCommand);
	string parseResult(string strCommand, string strResult);

	string getWarningFromOK(string strResult);
	void printWarning(string strWarning);
	string getError(string strResult);
	vector<string> getResultAndWarningFromAnswer(string strResult);

	/*
	string WChar2Ansi(LPCWSTR pwszSrc);
	string ws2s(wstring& inputws);
	wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
	wstring s2ws(const string& s);*/
};