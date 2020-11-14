#pragma once

#include "Action.h"

class NewGame : public Action
{
public:
	NewGame(ApplicationManager *pApp);
    virtual ~NewGame();
	virtual void ReadActionParameters();
	virtual void Execute();
};

