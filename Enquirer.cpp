#include "Enquirer.h"
#include "JRacerInterface.h"
#include "Policet.h"
#include <iostream>
#include <fstream>
using namespace std;

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

void Enquirer::initConnection()
{
	m_strIP = "127.0.0.1";
	m_iPort = 8088;
}

Enquirer::Enquirer()
{
	m_nstrABox.clear();
	m_nplcQuints.clear();
	//initRuleBase();

	m_iProgress = 0;

	initConnection();
	m_JRacer = new JRacerInterface(m_strIP, m_iPort);
	m_JRacer->openConnection();
	
	m_iProgress = 5;
		
	//submitInformation();
	
	m_nstrReport.clear();
}

Enquirer::Enquirer(vector<string>& a_nstrABox, vector<Policet>& a_nplcQuints)
{
	m_nstrABox.clear();
	m_nplcQuints.clear();
	for (int i = 0; i < 16; i ++)
	{
		m_nstrABox.insert(m_nstrABox.end(), a_nstrABox.begin(), a_nstrABox.end());
		m_nplcQuints.insert(m_nplcQuints.end(), a_nplcQuints.begin(), a_nplcQuints.end());
	}


	//initRuleBase();
	m_iProgress = 0;

	initConnection();
	m_JRacer = new JRacerInterface(m_strIP, m_iPort);
	m_JRacer->openConnection();

	m_iProgress = 5;

	//submitInformation();

	m_nstrReport.clear();
}

Enquirer::~Enquirer()
{
	m_JRacer->closeConnection();
	delete(m_JRacer);
	m_JRacer = NULL;
}

void Enquirer::setTBox(vector<string>& a_nstrTBox)
{
	m_nstrTBox = a_nstrTBox;
}
vector<string> Enquirer::getTBox()
{
	return m_nstrTBox;
}
void Enquirer::setSWRLR(vector<string>& a_nstrSWRLR)
{
	m_nstrSWRLR = a_nstrSWRLR;
}
vector<string> Enquirer::getSWRLR()
{
	return m_nstrSWRLR;
}
void Enquirer::setABox(vector<string>& a_nstrABox)
{
	m_nstrABox = a_nstrABox;
}
vector<string> Enquirer::getABox()
{
	return m_nstrABox;
}
void Enquirer::setQuints(vector<Policet>& a_nplcQuints)
{
	m_nplcQuints = a_nplcQuints;
}
vector<Policet> Enquirer::getQuints()
{
	return m_nplcQuints;
}

void Enquirer::printReport()
{
	vector<string>::iterator iter;
	for (iter = m_nstrReport.begin(); iter < m_nstrReport.end(); iter ++)
	{
		cout << *iter << endl;
	}
}

vector<string> Enquirer::getReport()
{
	return m_nstrReport;
}

void Enquirer::loadFile(string strFile, vector<string>& nsString)
{
	ifstream fIn(strFile.c_str(), ios::in);
	if (!fIn)
	{
		cout << "Cannot open file." << endl;
		return;
	}
	nsString.clear();
	string s;
	char c;
	while (fIn.get(c))
	{
		if (c != '\n' && c != '\t')
			s += c;
	}
	fIn.close();

	int index = 0;
	int pos1, pos2;
	int level = 0;

	int head = 0;
	int rear = 0;

	int flag = 1;
	while (index < s.length() && flag)
	{
		pos1 = s.find("(", index);
		pos2 = s.find(")", index);

		if (pos1 == string::npos && pos2 == string::npos)
		{
			break;
			flag  = 0;
		}
		else if (pos1 == string::npos)
		{
			level --;
			index = pos2 + 1;
		}
		else if (pos1 < pos2)
		{
			level ++;
			index = pos1 + 1;
		}
		else if (pos2 < pos1)
		{
			level --;
			index = pos2 + 1;
		}

		if (level == 0)
		{
			head = rear;
			rear = index;

			while (s[head] == ' ' || s[head] == '\t' || s[head] == '\n' || s[head] == -1)
				head ++;
			nsString.push_back(s.substr(head, rear - head));
			//cout << endl << "///////////////////////////////////////////////////////////" << endl;
			//cout << s.substr(head, rear - head);
			//cout << endl << "///////////////////////////////////////////////////////////" << endl;
		}

	}
}

