#include "Snake.h"	
#include <fstream>
Snake::Snake(const CellPosition & startCellPos, const CellPosition & endCellPos): GameObject(startCellPos) // A constructor for initialization
{

if ( (startCellPos.HCell() != endCellPos.HCell()) || startCellPos.VCell() > endCellPos.VCell())
	{
		if ( (startCellPos.HCell() != endCellPos.HCell()) && startCellPos.VCell() < endCellPos.VCell())
		{
			this->endCellPos = endCellPos;
			this -> endCellPos.SetHCell(startCellPos.HCell());
		}
		else if ((startCellPos.HCell() == endCellPos.HCell()) && startCellPos.VCell() > endCellPos.VCell())
		{
		    position = endCellPos;
			this->endCellPos = startCellPos;
		}
		else 
		{
			 position = endCellPos;
			this->endCellPos = startCellPos;
			this -> endCellPos.SetHCell(endCellPos.HCell());
		}
	}
	else {
	this->endCellPos = endCellPos;
	}
}

Snake::Snake ()
{

}

void Snake::Draw(Output* pOut) const // Draws a snake from its start cell to its end cell
{
		pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer) // Applys the effect of the snake by moving player to ladder's end cell
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x,y;
	pOut ->PrintMessage("You have reached a Snake. Click to continue ..." );
	pIn ->GetPointClicked(x,y);
	pOut ->ClearStatusBar();
	pGrid ->UpdatePlayerCell(pPlayer,endCellPos);
}
CellPosition Snake::GetEndPosition() const  // A getter for the endCellPos data member
{
	return endCellPos;
}

void Snake::Save(ofstream &OutFile, Type gameObject)
{
	if ( gameObject == Snakes )
	{
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
	}
}
Snake::~Snake() // Virtual destructor
{}

void Snake::Load(ifstream& Infile)
{
int StartCellNum, EndCellNum;
	Infile >> StartCellNum >> EndCellNum ;
	CellPosition SartCell(StartCellNum);
	CellPosition EndCell(EndCellNum);
	position = SartCell;
	endCellPos = EndCell;
}