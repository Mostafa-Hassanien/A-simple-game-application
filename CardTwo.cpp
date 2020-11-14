#include "CardTwo.h"

CardTwo::CardTwo(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (2 here)
}

CardTwo::~CardTwo()
{
}

CardTwo::CardTwo()
{
	cardNumber = 2;
}
void CardTwo::ReadCardParameters(Grid * pGrid)
{
	// Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Read an Integer from the user using the Input class and set the walletAmount parameter with it
	pOut ->PrintMessage("New CardTwo: Enter its wallet amount ...");
    walletAmount = pIn ->GetInteger(pOut);//Read the walletAmount parameter from the user

	// Check if the wallet amount smaller than zero
	while ( walletAmount < 0 )
	{
		pOut ->PrintMessage("New CardTwo: Re-enter its wallet amount ( a value greater than 0 )...");
      walletAmount = pIn ->GetInteger(pOut);
	}

    pOut ->ClearStatusBar();// Clear the status bar
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
		
	Output* pOut = pGrid->GetOutput();// Get pointer to Output class form the grid 
	Card::Apply(pGrid,pPlayer);// Call Apply() of the base class Card to print the message that you reached this card number

	//Increment the wallet of pPlayer by the walletAmount data member of CardTwo
	pPlayer ->SetWallet((pPlayer->GetWallet())+ walletAmount);
	string msg = "The new amount in the current player's wallet: "+ to_string(pPlayer ->GetWallet());
	pOut ->PrintMessage(msg);
	pOut->ClearStatusBar();
}

void CardTwo::Save(ofstream &OutFile, Type gameObject)
{
	if ( gameObject == Cards )
	{
	  OutFile << cardNumber << " " << position.GetCellNum() << " " << walletAmount << endl;
	}
}

void CardTwo::Load(ifstream& Infile)
{
int  CellposNum;
	Infile >> CellposNum >> walletAmount;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;
}