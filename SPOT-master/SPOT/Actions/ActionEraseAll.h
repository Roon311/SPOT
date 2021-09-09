#pragma once
#include"Action.h"
class ActionEraseAll : public Action
{
public:
	ActionEraseAll(Registrar*);
	bool virtual Execute();
	virtual ~ActionEraseAll();
};

