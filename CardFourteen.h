#pragma once
#include "Card.h"
#include <fstream>

// [ CardFourteen ] Summary:
// Gives the player the option to buy this cell and all cells containing a card with the same
// number

class CardFourteen : public Card
{
	// CardOne Parameters:
	static int FeesToPay; // fees to the player who owns the cell
	static int CardPrice; // the card price
	Player* OwnerPlayer;
	static bool checkCardFourteenSave;
	static bool checkCardFourteenload;
public:
	CardFourteen(const CellPosition& pos); // A Constructor takes card position
	CardFourteen(); // A Default Constructor
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member
	virtual void Save(ofstream& OutFile, Type gameObject);// Saves the GameObject parameters to the file
	virtual void Load(ifstream& Infile); // Loads and Reads the GameObject parameters from the file
	void SetOwnerPlayer(Player* pPlayer);
	virtual ~CardFourteen(); // A Virtual Destructor
};