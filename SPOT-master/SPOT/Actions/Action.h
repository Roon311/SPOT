#pragma once

class Registrar; //forward class declaration

//Base class for all possible actions (abstract class)
class Action
{
protected:
	Registrar* pReg;

public:
	Action(Registrar* p) { pReg = p; }
	
	//Execute action (code depends on action type)
	bool virtual Execute() = 0; //pure virtual
	virtual ~Action() {}
};

