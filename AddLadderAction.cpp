#include "AddLadderAction.h"
#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	checkLadderDrawing = true;
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	if ( startPos.IsValidCell() == false )
	{
		pGrid ->PrintErrorMessage(" The start cell is invalid! Click to continue ...");
		pOut->ClearStatusBar();
		checkLadderDrawing = false;
		return;
	}
	
	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	if ( endPos.IsValidCell() == false )
	{
		pGrid ->PrintErrorMessage(" The end cell is invalid! Click to continue ! Click to continue ...");
		pOut->ClearStatusBar();
		checkLadderDrawing = false;
		return;
	}
	if ( startPos.GetCellNum() == endPos.GetCellNum() )
	{
		pGrid ->PrintErrorMessage(" The end cell can't be the start cell ! Click to continue ...");
		pOut->ClearStatusBar();
		checkLadderDrawing = false;
		return;
	}
	Snake* parallelSnake = pGrid ->GetSnake(endPos);
	if ( parallelSnake )
	{
	if ( parallelSnake->GetPosition().GetCellNum() == endPos.GetCellNum() && parallelSnake->GetEndPosition().GetCellNum() == startPos.GetCellNum() )
	{
	    pGrid ->PrintErrorMessage(" You can't place ladder and snake parallel to each other. Click to continue ...");
		pOut->ClearStatusBar();
		checkLadderDrawing = false;
		return;
	}
	}
	if (pGrid ->GetCard(startPos))
		{
		  pGrid ->PrintErrorMessage(" The start cell cannot be a special cell ! Click to continue ...");
	      pOut->ClearStatusBar();
		  checkLadderDrawing = false;
		  return;
		}
	if (startPos.GetCellNum() == 1 || endPos.GetCellNum() == 99 )
	{
		pGrid ->PrintErrorMessage(" You cannot place game objects in the first or last cell! Click to continue ...");
	   pOut->ClearStatusBar();
	   checkLadderDrawing = false;
		return;
	}
	if (startPos.VCell() == NumVerticalCells-1 )
	{
	    pGrid ->PrintErrorMessage(" The start cell cannot be a cell in the last row ! Click to continue ...");
	    pOut->ClearStatusBar();
		checkLadderDrawing = false;
		return;
	}
	

	if (endPos.GetCellNum() < startPos.GetCellNum() )
	{
		pGrid ->PrintErrorMessage(" End cell cannot be smaller than start cell ! Click to continue ...");
		pOut->ClearStatusBar();
		checkLadderDrawing = false;
		return;
	}
    if ( endPos.HCell() != startPos.HCell() )
	{
		pGrid ->PrintErrorMessage(" End cell and start cell are not in the same column ! Click to continue ...");
		pOut->ClearStatusBar();
		checkLadderDrawing = false;
		return;
	}
	 
	CellPosition CellAbove (0,endPos.HCell());
	bool ThereisSnake = pGrid ->LoopFromAboveBelow(CellAbove,endPos);
	if ( ThereisSnake )
	{
	   pGrid ->PrintErrorMessage(" End cell cannot be a start of another ladder or snake ! Click to continue ...");
	             	pOut->ClearStatusBar();checkLadderDrawing = false;
	             	return;
	}
	for ( int i = startPos.GetCellNum(); i <= endPos.GetCellNum() ; i +=11)
	{
		CellPosition checkCell(i);
	    Ladder* checkLadder = pGrid->GetNextLadder(checkCell);
			if ( checkLadder)
			{
				if ( checkCell.HCell() == checkLadder->GetPosition().HCell() && (startPos.VCell() >= checkLadder->GetPosition().VCell() && endPos.VCell() <= checkLadder->GetPosition().VCell()))
				{
					if ( checkLadder->GetPosition().GetCellNum() != endPos.GetCellNum())
					{pGrid ->PrintErrorMessage(" Two ladders cannot overlap ! Click to continue ...");
	                 pOut->ClearStatusBar();
					 checkLadderDrawing = false;
	             	return;}
					else 
					{pGrid ->PrintErrorMessage(" End cell cannot be a start of another ladder or snake ! Click to continue ...");
	             	pOut->ClearStatusBar();checkLadderDrawing = false;
	             	return;}
				}
     		}
	}
  
    int StartH = startPos.HCell();
	int StartV = 8;
	CellPosition BottomUpCell(StartV,StartH);
	for ( int i = BottomUpCell.GetCellNum(); i <= startPos.GetCellNum() ; i +=11)
	{
		CellPosition checkCell(i);
	    Ladder* checkLadder = pGrid->GetNextLadder(checkCell);
			if ( checkLadder)
			{
				if ( checkCell.HCell() == checkLadder->GetPosition().HCell() && (startPos.VCell() >= checkLadder->GetEndPosition().VCell() && startPos.VCell() <= checkLadder->GetPosition().VCell()))
				{
					if ( checkLadder->GetPosition().GetCellNum() != endPos.GetCellNum())
					{pGrid ->PrintErrorMessage(" Two ladders cannot overlap ! Click to continue ...");
	                 pOut->ClearStatusBar();
					 checkLadderDrawing = false;
	             	return;}
					else 
					{pGrid ->PrintErrorMessage(" End cell cannot be a start of another ladder or snake ! Click to continue ...");
	             	pOut->ClearStatusBar();checkLadderDrawing = false;
	             	return;}
				}
     		}
	}

	    Snake* checkSnake = pGrid->GetNextSnake(endPos);
			if (checkSnake)
			{
				if ( endPos.HCell() == checkSnake->GetEndPosition().HCell() &&  endPos.VCell() == checkSnake->GetEndPosition().VCell())
				{
					pGrid ->PrintErrorMessage(" End cell cannot be a start of another ladder or snake ! Click to continue ...");
	             	pOut->ClearStatusBar();checkLadderDrawing = false;
	             	return;
				}
     		
	        }
	    checkSnake = pGrid->GetNextSnake(startPos);
			if (checkSnake)
			{
				if ( startPos.HCell() == checkSnake->GetEndPosition().HCell() &&  startPos.VCell() == checkSnake->GetEndPosition().VCell())
				{
					pGrid ->PrintErrorMessage(" End cell cannot be a start of another ladder or snake ! Click to continue ...");
	             	pOut->ClearStatusBar();checkLadderDrawing = false;
	             	return;
				}
     		
	        }

	///TODO: Make the needed validations on the read parameters
	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
	

	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if ( checkLadderDrawing == true )
	{
	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
	}
}

