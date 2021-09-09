#pragma once
#pragma once
#include "Action.h"
//Class responsible for adding course action
class ActionDDOOC :
	public Action
{
public:
	ActionDDOOC(Registrar*);
	bool virtual Execute();
	virtual ~ActionDDOOC();
};

