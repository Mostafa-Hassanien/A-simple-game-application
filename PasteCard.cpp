#include "Input.h"
#include "Output.h"
#include "PasteCard.h"
#include "Grid.h"
#include "Ladder.h"
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

PasteCard::PasteCard(ApplicationManager *pApp) : Action(pApp)
{
	checkPaste = true; // checkPaste is initially true
	// Initializes the pManager pointer of Action with the passed pointer
}

PasteCard::~PasteCard()
{
}

void PasteCard::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Paste Card Action: Click to continue ...");
	int x,y;
	pIn ->GetPointClicked(x,y);
	pOut ->PrintMessage("click on the destination cell");
	// Read the DestinationCellPosition
	DestinationCellPosition = pIn ->GetCellClicked();
	if (DestinationCellPosition.IsValidCell() == false )
	{
		pGrid ->PrintErrorMessage(" Error: Destination Cell is an invalid Cell ! Click to continue ...");
	   pOut->ClearStatusBar();
	   checkPaste = false;
		return;
	}
		
	if (DestinationCellPosition.GetCellNum() == 1 || DestinationCellPosition.GetCellNum() == 99 )
	{	
		pGrid->PrintErrorMessage("You cannot place game objects in the first or last cell! Click to continue ...");
	    pOut->ClearStatusBar();
	   checkPaste = false;
		return;
	}
	Ladder* HasLadder = pGrid ->GetLadder(DestinationCellPosition);
	if ( HasLadder)
	{
	if ( HasLadder->GetPosition().GetCellNum() == DestinationCellPosition.GetCellNum())
	{
		pGrid->PrintErrorMessage(" Cell already has an object ! Click to continue ...");
	    pOut->ClearStatusBar();
	   checkPaste = false;
		return;
	}
	}
	pOut ->ClearStatusBar();
}

void PasteCard::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters(); // Reading the Parameters 
	if ( checkPaste == true )
	{
		if ( pGrid ->GetClipboard())
		{
		Card* DestinationCard;
		int CardNumber = pGrid ->GetClipboard()->GetCardNumber();
		switch ( CardNumber )
	{
	case 1:
		DestinationCard = new CardOne( *(dynamic_cast < CardOne*> ( pGrid ->GetClipboard())));
		break;
	case 2:
		DestinationCard = new CardTwo( *(dynamic_cast < CardTwo*> ( pGrid ->GetClipboard())));
		break;
	case 3:
		DestinationCard = new CardThree( *(dynamic_cast < CardThree*> ( pGrid ->GetClipboard())));
		break;
	case 4:
		DestinationCard = new CardFour( *(dynamic_cast < CardFour*> ( pGrid ->GetClipboard())));
		break;
	case 5:
		DestinationCard = new CardFive( *(dynamic_cast < CardFive*> ( pGrid ->GetClipboard())));
		break;
	case 6:
		DestinationCard = new CardSix( *(dynamic_cast < CardSix*> ( pGrid ->GetClipboard())));
		break;
	case 7:
		DestinationCard = new CardSeven( *(dynamic_cast < CardSeven*> ( pGrid ->GetClipboard())));
		break;
	case 8:
		DestinationCard = new CardEight( *(dynamic_cast < CardEight*> ( pGrid ->GetClipboard())));
		break;
	case 9:
		DestinationCard = new CardNine( *(dynamic_cast < CardNine*> ( pGrid ->GetClipboard())));
		break;
	case 10:
		DestinationCard = new CardTen( *(dynamic_cast < CardTen*> ( pGrid ->GetClipboard())));
		break;
	case 11:
		DestinationCard = new CardEleven( *(dynamic_cast < CardEleven*> ( pGrid ->GetClipboard())));
		break;
	case 12:
		DestinationCard = new CardTwelve( *(dynamic_cast < CardTwelve*> ( pGrid ->GetClipboard())));
		break;
	case 13:
		DestinationCard = new CardThirteen( *(dynamic_cast < CardThirteen*> ( pGrid ->GetClipboard())));
		break;
	case 14:
		DestinationCard = new CardFourteen( *(dynamic_cast < CardFourteen*> ( pGrid ->GetClipboard())));
		break;
	}
		DestinationCard ->setPosition(DestinationCellPosition);
	   bool added = pGrid ->AddObjectToCell(DestinationCard);	
	   if (! added)
	        {
		        // Print an appropriate message
		        pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	        }
	     DestinationCard = NULL;
	     return;
	    }
		else
		{
		pGrid->PrintErrorMessage("Error: There is no Card to be pasted ! Click to continue ...");
		return;
		}
	}
}
