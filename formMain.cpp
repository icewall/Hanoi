//---------------------------------------------------------------------------
#include <vcl.h>
#include <algorithm>
#pragma hdrstop
using namespace std;

#include "formMain.h"
#include "parser.h"
#include "operator.h"
#include "debug.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
int k = 0;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	:
	TForm(Owner),
	HanoiCore("problem.xml")
{
	debug::init(true);
	m_amountOfElements = 0;
	m_firstSimulation = true;
	resetGame();
}
//---------------------------------------------------------------------------
void TfrmMain::generateInitState()
{
	m_currentState->Add(Parser::clear("P2"));
	m_currentState->Add(Parser::clear("P3"));
	m_currentState->Add(Parser::clear("1"));
	for(int i = 1;i < m_amountOfElements;++i)
	{
		m_currentState->Add(Parser::on(IntToStr(i),IntToStr(i+1)));
	}
	m_currentState->Add(Parser::on(IntToStr(m_amountOfElements),"P1"));
	for(int i = 1;i < m_amountOfElements;++i)
	{
		for(int j = i;j < m_amountOfElements;++j)
		{
			m_currentState->Add(Parser::smaller(IntToStr(i),IntToStr(j+1)));
		}
	}
	for(int i = 1;i < m_amountOfElements + 1;++i)
	{
		m_currentState->Add(Parser::smaller(IntToStr(i),"P1"));
		m_currentState->Add(Parser::smaller(IntToStr(i),"P2"));
		m_currentState->Add(Parser::smaller(IntToStr(i),"P3"));
	}
}
//---------------------------------------------------------------------------
void TfrmMain::generateEndState()
{
	m_endState->Add(Parser::clear("P1"));
	m_endState->Add(Parser::clear("P2"));
	m_endState->Add(Parser::clear("1"));
	for(int i = 1;i < m_amountOfElements;++i)
	{
		m_endState->Add(Parser::on(IntToStr(i),IntToStr(i+1)));
	}
	m_endState->Add(Parser::on(IntToStr(m_amountOfElements),"P3"));
}
//---------------------------------------------------------------------------
void TfrmMain::paintBoard()
{
	int shift = 80;
	int pileX = this->ClientWidth / 3 - shift;
	int pileY = this->ClientHeight/ 2;
	int pileWidth = 10;
	int elementHeight = 20;
	int elementWidth  = 30;
	Canvas->Pen->Color = clBlack;
	for(int i = 1; i < 4; ++i)
	{
		Canvas->Brush->Color = clGray;
		Canvas->Rectangle(pileX * i,
						  pileY,
						  pileX * i + pileWidth,
						  this->ClientHeight
						  );
		int j = 1;
		Canvas->Brush->Color = clBlue;
		for(vector<int>::iterator it = m_piles[IntToStr(i)].begin();
			it != m_piles[IntToStr(i)].end();
			++it)
			{
				Canvas->Rectangle(pileX * i - ((elementWidth * (*it) ) / 2) + (pileWidth / 2),
								  this->ClientHeight - (elementHeight * j),
								  pileX * i - ((elementWidth * (*it) ) / 2) + (elementWidth * (*it) )+(pileWidth / 2),
								  this->ClientHeight  - (elementHeight * j) + elementHeight
								  );
				Canvas->Font->Color = clWhite;
				Canvas->TextOutA(pileX * i + 2.5,this->ClientHeight - (elementHeight * j) + (elementHeight /4),IntToStr(m_piles[IntToStr(i)][j-1]) );
				++j;
			}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormPaint(TObject *Sender)
{
	paintBoard();
}
//---------------------------------------------------------------------------
void TfrmMain::resetGame()
{
	for(int i = 1; i < m_piles.size() + 1;i++)
	{
     	m_piles[IntToStr(i)].clear();
	}
	//initialize piles
	for(int i = m_amountOfElements; i > 0;--i)
	{
    	m_piles["1"].push_back(i);
	}
}
//---------------------------------------------------------------------------
void TfrmMain::updateBoard(::Move move)
{
	//remove element
	for(int i = 1; i < 4; ++i)
	{
		if(!m_piles[IntToStr(i)].empty() && m_piles[IntToStr(i)].back() == move.getElement().ToInt())
		{
			m_piles[IntToStr(i)].pop_back();
			break;
		}
	}

	if(move.getDestiny().Length() > 1) //desting is a empty pile
	{
		m_piles[move.getDestiny()[2]].push_back(StrToInt(move.getElement()));
	}
	else //destiny is an element
	{
		for(int i = 1; i < 4; ++i)
		{
			if(m_piles[IntToStr(i)].back() == move.getDestiny().ToInt())
				m_piles[IntToStr(i)].push_back(move.getElement().ToInt());
		}
	}

	this->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Button1Click(TObject *Sender)
{
//
//	CHanoiCore HanoiCore("..\\problem.xml");
	HanoiCore.solve();
	tmpSol = new TStringList();
	tmpSol->Delimiter = '\n';
	tmpSol->DelimitedText =  HanoiCore["result"];
	ShowMessage("Solved!!!");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Button2Click(TObject *Sender)
{
	int amountOfElements = Edit1->Text.ToInt();
	HanoiCore.setAmountOfElements(amountOfElements);
	m_amountOfElements = amountOfElements;
	resetGame();
	paintBoard();
	HanoiCore.generate();
	Memo5->Text = HanoiCore["init"];
	Memo6->Text = HanoiCore["end"];
	Memo7->Text = HanoiCore["operators"];
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Button3Click(TObject *Sender)
{
	if(m_firstSimulation)
	{
		m_firstSimulation = false;
		bestMoves =  new TStringList();
		bestMoves->LoadFromFile("bestmoves.txt");
		e = bestMoves->GetEnumerator();
		e->MoveNext();
		m_lastMove = Parser::getMove(e->Current);
		Memo1->Lines->Text = m_lastMove.getMove();
		Memo2->Lines = m_lastMove.getPreconditions();
		Memo3->Lines = m_lastMove.getEffects();
		apply(m_lastMove);		
	}
	else
	{
		if(!e->MoveNext())
		{
			e->Free();
			bestMoves->Free();
			m_firstSimulation = true;
			updateBoard(m_lastMove);
			ShowMessage("Solved!");			
			return;
		}
		updateBoard(m_lastMove);
		m_lastMove = Parser::getMove(e->Current);
		Memo1->Lines->Text = m_lastMove.getMove();
		Memo2->Lines = m_lastMove.getPreconditions();
		Memo3->Lines = m_lastMove.getEffects();
		apply(m_lastMove);
	}
}
//---------------------------------------------------------------------------
void TfrmMain::apply(::Move& move)
{
	TStringsEnumerator *e = move.getEffects()->GetEnumerator();
	while(e->MoveNext())
	{
		if(e->Current[1] == '!')
		{
			Memo5->Lines->Delete(Memo5->Lines->IndexOf(e->Current.SubString(2,e->Current.Length())) );
		}
		else //add something
		{
			Memo5->Lines->Add(e->Current);        	
		}
	}
	TStringList *tmpState = new TStringList(); 
	TStringsEnumerator *eM = Memo5->Lines->GetEnumerator();
	while(eM->MoveNext())
	{
     	tmpState->Add(eM->Current);
	}
	Memo5->Clear();
	tmpState->Sort();
	Memo5->Lines->AddStrings(tmpState);
	tmpState->Free();
	eM->Free();
}

