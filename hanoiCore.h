//---------------------------------------------------------------------------

#ifndef hanoiCoreH
#define hanoiCoreH
//---------------------------------------------------------------------------
#include "planner.h"
#include <vector>


class CHanoiCore : public CPlanner 
{
	public:
	CHanoiCore(String config);
    void setAmountOfElements(int amount);
	std::vector<String> generateInitState();
	std::vector<String> generateEndState();
	std::vector<String> generateObjects();
	void generate();
	
	private:

	int m_amountOfElements;
};
#endif
