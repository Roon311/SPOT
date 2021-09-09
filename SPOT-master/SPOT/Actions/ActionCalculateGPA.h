#pragma once
#include "Action.h"
//Class responsible for adding course action
class ActionCalculateGPA :
	public Action
{
private:
	double GPA=0;
	const double A = 4.0;
	const double A_MINUS = 3.67;
	const double B_PLUS = 3.33;
	const double B = 3.0;
	const double B_MINUS = 2.67;
	const double C_PLUS = 2.33;
	const double C = 2.0;
	const double C_MINUS = 1.67;
	const double F = 0.0;
	double total = 0;
	int totaldonehours = 0;
public:
	ActionCalculateGPA(Registrar*);
	bool virtual Execute();
	double getGPA() const;
	virtual ~ActionCalculateGPA();
};