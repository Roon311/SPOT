#pragma once
#include "Action.h"
#include<iostream>
using namespace std;

//Class responsible for adding course action
class ActionCourseDependancies :
	public Action
{
public:
	ActionCourseDependancies(Registrar*);
	bool virtual Execute();
	virtual ~ActionCourseDependancies();
};