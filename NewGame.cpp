#include "NewGame.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

NewGame::NewGame(ApplicationManager *pApp) : Action(pApp)
{
	
	// The constructor initializes the ApplicationManager pointer data member
}

NewGame::~NewGame()
{
}

void NewGame::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("New Game: Click Anywhere to Continue ...");
	int x ,y ;
    pIn ->GetPointClicked(x,y);
	pOut->ClearStatusBar();
}
void NewGame::Execute()
{
	ReadActionParameters();
    Grid* pGrid = pManager->GetGrid();
	pGrid ->StartNewGame();
}
