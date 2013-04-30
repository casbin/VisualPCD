#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include "SampleQuints.h"
#include "Translator.h"
#include "JRacerInterface.h"
#include "Enquirer.h"
#include "XMLParser.h"
#include "ErrorHandler.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class PCDControler
{
public:
	string m_strLogFileLocation;
	string m_strPolicyFileALocation;
	string m_strPolicyFileBLocation;
	string m_strTBoxLocation;
	string m_strSWRLRLocation;
	

	ErrorHandler* m_handler;
	XMLParser* m_parser;
	Translator* m_trans;
	Enquirer* m_enq;
	

public:
	PCDControler();

	void setPolicyFiles(string a_strPolicyFileALocation, string a_strPolicyFileBLocation);
	void setKnowledgeBase(string a_strTBoxLocation, string a_strSWRLRLocation);
	void setDefaultKnowledgeBase(string a_strKBDir);
	void setLogFile(string a_strLogFileLocation);
	void redirectTo(int iMode);

	DWORD implementDetection();
	int m_iProgress;
	int getProgress();
	vector<string> getReport();
	void printReport();
	void releaseResource();
};