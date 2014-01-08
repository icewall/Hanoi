//---------------------------------------------------------------------------

#include <Classes.hpp>
#pragma hdrstop

#include "move.h"
#include "parser.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
Move::Move()throw(Exception)
{
	//throw Exception("Don't use this class like that!!!");
}
Move::Move(String element,String pileSource,String pileDestiny)
{
	m_preconditions = new TStringList();
	m_args		   	= new TStringList();
	m_effects 		= new TStringList();
	
	//save args
	m_args->Add(element);
	m_args->Add(pileSource);
	m_args->Add(pileDestiny);
			
	m_move = Parser::move(element,pileSource,pileDestiny);
	//generate pre-conditions
	m_preconditions->Add(Parser::clear(element));
	m_preconditions->Add(Parser::clear(pileDestiny));
	m_preconditions->Add(Parser::on(element,pileSource));
	m_preconditions->Add(Parser::smaller(element,pileDestiny));

	//generate effects
	m_effects->Add(Parser::on(element,pileDestiny));
	m_effects->Add("!"+Parser::on(element,pileSource));
	m_effects->Add("!"+Parser::clear(pileDestiny));
	m_effects->Add(Parser::clear(pileSource));
}
::Move& Move::operator=(const ::Move& rhs)
{
	if(this == &rhs)
    	return *this;

	m_preconditions->Free();
	m_args->Free();
	m_effects->Free();

    copyFrom(rhs);

	return *this;
}
Move::Move(const ::Move& src)
{
	copyFrom(src);
}
String Move::getMove()
{
	return m_move;
}
TStringList* Move::getPreconditions()
{
	return m_preconditions;
}
void Move::copyFrom(const ::Move& src)
{
	m_move = src.m_move;
	m_preconditions = new TStringList();
	m_args = new TStringList();
	m_effects = new TStringList();

	m_preconditions->AddStrings(src.m_preconditions);
	m_args->AddStrings(src.m_args);
	m_effects->AddStrings(src.m_effects);
}
Move::~Move()
{
	if(m_preconditions)
		m_preconditions->Free();

	if(m_args)
		m_args->Free();
		
	if(m_effects)
    	m_effects->Free();		
}
TStringList* Move::getEffects()
{
	return m_effects;
}
String Move::getElement()
{
	return m_args->Strings[0];
}
String Move::getSource()
{
	return m_args->Strings[1];
}
String Move::getDestiny()
{
	return m_args->Strings[2];
}