void Enquirer::initRuleBase(string a_strTBoxLocation, string a_strSWRLRLocation)
{
	loadFile(a_strTBoxLocation, m_nstrTBox);
	loadFile(a_strSWRLRLocation, m_nstrSWRLR);
}

void Enquirer::submitInformation()
{
	vector<string>::iterator iter;

	/*
	vector<string> s;
	loadFile("C:\\PCDExample.racer", s);
	for (iter = s.begin(); iter < s.end(); iter ++)
	{
		m_JRacer->sendCommand(*iter);
	}*/

	m_JRacer->sendCommand("(full-reset)");
	m_JRacer->sendCommand("(restore-standard-settings)");
	m_JRacer->sendCommand("(process-set-at-a-time)");
	m_JRacer->sendCommand("(add-rule-consequences-automatically)");
	//cout << m_JRacer->sendCommand("(describe-query-processing-mode)") << endl;

	int i = 1;
	for (iter = m_nstrTBox.begin(); iter < m_nstrTBox.end(); iter ++)
	{
		m_JRacer->sendCommand(*iter);
		cout << "submit TBox Sentence-" + itos(i ++) + "." << endl;
	}
	cout << "submit TBox ok." << endl << endl;
	m_iProgress = 10;

	i = 1;
	for (iter = m_nstrABox.begin(); iter < m_nstrABox.end(); iter ++)
	{
		m_JRacer->sendCommand(*iter);
		cout << "submit ABox Sentence-" + itos(i ++) + "." << endl;
	}
	cout << "submit ABox ok." << endl << endl;
	m_iProgress = 20;

	i = 1;
	for (iter = m_nstrSWRLR.begin(); iter < m_nstrSWRLR.end(); iter ++)
	{
		m_JRacer->sendCommand(*iter);
		//cout << m_JRacer->sendCommand(*iter) << endl;
		//cout << m_JRacer->sendCommand("(add-chosen-sets-of-rule-consequences :last)") << endl;
		cout << "submit SWRLR Rule-" + itos(i ++) + "." << endl;
		//Sleep(5000);
	}
	cout << "submit SWRLR ok." << endl << endl;
	m_iProgress = 70;

	//cout <<  m_JRacer->sendCommand("(current-abox)") << endl;
	cout << "submitInformation ok." << endl << endl;
	
}

string Enquirer::itos(int i)
{
	char cBuffer[10];
	itoa(i, cBuffer, 10);
	string s(cBuffer);
	return s;
}

void Enquirer::implementEnquiryAllOld()
{
	int iPolicy = m_nplcQuints.size();
	int iRolePolicy = 0;
	int iTargetPolicy;
	
	vector<Policet>::iterator iter;
	for (iter = m_nplcQuints.begin(); iter < m_nplcQuints.end(); iter ++)
	{
		if ((*iter).per == SUB_CONTAIN || (*iter).per == RES_CONTAIN ||  (*iter).per == ACT_OVERLAP)
		{
			iRolePolicy ++;
		}
	}
	
	for (int k = 0; k < iPolicy - iRolePolicy; k ++)
	{
		if (enquirePolicyPermitB(k))
		{
			iTargetPolicy = k;
			break;
		}
		else if (enquirePolicyDenyB(k))
		{
			iTargetPolicy = k;
			break;
		}
	}

	cout << "iPolicy = " << iPolicy << endl;
	cout << "iRolePolicy = " << iRolePolicy << endl;
	cout << "iTargetPolicy = " << iTargetPolicy << endl << endl;

	m_nstrReport.clear();

	for (int i = 0; i < iPolicy - iRolePolicy; i ++)
	{
		if ( i != iTargetPolicy)
		{
			implementEnquiry(i, iTargetPolicy);
		}
	}
	//implementEnquiry(0, 1);

	cout << "implementEnquiryAll ok." << endl << endl;
	m_iProgress = 100;
}

