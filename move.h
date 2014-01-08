//---------------------------------------------------------------------------

#ifndef moveH
#define moveH
//---------------------------------------------------------------------------
class Move
{
public:
	Move()throw(Exception);
	Move(String move);
	Move(String element,String pileSource,String pileDestiny);
	Move& operator=(const Move& rhs);
	Move(const Move& src);
	~Move();	
	String getMove();
	TStringList* getPreconditions();
	TStringList* getEffects();
	String getElement();
	String getSource();
	String getDestiny();

private:
	String m_move;
	TStringList *m_preconditions;
	TStringList *m_args;
	TStringList *m_effects;

	void copyFrom(const Move& src);	
};
#endif
