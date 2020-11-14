#include"Lightning.h"

Lightning::Lightning()
{
	// constructor 
}
Lightning::~Lightning()
{
		// virtual Destructor
}
void Lightning::ReadAttackParameters(Grid* pGrid)
{
	Output* pOut = pGrid ->GetOutput();
	Input* pIn = pGrid ->GetInput();
	pOut ->PrintMessage(" Lightning Attack is being launched. Click to continue... " );
	int x, y ;
	pIn ->GetPointClicked(x,y);
	pOut ->ClearStatusBar();
}
bool Lightning::ApplyAttack(Grid* pGrid, Player* pPlayer)
{
	if ( pPlayer ->getthefirstAttack())
	{
	     if ( pPlayer->gettheNumAttacks() !=0 && dynamic_cast <Lightning*>(pPlayer ->getthefirstAttack()))
		 {
			 pGrid ->PrintErrorMessage(" You have chosen this attack before. Click to continue ... ");
		     return false;
		 }
	}
	ReadAttackParameters(pGrid);
	pGrid ->DeductCoins();
	return true;
}