#include "Fire.h"

Fire::Fire()
{}
Fire:: ~Fire()
{}

void Fire::ReadAttackParameters(Grid* pGrid)
{
	 Output* pOut = pGrid ->GetOutput();
	Input* pIn = pGrid ->GetInput();
	Player* CurrentPlayer = pGrid ->GetCurrentPlayer();
	pOut ->PrintMessage(" Fire Attack is being launched. Click to continue... " );
	int x, y ;
	pIn ->GetPointClicked(x,y);
	pOut ->PrintMessage(" Write the index of the player to burned (Deduct 20 coins from his wallet for his next 3 turns) ");
	Index_Player = pIn ->GetInteger(pOut);
	while ( Index_Player > 3 || Index_Player < 0 || Index_Player == CurrentPlayer ->getPlayerNum() )
	{
		if (Index_Player == CurrentPlayer ->getPlayerNum() )
		{
		   pOut ->PrintMessage(" Write the index of the player to burn him ( not your index ) ");
	       Index_Player = pIn ->GetInteger(pOut);
		}
		else {
	  pOut ->PrintMessage(" Write the index of the player to burn him (Deduct 20 coins from his wallet for his next 3 turns)(from 0 to 3) ");
	  Index_Player = pIn ->GetInteger(pOut);
		}
	}
	pOut ->ClearStatusBar();

}

bool Fire::ApplyAttack(Grid* pGrid, Player* pPlayer)
{
		if ( pPlayer ->getthefirstAttack())
	{
	     if ( pPlayer->gettheNumAttacks() !=0 && dynamic_cast <Fire*>(pPlayer ->getthefirstAttack()))
		 {
			 pGrid ->PrintErrorMessage(" You have chosen this attack before. Click to continue ... ");
		     return false;
		 }
	}
	ReadAttackParameters(pGrid);
	if ( pGrid ->CheckCurrent_AppliedAttack(Index_Player,pPlayer ->getCurrentAttack()) == true)
	{
	pGrid ->Change_DeductCoinsState(Index_Player);
	return true;
	}
	else
	{
	     pGrid ->PrintErrorMessage(" The chosen player is currently affected by the same attack from another player. Click to ccontinue ...");
		 return false;
	}
}
