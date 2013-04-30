#include "Translator.h"
#include "Policet.h"
#include <iostream>
using namespace std;

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

Translator::Translator()
{
	m_nplcQuints.clear();
}

Translator::Translator(vector<Policet>& a_nplcQuints)
{
	assignNames(a_nplcQuints);
	m_nplcQuints = a_nplcQuints;
}

string Translator::appendFigure(string strHead, int iRear)
{
	char cBuffer[30];
	itoa(iRear, cBuffer, 10);
	string strBuffer(cBuffer);
	return strHead + strBuffer;
}

void Translator::assignNames(vector<Policet>& a_nplcQuints)
{
	vector<Policet>::iterator iter;
	for (iter = a_nplcQuints.begin(); iter < a_nplcQuints.end(); iter ++)
	{
		(*iter).polName = appendFigure("pol_", (*iter).pol);
		(*iter).perName = appendFigure("per_", (*iter).pol);
		(*iter).subName = "sub_" + (*iter).sub;// + appendFigure("_", (*iter).pol);
		(*iter).resName = "res_" + (*iter).res;// + appendFigure("_", (*iter).pol);
		(*iter).actName = "act_" + (*iter).act;// + appendFigure("_", (*iter).pol);
	}
}

void Translator::translateAll()
{
	vector<Policet>::iterator iter;
	for (iter = m_nplcQuints.begin(); iter != m_nplcQuints.end(); iter ++)
	{
		translate(*iter, m_nstrABox);
	}
	//overlapTranslateAll(m_nplcQuints, m_nstrABox);

	cout << "translateAll ok." << endl << endl;
}

void Translator::translate(Policet plcSrc, vector<string>& strDest)
{
	if (plcSrc.per == PERMITA || plcSrc.per == DENYA || plcSrc.per == PERMITB || plcSrc.per == DENYB)
	{
		elementTranslate(plcSrc, strDest);
		affiliateTranslate(plcSrc, strDest);
	}
	else if (plcSrc.per == SUB_CONTAIN || plcSrc.per == RES_CONTAIN)
	{
		containTranslate(plcSrc, strDest);
	}
	else if (plcSrc.per == SUB_OVERLAP)
	{
		subjectOverlapTranslate(plcSrc, strDest);
	}
	else if (plcSrc.per == RES_OVERLAP)
	{
		resourceOverlapTranslate(plcSrc, strDest);
	}
	else if (plcSrc.per == ACT_OVERLAP)
	{
		actionOverlapTranslate(plcSrc, strDest);
	}
	else
	{
		cout << "translate error." << endl;
	}

}

void Translator::elementTranslate(Policet plcSrc, vector<string>& strDest)
{
	vector<string> res;

	res.push_back("(instance " + plcSrc.polName + " Policy)");
	res.push_back("(instance " + plcSrc.perName + " Permission)");
	res.push_back("(instance " + plcSrc.subName + " Subject)");
	res.push_back("(instance " + plcSrc.resName + " Resource)");
	res.push_back("(instance " + plcSrc.actName + " Action)");

	strDest.insert(strDest.end(), res.begin(), res.end());
}

void Translator::affiliateTranslate(Policet plcSrc, vector<string>& strDest)
{
	vector<string> res;
	if (plcSrc.per == PERMITA)
	{
		res.push_back("(related " + plcSrc.polName + " " + plcSrc.perName + " has_PermitA)");
	}
	else if (plcSrc.per == DENYA)
	{
		res.push_back("(related " + plcSrc.polName + " " + plcSrc.perName + " has_DenyA)");
	}
	else if (plcSrc.per == PERMITB)
	{
		res.push_back("(related " + plcSrc.polName + " " + plcSrc.perName + " has_PermitB)");
	}
	else if (plcSrc.per == DENYB)
	{
		res.push_back("(related " + plcSrc.polName + " " + plcSrc.perName + " has_DenyB)");
	}
	else
	{
		cout << "affiliateTranslate error." << endl;
	}

	res.push_back("(related " + plcSrc.perName + " " + plcSrc.subName + " has_Subject)");
	res.push_back("(related " + plcSrc.perName + " " + plcSrc.resName + " has_Resource)");
	res.push_back("(related " + plcSrc.perName + " " + plcSrc.actName + " has_Action)");

	//res.push_back("(related " + plcSrc.subName + " " + plcSrc.subName + " has_Subject_Overlap)");
	//res.push_back("(related " + plcSrc.resName + " " + plcSrc.resName + " has_Resource_Overlap)");
	//res.push_back("(related " + plcSrc.actName + " " + plcSrc.actName + " has_Action_Overlap)");

	strDest.insert(strDest.end(), res.begin(), res.end());
}

