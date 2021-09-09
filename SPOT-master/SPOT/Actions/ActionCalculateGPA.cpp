#include "ActionCalculateGPA.h"
#include "..\Registrar.h"
#include<iterator>
#include <iostream>
#include"../GUI/GUI.h"
#include"../Utils/Utils.h"
#include <cmath>
ActionCalculateGPA::ActionCalculateGPA(Registrar* P) :Action(P)
{
}


bool ActionCalculateGPA::Execute()
{
	vector<string>GPA_OF_All_Semesters;
	StudyPlan* plan = pReg->getStudyPlay();//get the study plan
	GUI* pGUI = pReg->getGUI();//get the gui to send the gpa to be displayed 
	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
	double DummyTotal = 0, DummyTotalDone = 0; //variables that restart 
	GPA_OF_All_Semesters.clear();//omar added this to implement something additional (Display the gpa of each semester )
	pGUI->GPA_Semesters.clear();//omar added this to implement something additional (Display the gpa of each semester )
	
	//looping through the study plan, if the course is done get the grade inside it
	for (AcademicYear* yr : *pPlan)
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			DummyTotal = 0; DummyTotalDone = 0;
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				// Iterate on courses
				Course* pCr = (*it);
				if (pCr->repeatedCourse && pCr->repeatedTimes != 0) continue;
				if (pCr->getCoursedone() == true)
				{
					int credits=pCr->getCredits();
					double dummy = 0;
					if (pCr->getGrade() == "A")
					{
						dummy = A * credits;
					}
					else if (pCr->getGrade() == "A-")
					{
						dummy = A_MINUS * credits;
					}
					else if (pCr->getGrade() == "B+")
					{
						dummy = B_PLUS * credits;
					}
					else if (pCr->getGrade() == "B")
					{
						dummy = B * credits;
					}
					else if (pCr->getGrade() == "B-")
					{
						dummy = B_MINUS * credits;
					}
					else if (pCr->getGrade() == "C+")
					{
						dummy = C_PLUS * credits;
					}
					else if (pCr->getGrade() == "C-")
					{
						dummy = C_MINUS * credits;
					}
					else if (pCr->getGrade() == "C")
					{
						dummy = C * credits;
					}
					else if (pCr->getGrade() == "F")
					{
						dummy = F * credits;
					}
					total = total + dummy;//total grade* the weight 
					totaldonehours = totaldonehours + credits;//increase the total done hours 
					DummyTotal = total;//omar added those to implement an additional feature for the GUI (he wanted to display every semester)
					DummyTotalDone = totaldonehours;//omar added those to implement an additional feature for the GUI (he wanted to display every semester)
				}
		
			}
			//omar added those to implement an additional feature for the GUI (he wanted to display every semester)
			if ((DummyTotal != 0) && (DummyTotalDone != 0))
			{
				string str = to_string(DummyTotal/DummyTotalDone);
				GPA_OF_All_Semesters.push_back(str.substr(0,4));
			}
			else
			{
				GPA_OF_All_Semesters.push_back("0");
			}
		}

	}
	GPA = total / totaldonehours;//to calculate the GPA we divide the toal by the hours 
	GPA = ceil(GPA * 100.0) / 100.0;// this ceil is to round GPA to 2 significant figures
	
	if ((total !=0)&&(totaldonehours!=0))//if the total and total done hours are not zero, pass the GPA value to the GUI
	{
		string str = to_string(GPA); // converts the value to string to represent it 
		pGUI->GPA = str.substr(0, 4);// pass the GPA value to a sting variable called GPA in the GUI
	}

	for(int i=0;i< GPA_OF_All_Semesters.size();i++)
	pGUI->GPA_Semesters.push_back(GPA_OF_All_Semesters[i]);
	return true;
}
double ActionCalculateGPA::getGPA() const
{
	return GPA;
}
ActionCalculateGPA::~ActionCalculateGPA()
{
}
