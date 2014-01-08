//---------------------------------------------------------------------------
#include <Classes.hpp>
#pragma hdrstop

#include "hanoiCore.h"
#include "parser.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
CHanoiCore::CHanoiCore(String config)
:
CPlanner(config),
m_amountOfElements(0)
{

}
void CHanoiCore::generate()
{
	loadOperators();
	if(m_amountOfElements)
	{
		setInitState(generateInitState());
		setEndState(generateEndState());
		setObjects(generateObjects());
	}
	else
	{
		loadInitState();
		loadEndState();
		loadObjects();
	}
	//generate all possible operators
	generateAllOperators();	
}
vector<String> CHanoiCore::generateInitState()
{
	vector<String> tmpInit;
	tmpInit.push_back(Parser::clear("P2"));
	tmpInit.push_back(Parser::clear("P3"));
	tmpInit.push_back(Parser::clear("1"));
	for(int i = 1;i < m_amountOfElements;++i)
	{
		tmpInit.push_back(Parser::on(IntToStr(i),IntToStr(i+1)));
	}
	tmpInit.push_back(Parser::on(IntToStr(m_amountOfElements),"P1"));
	for(int i = 1;i < m_amountOfElements;++i)
	{
		for(int j = i;j < m_amountOfElements;++j)
		{
			tmpInit.push_back(Parser::smaller(IntToStr(i),IntToStr(j+1)));
		}
	}
	for(int i = 1;i < m_amountOfElements + 1;++i)
	{
		tmpInit.push_back(Parser::smaller(IntToStr(i),"P1"));
		tmpInit.push_back(Parser::smaller(IntToStr(i),"P2"));
		tmpInit.push_back(Parser::smaller(IntToStr(i),"P3"));
	}
	return tmpInit;
}
std::vector<String> CHanoiCore::generateEndState()
{
	std::vector<String> tmpEnd;
	tmpEnd.push_back(Parser::clear("P1"));
	tmpEnd.push_back(Parser::clear("P2"));
	tmpEnd.push_back(Parser::clear("1"));
	for(int i = 1;i < m_amountOfElements;++i)
	{
		tmpEnd.push_back(Parser::on(IntToStr(i),IntToStr(i+1)));
	}
	tmpEnd.push_back(Parser::on(IntToStr(m_amountOfElements),"P3"));
	return tmpEnd;
}
std::vector<String> CHanoiCore::generateObjects()
{
	std::vector<String> tmpObjects;
	tmpObjects.push_back("P1");
	tmpObjects.push_back("P2");
	tmpObjects.push_back("P3");
	for(int i = 1; i < m_amountOfElements + 1;++i)
	{
    	tmpObjects.push_back(IntToStr(i));
	}
	return tmpObjects;			
}
void CHanoiCore::setAmountOfElements(int amount)
{
	m_amountOfElements = amount;
}

