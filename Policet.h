#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <string>
using namespace std;

#define PERMITA 1
#define DENYA 2
#define PERMITB 3
#define DENYB 4
#define SUB_CONTAIN 5
#define RES_CONTAIN 6
#define SUB_OVERLAP 7
#define RES_OVERLAP 8
#define ACT_OVERLAP 9

class Policet
{
public:
	int pol;		//0, 1, 2... -1
	int per;		//PERMIT, DENY, SUB_CONTAIN, RES_CONTAIN
	string sub;		//A, B, C..
	string res;		//a, b, c..
	string act;		//read, write..

	string polName;
	string perName;
	string subName;
	string resName;
	string actName;

	string policyId;
	string ruleId;

public:
	Policet(int a_pol, int a_per, string a_sub, string a_res, string a_act);
	Policet(int a_pol, int a_per, string a_sub, string a_res, string a_act, string a_policyId, string a_ruleId);

	static string PermissionToString(int i);
	static string PermissionToText(int i);
};