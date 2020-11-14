#include "SwitchToPlayMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

SwitchToPlayMode::SwitchToPlayMode(ApplicationManager *pApp) : Action(pApp)
{
	// The constructor initializes the ApplicationManager pointer data member
}

SwitchToPlayMode::~SwitchToPlayMode()
{
}
void SwitchToPlayMode::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Switch To Play Mode: Click Anywhere to Continue ...");
	int x ,y ;
    pIn ->GetPointClicked(x,y);
	pOut ->ClearStatusBar();
}

void SwitchToPlayMode::Execute()
{
	ReadActionParameters();
    Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->CreatePlayModeToolBar();
}
