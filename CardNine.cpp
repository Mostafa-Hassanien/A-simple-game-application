#include "CardNine.h"
#include "Ladder.h"
#include "Snake.h"

CardNine::CardNine(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (9)
}

CardNine::~CardNine()
{
}

CardNine::CardNine() 
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (9)
}

void CardNine::ReadCardParameters(Grid * pGrid)
{
	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut ->PrintMessage("New CardNine: Enter a special Cell for the player to move to ...");
	// read the special cell from the user
	CellToMoveTo = pIn ->GetCellClicked();
	pOut ->ClearStatusBar();
	while ( CellToMoveTo.IsValidCell() == false || CellToMoveTo.GetCellNum() == 99 )
	{
		if ( CellToMoveTo.IsValidCell() == false)
		{
	    pOut ->PrintMessage("New CardNine: Re-enter a valid special Cell to move to ...");
	    CellToMoveTo = pIn ->GetCellClicked();
	    pOut ->ClearStatusBar();
		}
		else 
		{
		pOut ->PrintMessage("Cell-to-move-to can't be the last cell, Re-enter a valid special Cell to move to ...");
	    CellToMoveTo = pIn ->GetCellClicked();
	    pOut ->ClearStatusBar();
		}
	}
}


void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	CellPosition checkCrurrentPlayerCEll = pPlayer ->GetCell() ->GetCellPosition();
	Card::Apply(pGrid,pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int CurrentCardCellNum = position.GetCellNum();
	Ladder* TheNextLadder = pGrid ->GetLadder(CellToMoveTo);
	if ( TheNextLadder )
	{
	if ( TheNextLadder->GetEndPosition().GetCellNum() ==  CurrentCardCellNum)
	   {
	   pOut ->PrintMessage("The Ladder will move you up to the same card. Click to continue...");
	int x,y;
	pIn ->GetPointClicked(x,y);
    pOut ->ClearStatusBar();
	return;
	   }
	}
	Snake* TheNextSnake = pGrid ->GetSnake(CellToMoveTo);
	if (TheNextSnake)
	{
		if ( TheNextSnake ->GetEndPosition().GetCellNum() == CurrentCardCellNum )
		{
			pOut ->PrintMessage("The Snake will bring you down to the same card. Click to continue...");
	int x,y;
	pIn ->GetPointClicked(x,y);
    pOut ->ClearStatusBar();
	return;
		}
	}
	if ( checkCrurrentPlayerCEll.GetCellNum() != CellToMoveTo.GetCellNum())
	{
	string msg = " Go to cell " + to_string(CellToMoveTo.GetCellNum()) +". Click to continue ... ";
	pOut ->PrintMessage(msg);
	int x,y;
	pIn ->GetPointClicked(x,y);
    pOut ->ClearStatusBar();
	pGrid->UpdatePlayerCell(pPlayer,CellToMoveTo);
	}
}

void CardNine::Save(ofstream &OutFile, Type gameObject)
{
	if ( gameObject == Cards )
	{
	  OutFile << cardNumber << " " << position.GetCellNum() << " " << CellToMoveTo.GetCellNum() << endl;
	}
}

 void CardNine::Load(ifstream& Infile)
 {
     int  CellposNum, CellNumToMove;
	Infile >> CellposNum >> CellNumToMove;
	CellPosition Cellpos(CellposNum);
	CellPosition CellposToMove(CellNumToMove);
	position = Cellpos;
	CellToMoveTo = CellposToMove;
 }