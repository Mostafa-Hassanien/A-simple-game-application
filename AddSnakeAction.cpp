#include "AddSnakeAction.h"
#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager *pApp) : Action(pApp)
{
	checkSnakedrawing = true;
	// Initializes the pManager pointer of Action with the passed pointer
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	if ( startPos.IsValidCell() == false )
	{
		pGrid ->PrintErrorMessage(" The start cell is invalid! Click to continue ! Click to continue ...");
		pOut->ClearStatusBar();
		checkSnakedrawing = false;
		return;
	}


	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	if ( endPos.IsValidCell() == false )
	{
		pGrid ->PrintErrorMessage(" The end cell is invalid! Click to continue ! Click to continue ...");
		pOut->ClearStatusBar();
		checkSnakedrawing = false;
		return;
	}
	if ( startPos.GetCellNum() == endPos.GetCellNum() )
	{
		pGrid ->PrintErrorMessage(" The end cell can't be the start cell ! Click to continue ...");
		pOut->ClearStatusBar();
		checkSnakedrawing = false;
		return;
	}
	Ladder* ParallelLadder = pGrid ->GetLadder(endPos);
	if (ParallelLadder)
	{
	if ( ParallelLadder->GetPosition().GetCellNum() == endPos .GetCellNum() && startPos.GetCellNum() == ParallelLadder ->GetEndPosition().GetCellNum())
	{
	pGrid ->PrintErrorMessage(" You can't place ladder and snake parallel to each other. Click to continue ...");
		pOut->ClearStatusBar();
		checkSnakedrawing = false;
		return;
	}
	}
	if (pGrid ->GetCard(startPos))
		{
		  pGrid ->PrintErrorMessage(" The start cell cannot be a special cell ! Click to continue ...");
	      pOut->ClearStatusBar();
		  checkSnakedrawing = false;
		  return;
		}
	if (startPos.GetCellNum() == 99 || endPos.GetCellNum() == 1 )
	{
		pGrid ->PrintErrorMessage(" You cannot place game objects in the first or last cell! Click to continue ...");
	   pOut->ClearStatusBar();
	   checkSnakedrawing = false;
		return;
	}
	if (startPos.VCell() == NumVerticalCells-9 )
	{
	    pGrid ->PrintErrorMessage(" The start cell cannot be a cell in the first row ! Click to continue ...");
	    pOut->ClearStatusBar();
		checkSnakedrawing = false;
		return;
	}
	if (endPos.GetCellNum() > startPos.GetCellNum() )
	{
		pGrid ->PrintErrorMessage(" end cell cannot be bigger than start cell ! Click to continue ...");
		pOut->ClearStatusBar();
		checkSnakedrawing = false;
		return;
	}
    if ( endPos.HCell() != startPos.HCell() )
	{
		pGrid ->PrintErrorMessage(" end cell and start cell are not in the same column ! Click to continue ...");
		pOut->ClearStatusBar();
		checkSnakedrawing = false;
		return;
	}
	for ( int i = endPos.GetCellNum(); i <= startPos.GetCellNum() ; i +=11)
	{
		CellPosition checkCell(i);
	    Snake* checkSnake = pGrid->GetNextSnake(checkCell);
			if ( checkSnake)
			{
				if ( checkCell.HCell() == checkSnake->GetPosition().HCell() && (startPos.VCell() <= checkSnake->GetPosition().VCell() && endPos.VCell() >= checkSnake->GetPosition().VCell()))
				{
					if ( checkSnake->GetPosition().GetCellNum() != endPos.GetCellNum())
					{pGrid ->PrintErrorMessage(" Two snakes cannot overlap ! Click to continue ...");
	                 pOut->ClearStatusBar();
					 checkSnakedrawing = false;
	             	return;}
					else 
					{pGrid ->PrintErrorMessage(" end cell cannot be a start of another ladder or snake ! Click to continue ...");
	             	pOut->ClearStatusBar();checkSnakedrawing = false;
	             	return;}
				}
     		}
	}
	int EndH= startPos.HCell();
	int EndV = 0;
	CellPosition ToUpCell(EndV,EndH);
	for ( int i = endPos.GetCellNum(); i <= ToUpCell.GetCellNum() ; i +=11)
	{
		CellPosition checkCell(i);
	    Snake* checkSnake = pGrid->GetNextSnake(checkCell);
			if ( checkSnake)
			{
				if ( checkCell.HCell() == checkSnake->GetPosition().HCell() && (startPos.VCell() <= checkSnake->GetEndPosition().VCell() && startPos.VCell() >= checkSnake->GetPosition().VCell()))
				{
					if ( checkSnake->GetEndPosition().GetCellNum() != startPos.GetCellNum())
					{pGrid ->PrintErrorMessage(" Two snakes cannot overlap ! Click to continue ...");
	                 pOut->ClearStatusBar();
					 checkSnakedrawing = false;
	             	return;}
					else 
					{pGrid ->PrintErrorMessage(" end cell cannot be a start of another ladder or snake ! Click to continue ...");
	             	pOut->ClearStatusBar();checkSnakedrawing = false;
	             	return;}
				}
     		}
	}
	  
		int StartH = startPos.HCell();
		int StartV = 8;
		CellPosition BottomUpCell(StartV,StartH);
	bool ThereisALadder = pGrid ->LoopFromBottomToAbove(endPos,BottomUpCell);
	if (ThereisALadder)
	{
		pGrid ->PrintErrorMessage(" end cell cannot be a start of another ladder or snake ! Click to continue ...");
	             	pOut->ClearStatusBar();checkSnakedrawing = false;
	             	return;
	}
		
	pOut->ClearStatusBar();
}
AddSnakeAction::~AddSnakeAction()
{
}
void AddSnakeAction::Execute() 
{
	

	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if ( checkSnakedrawing == true )
	{
	// Create a Ladder object with the parameters read from the user
	Snake * pSnake = new Snake(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	}
}
