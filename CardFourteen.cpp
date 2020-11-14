#include "CardFourteen.h"
CardFourteen::CardFourteen(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 14; // set the inherited cardNumber data member with the card number (9 here)
	OwnerPlayer = NULL; //initialize the ownerplayer to null
}
CardFourteen::CardFourteen()
{
	cardNumber = 14;
	OwnerPlayer = NULL; //initialize the ownerplayer to null
}
void CardFourteen::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card* pCard = pGrid->GetTheFirstCardFourteen();
	if (pCard)
	{
		pOut->PrintMessage("New CardFourteen. Click to continue...");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		CardFourteen* FirstCardFourteen = dynamic_cast <CardFourteen*> (pCard);
		CardPrice = FirstCardFourteen->CardPrice;
		FeesToPay = FirstCardFourteen->FeesToPay;
		return;
	}
	pOut->PrintMessage("New CardFourteen: Enter its CardPrice ...");
	CardPrice = pIn->GetInteger(pOut);
	pOut->PrintMessage(" Enter the fees you  want any other player to pay ...");
	FeesToPay = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}

void CardFourteen::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card::Apply(pGrid,pPlayer);
	if (!OwnerPlayer)
	{
		pOut->PrintMessage("Do you want to buy CardFourteen? (y/n) ");
		string actualmsg = pIn->GetSrting(pOut);
		while (actualmsg != "y" && actualmsg != "n")
		{
			pOut->PrintMessage("Do you want to buy CardFourteen, please enter y for Yes and n for No: ");
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
				pGrid->setAllCardFourteen(OwnerPlayer);
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
void CardFourteen::Save(ofstream& OutFile, Type gameObject)
{
	if (checkCardFourteenSave == false)
	{
		if (gameObject == Cards)
		{
			OutFile << cardNumber << " " << position.GetCellNum() << " " << CardPrice << " " << FeesToPay << endl;
			checkCardFourteenSave = true;
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
void CardFourteen::Load(ifstream& Infile)
{
	if (checkCardFourteenload == false)
	{
		int  CellposNum;
		Infile >> CellposNum >> CardPrice >> FeesToPay;
		CellPosition Cellpos(CellposNum);
		position = Cellpos;
		checkCardFourteenload = true;
	}
	else
	{
		int  CellposNum;
		Infile >> CellposNum;
		CellPosition Cellpos(CellposNum);
		position = Cellpos;

	}
}

void CardFourteen::SetOwnerPlayer(Player* pPlayer)
{
	OwnerPlayer = pPlayer;
}
CardFourteen::~CardFourteen()
{
}
bool CardFourteen::checkCardFourteenSave = false; // initialize cardten to false ( first save )
bool CardFourteen::checkCardFourteenload = false; // initialize cardten to false ( first load )
int CardFourteen::FeesToPay = 0; // fees to the player who owns the cell
int CardFourteen::CardPrice = 0; // the card price 
