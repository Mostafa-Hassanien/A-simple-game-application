#include "InputDiceValue.h"
#include "Grid.h"
#include "Player.h"


InputDiceValue::InputDiceValue(ApplicationManager *pApp) : Action(pApp)
{
		// Initializes the pManager pointer of Action with the passed pointer
}

void InputDiceValue::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut ->PrintMessage("Please, enter a dice value between 1-6");
	DiceValue = pIn ->GetInteger(pOut);
	pOut->ClearStatusBar();
	while ( DiceValue > 6 || DiceValue < 1 )
	{
		pOut ->PrintMessage("Please, Re-enter a dice value between 1-6");
	    DiceValue = pIn ->GetInteger(pOut);
		pOut->ClearStatusBar();
	}

}

void InputDiceValue::Execute()
{
	
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid)
	if ( pGrid ->GetEndGame() == true )
	{
	   pOut ->PrintMessage(" The Game is finished. Thank you ! Click to continue ....");
	   int x,y;
	   pIn ->GetPointClicked(x,y);
	   return;
	}

	// 2- Get the "current" player from pGrid ( in case the game wasn't finished )
	Player* CurrentPlayer = pGrid ->GetCurrentPlayer();
	if ( pGrid ->GetEndGame() == true )
	{
	   pOut ->PrintMessage(" The Game is finished. Thank you ! Click to continue ....");
	   int x,y;
	   pIn ->GetPointClicked(x,y);
	   return;
	}
	if ( CurrentPlayer ->getCheck_PreventPlayer() == true )
	{
		CurrentPlayer ->setCheck_PreventPlayer( false );
	    pOut ->PrintMessage(" You are prevented from rolling this turn. Click to continue ...");
		int x,y;
	   pIn ->GetPointClicked(x,y);
	   pOut ->ClearStatusBar();
	   pGrid ->AdvanceCurrentPlayer();
	   CurrentPlayer ->increament_turnCount();
	   return;
	}
	if ( CurrentPlayer ->getCheck_DeductCoins() == true)
	{
	      pGrid ->DeductCoins_OnePlayer(CurrentPlayer ->getPlayerNum());
		  pOut ->PrintMessage(" Your wallet will be decreased by 20 Coins in this turn. Click to continue ... ");
		  int x,y;
	      pIn ->GetPointClicked(x,y);
	      pOut ->ClearStatusBar();
		  CurrentPlayer ->increament_NumOfDeductCoins();
	}
	// 3- ReadActionParameters
	ReadActionParameters();
	if ( CurrentPlayer ->getCheck_DeductRollNumb() == true )
	{
		 pGrid ->DeductCoins_OnePlayer(CurrentPlayer ->getPlayerNum());
		 string msg = "You got a dice value of : " + to_string(DiceValue);
		 pOut ->PrintMessage(msg);
		 int x,y;
	     pIn->GetPointClicked(x,y);
		 pOut ->ClearStatusBar();
		  pOut ->PrintMessage(" Your diceNumber will be decreased by 1 number in this turn. Click to continue ... ");
		  DiceValue -=1;
	      pIn ->GetPointClicked(x,y);
	      pOut ->ClearStatusBar();
	     CurrentPlayer ->increament_NumOfDeductRollNum();
	}
	// 4- Move the currentPlayer using function Move of class player
	CurrentPlayer ->Move(pGrid,DiceValue);
	// 5- Advance the current player number of pGrid
	pGrid ->AdvanceCurrentPlayer();
	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
}

InputDiceValue::~InputDiceValue()
{
}
