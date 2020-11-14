#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Poison.h"
#include "Fire.h"
#include "Ice.h"
#include "Lightning.h"
#include "Snake.h"
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


Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}
bool Grid::LoopFromAboveBelow(CellPosition AboveCell, CellPosition BelowCell )
{
	for ( int i = AboveCell.GetCellNum() ; i >= BelowCell.GetCellNum() ; i -=11)
	{
		CellPosition checkCell(i);
	     Snake* HasSnak = GetSnake(checkCell);
		 if ( HasSnak )
		 { 
			 if ( HasSnak ->GetEndPosition().GetCellNum() == BelowCell.GetCellNum())
			 {
	             	return true;
			 }
		 }
	}
	return false;
}
bool Grid::LoopFromBottomToAbove(CellPosition AboveCell, CellPosition BelowCell)
{
	for ( int i = BelowCell.GetCellNum(); i <= AboveCell.GetCellNum() ; i +=11)
       	{
		CellPosition checkCell(i);
		Ladder* checkLadder = GetLadder(checkCell);
		if ( checkLadder)
			{
				if (  checkLadder ->GetEndPosition().GetCellNum() == AboveCell.GetCellNum())
			    {	
					return true;
				}
				}
     		
	    }
	return false;
}

void Grid::CleanGrid()
{
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
		}
	}
}
void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	if ( newPosition.IsValidCell() == false )
	return;
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}

void Grid::StartNewGame()
{
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] ->ClearDrawing(pOut);
		Cell * newCell = CellList[NumVerticalCells-1][0];  // Restarts players positions
	    PlayerList[i]->SetCell(newCell);    // setting every player cell (pCell ) with the newCell
		PlayerList[i] ->SetWallet(100); // Restarts players wallet,
		PlayerList[i] ->SetStepCount(0);   //  Restarts players StepCount,
	    PlayerList[i]->Draw(pOut); // drawing the player in the new cell 
		PlayerList[i] ->SetTurnCount(0); // setting TurnCount to zero
	}
	currPlayerNumber = 0;
	endGame = false;
}

void Grid::DeductCoins()
{
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		if ( i != currPlayerNumber )
		{
			DeductCoins_OnePlayer(i);
		}
	}
}
void Grid::DeductCoins_OnePlayer(int Index_Player)
{
	PlayerList[Index_Player] ->SetWallet((PlayerList[Index_Player]->GetWallet())-20);
}
void Grid::Change_Preventsatate(int Index_Player )
{
	PlayerList[Index_Player] ->setCheck_PreventPlayer(true);
}
void Grid::Change_DeductCoinsState(int Index_Player )
{
	PlayerList[Index_Player] ->setCheck_DeductCoins(true);
}
void Grid::Change_Check_DeductRollNumb( int Index_Player)
{
   PlayerList[Index_Player] ->setCheck_DeductRollNumb(true);
}
bool Grid::CheckCurrent_AppliedAttack(int Index_Player, SpecialAttack* Coming_AppliedAttack)
{
	if ( Coming_AppliedAttack )
	if ( (PlayerList[Index_Player]->getCheck_DeductCoins() == true && dynamic_cast <Fire*> (Coming_AppliedAttack)) ||
		( PlayerList[Index_Player]->getCheck_DeductRollNumb() == true && dynamic_cast <Poison*> (Coming_AppliedAttack))||
		( PlayerList[Index_Player]->getCheck_PreventPlayer() == true && dynamic_cast <Ice*> (Coming_AppliedAttack)))
		return false;  // the current applied attack is the same as the coming attack 
	return true; // they are different
}

void Grid::setAllCardTen(Player* OwnerPlayer )
{
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardTen* Cardten = dynamic_cast <CardTen*> (CellList[i][j] ->GetGameObject());
			if (Cardten)
				Cardten ->SetOwnerPlayer(OwnerPlayer);
		}
	}
}
void Grid::setAllCardEleven(Player* OwnerPlayer)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardEleven* Cardeleven = dynamic_cast <CardEleven*> (CellList[i][j]->GetGameObject());
			if (Cardeleven)
				Cardeleven->SetOwnerPlayer(OwnerPlayer);
		}
	}
}
void Grid::setAllCardTwelve(Player* OwnerPlayer)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardTwelve* Cardtwelev = dynamic_cast <CardTwelve*> (CellList[i][j]->GetGameObject());
			if (Cardtwelev)
				Cardtwelev->SetOwnerPlayer(OwnerPlayer);
		}
	}
}
void Grid::setAllCardThirteen(Player* OwnerPlayer)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardThirteen* Cardthirteen = dynamic_cast <CardThirteen*> (CellList[i][j]->GetGameObject());
			if (Cardthirteen)
				Cardthirteen->SetOwnerPlayer(OwnerPlayer);
		}
	}
}
void Grid::setAllCardFourteen(Player* OwnerPlayer)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardFourteen* Cardfourteen = dynamic_cast <CardFourteen*> (CellList[i][j]->GetGameObject());
			if (Cardfourteen)
				Cardfourteen->SetOwnerPlayer(OwnerPlayer);
		}
	}
}
// ========= Setters and Getters Functions =========

