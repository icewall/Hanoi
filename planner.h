//---------------------------------------------------------------------------

#ifndef plannerH
#define plannerH
//---------------------------------------------------------------------------
#include <vector>
#include <map>
#include <Classes.hpp>
#include "operator.h"
#include "parser.h"
class CPlanner
{
public:
	CPlanner(String config);
	void loadOperators();
	void loadInitState();
	void loadEndState();
	void loadObjects();
	void setInitState(std::vector<String> initState);
	void setEndState(std::vector<String> endState);
	void setObjects(std::vector<String> endState);
	void solve();
	String operator[](String container);
protected:

	Parser m_parser;
	std::vector<COperator> m_operators;
	std::vector<String> m_initState;
	std::vector<String> m_endState;
	std::vector<String> m_objects;
	std::map<int,std::vector<String> > m_results;
	int m_amountOfResults;
	void generateAllOperators();
	String toString(std::vector<String>& container);
	String toString(std::vector<COperator>& container);	
private:
	std::vector<COperator> m_readyOperators;

	void __fastcall createOperator(COperator op);
	void __fastcall apply(vector<String>& state,COperator& op);
	void __fastcall solve_inter(std::vector<std::vector<String> >& statesInPast,
					 std::vector<String>& state,
					 std::vector<String>& correctOps
					 );
	bool isEndState(vector<String>& state);
	void addSolution(int startOffset,String schema);
	bool __fastcall appearedBefore(std::vector<std::vector<String> >& statesInPast,vector<String>& state);
	void saveToFile(String str,String filePath = "rez.txt");
    int m_bestSolution;
					 
                	
                     
};
#endif
