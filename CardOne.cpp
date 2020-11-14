#include "CardOne.h"

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}

CardOne::~CardOne()
{
}

CardOne::CardOne()
{
	cardNumber = 1;
}
void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	pOut ->PrintMessage("New CardOne: Enter its wallet amount ...");
    walletAmount = pIn ->GetInteger(pOut);
	while ( walletAmount < 0 )
	{
		pOut ->PrintMessage("New CardOne: Re-enter its wallet amount ( a value greater than 0 )...");
      walletAmount = pIn ->GetInteger(pOut);
	}
	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
    pOut ->ClearStatusBar();
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid ->GetInput();
	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==
	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid,pPlayer);
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	pPlayer ->SetWallet((pPlayer->GetWallet())- walletAmount);
	string msg = "The new amount in the current player's wallet: "+ to_string(pPlayer ->GetWallet());
	pOut ->PrintMessage(msg);
	int x,y;
	pIn ->GetPointClicked(x,y);
	pOut->ClearStatusBar();
}

void CardOne::Save(ofstream &OutFile, Type gameObject)
{
	if ( gameObject == Cards )
	{
	  OutFile << cardNumber << " " << position.GetCellNum() << " " << walletAmount << endl;
	}
}

void CardOne::Load(ifstream& Infile)
{
int  CellposNum;
	Infile >> CellposNum >> walletAmount;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;
}