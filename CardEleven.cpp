#include "CardEleven.h"
CardEleven::CardEleven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 11; // set the inherited cardNumber data member with the card number (9 here)
	OwnerPlayer = NULL; //initialize the ownerplayer to null
}
CardEleven::CardEleven()
{
	cardNumber = 11;
	OwnerPlayer = NULL; //initialize the ownerplayer to null

}
void CardEleven::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card* pCard = pGrid->GetTheFirstCardEleven();
	if (pCard)
	{
		pOut->PrintMessage("New CardEleven. Click to continue...");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		CardEleven* FirstCardEleven = dynamic_cast <CardEleven*> (pCard);
		CardPrice = FirstCardEleven->CardPrice;
		FeesToPay = FirstCardEleven->FeesToPay;
		return;
	}
	pOut->PrintMessage("New CardEleven: Enter its CardPrice ...");
	CardPrice = pIn->GetInteger(pOut);
	pOut->PrintMessage(" Enter the fees you  want any other player to pay ...");
	FeesToPay = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card::Apply(pGrid,pPlayer);
	if (!OwnerPlayer)
	{
		pOut->PrintMessage("Do you want to buy CardEleven? (y/n) ");
		string actualmsg = pIn->GetSrting(pOut);
		while (actualmsg != "y" && actualmsg != "n")
		{
			pOut->PrintMessage("Do you want to buy CardEleven, please enter y for Yes and n for No: ");
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
				pGrid->setAllCardEleven(OwnerPlayer);
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
void CardEleven::Save(ofstream& OutFile, Type gameObject)
{
	if (checkCardElevenSave == false)
	{
		if (gameObject == Cards)
		{
			OutFile << cardNumber << " " << position.GetCellNum() << " " << CardPrice << " " << FeesToPay << endl;
			checkCardElevenSave = true;
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
void CardEleven::Load(ifstream& Infile)
{
	if (checkCardElevenload == false)
	{
		int  CellposNum;
		Infile >> CellposNum >> CardPrice >> FeesToPay;
		CellPosition Cellpos(CellposNum);
		position = Cellpos;
		checkCardElevenload = true;
	}
	else
	{
		int  CellposNum;
		Infile >> CellposNum;
		CellPosition Cellpos(CellposNum);
		position = Cellpos;

	}
}

void CardEleven::SetOwnerPlayer(Player* pPlayer)
{
	OwnerPlayer = pPlayer;
}
CardEleven::~CardEleven()
{
}
bool CardEleven::checkCardElevenSave = false; // initialize cardten to false ( first save )
bool CardEleven::checkCardElevenload = false; // initialize cardten to false ( first load )
int CardEleven::FeesToPay = 0; // fees to the player who owns the cell
int CardEleven::CardPrice = 0; // the card price 
