#include "SwitchToDesignMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

SwitchToDesignMode::SwitchToDesignMode(ApplicationManager *pApp) : Action(pApp)
{
	// The constructor initializes the ApplicationManager pointer data member
}

SwitchToDesignMode::~SwitchToDesignMode()
{
}
void SwitchToDesignMode::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Switch To Design Mode: Click Anywhere to Continue ...");
	int x ,y ;
    pIn ->GetPointClicked(x,y);
	pOut ->ClearStatusBar();
}

void SwitchToDesignMode::Execute()
{
	ReadActionParameters();
    Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->CreateDesignModeToolBar();
	pGrid->StartNewGame();
}
