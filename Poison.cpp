#include "Poison.h"


Poison::Poison()
{}
Poison:: ~Poison()
{}

void Poison::ReadAttackParameters(Grid* pGrid)
{
	 Output* pOut = pGrid ->GetOutput();
	Input* pIn = pGrid ->GetInput();
	Player* CurrentPlayer = pGrid ->GetCurrentPlayer();
	pOut ->PrintMessage(" Poison Attack is being launched. Click to continue... " );
	int x, y ;
	pIn ->GetPointClicked(x,y);
	pOut ->PrintMessage(" Write the index of the player to poisoned ( For 5 turns, deduct 1 number from his dice roll) ");
	Index_Player = pIn ->GetInteger(pOut);
	while ( Index_Player > 3 || Index_Player < 0 || Index_Player == CurrentPlayer ->getPlayerNum() )
	{
		if (Index_Player == CurrentPlayer ->getPlayerNum() )
		{
		   pOut ->PrintMessage(" Write the index of the player to poison him ( not your index ) ");
	       Index_Player = pIn ->GetInteger(pOut);
		}
		else {
	  pOut ->PrintMessage(" Write the index of the player to poison him (For 5 turns, deduct 1 number from his dice roll)");
	  Index_Player = pIn ->GetInteger(pOut);
		}
	}
	pOut ->ClearStatusBar();

}

bool Poison::ApplyAttack(Grid* pGrid, Player* pPlayer)
{
		if ( pPlayer ->getthefirstAttack())
	{
	     if ( pPlayer->gettheNumAttacks() !=0 && dynamic_cast <Poison*>(pPlayer ->getthefirstAttack()))
		 {
			 pGrid ->PrintErrorMessage(" You have chosen this attack before. Click to continue ... ");
		     return false;
		 }
	}
	ReadAttackParameters(pGrid);
	if ( pGrid ->CheckCurrent_AppliedAttack(Index_Player,pPlayer ->getCurrentAttack()) == true)
	{
	pGrid ->Change_Check_DeductRollNumb(Index_Player);
	return true;
	}
	else
	{
	   pGrid ->PrintErrorMessage(" The chosen player is currently affected by the same attack from another player. Click to ccontinue ...");
		 return false;
	}
}