#include "CardTwelve.h"
CardTwelve::CardTwelve(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 12; // set the inherited cardNumber data member with the card number (9 here)
	OwnerPlayer = NULL; //initialize the ownerplayer to null
}
CardTwelve::CardTwelve()
{
	cardNumber = 12;
	OwnerPlayer = NULL; //initialize the ownerplayer to null
}
void CardTwelve::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card* pCard = pGrid->GetTheFirstCardTwelve();
	if (pCard)
	{
		pOut->PrintMessage("New CardTwelve. Click to continue...");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		CardTwelve* FirstCardTwelve = dynamic_cast <CardTwelve*> (pCard);
		CardPrice = FirstCardTwelve->CardPrice;
		FeesToPay = FirstCardTwelve->FeesToPay;
		return;
	}
	pOut->PrintMessage("New CardTwelve: Enter its CardPrice ...");
	CardPrice = pIn->GetInteger(pOut);
	pOut->PrintMessage(" Enter the fees you  want any other player to pay ...");
	FeesToPay = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card::Apply(pGrid,pPlayer);
	if (!OwnerPlayer)
	{
		pOut->PrintMessage("Do you want to buy CardTwelve? (y/n) ");
		string actualmsg = pIn->GetSrting(pOut);
		while (actualmsg != "y" && actualmsg != "n")
		{
			pOut->PrintMessage("Do you want to buy CardTwelve, please enter y for Yes and n for No: ");
			actualmsg = pIn->GetSrting(pOut);
		}
		if (actualmsg == "y")
		{
			if (pPlayer->GetWallet() > CardPrice)
			{
				int NewWalletAmount = pPlayer->GetWallet() - CardPrice;
				pPlayer->SetWallet(NewWalletAmount);
				string msg = " Your new wallet amount is equal to " + to_string(NewWalletAmount);
				pOut->PrintMessage(msg);
				int x, y;
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				OwnerPlayer = pPlayer;
				pGrid->setAllCardTwelve(OwnerPlayer);
				return;
			}
			else
			{
				pOut->PrintMessage(" you don't have enough money to buy the card . Click to continue...");
				int x, y;
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
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
		if (pPlayer->getPlayerNum() != OwnerPlayer->getPlayerNum())
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - FeesToPay);
			OwnerPlayer->SetWallet(OwnerPlayer->GetWallet() + FeesToPay);
			string msg = " Your new wallet amount is equal to " + to_string(pPlayer ->GetWallet());
			pOut->PrintMessage(msg);
			int x, y;
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			return;
		}
	}
}
void CardTwelve::Save(ofstream& OutFile, Type gameObject)
{
	if (checkCardTwelveSave == false)
	{
		if (gameObject == Cards)
		{
			OutFile << cardNumber << " " << position.GetCellNum() << " " << CardPrice << " " << FeesToPay << endl;
			checkCardTwelveSave = true;
		}
	}
	else
	{
		if (gameObject == Cards)
		{
			OutFile << cardNumber << " " << position.GetCellNum() << endl;
		}
	}
}
void CardTwelve::Load(ifstream& Infile)
{
	if (checkCardTwelveload == false)
	{
		int  CellposNum;
		Infile >> CellposNum >> CardPrice >> FeesToPay;
		CellPosition Cellpos(CellposNum);
		position = Cellpos;
		checkCardTwelveload = true;
	}
	else
	{
		int  CellposNum;
		Infile >> CellposNum;
		CellPosition Cellpos(CellposNum);
		position = Cellpos;

	}
}

void CardTwelve::SetOwnerPlayer(Player* pPlayer)
{
	OwnerPlayer = pPlayer;
}
CardTwelve::~CardTwelve()
{

}
bool CardTwelve::checkCardTwelveSave = false; // initialize cardten to false ( first save )
bool CardTwelve::checkCardTwelveload = false; // initialize cardten to false ( first load )
int CardTwelve::FeesToPay = 0; // fees to the player who owns the cell
int CardTwelve::CardPrice = 0; // the card price 
