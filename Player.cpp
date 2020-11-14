#include "Player.h"
#include"Lightning.h"
#include "GameObject.h"
#include "Ice.h"
#include "Fire.h"
#include "Poison.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;  // initialize the turn count with zero 
	NumberOfAttacks = 0; // initialize the number of attacks with zero 
	// Make all the needed initialization or validations
	for (int i =0; i < MaximumUniqueAttacks; i++)
	{
	    Attacks[i] = NULL; //  intialize the pointers to NULL
	}
	    Check_PreventPlayer = false; // intialize prevent player with false ( was not prevented )
		Check_DeductCoins = false;  // intialize Check_DeductCoins with false ( was not burned )
		NumOfDeductCoins = 0; // intialize NumOfDeductCoins with (0) (player was not affected by Fire Attack yet )
	    Check_DeductRollNumb= false;//  intialize Check_DeductRollNumb with false ( was not poisoned )
		CheckAnotherRoll = false; // initialize CheckAnotherRoll with false ( the player has not given Another Roll yet )
	    NumOfDeductRollNum = 0; // intialize NumOfDeductRollNum with (0) (player was not affected by Poison Attack yet )
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

void Player::SetTurnCount( int x)
{
   turnCount = ( x < 3 && x > -1 ) ? x:0;
}

void Player::increament_turnCount()
{
	turnCount++;
	if ( turnCount == 3 )
		turnCount = 0;
}
Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetStepCount(int x)
{
stepCount = ( x > 0) ? x : 0;
}

void Player::SetWallet(int wallet)
{
	this->wallet = ( wallet > 0 ) ? wallet:0;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}
int Player::getjustRolledDiceNum()
{
	return justRolledDiceNum;
}

int Player::GetTurnCount() const
{
	return turnCount;
}
SpecialAttack* Player::getthefirstAttack()
{
	return Attacks[0];
}
SpecialAttack* Player::getCurrentAttack()
{
	return Attacks[NumberOfAttacks];
}

