#include "SaveGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
SaveGridAction::SaveGridAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

SaveGridAction::~SaveGridAction()
{
}

void SaveGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
    pOut ->PrintMessage(" Enter the file name, please: ");
	FileName = pIn ->GetSrting(pOut);
	pOut ->ClearStatusBar();
}

void SaveGridAction::Execute()
{
	ReadActionParameters();
	ofstream OutFile;
	string file = FileName + ".txt";
	OutFile.open(file);
	Grid* pGrid = pManager->GetGrid();
	OutFile << pGrid ->GetNumberOfLadders() << endl;
	pGrid ->SaveAll(OutFile,Ladders);
	OutFile << pGrid ->GetNumberOfSnakes() << endl;
	pGrid ->SaveAll(OutFile,Snakes);
	OutFile << pGrid ->GetNumberOfCards() << endl;
	pGrid ->SaveAll(OutFile,Cards);
	OutFile.close();
}