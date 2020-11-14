#pragma once
#include "Card.h"
#include <fstream>

// [ CardTen ] Summary:
// Gives the player the option to buy this cell and all cells containing a card with the same
// number

class CardTwelve : public Card
{
	// CardOne Parameters:
	static int FeesToPay; // fees to the player who owns the cell
	static int CardPrice; // the card price
	Player* OwnerPlayer;
	static bool checkCardTwelveSave;
	static bool checkCardTwelveload;
public:
	CardTwelve(const CellPosition& pos); // A Constructor takes card position
	CardTwelve(); // A Default Constructor
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member
	virtual void Save(ofstream& OutFile, Type gameObject);// Saves the GameObject parameters to the file
	virtual void Load(ifstream& Infile); // Loads and Reads the GameObject parameters from the file
	void SetOwnerPlayer(Player* pPlayer);
	virtual ~CardTwelve(); // A Virtual Destructor
};