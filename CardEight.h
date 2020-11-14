#pragma once
#include "Card.h"
#include <fstream>
class CardEight : public Card
{
public:
	CardEight(const CellPosition& pos);
	CardEight();
	virtual ~CardEight();
	virtual void ReadCardParameters(Grid* pGrid); // Parameters: rolled dice value
	virtual void Apply(Grid* pGrid, Player* pPlayer); // moves the player forward the same number of steps previously rolled
	virtual void Save(ofstream& OutFile, Type gameObject); // 
	virtual void Load(ifstream& Infile);
};


