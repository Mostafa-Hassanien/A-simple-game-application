#include "OpenGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
#include "Ladder.h"
#include "Snake.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include "CardFourteen.h"



OpenGridAction::OpenGridAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

OpenGridAction::~OpenGridAction()
{
}

void OpenGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
    pOut ->PrintMessage(" Enter the file name to be opened, please: ");
	FileName = pIn ->GetSrting(pOut);
	pOut ->ClearStatusBar();
}

void OpenGridAction::Execute()
{
	int NumberOfLadders, NumberOfSnakes,NumberOfCards;
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters();
	ifstream Infile;
	string file = FileName + ".txt";
	Infile.open(file);
	if ( !Infile.is_open())
	{
		pGrid ->PrintErrorMessage(" This File doesn't exist. Click to continue ... ");
		return;
	}
	CellPosition FirstCellInTheGrid(1);
	if ( pGrid ->GetNextLadder(FirstCellInTheGrid) || pGrid ->GetNextSnake(FirstCellInTheGrid) || pGrid ->GetNextCard(FirstCellInTheGrid)  )
	{
		pGrid ->CleanGrid();
	}
	Infile >> NumberOfLadders;
	GameObject* pNewObject ;
	for ( int i = 0;i < NumberOfLadders ; i++)
	{
		 pNewObject = new Ladder();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
	}
	Infile >> NumberOfSnakes;
	for ( int i = 0;i < NumberOfSnakes ; i++)
	{
		pNewObject = new Snake();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
	}
	Infile >> NumberOfCards;
	for ( int i = 0;i < NumberOfCards ; i++)
	{
		int CardNumber;
		Infile >> CardNumber;
	switch ( CardNumber )
		{
	case 1 :
		 pNewObject = new CardOne();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 2 :
		 pNewObject = new CardTwo();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 3 :
		 pNewObject = new CardThree();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 4 :
		 pNewObject = new CardFour();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 5 :
		 pNewObject = new CardFive();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 6 :
		 pNewObject = new CardSix();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 7 :
		 pNewObject = new CardSeven();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 8 :
		 pNewObject = new CardEight();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 9:
		pNewObject = new CardNine();
		pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 10:
			pNewObject = new CardTen();
			pNewObject->Load(Infile);
			pGrid->AddObjectToCell(pNewObject);
			break;
	case 11 :
		 pNewObject = new CardEleven();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 12 :
		 pNewObject = new CardTwelve();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 13 :
		 pNewObject = new CardThirteen();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
	case 14 :
		 pNewObject = new CardFourteen();
		 pNewObject ->Load(Infile);
		pGrid ->AddObjectToCell(pNewObject);
		break;
		}
	}
	Infile.close();
}