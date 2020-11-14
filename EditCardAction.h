#pragma once

#include "Action.h"

class EditCardAction : public Action
{     
	Card* CardCheck;
	bool CheckEdit;

public:
	EditCardAction(ApplicationManager *pApp);// A Constructor
	virtual void ReadActionParameters();// Reads EditCardAction action parameters 
	virtual void Execute();// Reads the parameters of the selected card again to make the user able to edit it
	virtual ~EditCardAction();// A Virtual Destructor
};


