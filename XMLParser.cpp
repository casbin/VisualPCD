#include "XMLParser.h"
#include <iostream>
using namespace std;

#include <windows.h>

#define MAX_POLICY_NUMBER 100

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

XMLParser::XMLParser()
{
	m_Markup = new CMarkup();
	//m_nplcQuints.reserve(MAX_POLICY_NUMBER);
}

XMLParser::XMLParser(string a_strFileLocA, string a_strFileLocB)
{
	m_strFileLocA = a_strFileLocA;
	m_strFileLocB = a_strFileLocB;

	m_Markup = new CMarkup();
	//m_nplcQuints.reserve(MAX_POLICY_NUMBER);

	parseFileB();
	parseFileA();
	QuintsToSubjectsAndResources();
}

XMLParser::~XMLParser()
{
	delete m_Markup;
	m_Markup = NULL;
}

void XMLParser::setFileA(string a_strFileLocA)
{
	m_strFileLocA = a_strFileLocA;
}

void XMLParser::setFileB(string a_strFileLocB)
{
	m_strFileLocB = a_strFileLocB;
}

vector<Policet> XMLParser::getQuints()
{
	return m_nplcQuints;
}

string XMLParser::itos(int i)
{
	char cBuffer[10];
	itoa(i, cBuffer, 10);
	string s(cBuffer);
	return s;
}

int XMLParser::parse(vector<Policet>& a_nplcQuints, string a_strType)
{
	int policy = a_nplcQuints.size();
	string permission_string;// = "";
	int permission_int = -1;
	string subject;// = "";
	string resource;// = "";
	string action;// = "";

	string policyId;
	string ruleId;// = "";
	string matchId;
	

	Policet* tmp;

	m_Markup->ResetPos();

	if (!m_Markup->FindElem("PolicySet"))
	{
		cout << "FindElem(\"PolicySet\") error." << endl;
		return FALSE;
	}
	m_Markup->IntoElem();

	if (!m_Markup->FindElem("Policy"))
	{
		cout << "FindElem(\"Policy\") error." << endl;
		return FALSE;
	}
	m_Markup->ResetMainPos();

	while (m_Markup->FindElem("Policy"))
	{
		policyId = m_Markup->GetAttrib("PolicyId");

		///parent pointer to PolicySet///
		m_Markup->IntoElem();
		///parent pointer to Policy///
		if (!m_Markup->FindElem("Rule"))
		{
			cout << "FindElem(\"Rule\") error." << endl;
			m_Markup->OutOfElem();
			continue;
		}

		permission_string = m_Markup->GetAttrib("Effect");
		if (permission_string == "Permit" && a_strType == "A")
		{
			permission_int = PERMITA;
		}
		else if (permission_string == "Deny" && a_strType == "A")
		{
			permission_int = DENYA;
		}
		else if (permission_string == "Permit" && a_strType == "B")
		{
			permission_int = PERMITB;
		}
		else if (permission_string == "Deny" && a_strType == "B")
		{
			permission_int = DENYB;
		}
		else
		{
			//cout << "GetAttrib(\"Effect\") error." << endl;
			permission_int = -1;
			//return FALSE;
		}

		ruleId = m_Markup->GetAttrib("RuleId");
		///parent pointer to Policy///
		m_Markup->IntoElem();
		///parent pointer to Rule///
////////////////////////////////////////////////////////////
		if (!m_Markup->FindElem("Target"))
		{
			subject = "_null";
			resource = "_null";
			action = "_null";
		}
		else
		{
			m_Markup->IntoElem();
			///parent pointer to Target///
			if (m_Markup->FindElem("Subjects"))
			{
				m_Markup->IntoElem();
				if (m_Markup->FindElem("Subject"))
				{
					m_Markup->IntoElem();
					if (m_Markup->FindElem("SubjectMatch"))
					{
						matchId = m_Markup->GetAttrib("MatchId");
						//////////////////
						m_Markup->IntoElem();
						if (m_Markup->FindElem("AttributeValue"))
						{
							subject = m_Markup->GetData();
						}
						m_Markup->OutOfElem();
						//////////////////
					}
					m_Markup->OutOfElem();
				}
				m_Markup->OutOfElem();
			}
			else
			{
				subject = "_null";
			}
////////////////////////////////////////////////////////////
			if (m_Markup->FindElem("Resources"))
			{
				m_Markup->IntoElem();
				if (m_Markup->FindElem("Resource"))
				{
					m_Markup->IntoElem();
					if (m_Markup->FindElem("ResourceMatch"))
					{
						//////////////////
						m_Markup->IntoElem();
						if (m_Markup->FindElem("AttributeValue"))
						{
							resource = m_Markup->GetData();
						}
						m_Markup->OutOfElem();
						//////////////////
					}
					m_Markup->OutOfElem();
				}
				m_Markup->OutOfElem();
			}
			else
			{
				resource = "_null";
			}
////////////////////////////////////////////////////////////
			if (m_Markup->FindElem("Actions"))
			{
				m_Markup->IntoElem();
				if (m_Markup->FindElem("Action"))
				{
					m_Markup->IntoElem();
					if (m_Markup->FindElem("ActionMatch"))
					{
						//////////////////
						m_Markup->IntoElem();
						if (m_Markup->FindElem("AttributeValue"))
						{
							action = m_Markup->GetData();
						}
						m_Markup->OutOfElem();
						//////////////////
					}
					m_Markup->OutOfElem();
				}
				m_Markup->OutOfElem();
			}
			else
			{
				action = "_null";
			}
			///parent pointer to Target///
			m_Markup->OutOfElem();
		}
////////////////////////////////////////////////////////////
		///parent pointer to Rule///
		m_Markup->OutOfElem();
		///parent pointer to Policy///

		///parent pointer to Policy///
		m_Markup->OutOfElem();
		///parent pointer to PolicySet///

		if (matchId == "subject-contain")
		{
			permission_int = SUB_CONTAIN;
		}
		else if (matchId == "resource-contain")
		{
			permission_int = RES_CONTAIN;
		}
		tmp = new Policet(policy ++, permission_int, subject, resource, action, policyId, ruleId);
		a_nplcQuints.push_back(*tmp);
	}

	return policy;
}

