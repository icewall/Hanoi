//---------------------------------------------------------------------------

#include <algorithm>
#pragma hdrstop
#include "parser.h"
#include "planner.h"
#include "formMain.h"
#include "debug.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
bool equal_operator(COperator& op1,COperator& op2){ return op1.getSchema() == op2.getSchema();}
bool lt_operator(COperator& op1,COperator& op2){ return op1.getSchema() < op2.getSchema();}

CPlanner::CPlanner(String config)
:
m_parser(config),
m_amountOfResults(0),
m_bestSolution(0x7FFFFFFF)
{
		
}
String CPlanner::toString(vector<String>& container)
{
	String tmp = "";
	for(std::vector<String>::iterator it = container.begin();
		it != container.end();
		++it)
		{
            tmp += *it + "\r\n";
		}
	return tmp;		
}
String CPlanner::toString(vector<COperator>& operators)
{
	String tmp = "";
	for(std::vector<COperator>::iterator it = operators.begin();
		it != operators.end();
		++it)
		{
            tmp += it->getSchema() + "\r\n";
		}
	return tmp;		
}
String CPlanner::operator[](String container)
{
	if(container == "init")
		return toString(m_initState);
	else if(container == "end")
		return toString(m_endState);
	else if(container == "operators")
		return toString(m_readyOperators);
	else if(container == "result")
		return toString(m_results[0]);		

	return "";
}
void CPlanner::loadOperators()
{
	m_operators = m_parser.getOperators();			
}
void CPlanner::loadInitState()
{
	m_initState = m_parser.getInitState();
	std::sort(m_initState.begin(),m_initState.end());	
}
void CPlanner::loadEndState()
{
	m_endState = m_parser.getEndState();
	std::sort(m_endState.begin(),m_endState.end());	
}
void CPlanner::loadObjects()
{
	m_objects = m_parser.getObjects(); 	
}
void CPlanner::setInitState(std::vector<String> initState)
{
	m_initState = initState;
	std::sort(m_initState.begin(),m_initState.end());
}
void CPlanner::setEndState(std::vector<String> endState)
{
	m_endState = endState;
	std::sort(m_endState.begin(),m_endState.end());
}
void CPlanner::setObjects(std::vector<String> objects)
{
	m_objects = objects;
}
void CPlanner::generateAllOperators()
{
	int i = 0;
	//generate all permutations
	std::sort(m_objects.begin(),m_objects.end());
	while( std::next_permutation(m_objects.begin(),m_objects.end()) )
	{
		for(std::vector<COperator>::iterator it = m_operators.begin();
			it != m_operators.end();
			++it)
			{
             	createOperator(*it);
			}
		i++;
	}
	//sort it and remove duplicates
   	sort(m_readyOperators.begin(),m_readyOperators.end(),lt_operator);
	m_readyOperators.erase(unique(m_readyOperators.begin(),m_readyOperators.end(),equal_operator),m_readyOperators.end());
}
void CPlanner::solve()
{
	vector<String> tmpState = m_initState;
	//add inital state as state that shouldn't appear again
	std::vector<std::vector<String> > statesInPast;
	statesInPast.push_back(m_initState);
	//try to use each operator
	for(std::vector<COperator>::iterator it = m_readyOperators.begin();
		it != m_readyOperators.end();
		++it)
		{
			//check precondition
			if(includes(
						m_initState.begin(),
						m_initState.end(),
		 				it->getPreConditions().begin(),
						it->getPreConditions().end()
					   )
			  )
			  {
				apply(tmpState,*it);
				if(!isEndState(tmpState))
				{
					vector<String> tmpCorrectOps;
					tmpCorrectOps.push_back(it->getSchema());
					statesInPast.push_back(tmpState);
//					debug::write(it->getSchema());
//					debug::write("\n");
//					debug::write(toString(tmpState));
					solve_inter(statesInPast,tmpState,tmpCorrectOps);
				}
				else
				{//add solution
				   m_results[m_amountOfResults] = vector<String>();
				   m_results[m_amountOfResults].push_back(it->getSchema());
				   m_amountOfResults++;				
				}				
				tmpState = m_initState;
			  }
		
		}
}
void __fastcall CPlanner::solve_inter(vector<vector<String> >& statesInPast,
						  std::vector<String>& state,
                          std::vector<String>& correctOps
					     )
{
	vector<String> tmpState = state;
	vector<vector<String> > tmpStatesInPast = statesInPast;
	vector<String> tmpCorrectOps = correctOps;
	for(std::vector<COperator>::iterator it = m_readyOperators.begin();
		it != m_readyOperators.end();
		++it)
		{
			//check precondition
			if(includes(
						state.begin(),
						state.end(),
		 				it->getPreConditions().begin(),
						it->getPreConditions().end()
					   )
			  )
			  {
			  	
				apply(tmpState,*it);
//				debug::write(it->getSchema());
//				debug::write("\n");
//				debug::write(toString(tmpState));				
				if(!appearedBefore(tmpStatesInPast,tmpState))
				{
//					debug::write(it->getSchema());
//					debug::write("in past\n :" + toString(state));
//					debug::write("current \n:" + toString(tmpState));
                	tmpCorrectOps.push_back(it->getSchema());
					tmpStatesInPast.push_back(tmpState);
					if(!isEndState(tmpState))
					{
						 solve_inter(tmpStatesInPast,tmpState,tmpCorrectOps);
					}
					else
					{//add solution

//						debug::write(toString(tmpCorrectOps));
//						debug::write("Size: " + IntToStr(tmpCorrectOps.size()));
//						saveToFile(toString(tmpCorrectOps)+"\r\n" + IntToStr(tmpCorrectOps.size()) + "\r\n");
						m_results[m_amountOfResults] = tmpCorrectOps;
						m_amountOfResults++;
						if(tmpCorrectOps.size() < m_bestSolution)
						{
							m_bestSolution = tmpCorrectOps.size();
							debug::write(toString(tmpCorrectOps));
							saveToFile(toString(tmpCorrectOps),"bestmoves.txt");															
						}
					}
					tmpCorrectOps = correctOps;
					tmpStatesInPast = statesInPast;					
				}
				tmpState = state;
			  }
		}
}
void __fastcall CPlanner::createOperator(COperator op)
{
	std::vector<String> args;
	for(int i=0;i < op.getArgsNumber(); ++i)
	{
		args.push_back(m_objects[i]);
	}
	op.update(args);
	//add to ready operators
	m_readyOperators.push_back(op);
}
void __fastcall CPlanner::apply(vector<String>& state,COperator& op)
{
	for(vector<String>::iterator it = op.getEffects().begin();
		it != op.getEffects().end();
		++it)
		{
			if( (*it)[1] == '!' ) //remove predicate from current state
			{
				state.erase( find(state.begin(),state.end(),it->SubString(2,it->Length())) );
			}
			else
			{
            	state.push_back(*it);
			}
		}
	sort(state.begin(),state.end());
}
bool CPlanner::isEndState(vector<String>& state)
{
	return includes(state.begin(),
				state.end(),
				m_endState.begin(),
				m_endState.end());
}
void CPlanner::addSolution(int startOffset,String schema)
{
	if(!startOffset)
		return;
	startOffset = m_amountOfResults - startOffset;
	for(int i = startOffset; i < m_results.size();++i)
	{
		m_results[i].push_back(schema);
	}
}
bool __fastcall CPlanner::appearedBefore(std::vector<std::vector<String> >& statesInPast, vector<String>& state)
{
	for(vector<vector<String> >::iterator it = statesInPast.begin();
		it != statesInPast.end();
		++it)
		{
			if(state == *it)
            	return true;
		}
	return false;
}
void CPlanner::saveToFile(String str,String filePath)
{
	TFileStream *file = new TFileStream(filePath,fmCreate);
	file->Seek((__int64)0,soEnd);
	file->Write(AnsiString(str).c_str(),AnsiString(str).Length());
	file->Free();
}