void Enquirer::implementEnquiryAll()
{
	if (m_nplcQuints[0].per == PERMITB || m_nplcQuints[0].per == DENYB)
	{
		implementEnquiryAllOld();
		return;
	}

	vector<int> niDirectIndices;
	for (int i = 0; i < m_nplcQuints.size(); i ++)
	{
		if (m_nplcQuints[i].per == PERMITA ||  m_nplcQuints[i].per == DENYA ||
			m_nplcQuints[i].per == PERMITB || m_nplcQuints[i].per == DENYB)
		{
			niDirectIndices.push_back(i);
		}
	}

	m_nstrReport.clear();
	for (i = 0; i < niDirectIndices.size(); i ++)
	{
		for (int j = i + 1; j < niDirectIndices.size(); j ++)
		{
			implementEnquiry(niDirectIndices[i], niDirectIndices[j]);
		}
	}
	
	cout << "implementEnquiryAll2 ok." << endl << endl;
	m_iProgress = 100;
}

void Enquirer::implementEnquiry(int i, int j)
{
	char temp[100] = "";
	string s;
	if (enquirePolicyConflict(i, j))
	{
		m_niConflictIndex.push_back(i);

		m_nstrReport.push_back("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")" + 
			"与策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")" + "发生冲突.");

		if (enquirePolicyPermitA(i))
		{
			m_nstrReport.push_back("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")" + 
				"是策略文件1中的一条允许授权策略.");
		}
		else if (enquirePolicyDenyA(i))
		{
			m_nstrReport.push_back("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")" + 
				"是策略文件1中的一条拒绝授权策略.");
		}
		else if (enquirePolicyPermitB(i))
		{
			m_nstrReport.push_back("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")" + 
				"是策略文件2中的一条允许授权策略.");
		}
		else if (enquirePolicyDenyB(i))
		{
			m_nstrReport.push_back("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")" + 
				"是策略文件2中的一条拒绝授权策略.");
		}
		else
		{
			cout << "enquirePolicy(Permit/Deny)(A/B) " + itos(i) + " error." << endl;
		}

		if (enquirePolicyPermitA(j))
		{
			m_nstrReport.push_back("策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")" + 
				"是策略文件1中的一条允许授权策略.");
		}
		else if (enquirePolicyDenyA(j))
		{
			m_nstrReport.push_back("策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")" + 
				"是策略文件1中的一条拒绝授权策略.");
		}
		else if (enquirePolicyPermitB(j))
		{
			m_nstrReport.push_back("策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")" + 
				"是策略文件2中的一条允许授权策略.");
		}
		else if (enquirePolicyDenyB(j))
		{
			m_nstrReport.push_back("策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")" + 
				"是策略文件2中的一条拒绝授权策略.");
		}
		else
		{
			cout << "enquirePolicy(Permit/Deny)(A/B) " + itos(j) + " error." << endl;
		}

		m_nstrReport.push_back("");
		
		int flag;
		m_nstrReport.push_back("主体的包含序列为：");
		vector<string> nstrRes1 = enquireSubjectContain(i, j);
		if (nstrRes1.size() == 0)
		{
			nstrRes1 = enquireSubjectContain(j, i);
			if (nstrRes1.size() == 0)
			{
				cout << "enquireSubjectContain error." << endl;
			}
			else
			{
				flag = 0;
			}
		}
		else
		{
			flag = 1;
		}

		
		string strRes1;
		vector<string>::iterator iter;
		
		if (flag == 1)
		{
			strRes1 += ("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")的主体");
		}
		else
		{
			strRes1 += ("策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")的主体");
		}
		if (nstrRes1[1] == "The same subject")
		{
			if (flag == 1)
			{
				strRes1 += (nstrRes1[0] + " 与 策略" + itos(m_nplcQuints[j].pol) + "(ID = " +
					m_nplcQuints[j].policyId + ")的主体" + nstrRes1[2] + "相同");
			}
			else
			{
				strRes1 += (nstrRes1[0] + " 与 策略" + itos(m_nplcQuints[i].pol) + "(ID = " +
					m_nplcQuints[i].policyId + ")的主体" + nstrRes1[2] + "相同");
			}
		}
		else
		{
			for (iter = nstrRes1.begin(); iter < nstrRes1.end(); iter ++)
			{
				if (iter != nstrRes1.end() - 1)
				{
					strRes1 += ((*iter) + " 包含 ");
				}
				else
				{
					if (flag == 1)
					{
						strRes1 += ("策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")的主体" + *iter);
					}
					else
					{
						strRes1 += ("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")的主体" + *iter);
					}
				}
			}
		}
		m_nstrReport.push_back(strRes1);
		m_nstrReport.push_back("");

		m_nstrReport.push_back("资源的包含序列为：");
		vector<string> nstrRes2 = enquireResourceContain(i, j);
		if (nstrRes2.size() == 0)
		{
			nstrRes2 = enquireResourceContain(j, i);
			if (nstrRes2.size() == 0)
			{
				cout << "enquireResourceContain error." << endl;
			}
			else
			{
				flag = 0;
			}
		}
		else
		{
			flag = 1;
		}

		string strRes2;
		
		if (flag == 1)
		{
			strRes2 += ("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")的资源");
		}
		else
		{
			strRes2 += ("策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")的资源");
		}
		if (nstrRes2[1] == "The same resource")
		{
			if (flag == 1)
			{
				strRes2 += (nstrRes2[0] + " 与 策略" + itos(m_nplcQuints[j].pol) + "(ID = " +
					m_nplcQuints[j].policyId + ")的资源" + nstrRes2[2] + "相同");
			}
			else
			{
				strRes2 += (nstrRes2[0] + " 与 策略" + itos(m_nplcQuints[i].pol) + "(ID = " +
					m_nplcQuints[i].policyId + ")的资源" + nstrRes2[2] + "相同");
			}
		}
		else
		{
			for (iter = nstrRes2.begin(); iter < nstrRes2.end(); iter ++)
			{
				if (iter != nstrRes2.end() - 1)
				{
					strRes2 += ((*iter) + " 包含 ");
				}
				else
				{
					if (flag == 1)
					{
						strRes2 += ("策略" + itos(m_nplcQuints[j].pol) + "(ID = " + m_nplcQuints[j].policyId + ")的资源" + *iter);
					}
					else
					{
						strRes2 += ("策略" + itos(m_nplcQuints[i].pol) + "(ID = " + m_nplcQuints[i].policyId + ")的资源" + *iter);
					}
				}
			}
		}
		m_nstrReport.push_back(strRes2);
		m_nstrReport.push_back("\n");

		m_niSubjectContain.push_back(GetSubjectContain(nstrRes1));
		m_niResourceContain.push_back(GetResourceContain(nstrRes2));


		/*
		m_nstrReport.push_back("Policy " + itos(i) + " has conflict with Policy " + itos(j) + ".");

		if (enquirePolicyPermitA(i))
		{
			m_nstrReport.push_back("Policy " + itos(i) + " is a PermitA policy.");
		}
		else if (enquirePolicyDenyA(i))
		{
			m_nstrReport.push_back("Policy " + itos(i) + " is a DenyA policy.");
		}
		else if (enquirePolicyPermitB(i))
		{
			m_nstrReport.push_back("Policy " + itos(i) + " is a PermitB policy.");
		}
		else if (enquirePolicyDenyB(i))
		{
			m_nstrReport.push_back("Policy " + itos(i) + " is a DenyB policy.");
		}
		else
		{
			cout << "enquirePolicy(Permit/Deny)(A/B) " + itos(i) + " error." << endl;
		}

		if (enquirePolicyPermitA(j))
		{
			m_nstrReport.push_back("Policy " + itos(j) + " is a PermitA policy.");
		}
		else if (enquirePolicyDenyA(j))
		{
			m_nstrReport.push_back("Policy " + itos(j) + " is a DenyA policy.");
		}
		else if (enquirePolicyPermitB(j))
		{
			m_nstrReport.push_back("Policy " + itos(j) + " is a PermitB policy.");
		}
		else if (enquirePolicyDenyB(j))
		{
			m_nstrReport.push_back("Policy " + itos(j) + " is a DenyB policy.");
		}
		else
		{
			cout << "enquirePolicy(Permit/Deny)(A/B) " + itos(j) + " error." << endl;
		}


		m_nstrReport.push_back("");

		m_nstrReport.push_back("Subject contain chain is:");
		vector<string> nstrRes1 = enquireSubjectContain(i, j);
		if (nstrRes1.size() == 0)
		{
			nstrRes1 = enquireSubjectContain(j, i);
			if (nstrRes1.size() == 0)
			{
				cout << "enquireSubjectContain error." << endl;
			}
		}

		string strRes1;
		vector<string>::iterator iter;
		for (iter = nstrRes1.begin(); iter < nstrRes1.end(); iter ++)
		{
			strRes1 += ((*iter) + " ");
		}
		m_nstrReport.push_back(strRes1);
		m_nstrReport.push_back("");


		m_nstrReport.push_back("Resource contain chain is:");
		vector<string> nstrRes2 = enquireResourceContain(i, j);
		if (nstrRes2.size() == 0)
		{
			nstrRes2 = enquireResourceContain(j, i);
			if (nstrRes2.size() == 0)
			{
				cout << "enquireResourceContain error." << endl;
			}
		}

		string strRes2;
		for (iter = nstrRes2.begin(); iter < nstrRes2.end(); iter ++)
		{
			strRes2 += ((*iter) + " ");
		}
		m_nstrReport.push_back(strRes2);

		m_nstrReport.push_back("\n\n");*/
	}
}

