//---------------------------------------------------------------------------

#ifndef operatorH
#define operatorH
//---------------------------------------------------------------------------
#include <vector>
class COperator
{

public:
	COperator(String schema);
	void addPrecondition(String preCondition);
	void addEffect(String effect);
	int getArgsNumber();
	void update(std::vector<String> &args);
	std::vector<String>& getPreConditions();
	std::vector<String>& getEffects();	
	String getSchema();
	String operator[](String container);

private:
	String m_schema;
	std::vector<String> m_preConditions;
	std::vector<String> m_args;
	std::vector<String> m_effects;

	void parseArgs();
	String toString(std::vector<String>& container,String delimiter = " ");
};
#endif
