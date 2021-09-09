#pragma once
#include "Action.h"
#include<iostream>
using namespace std;

//Class responsible for adding course action
class ActionDragAndDrop :
	public Action
{
public:
	ActionDragAndDrop(Registrar*);
	bool virtual Execute();
	virtual ~ActionDragAndDrop();
};