int Enquirer::obtainBool(string s)
{
	if (s == "NIL" || s == "nil")
		return 0;
	else if (s == "T" || s == "t")
		return 1;
	else
		return 2;
}

int Enquirer::enquirePolicyConflict(int ia, int ib)
{
	/*
	cout << "(running-rules)";
	cout << m_JRacer->sendCommand("(running-rules)");
	cout << endl;
	cout << "(waiting-rules)";
	cout << m_JRacer->sendCommand("(waiting-rules)");
	cout << endl;
	cout << "(ready-rules)";
	cout << m_JRacer->sendCommand("(ready-rules)");
	cout << endl;
	cout << "(active-rules)";
	cout << m_JRacer->sendCommand("(active-rules)");
	cout << endl;
	cout << "(processed-rules)";
	cout << m_JRacer->sendCommand("(processed-rules)");
	cout << endl;*/
	string strSend = "(retrieve () (" + m_nplcQuints[ia].polName + " " +
		m_nplcQuints[ib].polName + " has_Policy_Conflict))";
	//(retrieve (m_nplcQuints[ia].polName m_nplcQuints[ib].polName)(m_nplcQuints[ia].polName m_nplcQuints[ib].polName 
	//	has_Policy_Conflict))
	//(retrieve (?po1 ?po2) (?po1 ?po2 has_Policy_Conflict))

	string strRecv = m_JRacer->sendCommand(strSend);
	//string strRecv = m_JRacer->sendCommand("(retrieve ()(pol_1 pol_3 has_Policy_Conflict))");
	return obtainBool(strRecv);
}

