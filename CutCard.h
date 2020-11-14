#pragma once

#include "Action.h"

class CutCard : public Action
{
	CellPosition SourceCellPosition;
public:

	CutCard(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads CutCard action parameters (SourceCellPosition)
	
	virtual void Execute(); // cuts a card with all its data to the clip board

	virtual ~CutCard(); // Virtual Destructor
};