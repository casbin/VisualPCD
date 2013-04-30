#include "SampleQuints.h"
#include "Policet.h"

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

SampleQuints::SampleQuints()
{
	m_nstrQuints.push_back(*new Policet(1, PERMITA, "s1", "r1", "a1"));
	m_nstrQuints.push_back(*new Policet(2, DENYA, "s2", "r2", "a2"));
	m_nstrQuints.push_back(*new Policet(3, DENYB, "s3", "r3", "a3"));

	m_nstrQuints.push_back(*new Policet(4, SUB_CONTAIN, "s1", "s2", ""));
	m_nstrQuints.push_back(*new Policet(5, SUB_CONTAIN, "s2", "s3", ""));

	m_nstrQuints.push_back(*new Policet(6, RES_CONTAIN, "r3", "r2", ""));
	m_nstrQuints.push_back(*new Policet(7, RES_CONTAIN, "r2", "r1", ""));

	m_nstrQuints.push_back(*new Policet(8, ACT_OVERLAP, "a1", "a2", ""));
	m_nstrQuints.push_back(*new Policet(9, ACT_OVERLAP, "a2", "a3", ""));
	m_nstrQuints.push_back(*new Policet(10, ACT_OVERLAP, "a3", "a1", ""));
}

vector<Policet> SampleQuints::getQuints()
{
	return m_nstrQuints;
}