int Enquirer::enquirePolicyPermitA(int i)
{
	string strSend = "(retrieve () (" + m_nplcQuints[i].polName + " " + m_nplcQuints[i].perName + " has_PermitA))";
	//(retrieve () (m_nplcQuints[i].polName m_nplcQuints[i].perName has_PermitA))
	string strRecv = m_JRacer->sendCommand(strSend);
	return obtainBool(strRecv);
}

int Enquirer::enquirePolicyDenyA(int i)
{
	string strSend = "(retrieve () (" + m_nplcQuints[i].polName + " " + m_nplcQuints[i].perName + " has_DenyA))";
	string strRecv = m_JRacer->sendCommand(strSend);
	return obtainBool(strRecv);
}

int Enquirer::enquirePolicyPermitB(int i)
{
	string strSend = "(retrieve () (" + m_nplcQuints[i].polName + " " + m_nplcQuints[i].perName + " has_PermitB))";
	string strRecv = m_JRacer->sendCommand(strSend);
	return obtainBool(strRecv);
}

int Enquirer::enquirePolicyDenyB(int i)
{
	string strSend = "(retrieve () (" + m_nplcQuints[i].polName + " " + m_nplcQuints[i].perName + " has_DenyB))";
	string strRecv = m_JRacer->sendCommand(strSend);
	return obtainBool(strRecv);
}

