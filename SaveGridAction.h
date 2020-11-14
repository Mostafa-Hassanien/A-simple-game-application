#pragma once

#include "Action.h"

class SaveGridAction : public Action
{
	string FileName;
public:
	SaveGridAction(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads SaveGridAction action parameters (FileName)
	
	virtual void Execute(); //  Reads the Parameters of SaveGridAction 
	                        // then calls SaveAll of every gameobject
	virtual ~SaveGridAction(); // A Virtual Destructor


};
