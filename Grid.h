#pragma once

#include "UI_Info.h"
#include "DEFS.h"

#include "Input.h"
#include "Output.h"
#include "CellPosition.h"


// forward declarations (the includes are in the cpp)
class Cell;
class GameObject;
class Ladder;
class Card;
class Player;
class Snake;
class SpecialAttack;

enum Type
{
	Ladders,
	Snakes,
	Cards,
};

class Grid
{
	Output * pOut;   // A pointer to the Output object
	Input * pIn;     // A pointer to the Input object
	Cell * CellList[NumVerticalCells][NumHorizontalCells];  // An array of "Pointers" to All Cells of the Grid Cells
															// We make it array of pointers not objects because
															// there are NO default constructor for class Cell

	Player* PlayerList[MaxPlayerCount]; // An array of "Pointers" to the Players of the Game (MaxPlayerCount Players)
	int currPlayerNumber;   // The player number that has the turn to play 
							// currPlayerNumber is: from 0 to MaxPlayerCount - 1

	Card * Clipboard;	   // This is used in copy/cut/paste card (should be set in copy/cut and got in paste)

	bool endGame;// A boolean indicating if the Game is ended or not (a player reaches the end cell of the grid or not)

	bool CheckStartNewGame;// A boolean indicating if it is the first time to Start New Game


public:

	Grid(Input * pIn, Output * pOut);	  // Gives the Grid a Pointer to the Output Object and the Input Object
										  // and makes any needed initializations

	// ========= Adding or Removing GameObjects to Cells =========

	bool AddObjectToCell(GameObject * pNewObject);		 // Adds a GameObject to the Cell of its "position" data member
	                                                     // only if the Cell does NOT already contain an object, 
	                                                     // otherwise return false and don't add

	void RemoveObjectFromCell(const CellPosition & pos); // Removes the GameObject of the Cell of the passed "position"
	void CleanGrid(); // Delete all gameobjects in the grid 
	void UpdatePlayerCell(Player * player, const CellPosition & newPosition); // Update the player's pCell with the CellList's Cell pointer of the "newPosition",
	                                                                          // Clears the player's circle from the previous cell
	    																	  // and  Draws it in the new cell
	void StartNewGame(); // for starting new game action
	void DeductCoins(); // Deduct coins from all player expect the player who launches the Lightning attack
	void Change_Preventsatate(int Index_Player ); // this is function is to change Check_PreventPlayer of the player chosen to be prevented in Ice attack
	void DeductCoins_OnePlayer(int Index_Player); // Deduct 20 Coins from a specific player whose player number is Index_Player
	void Change_DeductCoinsState(int Index_Player ); //  this is function is to change Check_DeductCoins of the player chosen to be burned in Fire attack
	void Change_Check_DeductRollNumb( int Index_Player); // this is function is to change DeductRollNumb of the player chosen to be poisoned in Poison attack
	bool CheckCurrent_AppliedAttack(int Index_Player, SpecialAttack* Coming_AppliedAttack);// check if the current applied attack on the player
	                                                                                 // is different from the comping applied attack
	void setAllCardTen(Player* OwnerPlayer ); // sets all card tens with the ownerplayer of one card
	void setAllCardEleven(Player* OwnerPlayer); // sets all card elevens with the ownerplayer of one card
	void setAllCardTwelve(Player* OwnerPlayer); // sets all card twelves with the ownerplayer of one card
	void setAllCardThirteen(Player* OwnerPlayer); // sets all card thirteens with the ownerplayer of one card
	void setAllCardFourteen(Player* OwnerPlayer); // sets all card fourteens with the ownerplayer of one card
	bool LoopFromAboveBelow(CellPosition AboveCell, CellPosition BelowCell );  // loop in the same column from above to below to chek if there is a snake
    bool LoopFromBottomToAbove(CellPosition AboveCell, CellPosition BelowCell); // loop in the same column from below to above to chek if there is a ladder
	// ========= Setters and Getters Functions =========

	Input * GetInput() const;	// Gets a Pointer to the Input
	Output * GetOutput() const; // Gets a Pointer to the Output 

	void SetClipboard(Card * card);  // A setter to be used in copy/cut (in order NOT to break class responsibilities)
	Card * GetClipboard() const;	 // A getter to be used in paste (in order NOT to break class responsibilities)

	void SetEndGame(bool endGame);	 // A setter for endGame data member
	bool GetEndGame() const;		 // A getter for endGame data member

	void AdvanceCurrentPlayer();     // Increments the currPlayerNum and if reaches MaxPlayerCount reset to 0 (using %)

	GameObject* GetGameObject(const CellPosition & position); // A getter for GameObject of the passed CellPosition 
	Card* GetTheFirstCardTen(); //  A getter for the first ten card in the grid
	Card* GetTheFirstCardEleven();
	Card* GetTheFirstCardTwelve();
	Card* GetTheFirstCardThirteen();
	Card* GetTheFirstCardFourteen();
	///TODO: add any needed setter/getter "EXCEPT" ANY setters or getters of "CellList" or "PlayerList" (Forbidden for class Responsibilities)
	int GetCurrentPlayerNumber() const; // getter for CurrentPlayer Number 
	int GetNumberOfLadders(); //	A getter for the number of Ladders in the grid
	int GetNumberOfSnakes(); //	A getter for the number of Snakes in the grid
	int GetNumberOfCards(); //	A getter for the number of Cards in the grid
	// ========= Other Getters =========
	
	Player * GetCurrentPlayer() const;	// Gets a Pointer to the Current Player	                                    
	Ladder * GetNextLadder(const CellPosition & position) const; // Gets a Pointer to the first Ladder after the passed "position"
	Snake*  GetNextSnake(const CellPosition & position) const;// Gets a Pointer to the first Snake after the passed "position"
	Card* GetNextCard(const CellPosition & position) const;// Gets a Pointer to the first Card after the passed "position"
	Card* GetCard(const CellPosition & position) const; // Gets a Pointer to the Card of the passed "position"
	Ladder* GetLadder(const CellPosition & position) const; // Gets a Pointer to the Ladder of the passed "position"
	Snake* GetSnake(const CellPosition & position) const; // Gets a Pointer to the Snake of the passed "position"
	// ========= User Interface Functions =========

	void UpdateInterface() const;		// It Updates the Grid according to the last state of the game
	                                    // In Design mode, it draws all cells/cards THEN all ladders/snakes THEN all players
	                                    // In Play mode, it only draws the player's info on the right side of the toolbar
	                                    // Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
	                                    //       and the cards/snakes/ladders positions do NOT change already in Play Mode

	void PrintErrorMessage(string msg); // Prints an error message on statusbar, Waits for mouse click then clears statusbar
									    // We added this function once here because it is used many times by other classes
	void SaveAll(ofstream &OutFile, Type gameobject); 

	~Grid(); // A destructor for any needed deallcations
};

