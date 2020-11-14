#pragma once

#include "Action.h"

class CopyCard : public Action
{
	CellPosition SourceCellPosition;
public:

	CopyCard(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads CopyCard action parameters (SourceCellPosition)
	
	virtual void Execute(); // copy a card with all its data to the clip board. 
	

	virtual ~CopyCard(); // Virtual Destructor
};