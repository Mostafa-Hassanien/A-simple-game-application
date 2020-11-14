#pragma once

#include "Card.h"
#include <fstream>

// [ CardTwo ] Summary:
// Its Apply() Function: Increments the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to Increase --> put it as a "data member" and read it in ReadCardParameters()

class CardTwo :	public Card
{
	// CardTwo Parameters:
	int walletAmount; // the wallet value to decrease from the player

public:
	CardTwo(const CellPosition & pos); // A Constructor takes card position
	CardTwo(); // A Default Constructor 
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardTwo which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwo on the passed Player
	                                                  // by incrementing the player's wallet by the walletAmount data member
   virtual void Save(ofstream &OutFile, Type gameObject);// Saves the GameObject parameters to the file
   virtual void Load(ifstream& Infile); // Loads and Reads the GameObject parameters from the file

	virtual ~CardTwo(); // A Virtual Destructor
};