int Player::gettheNumAttacks ()
{
	return NumberOfAttacks;
}
int Player::getPlayerNum()
{
   return playerNum;
}
void Player::setCheck_PreventPlayer(bool state)
{
	Check_PreventPlayer = state;
}
bool Player::getCheck_PreventPlayer()
{
return Check_PreventPlayer;
}
bool Player::getCheck_StateCard8()
{
	return Check_StateCard8;
}
void Player::setCheck_StateCard8(bool state)
{
	Check_StateCard8 = state;
}
void Player::setCheck_DeductCoins(bool state)
{
   Check_DeductCoins = state;
}
bool Player::getCheck_DeductCoins()
{
    return Check_DeductCoins;
}
void Player::increament_NumOfDeductCoins()
{
   NumOfDeductCoins++;
   if (NumOfDeductCoins == 3)
   {
     NumOfDeductCoins = 0;
	 Check_DeductCoins = false;
   }
}
void Player::increament_NumOfDeductRollNum()
{
	NumOfDeductRollNum++;
	if (NumOfDeductRollNum == 5)
	{
	  NumOfDeductRollNum = 0;
	  Check_DeductRollNumb = false;
	}
}
void Player::setCheckAnotherRoll(bool state)
{
	CheckAnotherRoll =state;
}
bool Player::getCheckAnotherRoll()
{
	return CheckAnotherRoll;
}
void Player::setCheck_DeductRollNumb( bool state )
{
	Check_DeductRollNumb = state;
}
bool Player::getCheck_DeductRollNumb()
{
	return Check_DeductRollNumb;
}
// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
    pOut ->DrawPlayer(pCell->GetCellPosition(),playerNum,playerColor);
	///TODO: use the appropriate output function to draw the player with "playerColor"
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	pOut ->DrawPlayer(pCell ->GetCellPosition() , playerNum , cellColor);
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	
	turnCount ++;
	CardSeven* CurrentCardSeven = dynamic_cast<CardSeven*>(pGrid->GetGameObject(pGrid ->GetCurrentPlayer()->GetCell()->GetCellPosition()));
	CardFive* CurrentCardFive = dynamic_cast<CardFive*>(pGrid->GetGameObject(pGrid ->GetCurrentPlayer()->GetCell()->GetCellPosition()));
	CardSix* CurrentCardSix = dynamic_cast<CardSix*>(pGrid->GetGameObject(pGrid ->GetCurrentPlayer()->GetCell()->GetCellPosition()));
	if (CurrentCardSeven || CurrentCardFive || CurrentCardSix )
	{
	     turnCount--;
	}
	Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
	Player* CurrentPlayer = pGrid ->GetCurrentPlayer();
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if ( turnCount == 3)
	{
		if ( NumberOfAttacks != 2)
		{
		pOut->PrintMessage("Do you wish to launch a special attack instead of recharging? y/n");
		string choice = pIn->GetSrting(pOut);
		while ( choice != "y" && choice != "n")
		{
			pOut->PrintMessage("Enter y for Yes of n for No");
		    choice = pIn->GetSrting(pOut);
		}
		if ( choice == "y")
		{
			pOut->PrintMessage(" Choose the special Attack: 1 for Ice , 2 for Fire , 3 for Poison, 4 for Lightning ");
			int choice_Attack = pIn ->GetInteger(pOut);
			while ( choice_Attack > 4 || choice_Attack < 1)
			{
			   pOut->PrintMessage(" Choose the special Attack from 1 to 4");
			   choice_Attack = pIn ->GetInteger(pOut);
			}
			bool added;
			switch ( choice_Attack )
			{
			case 1:
				Attacks[NumberOfAttacks] = new Ice;
				added = Attacks[NumberOfAttacks] ->ApplyAttack(pGrid,CurrentPlayer);
				if ( !added )
				{
					 wallet = wallet + ( diceNumber* 10);
	                 string msg = "Your Wallet increased by : " + to_string(diceNumber* 10);
	                  pOut ->PrintMessage(msg);
	                   int x,y;
	                 pIn->GetPointClicked(x,y);
	                pOut ->ClearStatusBar();
	                   turnCount = 0;
	                  return;
				}
				NumberOfAttacks++;
				turnCount = 0;
				return;
			case 2:
				Attacks[NumberOfAttacks] = new Fire;
				added = Attacks[NumberOfAttacks] ->ApplyAttack(pGrid,CurrentPlayer);
				if ( !added )
				{
					 wallet = wallet + ( diceNumber* 10);
	                 string msg = "Your Wallet increased by : " + to_string(diceNumber* 10);
	                  pOut ->PrintMessage(msg);
	                   int x,y;
	                 pIn->GetPointClicked(x,y);
	                pOut ->ClearStatusBar();
	                   turnCount = 0;
	                  return;
				}
				NumberOfAttacks++;
				turnCount = 0;
				return;
			case 3:
				Attacks[NumberOfAttacks] = new Poison;
				added = Attacks[NumberOfAttacks] ->ApplyAttack(pGrid,CurrentPlayer);
				if ( !added )
				{
					 wallet = wallet + ( diceNumber* 10);
	                 string msg = "Your Wallet increased by : " + to_string(diceNumber* 10);
	                  pOut ->PrintMessage(msg);
	                   int x,y;
	                 pIn->GetPointClicked(x,y);
	                pOut ->ClearStatusBar();
	                   turnCount = 0;
	                  return;
				}
				NumberOfAttacks++;
				turnCount = 0;
				return;

			case 4:
				Attacks[NumberOfAttacks] = new Lightning;
			     added = Attacks[NumberOfAttacks] ->ApplyAttack(pGrid,CurrentPlayer);
				if ( !added )
				{
					 wallet = wallet + ( diceNumber* 10);
	                 string msg = "Your Wallet increased by : " + to_string(diceNumber* 10);
	                  pOut ->PrintMessage(msg);
	                   int x,y;
	                 pIn->GetPointClicked(x,y);
	                pOut ->ClearStatusBar();
	                   turnCount = 0;
					return;
				}
				NumberOfAttacks++;
				turnCount = 0;
				return;
			}
		}
		}
	   wallet = wallet + ( diceNumber* 10);
	   string msg = "Your Wallet increased by : " + to_string(diceNumber* 10);
	   pOut ->PrintMessage(msg);
	   int x,y;
	   pIn->GetPointClicked(x,y);
	   pOut ->ClearStatusBar();
	   turnCount = 0;
	   return;
	}
	if ( CurrentPlayer ->GetWallet() == 0 )
	{
		pOut ->PrintMessage(" Your wallet is zero wait till your wallet is recharged again. Click to continue ...");
		 int x,y;
	   pIn->GetPointClicked(x,y);
	   pOut ->ClearStatusBar();
		return;
	}
	// 3- Set the justRolledDiceNum with the passed diceNumber
	justRolledDiceNum = diceNumber;
	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	CellPosition pos = CurrentPlayer ->GetCell() ->GetCellPosition();
	pos.AddCellNum(justRolledDiceNum);
	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid ->UpdatePlayerCell(CurrentPlayer,pos);
	// 6- Apply() the game object of the reached cell (if any)
	CellPosition checkPosition = pos;
	CellPosition tempCellPosition = pos;
	bool checkfirstApply = true;
	CurrentPlayer ->setCheckAnotherRoll(false);
	while ((pGrid ->GetGameObject(checkPosition)))
	{
		if ( checkfirstApply )
		{
	   tempCellPosition = checkPosition;
	   pGrid ->GetGameObject(checkPosition) ->Apply(pGrid,CurrentPlayer);
	   checkPosition = CurrentPlayer ->GetCell() ->GetCellPosition();
	   checkfirstApply = false;
		}
		else if ((pGrid ->GetGameObject(checkPosition)) != (pGrid ->GetGameObject(tempCellPosition)))
		{
		tempCellPosition = checkPosition;
	   pGrid ->GetGameObject(checkPosition) ->Apply(pGrid,CurrentPlayer);
	   checkPosition = CurrentPlayer ->GetCell() ->GetCellPosition();
		}
		else if ((pGrid ->GetGameObject(checkPosition)) == (pGrid ->GetGameObject(tempCellPosition)))
		{
			break;
		}
	} 
	
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if ( pos.GetCellNum() == 99 )
	{
	    pGrid ->SetEndGame(true);
	}
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}