int Grid::GetCurrentPlayerNumber() const
{
	return currPlayerNumber;
}
Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	int CardNumber = pCard ->GetCardNumber();
	switch ( CardNumber )
	{
	case 1:
		Clipboard = new CardOne( *(dynamic_cast < CardOne*> ( pCard)));
		break;
	case 2:
		Clipboard = new CardTwo( *(dynamic_cast < CardTwo*> ( pCard)));
		break;
	case 3:
		Clipboard = new CardThree( *(dynamic_cast < CardThree*> ( pCard)));
		break;
	case 4:
		Clipboard = new CardFour( *(dynamic_cast < CardFour*> ( pCard)));
		break;
	case 5:
		Clipboard = new CardFive( *(dynamic_cast < CardFive*> ( pCard)));
		break;
	case 6:
		Clipboard = new CardSix( *(dynamic_cast < CardSix*> ( pCard)));
		break;
	case 7:
		Clipboard = new CardSeven( *(dynamic_cast < CardSeven*> ( pCard)));
		break;
	case 8:
		Clipboard = new CardEight( *(dynamic_cast < CardEight*> ( pCard)));
		break;
	case 9:
		Clipboard = new CardNine( *(dynamic_cast < CardNine*> ( pCard)));
		break;
	case 10:
		Clipboard = new CardTen( *(dynamic_cast < CardTen*> ( pCard)));
		break;
	case 11:
		Clipboard = new CardEleven( *(dynamic_cast < CardEleven*> ( pCard)));
		break;
	case 12:
		Clipboard = new CardTwelve( *(dynamic_cast < CardTwelve*> ( pCard)));
		break;
	case 13:
		Clipboard = new CardThirteen( *(dynamic_cast < CardThirteen*> ( pCard)));
		break;
	case 14:
		Clipboard = new CardFourteen( *(dynamic_cast < CardFourteen*> ( pCard)));
		break;
	}
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

GameObject* Grid::GetGameObject(const CellPosition & position)
{
	return CellList[position.VCell()][position.HCell()] ->GetGameObject();
}

Card* Grid::GetTheFirstCardTen()
{
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardTen* card = dynamic_cast <CardTen*> (CellList[i][j] ->GetGameObject());
			if (card)
			  return card;
		}
	}
	return NULL;
}
Card* Grid::GetTheFirstCardEleven()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardEleven* card = dynamic_cast <CardEleven*> (CellList[i][j]->GetGameObject());
			if (card)
				return card;
		}
	}
	return NULL;
}
Card* Grid::GetTheFirstCardTwelve()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardTwelve* card = dynamic_cast <CardTwelve*> (CellList[i][j]->GetGameObject());
			if (card)
				return card;
		}
	}
	return NULL;
}
Card* Grid::GetTheFirstCardThirteen()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardThirteen* card = dynamic_cast <CardThirteen*> (CellList[i][j]->GetGameObject());
			if (card)
				return card;
		}
	}
	return NULL;
}
Card* Grid::GetTheFirstCardFourteen()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CardFourteen* card = dynamic_cast <CardFourteen*> (CellList[i][j]->GetGameObject());
			if (card)
				return card;
		}
	}
	return NULL;
}
// ========= Other Getters =========

int Grid::GetNumberOfLadders()
{
	int NumberOfLadders = 0;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			GameObject* object = CellList[i][j] ->GetGameObject();
			if ( dynamic_cast<Ladder*> (object) )
				NumberOfLadders++;
		}
	}
	return NumberOfLadders;
}
int  Grid::GetNumberOfSnakes()
{
	int NumberOfSnakes = 0;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			GameObject* object = CellList[i][j] ->GetGameObject();
			if ( dynamic_cast<Snake*> (object) )
				NumberOfSnakes++;
		}
	}
	return NumberOfSnakes;
}
int Grid::GetNumberOfCards()
{
	int NumberOfCards = 0;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			GameObject* object = CellList[i][j] ->GetGameObject();
			if ( dynamic_cast<Card*> (object) )
				NumberOfCards++;
		}
	}
	return NumberOfCards;
}

Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position) const
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			if ( CellList[i][j] ->HasLadder() != NULL)
				return CellList[i][j] ->HasLadder();
			// Check if CellList[i][j] has a ladder, if yes return it
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}
Snake*  Grid::GetNextSnake(const CellPosition & position) const
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the Snake in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			if ( CellList[i][j] ->HasSnake() != NULL)
				return CellList[i][j] ->HasSnake();
			// Check if CellList[i][j] has a Snake, if yes return it
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found

}
Card* Grid::GetNextCard(const CellPosition & position) const
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			if ( CellList[i][j] ->HasLadder() != NULL)
				return CellList[i][j] ->HasCard();
			// Check if CellList[i][j] has a ladder, if yes return it
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Card* Grid::GetCard(const CellPosition & position) const
{
	if ( position.IsValidCell()) // Validation for the passed CellPostion (Position)
	{
	if ( CellList[position.VCell()][position.HCell()] ->HasCard() )
	return CellList[position.VCell()][position.HCell()] ->HasCard(); // Returning the card of the selected CellPosition
	}
	return NULL; // Returning NULL in case there is no card in the CellPosition
}

Ladder* Grid::GetLadder(const CellPosition & position) const
{
	if ( position.IsValidCell()) // Validation for the passed CellPostion (Position)
	{
	if ( CellList[position.VCell()][position.HCell()] ->HasLadder() )
	return CellList[position.VCell()][position.HCell()] ->HasLadder(); // Returning the ladder of the selected CellPosition
	}
	return NULL; // Returning NULL in case there is no ladder in the CellPosition
}

Snake* Grid::GetSnake(const CellPosition & position) const
{
	if ( position.IsValidCell()) // Validation for the passed CellPostion (Position)
	{
	if ( CellList[position.VCell()][position.HCell()] ->HasSnake() )
	return CellList[position.VCell()][position.HCell()] ->HasSnake(); // Returning the Snake of the selected CellPosition
	}
	return NULL; // Returning NULL in case there is no Snake in the CellPosition
}
// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);
		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}
void Grid::SaveAll(ofstream &OutFile,  Type gameobject)
{
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			GameObject* object = CellList[i][j] ->GetGameObject();
			if ( object )
			object ->Save(OutFile,gameobject);
		}
	}
}

