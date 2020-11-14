#pragma once

#include"Player.h"
#include"Grid.h"


class SpecialAttack
{
public:
	SpecialAttack();// constructor 

	// ============ Virtual Functions ============

	virtual ~SpecialAttack();// virtual Destructor 
	virtual void ReadAttackParameters(Grid* pGrid) = 0; //  Reads parameters required for attack to apply 
	virtual bool ApplyAttack(Grid* pGrid, Player* pPlayer) = 0; //  Executes attack (code depends on attack type so virtual)
};