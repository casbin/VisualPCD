#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <vector>
using namespace std;
class JRacerInterface;
class Policet;

class Enquirer
{
public:
	string m_strTBoxLocation;
	string m_strSWRLRLocation;

	vector<string> m_nstrTBox;
	vector<string> m_nstrSWRLR;
	vector<string> m_nstrABox;
	vector<Policet> m_nplcQuints;

	JRacerInterface* m_JRacer;

	vector<string> m_nstrReport;

	vector<vector<int> > m_niSubjectContain;
	vector<vector<int> > m_niResourceContain;
	vector<int> m_niConflictIndex;

	string m_strIP;
	int m_iPort;

public:
	void initConnection();
	Enquirer();
	Enquirer(vector<string>& a_nstrABox, vector<Policet>& a_nplcQuints);
	~Enquirer();

	void setTBox(vector<string>& a_nstrTBox);
	vector<string> getTBox();
	void setSWRLR(vector<string>& a_nstrSWRLR);
	vector<string> getSWRLR();
	void setABox(vector<string>& a_nstrABox);
	vector<string> getABox();
	void setQuints(vector<Policet>& a_nplcQuints);
	vector<Policet> getQuints();
	void printReport();
	vector<string> getReport();

	void initRuleBase(string a_strTBoxLocation, string a_strSWRLRLocation);

	void loadFile(string strFile, vector<string>& nsString);
	int m_iProgress;
	void submitInformation();

	string itos(int i);
	void implementEnquiryAllOld();
	void implementEnquiryAll();
	void implementEnquiry(int i, int j);

	int obtainBool(string s);
	int enquirePolicyConflict(int ia, int ib);
	int enquirePolicyPermitA(int i);
	int enquirePolicyDenyA(int i);
	int enquirePolicyPermitB(int i);
	int enquirePolicyDenyB(int i);

	string genVar(int i);
	vector<string> enquireSubjectContain(int ia, int ib);
	vector<string> enquireResourceContain(int ia, int ib);

	vector<int> GetSubjectContain(vector<string> a_nstrRes);
	vector<int> GetResourceContain(vector<string> a_nstrRes);
	int GetConflictIndex(int a_iConflictNo);

	string CutHead(string s);
	
};
