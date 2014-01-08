//---------------------------------------------------------------------------
#include <windows.h>
#include <Classes.hpp>
#pragma hdrstop

#include "debug.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
void debug::init(bool state)
{
	m_state = state;
	if(m_state)
	{
		AllocConsole();
		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
}
void debug::write(String msg)
{
	if(m_state)
	{
		unsigned long written;
		msg += "\n";
		WriteConsoleA(m_hConsole,
					  msg.c_str(),
					  msg.Length(),
					  &written,
					  0
					 );
	 }	

}
