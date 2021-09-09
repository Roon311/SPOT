#pragma once
#include "Action.h"
class ActionAddNotes :
	public Action
{
public:
	ActionAddNotes(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddNotes();
};
