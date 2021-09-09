#pragma once
#include "Action.h"
//Class responsible for adding course action
class ActionCourseInfo :
	public Action
{
public:
	ActionCourseInfo(Registrar*);
	bool virtual Execute();
	virtual ~ActionCourseInfo();
};

