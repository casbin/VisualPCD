#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#include <vector>
using namespace std;

class Policet;

class SampleQuints
{
public:
	vector<Policet> m_nstrQuints;

public:
	SampleQuints();

	vector<Policet> getQuints();
};