#pragma once

#include "Grid.h"
#include "Cell.h"

class SpecialAttack;

class Player
{
	Cell * pCell;		   // pointer to the current Cell of the player

	const int playerNum;   // the player number (from 0 to MaxPlayerCount-1)
	                       // player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	int wallet;		       // player's wallet (how many coins he has -- integer)
	int justRolledDiceNum; // the current dice number which is just rolled by the player
	int turnCount;         // a counter that starts with 0, is incremented with each dice roll
	                       // and reset again when reached 3
	                       // it is used to indicate when to move and when to add to your wallet
	int NumberOfAttacks ; // it is used to indicate the number of attacks the player used during the game ( Maximum number of attacks = 2 );
    SpecialAttack* Attacks[MaximumUniqueAttacks]; // pointer to the two unique special attacks4
	bool Check_PreventPlayer; // check that the player was chosen in Ice attack ( prevented from rolling )
	bool Check_StateCard8;  // Check the stat of card 8
	bool Check_DeductCoins; // check that the player was chosen in Fire attack is burned or not 
	int NumOfDeductCoins; // it is used to indicate the number of turns a specific player was affected by Fire Attack (Deduct 20 coins from his wallet for his next 3 turns)
	                      // Starts with 0 and rest again when reached 3 
	bool Check_DeductRollNumb;// check that the player was chosen in Poison attack is poisoned or not 
	int NumOfDeductRollNum;// it is used to indicate the number of turns a specific player was affected by Fire Attack (Deduct 20 coins from his wallet for his next 3 turns)
                           //  // Starts with 0 and rest again when reached 5
	bool CheckAnotherRoll; // it is used to indicate if the player is given another roll from card seven
public:

	Player(Cell * pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell * cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetWallet(int wallet);		// A setter for the wallet
	int GetWallet() const;			// a getter for the wallet
	void setCheckAnotherRoll(bool state); // A setter for CheckAnotherRoll
	bool getCheckAnotherRoll(); //  A getter for CheckAnotherRoll
	int GetTurnCount() const;		// A getter for the turnCount
	void SetTurnCount( int x);      // A setter for SetTurnCount
	void SetStepCount(int x);       // A setter  for  SetStepCount
	SpecialAttack* getthefirstAttack(); // A getter for the first attack
	SpecialAttack* getCurrentAttack();
	int gettheNumAttacks () ;  // A getter for the number of  attacks
	int getPlayerNum(); // A getter for index of the player ( player number )
	void setCheck_PreventPlayer(bool state);// A setter for Check_PreventPlayer
	bool getCheck_PreventPlayer(); //  A getter for Check_PreventPlayer
	void setCheck_DeductCoins(bool state); // A setter for Check_DeductCoins
	bool getCheck_DeductCoins(); // A getter for Check_DeductCoins
	void setCheck_DeductRollNumb( bool state ); // A setter for Check_DeductRollNumb
	bool getCheck_DeductRollNumb(); // A getter for Check_DeductRollNumb
	void increament_turnCount(); // increament the player turnCount
	void increament_NumOfDeductCoins(); // increament the player NumOfDeductCoins
	void increament_NumOfDeductRollNum(); // increament the player NumOfDeductRollNum
	bool getCheck_StateCard8(); // A getter for state card 8 
	void setCheck_StateCard8(bool state); // A setter for  Check_StateCard8
	int getjustRolledDiceNum(); // A getter for the justRolledDiceNum
	///TODO: You can add setters and getters for data members here (if needed)

	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid * pGrid, int diceNumber);	// Moves the Player with the passed diceNumber 
	                                            // and Applies the Game Object's effect (if any) of the end reached cell 
	                                            // for example, if the end cell contains a ladder, take it
	void AppendPlayerInfo(string & playersInfo) const; // Appends player's info to the input string, 
	                                                   // for example: P0(wallet, turnCount)

};

