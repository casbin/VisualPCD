#include "Policet.h"

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

Policet::Policet(int a_pol, int a_per, string a_sub, string a_res, string a_act)
{
	pol = a_pol; 
	per = a_per;
	sub = a_sub;
	res = a_res;
	act = a_act;
}
Policet::Policet(int a_pol, int a_per, string a_sub, string a_res, string a_act, string a_policyId, string a_ruleId)
{
	pol = a_pol; 
	per = a_per;
	sub = a_sub;
	res = a_res;
	act = a_act;

	policyId = a_policyId;
	ruleId = a_ruleId;
}

#define PERMITA 1
#define DENYA 2
#define PERMITB 3
#define DENYB 4
#define SUB_CONTAIN 5
#define RES_CONTAIN 6
#define SUB_OVERLAP 7
#define RES_OVERLAP 8
#define ACT_OVERLAP 9

string Policet::PermissionToString(int i)
{
	switch (i)
	{
	case 1:
		return "PERMITA";
		break;
	case 2:
		return "DENYA";
		break;
	case 3:
		return "PERMITB";
		break;
	case 4:
		return "DENYB";
		break;
	case 5:
		return "SUB_CONTAIN";
		break;
	case 6:
		return "RES_CONTAIN";
		break;
	case 7:
		return "SUB_OVERLAP";
		break;
	case 8:
		return "RES_OVERLAP";
		break;
	case 9:
		return "ACT_OVERLAP";
		break;
	default:
		return "PermissionToString error.";
	}
}

string Policet::PermissionToText(int i)
{
	switch (i)
	{
	case 1:
		return "(允许授权策略)";
		break;
	case 2:
		return "(拒绝授权策略)";
		break;
	case 3:
		return "(允许授权策略)";
		break;
	case 4:
		return "(拒绝授权策略)";
		break;
	case 5:
		return "(主体的继承策略)";
		break;
	case 6:
		return "(资源的继承策略)";
		break;
	case 7:
		return "(主体的重叠策略)";
		break;
	case 8:
		return "(资源的重叠策略)";
		break;
	case 9:
		return "(动作的重叠策略)";
		break;
	default:
		return "PermissionToText error.";
	}
}