string Enquirer::genVar(int i)
{
	char cBuffer[30];
	itoa(i, cBuffer, 10);
	string strBuffer(cBuffer);
	return "?var" + strBuffer;
}

vector<string> Enquirer::enquireSubjectContain(int ia, int ib)
{
	string strHead = "(retrieve (";
	string strBody = ") (and";
	string strAtomsHead = "";
	string strAtomsRear = "";
	string strRear = "))";

	string strRecv;
	vector<string> nstrRes;

	if (m_nplcQuints[ia].subName == m_nplcQuints[ib].subName)
	{
		nstrRes.push_back(m_nplcQuints[ia].sub);
		nstrRes.push_back("The same subject");
		nstrRes.push_back(m_nplcQuints[ib].sub);
		return nstrRes;
	}

	int i = 0;
	string strSend = "(retrieve () (" + m_nplcQuints[ia].subName + " " + m_nplcQuints[ib].subName + " has_subSubjectOrigin))";
	int flag = obtainBool(m_JRacer->sendCommand(strSend));

	while (!flag)
	{
		if (i == 0)
		{
			strHead += genVar(i);
			strAtomsHead += "(" + m_nplcQuints[ia].subName + " " + genVar(i) + " has_subSubjectOrigin)";
			strAtomsRear = "(" + genVar(i) + " " + m_nplcQuints[ib].subName + " has_subSubjectOrigin)";
		}
		else
		{
			strHead += " " + genVar(i);
			strAtomsHead += " (" + genVar(i - 1) + " " + genVar(i) + " has_subSubjectOrigin)";
			strAtomsRear = " (" + genVar(i) + " " + m_nplcQuints[ib].subName + " has_subSubjectOrigin)";
		}
		i ++;
		strRecv = m_JRacer->sendCommand(strHead + strBody + strAtomsHead +strAtomsRear + strRear);
		flag = obtainBool(strRecv);

		if (i == 10)
		{
			//cout << "enquireSubjectContain error." << endl;
			return nstrRes;
		}
	}

	nstrRes.push_back(m_nplcQuints[ia].sub);//Name);
	int index = 0;
	int head, rear;
	for (int j = 0; j < i; j ++)
	{
		index = strRecv.find(genVar(j), index);
		head = index + genVar(j).length() + 1;
		rear = strRecv.find(")", index);
		nstrRes.push_back(strRecv.substr(head + 4, rear - head - 4));//(head, rear - head));
	}
	nstrRes.push_back(m_nplcQuints[ib].sub);//Name);

	return nstrRes;
}

