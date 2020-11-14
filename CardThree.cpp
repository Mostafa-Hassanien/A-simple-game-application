#include "CardThree.h"
#include "Ladder.h"

CardThree::CardThree(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
}

CardThree::~CardThree()
{
}

CardThree::CardThree()
{
	cardNumber = 3;
}
void CardThree::ReadCardParameters(Grid * pGrid)
{
	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut ->PrintMessage("New Card Three .Click to continue...");
	int x,y;
	pIn->GetPointClicked(x,y);
	pOut ->ClearStatusBar();

}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Ladder*ladder=pGrid->GetNextLadder(pPlayer->GetCell()->GetCellPosition().GetCellNum());
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	//Check if there is ladder ahead of the player 
	if (ladder==NULL)
	{
		pOut ->PrintMessage("There are no ladders ahead.Click to continue...");
		int x,y;
		pIn->GetPointClicked(x,y);
		pOut ->ClearStatusBar();
		return;
	}
	//Move the player to the start of the next ladder 
	CellPosition ladderStart =ladder->GetPosition();
	pOut ->PrintMessage("Go to the start of the next ladder.Click to continue...");
	int x,y;
	pIn->GetPointClicked(x,y);
	pOut ->ClearStatusBar();
	pGrid->UpdatePlayerCell(pPlayer,ladderStart);
}
void CardThree::Save(ofstream &OutFile, Type gameObject)
{
	if ( gameObject == Cards )
	{
		OutFile << cardNumber << " " << position.GetCellNum()  << endl;
	}
}

void CardThree::Load(ifstream& Infile)
{
	int  CellposNum;
	Infile >> CellposNum;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;
}
