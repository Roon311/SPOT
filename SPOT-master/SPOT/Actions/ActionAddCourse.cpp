#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include <algorithm>
#include <iostream>
#include"../Utils/Utils.h"
#include"../GUI/GUI.h"
#include<iterator>
#include<sstream>  

ActionAddCourse::ActionAddCourse(Registrar* p):Action(p)
{
}

bool ActionAddCourse::Execute()
{
	cout << "Add button is pressed.\n"; // for debugging

	GUI* pGUI = pReg->getGUI();	

	// 1) Get Course Code
	pGUI->PrintMsg("<< Add Course to plan >> Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();

	//Input validations
	if (code == " ")//to exit when the user presses escape
	{
		pReg->Not_Worth_Saving_Flag = true;
		return true;
	}
	pReg->transformCode(code);

	//Check if exists
	bool exists;
	CourseInfo* pCInfo = pReg->inCatalog(code, exists);
	while (exists == 0) {
		pGUI->PrintMsg("ERROR: " + code + " is an invalid course code! Enter a valid one:");
		code = pGUI->GetSrting();
		if (code == " ")//to exit when the user presses escape
			return true;
		pReg->transformCode(code);
		pCInfo = pReg->inCatalog(code, exists);
	}
	
	ActionData actData = pGUI->GetUserAction("Select where you want to add your course"); 
	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		int year = NULL;
		SEMESTER semester = FALL;

		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		
		graphicsInfo gInfo{ x, y };
		if (x > GUI::VerticalSeparatorX && x < GUI::Year_X2) {
			// The click X is inside the boundaries
			
			//Get the Year
			for (int i = 1; i <= GUI::NumOfYrs; i++) {
				int yi = (GUI::MenuBarHeight + (i * GUI::MyFactor) + ((i - 1) * GUI::One_Year_Div));
				int yf = (GUI::MenuBarHeight + (i * GUI::MyFactor) + (i * GUI::One_Year_Div));

				if (y > yi && y < yf) {
					year = i;
					// Get the semester
					int s1 = yi + GUI::One_Semester_Div;
					int s2 = yf - GUI::One_Semester_Div;
					
					if (y > yi && y < s1) semester = FALL;
					else if (y > s1 && y < s2) semester = SPRING;
					else if (y > s2 && y < yf) semester = SUMMER;
				}
			}

		}
		else {
			//The user clicked outside the region
		}
		if (year != NULL && pCInfo != nullptr) {
			StudyPlan* pS = pReg->getStudyPlay();
			string Title = pCInfo->Title;
			int crd = pCInfo->Credits;
			vector<Course_Code> PreReq = pCInfo->PreReqList;
			vector<Course_Code> CoReq = pCInfo->CoReqList;
			Course* pC = new Course(code, Title, crd, PreReq, CoReq, year, semester);
			pC->Set_Type(pCInfo->type);
			bool check = pS->AddCourse(pC, year, static_cast<SEMESTER>(semester));
			if (check) {
				cout << code << " is added to year " << year << " semester " << semester << endl;
				pC->setYear(year);
				pC->setSemester(semester);
				pC->setUnknownCrs(false);
				int iter = pC->numOfCoursesPerSem[(3 * (year - 1)) + semester] - 1;
				gInfo.x = GUI::TitleBarWidth + (iter * CRS_WIDTH);
				gInfo.y = GUI::MenuBarHeight + GUI::MyFactor + ((year - 1) * GUI::One_Year_Div) + (semester * GUI::One_Semester_Div) +
					(GUI::MyFactor * (year - 1));
				pC->setGfxInfo(gInfo);
				pC->changeColor(BLACK);
				if ((pReg->OldpCr != nullptr) && (pReg->OldpCr != pC))
				{
					if (pReg->OldpCr->getType() == maj)
					{
						pReg->OldpCr->changeColor(GOLDENROD);
					}
					else if (pReg->OldpCr->getType() == Uni)
					{
						pReg->OldpCr->changeColor(SLATEGREY);
					}
					else if (pReg->OldpCr->getType() == Track)
					{
						pReg->OldpCr->changeColor(DARKGREEN);
					}
					else if (pReg->OldpCr->getType() == Elective)
					{
						pReg->OldpCr->changeColor(FIREBRICK);
					}
					else if (pReg->OldpCr->getType() == concentration)
					{
						pReg->OldpCr->changeColor(DARKMAGENTA);
					}
					else
					{
						pReg->OldpCr->changeColor(MYCYAN);
					}
				}
				pReg->OldpCr = pC;
				pGUI->setCurrent_Page_Info(1);
				string title = "Course Title: " + pC->getTitle();
				string code = "Course Code: " + pC->getCode();
				int credits = pC->getCredits();
				stringstream ss;
				ss << credits;
				string String_Credits;
				ss >> String_Credits;
				pGUI->CourseTitle = title;
				pGUI->CourseCode = code;
				pGUI->CourseCredit = "Course Credits: " + String_Credits;
				pGUI->CourseGrade = "Course Grade: " + pC->getGrade();
				pGUI->CourseStatus = "Course Status: " + pC->getStatus();
			}
			else {

				pGUI->GetUserAction("This Course already exists!");
			}
		}
	}
	return true;
}


ActionAddCourse::~ActionAddCourse()
{
}

