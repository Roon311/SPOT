#pragma once
#include "Action.h"
class ActionDeleteCourse : public Action
{
public:
	ActionDeleteCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionDeleteCourse();
};