void XMLParser::parseFileA()
{
	if (!m_Markup->Load(m_strFileLocA))
	{
		cout << "parseFileA error." << endl;
	}
	else
	{
		int iSize = m_nplcQuints.size();
		parse(m_nplcQuints, "A");
		m_nplcFileAQuints.insert(m_nplcFileAQuints.end(), m_nplcQuints.begin() + iSize, m_nplcQuints.end());
	}
}

void XMLParser::parseFileB()
{
	if (!m_Markup->Load(m_strFileLocB))
	{
		cout << "parseFileB error." << endl;
	}
	else
	{
		int iSize = m_nplcQuints.size();
		parse(m_nplcQuints, "B");
		m_nplcFileBQuints.insert(m_nplcFileBQuints.end(), m_nplcQuints.begin() + iSize, m_nplcQuints.end());
	}
}

void XMLParser::printQuints()
{
	vector<Policet>::iterator iter;
	for (iter = m_nplcQuints.begin(); iter < m_nplcQuints.end(); iter ++)
	{
		cout << "Policy: " << (*iter).pol << endl <<
				"PolicyId: " << (*iter).policyId << endl <<
				"RuleId: " << (*iter).ruleId << endl <<
				"Permission: " << Policet::PermissionToString((*iter).per) << endl <<
				"Subject: " << (*iter).sub << endl <<
				"Resource: " << (*iter).res << endl <<
				"Action: " << (*iter).act << endl << endl;
	}
}

void XMLParser::QuintsToSubjectsAndResources()
{
	vector<Policet>::iterator iter1;
	vector<string>::iterator iter2;
	for (iter1 = m_nplcQuints.begin(); iter1 < m_nplcQuints.end(); iter1 ++)
	{
		if ((*iter1).per <= DENYB)
		{
			if (m_nstrSubjects.size() == 0)
			{
				m_nstrSubjects.push_back((*iter1).sub);
			}
			else
			{
				for (iter2 = m_nstrSubjects.begin(); iter2 < m_nstrSubjects.end(); iter2 ++)
				{
					if ((*iter2) == (*iter1).sub)
					{
						break;
					}
					else if (iter2 == m_nstrSubjects.end() - 1)
					{
						m_nstrSubjects.push_back((*iter1).sub);
						break;
					}
				}
			}

			if (m_nstrResources.size() == 0)
			{
				m_nstrResources.push_back((*iter1).res);
			}
			else
			{
				for (iter2 = m_nstrResources.begin(); iter2 < m_nstrResources.end(); iter2 ++)
				{
					if ((*iter2) == (*iter1).res)
					{
						break;
					}
					else if (iter2 == m_nstrResources.end() - 1)
					{
						m_nstrResources.push_back((*iter1).res);
						break;
					}
				}
			}
		}
		else if ((*iter1).per == SUB_CONTAIN)
		{
			if (m_nstrSubjects.size() == 0)
			{
				m_nstrSubjects.push_back((*iter1).sub);
			}
			else
			{
				for (iter2 = m_nstrSubjects.begin(); iter2 < m_nstrSubjects.end(); iter2 ++)
				{
					if ((*iter2) == (*iter1).sub)
					{
						break;
					}
					else if (iter2 == m_nstrSubjects.end() - 1)
					{
						m_nstrSubjects.push_back((*iter1).sub);
						break;
					}
				}
				for (iter2 = m_nstrSubjects.begin(); iter2 < m_nstrSubjects.end(); iter2 ++)
				{
					if ((*iter2) == (*iter1).res)
					{
						break;
					}
					else if (iter2 == m_nstrSubjects.end() - 1)
					{
						m_nstrSubjects.push_back((*iter1).res);
						break;
					}
				}
			}
		}
		else if ((*iter1).per == RES_CONTAIN)
		{
			if (m_nstrResources.size() == 0)
			{
				m_nstrResources.push_back((*iter1).sub);
			}
			else
			{
				for (iter2 = m_nstrResources.begin(); iter2 < m_nstrResources.end(); iter2 ++)
				{
					if ((*iter2) == (*iter1).sub)
					{
						break;
					}
					else if (iter2 == m_nstrResources.end() - 1)
					{
						m_nstrResources.push_back((*iter1).sub);
						break;
					}
				}
				for (iter2 = m_nstrResources.begin(); iter2 < m_nstrResources.end(); iter2 ++)
				{
					if ((*iter2) == (*iter1).res)
					{
						break;
					}
					else if (iter2 == m_nstrResources.end() - 1)
					{
						m_nstrResources.push_back((*iter1).res);
						break;
					}
				}
			}
		}
		else
		{
			cout << "QuintsToSubjectsAndResources error." << endl;
		}
	}

}

