#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"
#include "CardSeven.h"
#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
		// Initializes the pManager pointer of Action with the passed pointer
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Player* CurrentPlayer = pGrid ->GetCurrentPlayer();
	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	if ( pGrid ->GetEndGame() == true )
	{
	   pOut ->PrintMessage(" The Game is finished. Thank you ! Click to continue ....");
	   int x,y;
	   pIn ->GetPointClicked(x,y);
	   return;
	}
	// -- If not ended, do the following --:
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
	if (CurrentPlayer->getCheck_StateCard8() == true)
	{
		CurrentPlayer->setCheck_StateCard8(false);
		pOut->PrintMessage(" You are prevented from rolling this turn. Click to continue ...");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		pGrid->AdvanceCurrentPlayer();
		CurrentPlayer->increament_turnCount();
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

	// 2- Generate a random number from 1 to 6 --> This step is done for you
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed
	if ( CurrentPlayer ->getCheck_DeductRollNumb() == true )
	{
		 string msg = "You got a dice value of : " + to_string(diceNumber);
		 pOut ->PrintMessage(msg);
		 int x,y;
	     pIn->GetPointClicked(x,y);
		 pOut ->ClearStatusBar();
		  pOut ->PrintMessage(" Your diceNumber will be decreased by 1 number in this turn. Click to continue ... ");
		  diceNumber -=1;
	      pIn ->GetPointClicked(x,y);
	      pOut ->ClearStatusBar();
	     CurrentPlayer ->increament_NumOfDeductRollNum();
	}
	string msg = "You got a dice value of : " + to_string(diceNumber);
	pOut ->PrintMessage(msg);
	int x,y;
	pIn->GetPointClicked(x,y);
	pOut ->ClearStatusBar();
	// 3- Get the "current" player from pGrid
	// 4- Move the currentPlayer using function Move of class player
	CurrentPlayer ->Move(pGrid,diceNumber);
	// 5- Advance the current player number of pGrid
	if (CurrentPlayer ->getCheckAnotherRoll())
	{
		RollDiceAction::Execute();
		return;
	}
	
	pGrid ->AdvanceCurrentPlayer();
	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
}

RollDiceAction::~RollDiceAction()
{
}
