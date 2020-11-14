#include "CardSix.h"


CardSix::CardSix(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (6 here)
}

CardSix::~CardSix()
{
}

CardSix::CardSix()
{
	cardNumber = 6;
}

void CardSix::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New CardSix. Click to continue...");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();


}

void CardSix::Apply(Grid* pGrid, Player* CurrentPlayer)
{
	Card::Apply(pGrid,CurrentPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Move backward the same number of steps that you just rolled. Click to continue...");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	CurrentPlayer ->Move(pGrid, (CurrentPlayer ->getjustRolledDiceNum())* -1);
}

void CardSix::Save(ofstream& OutFile, Type gameObject)
{
	if (gameObject == Cards)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardSix::Load(ifstream& Infile)
{
	int  CellposNum;
	Infile >> CellposNum;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;
}