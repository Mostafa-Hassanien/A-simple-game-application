#pragma once
 
#include "SpecialAttack.h"
#include"Grid.h"
#include"Player.h"
#include "Input.h"
#include "Output.h"

class Ice : public SpecialAttack
{
	int Index_Player; // index of the player that will be prevented from rolling next turn
public:
	Ice();// constructor 
	virtual ~Ice();// virtual Destructor 
	virtual void ReadAttackParameters(Grid* pGrid); //  Reads parameters required for attack to apply (Index_Player)
	virtual bool ApplyAttack(Grid* pGrid, Player* pPlayer);
	int getIndexOfPlayer(); // A getter for the index of the player that will be prevented from rolling next turn
};