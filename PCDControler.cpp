#include "PCDControler.h"

PCDControler::PCDControler()
{
	m_iProgress = 0;
	m_enq = NULL;
}

void PCDControler::setPolicyFiles(string a_strPolicyFileALocation, string a_strPolicyFileBLocation)
{
	m_strPolicyFileALocation = a_strPolicyFileALocation;
	m_strPolicyFileBLocation = a_strPolicyFileBLocation;
}

void PCDControler::setKnowledgeBase(string a_strTBoxLocation, string a_strSWRLRLocation)
{
	m_strTBoxLocation = a_strTBoxLocation;
	m_strSWRLRLocation = a_strSWRLRLocation;
}

void PCDControler::setDefaultKnowledgeBase(string a_strKBDir)
{
	m_strTBoxLocation = a_strKBDir + "TBox.txt";
	m_strSWRLRLocation = a_strKBDir + "SWRLR.txt";
}

void PCDControler::setLogFile(string a_strLogFileLocation)
{
	m_strLogFileLocation = a_strLogFileLocation;
}


void PCDControler::redirectTo(int iMode)
{
	if (m_handler)
	{
		m_handler->redirectTo(iMode);
	}
}

DWORD PCDControler::implementDetection()
{
	DWORD dwBeginTime=GetTickCount();
	m_handler = new ErrorHandler(m_strLogFileLocation);
	m_iProgress = 5;

	m_parser = new XMLParser(m_strPolicyFileALocation, m_strPolicyFileBLocation);
	m_iProgress = 10;
	
	m_trans = new Translator(m_parser->getQuints());
	m_trans->translateAll();
	m_iProgress = 20;
	//m_trans->printABox();
	
	m_enq = new Enquirer(m_trans->getABox(), m_trans->getQuints());
	m_enq->initRuleBase(m_strTBoxLocation, m_strSWRLRLocation);
	m_enq->submitInformation();
	m_enq->implementEnquiryAll();
	//m_enq->printReport();

	DWORD dwEndTime=GetTickCount();
	return dwEndTime - dwBeginTime;
}

int PCDControler::getProgress()
{
	if (m_iProgress < 20 || m_enq == NULL)
		return m_iProgress;
	else
		return m_iProgress + m_enq->m_iProgress * 0.8;
}

vector<string> PCDControler::getReport()
{
	return m_enq->getReport();
}

void PCDControler::printReport()
{
	m_enq->printReport();
}

void PCDControler::releaseResource()
{
	if (m_handler != NULL)
	{
		delete m_handler;
		m_handler = NULL;
	}

	if (m_parser != NULL)
	{
		delete m_parser;
		m_parser = NULL;
	}
	
	if (m_trans != NULL)
	{
		delete m_trans;
		m_trans = NULL;
	}

	if (m_enq != NULL)
	{
		delete m_enq;
		m_enq = NULL;
	}
}