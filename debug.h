//---------------------------------------------------------------------------

#ifndef debugH
#define debugH
//---------------------------------------------------------------------------
class debug
{
public:
	static void init(bool state = true);
	static void write(String msg);
private:
	static HANDLE m_hConsole;
	static bool m_state;
};
HANDLE debug::m_hConsole;
bool   debug::m_state;
#endif
