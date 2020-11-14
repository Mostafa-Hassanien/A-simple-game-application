#pragma once

#include "Action.h"

class SwitchToPlayMode : public Action
{
public:
	SwitchToPlayMode(ApplicationManager *pApp);
    virtual ~SwitchToPlayMode();
	virtual void ReadActionParameters();
	virtual void Execute();
};