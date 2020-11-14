#include "Input.h"
#include "Output.h"
#include "CutCard.h"
#include "Grid.h"

CutCard::CutCard(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

CutCard::~CutCard()
{
}

void CutCard::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Cut Card Action: Click to continue ...");
	int x,y;
	pIn ->GetPointClicked(x,y);
	pOut ->PrintMessage("click on the source cell");
	// Read the SourceCellPosition
	SourceCellPosition = pIn ->GetCellClicked();
	pOut ->ClearStatusBar();	
}

void CutCard::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters(); // Reading the Parameters 
	if ( pGrid ->GetCard(SourceCellPosition) )
	{
		pGrid ->SetClipboard(pGrid ->GetCard(SourceCellPosition)); // Setting all SourceCellPositionCard data to the clip board
		pGrid ->RemoveObjectFromCell(SourceCellPosition); // Removing the selcted card from the SourceCell
	}
}

