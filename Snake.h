#pragma once

#include "GameObject.h"

class Snake : public GameObject // inherited from GameObject
{
	CellPosition endCellPos; // here is the snake's End Cell Position -- note ( endCellPos is greater than startCellPos that is inherited from GameObject )
public:
	Snake(const CellPosition & startCellPos, const CellPosition & endCellPos); // A constructor for initialization
	Snake (); // A Default constructor
	virtual void Draw(Output* pOut) const; // Draws a snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the snake by moving player to ladder's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	virtual void Save(ofstream &OutFile, Type gameObject);	// Saves the GameObject parameters to the file
	virtual void Load(ifstream &Infile); // Loads and Reads the GameObject parameters from the file

	virtual ~Snake(); // Virtual destructor
};