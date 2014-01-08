//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <algorithm>
#pragma hdrstop

#include "operator.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
class CUpdater
{
public:
	void operator()(String& src)
	{
		src = StringReplace(src, m_pattern,m_value,TReplaceFlags() << rfReplaceAll);
	}
	void toReplace(String pattern,String value)
	{
		m_pattern = pattern;
		m_value   = value;
	}
private:
	String m_pattern;
	String m_value;
};
String COperator::operator[](String container)
{
	if(container == "pre")
    	return toString(m_preConditions);
	else if(container == "effects")
    	return toString(m_effects);
	return "";
}
String COperator::toString(std::vector<String>& container,String delimiter)
{
	String str;
	for(std::vector<String>::iterator it = container.begin();
		it != container.end();
		++it)
		{
			str += *it + delimiter;    	
		}
	return str;
}
COperator::COperator(String schema)
{
	m_schema = schema;
	parseArgs();
}
void COperator::addPrecondition(String preCondition)
{
	m_preConditions.push_back(preCondition);	
}
void COperator::addEffect(String effect)
{
	m_effects.push_back(effect);
}
void COperator::parseArgs()
{
	TStringList *tmpStr = new TStringList();
	tmpStr->Delimiter = ',';
	tmpStr->DelimitedText  = m_schema.SubString(m_schema.Pos("(")+1,m_schema.Pos(")")-m_schema.Pos("(") - 1);
	TStringsEnumerator *e = tmpStr->GetEnumerator();
	while(e->MoveNext())
	{
		m_args.push_back(e->Current);
	}
	tmpStr->Free();
}
int COperator::getArgsNumber()
{
	return m_args.size();
}
void COperator::update(std::vector<String> &args)
{
	CUpdater updater;
	for(int i = 0; i < args.size(); ++i)
	{
		updater.toReplace(m_args[i],args[i]);
		std::for_each(m_preConditions.begin(),m_preConditions.end(),updater);
		std::for_each(m_effects.begin(),m_effects.end(),updater);
		m_schema  =  StringReplace(m_schema,m_args[i],args[i],TReplaceFlags() << rfReplaceAll);
	}
	//sort container to be able to use includes function
	std::sort(m_preConditions.begin(),m_preConditions.end());
	std::sort(m_effects.begin(),m_effects.end());
}
std::vector<String>& COperator::getPreConditions()
{
	return m_preConditions;
}
std::vector<String>& COperator::getEffects()
{
	return m_effects;
}
String COperator::getSchema()
{
	return m_schema; 	
}
