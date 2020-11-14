#include "EditCardAction.h"

#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include "CardFourteen.h"



EditCardAction::EditCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	Card* CardCheck = NULL; 
	CheckEdit = true ; // initialize with true
}
EditCardAction::~EditCardAction()
{
}

void EditCardAction::ReadActionParameters() 
{
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//Read the selected cell to be edited from the user
	pOut->PrintMessage("click on the source to edit");
	CellPosition cardPosition=pIn->GetCellClicked();

	// Check if the Cell is a valid one
	if (cardPosition.IsValidCell() == false )
	{
		pGrid ->PrintErrorMessage(" The selected cell is invalid! Click to continue ...");
		pOut->ClearStatusBar();
		CheckEdit = false;
		return;
	}

	// Check if the cell already has a card
	if (pGrid->GetCard(cardPosition)== NULL)
	{
		pGrid ->PrintErrorMessage(" This cell doesn't contain any card..");
		CheckEdit = false;
		return;
	}
	// Check if the card takes values or not 
	CardCheck = pGrid->GetCard(cardPosition);
	int CardNumber=CardCheck->GetCardNumber();
	if ( CardNumber==3||CardNumber==4||CardNumber==5||CardNumber==6||CardNumber==7||CardNumber==8 )
	{
		pGrid ->PrintErrorMessage(" This Card doesn't take values..");
		CheckEdit = false;
		return;
	}
	// Clear status bar
	pOut->ClearStatusBar();
}
void EditCardAction::Execute()
{
	ReadActionParameters();		//  The first line of any Action Execution is to read its parameter first
	Card * pCard = NULL;
	Grid* pGrid = pManager->GetGrid();
	if ( CheckEdit == true )
	{
		int CardNumber=CardCheck->GetCardNumber();
		CellPosition cardPosition = CardCheck ->GetPosition();
		//  Switch case on cardNumber 
		switch (CardNumber)
		{
		case 1:
			pCard = CardCheck;
			break;
		case 2:
			pCard = CardCheck;
			break;
		case 9:
			pCard = CardCheck;
			break;
		case 10:
			pCard = CardCheck;
			break;
		case 11:
			pCard = CardCheck;
			break;
		case 12:
			pCard = CardCheck;
			break;
		case 13:
			pCard = CardCheck;
			break;
		case 14:
			pCard = CardCheck;
			break;
		}
		if (pCard)
		{
			// A- We get a pointer to the Grid from the ApplicationManager
			Grid* pGrid = pManager->GetGrid();
			// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
			pCard ->ReadCardParameters(pGrid);
		}
	}
};