#pragma once

#include "Action.h"

class PasteCard : public Action
{
	CellPosition DestinationCellPosition;
	bool checkPaste;
public:

	PasteCard(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads PasteCard action parameters (DestinationCellPosition)
	
	virtual void Execute(); // Paste the card in the clip board to the destination cell
	
	virtual ~PasteCard(); // Virtual Destructor
};