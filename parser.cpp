//---------------------------------------------------------------------------

#include <vcl.h>
#include "move.h"
#include "operator.h"
#pragma hdrstop

#include "parser.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
Parser::Parser(String path)
{
	try
	{
	   m_operator = true;
	   m_predicate = true;
	   m_xml = NewXMLDocument();
	   m_xml->LoadFromFile(path);
	   m_xml->Active = true;
	}catch(...)
	{
	   ShowMessage("Some problem with xml file");
	}
}
Parser::~Parser()
{
	m_xml->Active = false;
}
String Parser::clear(String arg)
{
	return Format("Clear(%s)",OPENARRAY(TVarRec,(arg)));
}
String Parser::on(String arg1,String arg2)
{
	return Format("On(%s,%s)",OPENARRAY(TVarRec,(arg1,arg2)));
}
String Parser::smaller(String arg1,String arg2)
{
	return Format("Smaller(%s,%s)",OPENARRAY(TVarRec,(arg1,arg2)));
}
String Parser::move(String element,String pile1,String pile2)
{
	return Format("Move(%s,%s,%s)",OPENARRAY(TVarRec,(element,pile1,pile2)));
}
::Move Parser::getMove(String move)
{
	TStringList *tmpArgs = new TStringList();
	tmpArgs->Delimiter = ',';
	tmpArgs->DelimitedText = move.SubString(move.Pos("(")+1,move.Pos(")")-move.Pos("(") - 1);
	::Move tmpMove(tmpArgs->Strings[0],tmpArgs->Strings[1],tmpArgs->Strings[2]);
	tmpArgs->Free();

	return tmpMove;
}
bool Parser::nextOperator()
{
	if(m_operator)
	{
	    m_current = m_xml->GetDocumentElement()->ChildNodes->FindNode(L"operators")->ChildNodes->First();	
		m_operator = false;
		return true;
	}
	m_current = m_current->NextSibling();
	return (m_current != NULL);
}
COperator Parser::getOperator()
{
	_di_IXMLNode tmpNode;	
	COperator op(m_current->Attributes["template"]);

	//add preconditions
	tmpNode = m_current->ChildNodes->FindNode(L"preconditions")->ChildNodes->First();
	do
	{
	 op.addPrecondition(tmpNode->Attributes["value"]);
     tmpNode = tmpNode->NextSibling();
	}while(tmpNode);

	//add effects
	tmpNode = m_current->ChildNodes->FindNode(L"effects")->ChildNodes->First();
	do
	{
	 op.addEffect(tmpNode->Attributes["value"]);
     tmpNode = tmpNode->NextSibling();
	}while(tmpNode);
	return  op;
}
vector<String> Parser::getInitState()
{
	vector<String> tmpInits;
	_di_IXMLNode tmpNode = m_xml->GetDocumentElement()->ChildNodes->FindNode(L"initState")->ChildNodes->First();

	do
	{
		tmpInits.push_back(tmpNode->Attributes["value"]);
		tmpNode = tmpNode->NextSibling();
	}while(tmpNode);

	return tmpInits;
}
vector<String> Parser::getEndState()
{
	vector<String> tmpEnd;
	_di_IXMLNode tmpNode = m_xml->GetDocumentElement()->ChildNodes->FindNode(L"endState")->ChildNodes->First();

	do
	{
		tmpEnd.push_back(tmpNode->Attributes["value"]);
		tmpNode = tmpNode->NextSibling();
	}while(tmpNode);

	return tmpEnd;
}
vector<COperator> Parser::getOperators()
{
	vector<COperator> tmpOperators;
	while(nextOperator())
	{
		tmpOperators.push_back(getOperator());
	}

	return tmpOperators;
}
vector<String> Parser::getObjects()
{
	vector<String> tmpObjects;
	_di_IXMLNode tmpNode = m_xml->GetDocumentElement()->ChildNodes->FindNode(L"objects")->ChildNodes->First();

	do
	{
		tmpObjects.push_back(tmpNode->Attributes["value"]);
		tmpNode = tmpNode->NextSibling();
	}while(tmpNode);

	return tmpObjects;
}
void Parser::test()
{
	_di_IXMLNode tmpNode = m_xml->GetDocumentElement()->ChildNodes->FindNode(L"initState");
	_di_IXMLNode tmpPredicate;
	tmpPredicate = tmpNode->AddChild("predicate",0);
	tmpPredicate->SetAttribute(L"value","On(1,2)");
	m_xml->SaveToFile("C:\\zlo.xml");


}
