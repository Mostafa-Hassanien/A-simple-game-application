#pragma once
 
#include "SpecialAttack.h"
#include"Grid.h"
#include"Player.h"
#include "Input.h"
#include "Output.h"

class Lightning : public SpecialAttack
{
public:
	Lightning();// constructor 
	virtual ~Lightning();// virtual Destructor 
	virtual void ReadAttackParameters(Grid* pGrid); //  Reads parameters required for attack to apply 
	virtual bool ApplyAttack(Grid* pGrid, Player* pPlayer); // deduct 20 coins from all other players 
};