int XMLParser::QuintsToSubjectsNO(int iNO)
{
	vector<string>::iterator iter;
	int i = 0;
	for (iter = m_nstrSubjects.begin(); iter < m_nstrSubjects.end(); iter ++)
	{
		if (m_nplcQuints[iNO].sub == (*iter))
			return i;
		i ++;
	}
	return -1;
}

int XMLParser::QuintsToSubjectsNO2(int iNO)
{
	vector<string>::iterator iter;
	int i = 0;
	for (iter = m_nstrSubjects.begin(); iter < m_nstrSubjects.end(); iter ++)
	{
		if (m_nplcQuints[iNO].res == (*iter))
			return i;
		i ++;
	}
	return -1;
}

int XMLParser::QuintsToResourcesNO(int iNO)
{
	vector<string>::iterator iter;
	int i = 0;
	for (iter = m_nstrResources.begin(); iter < m_nstrResources.end(); iter ++)
	{
		if (m_nplcQuints[iNO].res == (*iter))
			return i;
		i ++;
	}
	return -1;
}

int XMLParser::QuintsToResourcesNO2(int iNO)
{
	vector<string>::iterator iter;
	int i = 0;
	for (iter = m_nstrResources.begin(); iter < m_nstrResources.end(); iter ++)
	{
		if (m_nplcQuints[iNO].sub == (*iter))
			return i;
		i ++;
	}
	return -1;
}

vector<string> XMLParser::FileAQuintsToString()
{
	vector<string> nstr;
	string temp;
	vector<Policet>::iterator iter;
	for (iter = m_nplcFileAQuints.begin(); iter < m_nplcFileAQuints.end(); iter ++)
	{
		
		temp = "Policy: " + itos((*iter).pol) + "\r\n";
		temp += "PolicyId: " + (*iter).policyId + "\r\n";
		temp += "RuleId: " + (*iter).ruleId + "\r\n";
		temp += "Permission: " + Policet::PermissionToString((*iter).per) + "\r\n";
		temp += "Subject: " + (*iter).sub + "\r\n";
		temp += "Resource: " + (*iter).res + "\r\n";
		temp += "Action: " +(*iter).act + "\r\n";
		nstr.push_back(temp);

// 		temp = "策略:   " + itos((*iter).pol) + "\r\n";
// 		temp += "策略ID: " + (*iter).policyId + "\r\n";
// 		temp += "规则ID: " + (*iter).ruleId + "\r\n";
// 		temp += "权限:   " + Policet::PermissionToString((*iter).per) + Policet::PermissionToText((*iter).per) + "\r\n";
// 		temp += "主体:   " + (*iter).sub + "\r\n";
// 		temp += "资源:   " + (*iter).res + "\r\n";
// 		temp += "动作:   " +(*iter).act + "\r\n";
// 		nstr.push_back(temp);
	}
	return nstr;
}

vector<string> XMLParser::FileBQuintsToString()
{
	vector<string> nstr;
	string temp;
	vector<Policet>::iterator iter;
	for (iter = m_nplcFileBQuints.begin(); iter < m_nplcFileBQuints.end(); iter ++)
	{
	
		temp = "Policy: " + itos((*iter).pol) + "\r\n";
		temp += "PolicyId: " + (*iter).policyId + "\r\n";
		temp += "RuleId: " + (*iter).ruleId + "\r\n";
		temp += "Permission: " + Policet::PermissionToString((*iter).per) + "\r\n";
		temp += "Subject: " + (*iter).sub + "\r\n";
		temp += "Resource: " + (*iter).res + "\r\n";
		temp += "Action: " +(*iter).act + "\r\n";
		nstr.push_back(temp);

// 		temp = "策略:   " + itos((*iter).pol) + "\r\n";
// 		temp += "策略ID: " + (*iter).policyId + "\r\n";
// 		temp += "规则ID: " + (*iter).ruleId + "\r\n";
// 		temp += "权限:   " + Policet::PermissionToString((*iter).per) + Policet::PermissionToText((*iter).per) + "\r\n";
// 		temp += "主体:   " + (*iter).sub + "\r\n";
// 		temp += "资源:   " + (*iter).res + "\r\n";
// 		temp += "动作:   " +(*iter).act + "\r\n";
// 		nstr.push_back(temp);
	}
	return nstr;
}