#pragma once
 
#include "SpecialAttack.h"
#include"Grid.h"
#include"Player.h"
#include "Input.h"
#include "Output.h"

class Fire : public SpecialAttack
{
	int Index_Player; // index of the player that will be burned (Deduct 20 coins from his wallet for his next 3 turns)
public: 
	Fire();// constructor 
	virtual ~Fire();// virtual Destructor 
	virtual void ReadAttackParameters(Grid* pGrid); //  Reads parameters required for attack to apply (Index_Player)
	virtual bool ApplyAttack(Grid* pGrid, Player* pPlayer);
	int getIndexOfPlayer(); // A getter for the index of the player that will be burned (Deduct 20 coins from his wallet for his next 3 turns)
};