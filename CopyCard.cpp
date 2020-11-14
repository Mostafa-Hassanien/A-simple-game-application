#include "Input.h"
#include "Output.h"
#include "CopyCard.h"
#include "Grid.h"

CopyCard::CopyCard(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

CopyCard::~CopyCard()
{
}

void CopyCard::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Copy Card Action: Click to continue ...");
	int x,y;
	pIn ->GetPointClicked(x,y);
	pOut ->PrintMessage("click on the source cell");
	// Read the SourceCellPosition
	SourceCellPosition = pIn ->GetCellClicked();
	pOut ->ClearStatusBar();	
}

void CopyCard::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters(); // Reading the Parameters 
	if ( pGrid ->GetCard(SourceCellPosition) )
	{
		pGrid ->SetClipboard(pGrid ->GetCard(SourceCellPosition)); // Setting all SourceCellPositionCard data to the clip board
	}
}