vector<string> Enquirer::enquireResourceContain(int ia, int ib)
{
	string strHead = "(retrieve (";
	string strBody = ") (and";
	string strAtomsHead = "";
	string strAtomsRear = "";
	string strRear = "))";
	
	string strRecv;
	vector<string> nstrRes;

	if (m_nplcQuints[ia].resName == m_nplcQuints[ib].resName)
	{
		nstrRes.push_back(m_nplcQuints[ia].res);
		nstrRes.push_back("The same resource");
		nstrRes.push_back(m_nplcQuints[ib].res);
		return nstrRes;
	}
	
	int i = 0;
	string strSend = "(retrieve () (" + m_nplcQuints[ia].resName + " " + m_nplcQuints[ib].resName + " has_subResourceOrigin))";
	int flag = obtainBool(m_JRacer->sendCommand(strSend));
	
	while (!flag)
	{
		if (i == 0)
		{
			strHead += genVar(i);
			strAtomsHead += "(" + m_nplcQuints[ia].resName + " " + genVar(i) + " has_subResourceOrigin)";
			strAtomsRear = "(" + genVar(i) + " " + m_nplcQuints[ib].resName + " has_subResourceOrigin)";
		}
		else
		{
			strHead += " " + genVar(i);
			strAtomsHead += " (" + genVar(i - 1) + " " + genVar(i) + " has_subResourceOrigin)";
			strAtomsRear = " (" + genVar(i) + " " + m_nplcQuints[ib].resName + " has_subResourceOrigin)";
		}
		i ++;
		strRecv = m_JRacer->sendCommand(strHead + strBody + strAtomsHead +strAtomsRear + strRear);
		flag = obtainBool(strRecv);
		
		if (i == 10)
		{
			//cout << "enquireResourceContain error." << endl;
			return nstrRes;
		}
	}
	
	nstrRes.push_back(m_nplcQuints[ia].res);//Name);
	int index = 0;
	int head, rear;
	for (int j = 0; j < i; j ++)
	{
		index = strRecv.find(genVar(j), index);
		head = index + genVar(j).length() + 1;
		rear = strRecv.find(")", index);
		nstrRes.push_back(strRecv.substr(head + 4, rear - head - 4));//(head, rear - head));
	}
	nstrRes.push_back(m_nplcQuints[ib].res);//Name);
	
	return nstrRes;
}

vector<int> Enquirer::GetSubjectContain(vector<string> a_nstrRes)
{
	int iPolicy = m_nplcQuints.size();
	int iRolePolicy = 0;
	vector<int> iSubjectContain;
	
	vector<Policet>::iterator iter;
	for (iter = m_nplcQuints.begin(); iter < m_nplcQuints.end(); iter ++)
	{
		if ((*iter).per == SUB_CONTAIN || (*iter).per == RES_CONTAIN ||  (*iter).per == ACT_OVERLAP)
		{
			iRolePolicy ++;
		}
	}

	for (int i = 0; i < a_nstrRes.size() - 1; i ++)
	{
		for (int j = iPolicy - iRolePolicy; j < m_nplcQuints.size(); j ++)
		{
			if (m_nplcQuints[j].sub == a_nstrRes[i] && m_nplcQuints[j].res == a_nstrRes[i + 1])
			{
				iSubjectContain.push_back(j);
			}
		}
	}

	return iSubjectContain;
}

vector<int> Enquirer::GetResourceContain(vector<string> a_nstrRes)
{
	int iPolicy = m_nplcQuints.size();
	int iRolePolicy = 0;
	vector<int> iResourceContain;
	
	vector<Policet>::iterator iter;
	for (iter = m_nplcQuints.begin(); iter < m_nplcQuints.end(); iter ++)
	{
		if ((*iter).per == SUB_CONTAIN || (*iter).per == RES_CONTAIN ||  (*iter).per == ACT_OVERLAP)
		{
			iRolePolicy ++;
		}
	}
	
	for (int i = 0; i < a_nstrRes.size() - 1; i ++)
	{
		for (int j = iPolicy - iRolePolicy; j < m_nplcQuints.size(); j ++)
		{
			if (m_nplcQuints[j].sub == a_nstrRes[i] && m_nplcQuints[j].res == a_nstrRes[i + 1])
			{
				iResourceContain.push_back(j);
			}
		}
	}
	
	return iResourceContain;
}

int Enquirer::GetConflictIndex(int a_iConflictNo)
{
	vector<int>::iterator iter;
	int i = 0;
	for (iter = m_niConflictIndex.begin(); iter < m_niConflictIndex.end(); iter ++)
	{
		if (a_iConflictNo == (*iter))
		{
			return i;
		}
		i ++;
	}
	return -1;
}

string Enquirer::CutHead(string s)
{
	return s.substr(4, s.length() - 4);
}