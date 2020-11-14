#pragma once

#include "Card.h"
#include <fstream>
// [ CardNine ] Summary:
// Its Apply() Function: Instructs the player to go to a specific cell. This specific cell is specified during grid design
// Its Parameters: Cell to move to

class CardNine :	public Card
{
	// CardNine Parameters:
	CellPosition CellToMoveTo; // the specified Cell to move to
public:
	CardNine(const CellPosition & pos);  // A Constructor takes card position
	CardNine() ; // A Default Constructor
	virtual ~CardNine(); // A Virtual Destructor

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardNine which is: CellToMoveTo

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardNine on the passed Player
	                                                  // by moving the player to the specified Cell " CellToMoveTo "
	virtual void Save(ofstream &OutFile, Type gameObject);// Saves the GameObject parameters to the file
   virtual void Load(ifstream& Infile); // Loads and Reads the GameObject parameters from the file
};