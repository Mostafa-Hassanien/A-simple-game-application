#include "CardSeven.h"


CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (5 here)
}

CardSeven::~CardSeven()

{

}


CardSeven::CardSeven()
{
	cardNumber = 7;
}

void CardSeven::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New CardSeven. Click to continue");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();


}

void CardSeven::Apply(Grid* pGrid, Player* CurrentPlayer)
{
	Card::Apply(pGrid,CurrentPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("You are given another dice roll. Click to continue");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	CurrentPlayer ->setCheckAnotherRoll(true);
}

void CardSeven::Save(ofstream& OutFile, Type gameObject)
{
	if (gameObject == Cards)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardSeven::Load(ifstream& Infile)
{
	int  CellposNum;
	Infile >> CellposNum;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;

}