void Translator::containTranslate(Policet plcSrc, vector<string>& strDest)
{
	string strTemp;
	vector<string> res;
	if (plcSrc.per == SUB_CONTAIN)
	{
		res.push_back("(related sub_" + plcSrc.sub + " sub_" + plcSrc.res + " has_subSubject)");
		res.push_back("(related sub_" + plcSrc.sub + " sub_" + plcSrc.res + " has_subSubjectOrigin)");
	}
	else if (plcSrc.per == RES_CONTAIN)
	{
		res.push_back("(related res_" + plcSrc.sub + " res_" + plcSrc.res + " has_subResource)");
		res.push_back("(related res_" + plcSrc.sub + " res_" + plcSrc.res + " has_subResourceOrigin)");
	}
	else
	{
		cout << "containTranslate error." << endl;
	}

	strDest.insert(strDest.end(), res.begin(), res.end());
}

void Translator::subjectOverlapTranslate(Policet plcSrc, vector<string>& nstrDest)
{
	vector<string> res;
	if (plcSrc.per == SUB_OVERLAP)
	{
		res.push_back("(related sub_" + plcSrc.sub + " sub_" + plcSrc.res + " has_Subject_Overlap)");
	}
	else
	{
		cout << "subjectOverlapTranslate error." << endl;
	}

	nstrDest.insert(nstrDest.end(), res.begin(), res.end());
}

void Translator::resourceOverlapTranslate(Policet plcSrc, vector<string>& nstrDest)
{
	vector<string> res;
	if (plcSrc.per == RES_OVERLAP)
	{
		res.push_back("(related res_" + plcSrc.sub + " res_" + plcSrc.res + " has_Resource_Overlap)");
	}
	else
	{
		cout << "resourceOverlapTranslate error." << endl;
	}

	nstrDest.insert(nstrDest.end(), res.begin(), res.end());
}

void Translator::actionOverlapTranslate(Policet plcSrc, vector<string>& nstrDest)
{
	vector<string> res;
	if (plcSrc.per == ACT_OVERLAP)
	{
		res.push_back("(related act_" + plcSrc.sub + " act_" + plcSrc.res + " has_Action_Overlap)");
	}
	else
	{
		cout << "actionOverlapTranslate error." << endl;
	}

	nstrDest.insert(nstrDest.end(), res.begin(), res.end());
}

void Translator::overlapTranslateAll(vector<Policet>& nplcSrc, vector<string>& nstrDest)
{
	//vector<Policet> nplcRes;
	vector<string> nstrRes;

	vector<Policet>::iterator iter1;
	vector<Policet>::iterator iter2;
	
	//int index = nplcSrc.size();

	for (iter1 = nplcSrc.begin(); iter1 != nplcSrc.end(); iter1 ++)
	{
		for (iter2 = iter1 + 1; iter2 != nplcSrc.end(); iter2 ++)
		{
			if ((*iter1).sub == (*iter2).sub)
			{
				//nplcRes.push_back(new Policet(index ++, SUB_OVERLAP, ))


				nstrRes.push_back("(related " + (*iter1).subName + " " + (*iter2).subName + " has_Subject_Overlap)");
				nstrRes.push_back("(related " + (*iter2).subName + " " + (*iter1).subName + " has_Subject_Overlap)");
			}
			if ((*iter1).res == (*iter2).res)
			{
				nstrRes.push_back("(related " + (*iter1).resName + " " + (*iter2).resName + " has_Resource_Overlap)");
				nstrRes.push_back("(related " + (*iter2).resName + " " + (*iter1).resName + " has_Resource_Overlap)");
			}
			if ((*iter1).act == (*iter2).act)
			{
				nstrRes.push_back("(related " + (*iter1).actName + " " + (*iter2).actName + " has_Action_Overlap)");
				nstrRes.push_back("(related " + (*iter2).actName + " " + (*iter1).actName + " has_Action_Overlap)");
			}
		}
	}

	nstrDest.insert(nstrDest.end(), nstrRes.begin(), nstrRes.end());
}

void Translator::printABox()
{
	vector<string>::iterator iter;
	cout << endl << "/////////////////////////ABox BEGIN///////////////////////////////" << endl;
	for (iter = m_nstrABox.begin(); iter < m_nstrABox.end(); iter ++)
	{
		cout << *iter << endl;
	}
	cout << "/////////////////////////ABox END/////////////////////////////////" << endl << endl;
}

vector<string> Translator::getABox()
{
	return m_nstrABox;
}

vector<Policet> Translator::getQuints()
{
	return m_nplcQuints;
}