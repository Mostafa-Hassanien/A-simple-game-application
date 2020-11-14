#include "CardFive.h"


CardFive::CardFive(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (5 here)
}

CardFive::~CardFive()
{
}

CardFive::CardFive()
{
	cardNumber = 5;
}

void CardFive::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New CardFive.Click to continue...");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void CardFive::Apply(Grid *pGrid, Player *CurrentPlayer)
{
	Card::Apply(pGrid,CurrentPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Move forward the same number of steps that you just rolled. Click to continue...");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	CurrentPlayer ->Move(pGrid, CurrentPlayer ->getjustRolledDiceNum());
}

void CardFive::Save(ofstream& OutFile, Type gameObject)
{
	if (gameObject == Cards)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardFive::Load(ifstream& Infile)
{
	int  CellposNum;
	Infile >> CellposNum;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;
	
}