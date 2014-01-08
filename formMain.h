//---------------------------------------------------------------------------

#ifndef formMainH
#define formMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <vector>
#include <map>
#include "hanoiCore.h"
#include "move.h"
//---------------------------------------------------------------------------
using std::vector;
using std::map;


class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TMemo *Memo1;
	TMemo *Memo2;
	TMemo *Memo3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TMemo *Memo5;
	TLabel *Label5;
	TMemo *Memo6;
	TLabel *Label6;
	TButton *Button1;
	TMemo *Memo7;
	TButton *Button2;
	TButton *Button3;
	TEdit *Edit1;
	TLabel *Label4;
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
	int m_amountOfElements; 
	//piles
	map<String,vector<int> > m_piles;
	TStringList *m_currentState;
	TStringList *m_endState;
	void generateInitState();
	void generateEndState();
	CHanoiCore HanoiCore;	

public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);

public:
	void paintBoard();
	void resetGame();
	void updateBoard(::Move move);  
	String Move(String element,String pileSource,String pileDestiny);
	TStringList *tmpSol;
	TStringList *bestMoves;
	TStringsEnumerator *e;
	bool m_firstSimulation;
	::Move m_lastMove;
	void apply(::Move& move);
		
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
