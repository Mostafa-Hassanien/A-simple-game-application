#include "CardFour.h"
#include "Snake.h"

CardFour::CardFour(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (4 here)
}

CardFour::~CardFour()
{
}

CardFour::CardFour()
{
	cardNumber = 4;
}
void CardFour::ReadCardParameters(Grid * pGrid)
{
	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut ->PrintMessage("New Card Four. Click to continue...");
	int x,y;
	pIn->GetPointClicked(x,y);
	pOut ->ClearStatusBar();
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);// Call Apply() of the base class Card to print the message that you reached this card number
	Snake*snake=pGrid->GetNextSnake(pPlayer->GetCell()->GetCellPosition().GetCellNum());
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	//Check if there is Snake ahead of the player 
	if (snake==NULL)
	{
		pOut ->PrintMessage("There are no Snakes ahead. Click to continue");
		int x,y;
		pIn->GetPointClicked(x,y);
		pOut ->ClearStatusBar();
		return;
	}
	//Check if the player is at the end of a snake 
	CellPosition SnakeStart =snake->GetPosition();
	if ( snake ->GetEndPosition().GetCellNum()== pPlayer ->GetCell()->GetCellPosition().GetCellNum())
	{
		pOut ->PrintMessage("The next snake is the same as the previous one. Click to continue");
		int x,y;
		pIn->GetPointClicked(x,y);
		pOut ->ClearStatusBar();
		return;
	}
	//Move the player to the start of the next snake
	pOut ->PrintMessage("Go to the start of the next Snake.Click to continue...");
	int x,y;
	pIn->GetPointClicked(x,y);
	pOut ->ClearStatusBar();
	pGrid->UpdatePlayerCell(pPlayer,SnakeStart);
}
void CardFour::Save(ofstream &OutFile, Type gameObject)
{
	if ( gameObject == Cards )
	{
		OutFile << cardNumber << " " << position.GetCellNum()  << endl;
	}
}

void CardFour::Load(ifstream& Infile)
{
	int  CellposNum;
	Infile >> CellposNum;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;
}
