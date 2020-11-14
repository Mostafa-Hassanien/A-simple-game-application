#include "CardTen.h"


CardTen::CardTen(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 10; // set the inherited cardNumber data member with the card number (9 here)
	OwnerPlayer = NULL ; //initialize the ownerplayer to null 
}
CardTen::CardTen()
{
	cardNumber = 10;
	OwnerPlayer = NULL ; //initialize the ownerplayer to null
}
void CardTen::ReadCardParameters(Grid * pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card* pCard = pGrid ->GetTheFirstCardTen();
	if ( pCard)
	{
	   pOut ->PrintMessage("New CardTen. Click to continue...");
	   int x,y;
	   pIn ->GetPointClicked(x,y);
	   pOut ->ClearStatusBar();
	   CardTen* FirstCardTen = dynamic_cast <CardTen*> ( pCard ); 
	   CardPrice = FirstCardTen ->CardPrice;
	   FeesToPay = FirstCardTen ->FeesToPay;
	   return;
	}
	pOut ->PrintMessage("New CardTen: Enter its CardPrice ...");
	CardPrice = pIn ->GetInteger(pOut);
	pOut ->PrintMessage(" Enter the fees you  want any other player to pay ...");
	FeesToPay = pIn ->GetInteger(pOut);
    pOut ->ClearStatusBar();
}

void CardTen::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card::Apply(pGrid,pPlayer);
	if(OwnerPlayer == NULL)
	{
		pOut ->PrintMessage ("Do you want to buy CardTen? (y/n) ");
	    string actualmsg = pIn ->GetSrting(pOut);
		while ( actualmsg != "y" && actualmsg != "n" )
		{
		 pOut ->PrintMessage ("Do you want to buy CardTen, please enter y for Yes and n for No: ");
	     actualmsg = pIn ->GetSrting(pOut);
		}
			if (actualmsg=="y")
			{
				if (pPlayer->GetWallet()> CardPrice)
				{
					int NewWalletAmount = pPlayer->GetWallet()-CardPrice;
					pPlayer->SetWallet(NewWalletAmount);
					string msg =" Your new wallet amount is equal to " + to_string(NewWalletAmount);
					pOut ->PrintMessage(msg);
					int x,y;
	                pIn ->GetPointClicked(x,y);
					pOut ->ClearStatusBar();
					OwnerPlayer = pPlayer;
					pGrid ->setAllCardTen(OwnerPlayer);
					return;
				}
				else
				{
				    pOut ->PrintMessage(" you don't have enough money to buy the card . Click to continue...");
					int x,y;
	                pIn ->GetPointClicked(x,y);
					pOut ->ClearStatusBar();
					return;
				}
			}
			else
				{
			pOut->ClearStatusBar();
			return;
		}
	}
	else
	{
		{
		if ( pPlayer->getPlayerNum() != OwnerPlayer ->getPlayerNum())
		{
		pPlayer ->SetWallet(pPlayer ->GetWallet() - FeesToPay);
		OwnerPlayer ->SetWallet(OwnerPlayer ->GetWallet() + FeesToPay );
		string msg =" Your new wallet amount is equal to " + to_string((pPlayer ->GetWallet()));
	    pOut ->PrintMessage(msg);
		int x,y;
	    pIn ->GetPointClicked(x,y);
		pOut ->ClearStatusBar();
		return;
		}
		}
	}
}
void CardTen::Save(ofstream &OutFile, Type gameObject)
{
	if ( checkCardTenSave == false )
	{
	if ( gameObject == Cards )
	{
	  OutFile << cardNumber << " " << position.GetCellNum() << " " << CardPrice << " " << FeesToPay << endl;
	  checkCardTenSave = true;
	}
	}
	else
	{
		if ( gameObject == Cards )
	{
	  OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}	
	}
}
void CardTen::Load(ifstream& Infile)
{
	
	if ( checkCardTenload == false )
	{
	 int  CellposNum;
	Infile >> CellposNum >> CardPrice >> FeesToPay;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;
	checkCardTenload = true;
	}
	else 
	{
	int  CellposNum;
	Infile >> CellposNum ;
	CellPosition Cellpos(CellposNum);
	position = Cellpos;
	}
}

void CardTen::SetOwnerPlayer(Player* pPlayer)
{
	OwnerPlayer = pPlayer;
}
CardTen::~CardTen()
{

}

bool CardTen::checkCardTenSave = false; // initialize cardten to false ( first save )
bool CardTen::checkCardTenload = false; // initialize cardten to false ( first load )
int CardTen::FeesToPay = 0; // fees to the player who owns the cell
int CardTen::CardPrice = 0; // the card price 
