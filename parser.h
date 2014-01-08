//---------------------------------------------------------------------------

#ifndef parserH
#define parserH
//---------------------------------------------------------------------------
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <vector>
using std::vector;

class Move;
class COperator;
class Parser
{
	public:
	Parser(String path);
	~Parser();

	static String clear(String arg);
	static String on(String arg1,String arg2);
	static String smaller(String arg1,String arg2);
	static String move(String element,String pile1,String pile2);
	static ::Move   getMove(String move);
	bool nextOperator();
	vector<String> getInitState();
	vector<String> getEndState();
	vector<String> getObjects();
	vector<COperator> getOperators();
	COperator getOperator();
	void test();
private:
	_di_IXMLDocument m_xml;
	_di_IXMLNode	 m_current;
	bool m_operator;
	bool m_predicate;


};
#endif
