#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Policet.h"
#include "Markup.h"

class XMLParser
{
public:
	string m_strFileLocA;
	string m_strFileLocB;
	vector<Policet> m_nplcQuints;
	vector<Policet> m_nplcFileAQuints;
	vector<Policet> m_nplcFileBQuints;

	vector<string> m_nstrSubjects;
	vector<string> m_nstrResources;

	CMarkup* m_Markup;

public:
	XMLParser();
	XMLParser(string a_strFileLocA, string a_strFileLocB);
	~XMLParser();

	void setFileA(string a_strFileLocA);
	void setFileB(string a_strFileLocB);
	vector<Policet> getQuints();

	string itos(int i);

	int parse(vector<Policet>& a_nplcQuints, string a_strType);
	void parseFileA();
	void parseFileB();

	void printQuints();

	void QuintsToSubjectsAndResources();
	int QuintsToSubjectsNO(int iNO);
	int QuintsToSubjectsNO2(int iNO);
	int QuintsToResourcesNO(int iNO);
	int QuintsToResourcesNO2(int iNO);

	vector<string> FileAQuintsToString();
	vector<string> FileBQuintsToString();

};
