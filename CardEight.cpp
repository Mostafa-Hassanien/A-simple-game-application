#include "CardEight.h"


CardEight::CardEight(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (8 here)
}

CardEight::~CardEight()

{


}


CardEight::CardEight()
{
	cardNumber = 8;
}

void CardEight::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New CardEight.Click to continue...");

	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();


}

void CardEight::Apply(Grid* pGrid, Player* CurrentPlayer)
{
	Card::Apply(pGrid,CurrentPlayer);
	CurrentPlayer->setCheck_StateCard8(true);
}

void CardEight::Save(ofstream& OutFile, Type gameObject)
{
	if (gameObject == Cards)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardEight::Load(ifstream& Infile)
{
	int  CellposNum;
	Infile >> CellposNum;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;

}



