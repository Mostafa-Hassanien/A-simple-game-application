#include "Input.h"
#include "Output.h"
#include "DeleteGameObject.h"
#include "Grid.h"

DeleteGameObject::DeleteGameObject(ApplicationManager *pApp) : Action(pApp)
{
	checkdeleting = true; // deleting intializes with true
	// Initializes the pManager pointer of Action with the passed pointer
}

DeleteGameObject::~DeleteGameObject()
{
}

void DeleteGameObject::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Delete Game Object: Click to continue ...");
	int x,y;
	pIn ->GetPointClicked(x,y);
	pOut ->PrintMessage("Click on the Object");
	// Read the Cellposition
	Cellposition = pIn ->GetCellClicked();
	if ( Cellposition.IsValidCell() == false )
	{
	   pGrid ->PrintErrorMessage(" The selected cell is invalid! Click to continue ...");
	   pOut->ClearStatusBar();
	   checkdeleting = false;
		return;
	}

  if (!pGrid ->GetGameObject(Cellposition))
  {
	  pGrid ->PrintErrorMessage(" There is no Object in the cell! Click to continue ...");
	   pOut->ClearStatusBar();
	   checkdeleting = false;
		return;
  }


	pOut ->ClearStatusBar();	
}

void DeleteGameObject::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters(); // Reading the Parameters 
	if ( checkdeleting == true )
	{
	if ( pGrid ->GetGameObject(Cellposition) )
	{
		pGrid ->RemoveObjectFromCell(Cellposition); // Removing the selcted object from the cell
		return;
	}
	}
}

