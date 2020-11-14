#pragma once

#include "Action.h"

class DeleteGameObject : public Action
{
	CellPosition Cellposition;
	bool checkdeleting;
public:

	DeleteGameObject(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads DeleteGameObject action parameters (Cellposition)
	
	virtual void Execute(); // delete the game object in the cell that the user chooses.

	virtual ~DeleteGameObject(); // Virtual Destructor
};