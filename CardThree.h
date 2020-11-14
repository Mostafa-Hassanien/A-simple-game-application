#pragma once

#include "Card.h"
#include <fstream>

class CardThree :	public Card
{

public:
	CardThree(const CellPosition & pos); // A Constructor takes card position
	CardThree(); // A Default Constructor 
	virtual void ReadCardParameters(Grid * pGrid); 
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardThree on the passed Player
	 	                                              // by moving the player to the start of the next ladder                                                  
	virtual void Save(ofstream &OutFile, Type gameObject);// Saves the GameObject parameters to the file
	virtual void Load(ifstream& Infile); // Loads and Reads the GameObject parameters from the file
	virtual ~CardThree(); // A Virtual Destructor
};


