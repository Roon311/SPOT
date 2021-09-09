#pragma once
#include "Action.h"
#include<iostream>
using namespace std;

//Class responsible for adding course action
class ActionAddCourse :
	public Action
{
public:
	ActionAddCourse(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddCourse();
};

