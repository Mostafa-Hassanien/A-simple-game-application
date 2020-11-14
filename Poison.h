#pragma once
 
#include "SpecialAttack.h"
#include"Grid.h"
#include"Player.h"
#include "Input.h"
#include "Output.h"

class Poison : public SpecialAttack
{
	int Index_Player; // index of the player who wil, for 5 turns, be affected by deducting 1 number from his dice roll
public: 
	Poison();// constructor 
	virtual ~Poison();// virtual Destructor 
	virtual void ReadAttackParameters(Grid* pGrid); //  Reads parameters required for attack to apply (Index_Player)
	virtual bool ApplyAttack(Grid* pGrid, Player* pPlayer);
	int getIndexOfPlayer(); // A getter for index of the player who wil, for 5 turns, be affected by deducting 1 number from his dice roll
};