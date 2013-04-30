#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <vector>
using namespace std;

class Policet;

typedef struct
{
	string pol;
	string per;
	string sub;
	string res;
	string act;
}StringNames;

class Translator
{
public:
	vector<Policet> m_nplcQuints;
	vector<string> m_nstrABox;

public:
	Translator();
	Translator(vector<Policet>& a_nplcQuints);

	string appendFigure(string strHead, int iRear);
	void assignNames(vector<Policet>& a_nplcQuints);

	void translateAll();
	void translate(Policet plcSrc, vector<string>& strDest);

	void elementTranslate(Policet plcSrc, vector<string>& strDest);
	void affiliateTranslate(Policet plcSrc, vector<string>& strDest);
	void containTranslate(Policet plcSrc, vector<string>& strDest);

	void subjectOverlapTranslate(Policet plcSrc, vector<string>& nstrDest);
	void resourceOverlapTranslate(Policet plcSrc, vector<string>& nstrDest);
	void actionOverlapTranslate(Policet plcSrc, vector<string>& nstrDest);

	void overlapTranslateAll(vector<Policet>& nplcSrc, vector<string>& nstrDest);

	void printABox();
	vector<string> getABox();
	vector<Policet> getQuints();
	
};

