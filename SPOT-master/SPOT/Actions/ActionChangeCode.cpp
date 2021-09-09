#include "ActionChangeCode.h"
#include "..\Registrar.h"
#include <iostream>
#include"../Utils/Utils.h"
#include"../GUI/GUI.h"
#include <algorithm>
#include"../GUI/Drawable.h"
#include<sstream>

ActionChangeCode::ActionChangeCode(Registrar* p) :Action(p)
{
}
ActionChangeCode::~ActionChangeCode()
{
}
bool ActionChangeCode::Execute()
{
	cout << "change code button is pressed.\n"; // for debugging
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Select the course you would like to change its code  ");
	int x, y;
	if (actData.actType == DRAW_AREA) {
		x = actData.x;
		y = actData.y;
		Course* pCr = pReg->interrogateCourse(x, y);
		if (pCr == nullptr)
		{
			pReg->Not_Worth_Saving_Flag = true;
			// No course is sellected
		}
		else 
		{
			pGUI->PrintMsg("<< Add Course to plan >> Enter new course Code: ");
			Course_Code code = pGUI->GetSrting();
			//Input validations
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
			StudyPlan* pS= pReg->getStudyPlay();
			//if (!pS->alreadyExistingCourse(code)) {
			if(true){
			int year = pCr->getYear();
			SEMESTER sem = pCr->getSemester();
			StudyPlan* pS = pReg->getStudyPlay();
			graphicsInfo Old_ginfo{ x,y };
			Old_ginfo = pCr->getGfxInfo();
			graphicsInfo anew_ginfo{ Old_ginfo.x, Old_ginfo.y };
			pCr->CCC_Flag = true;
			pS->DeleteCourse(pCr);
			//CourseInfo chosenCourseInfo = pReg->getCourseInfo(code);
			string Title = pCInfo->Title;
			int crd = pCInfo->Credits;
			vector<Course_Code> PreReq = pCInfo->PreReqList;
			vector<Course_Code> CoReq = pCInfo->CoReqList;
			Course* pnewcR = new  Course(code, Title, crd, PreReq, CoReq, year, sem);
			pnewcR->CCC_Flag = true;
			pnewcR->setGfxInfo(anew_ginfo);
			pS->AddCourse(pnewcR, year, sem);
			pnewcR->Course_Number = pCr->Course_Number;
			pnewcR->changeColor(BLACK);
			if ((pReg->OldpCr != nullptr) && (pReg->OldpCr != pnewcR))
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
				else {
					pReg->OldpCr->changeColor(MYCYAN);
				}
			}
			pReg->OldpCr = pnewcR;
			pGUI->setCurrent_Page_Info(1);
			string title = "Course Title: " + pnewcR->getTitle();
			string code = "Course Code: " + pnewcR->getCode();
			int credits = pnewcR->getCredits();
			stringstream ss;
			ss << credits;
			string String_Credits;
			ss >> String_Credits;
			pGUI->CourseTitle = title;
			pGUI->CourseCode = code;
			pGUI->CourseCredit = "Course Credits: " + String_Credits;
			pGUI->CourseGrade = "Course Grade: " + pnewcR->getGrade();
			pGUI->CourseStatus = "Course Status: " + pnewcR->getStatus();
			
			}
			else
				pGUI->GetUserAction("This Course already exists!");
		}
	}
	return true;
}
