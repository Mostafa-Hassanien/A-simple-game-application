#include "CardThirteen.h"
CardThirteen::CardThirteen(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 13; // set the inherited cardNumber data member with the card number (9 here)
	OwnerPlayer = NULL; //initialize the ownerplayer to null
}
CardThirteen::CardThirteen()
{
	cardNumber = 13;
    OwnerPlayer = NULL; //initialize the ownerplayer to null
}
void CardThirteen::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card* pCard = pGrid->GetTheFirstCardThirteen();
	if (pCard)
	{
		pOut->PrintMessage("New CardThirteen. Click to continue...");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		CardThirteen* FirstCardThirteen = dynamic_cast <CardThirteen*> (pCard);
		CardPrice = FirstCardThirteen->CardPrice;
		FeesToPay = FirstCardThirteen->FeesToPay;
		return;
	}
	pOut->PrintMessage("New CardThirteen: Enter its CardPrice ...");
	CardPrice = pIn->GetInteger(pOut);
	pOut->PrintMessage(" Enter the fees you  want any other player to pay ...");
	FeesToPay = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}

void CardThirteen::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card::Apply(pGrid,pPlayer);
	if (!OwnerPlayer)
	{
		pOut->PrintMessage("Do you want to buy CardThirteen? (y/n) ");
		string actualmsg = pIn->GetSrting(pOut);
		while (actualmsg != "y" && actualmsg != "n")
		{
			pOut->PrintMessage("Do you want to buy CardThirteen, please enter y for Yes and n for No: ");
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
				pGrid->setAllCardThirteen(OwnerPlayer);
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
void CardThirteen::Save(ofstream& OutFile, Type gameObject)
{
	if (checkCardThirteenSave == false)
	{
		if (gameObject == Cards)
		{
			OutFile << cardNumber << " " << position.GetCellNum() << " " << CardPrice << " " << FeesToPay << endl;
			checkCardThirteenSave = true;
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
void CardThirteen::Load(ifstream& Infile)
{
	if (checkCardThirteenload == false)
	{
		int  CellposNum;
		Infile >> CellposNum >> CardPrice >> FeesToPay;
		CellPosition Cellpos(CellposNum);
		position = Cellpos;
		checkCardThirteenload = true;
	}
	else
	{
		int  CellposNum;
		Infile >> CellposNum;
		CellPosition Cellpos(CellposNum);
		position = Cellpos;

	}
}

void CardThirteen::SetOwnerPlayer(Player* pPlayer)
{
	OwnerPlayer = pPlayer;
}
CardThirteen::~CardThirteen()
{
}
bool CardThirteen::checkCardThirteenSave = false; // initialize cardten to false ( first save )
bool CardThirteen::checkCardThirteenload = false; // initialize cardten to false ( first load )
int CardThirteen::FeesToPay = 0; // fees to the player who owns the cell
int CardThirteen::CardPrice = 0; // the card price 
