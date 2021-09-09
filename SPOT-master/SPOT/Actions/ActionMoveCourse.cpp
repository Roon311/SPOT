#include "ActionMoveCourse.h"
#include "..\Registrar.h"
#include <iostream>
#include"../GUI/GUI.h"
#include"../Utils/Utils.h"

ActionMoveCourse::ActionMoveCourse(Registrar* p) :Action(p)
{
}

ActionMoveCourse::~ActionMoveCourse()
{
}

bool ActionMoveCourse::Execute() {
	cout << "Move button is pressed.\n"; // for debugging
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Select the course you want to move");
	int x, y;
	if (actData.actType == DRAW_AREA) {
		x = actData.x;
		y = actData.y;
		Course* pCr = pReg->interrogateCourse(x, y);
		if (pCr == nullptr) {
			// No course is sellected
		}
		else {
			StudyPlan* pS = pReg->getStudyPlay();
			ActionData actData = pGUI->GetUserAction("Select the new destination ");

			int oldYear = pCr->getYear();
			int newYear = NULL;
			SEMESTER oldSem = pCr->getSemester();
			SEMESTER newSem;

			graphicsInfo gInfo{ x, y };
			x = actData.x;
			y = actData.y;
			if (x > GUI::VerticalSeparatorX && x < GUI::Year_X2) {
				// The click X is inside the boundaries
				//Get the Year
				for (int i = 1; i <= GUI::NumOfYrs; i++) {
					int yi = (GUI::MenuBarHeight + (i * GUI::MyFactor) + ((i - 1) * GUI::One_Year_Div));
					int yf = (GUI::MenuBarHeight + (i * GUI::MyFactor) + (i * GUI::One_Year_Div));

					if (y > yi && y < yf) {
						newYear = i;
						// Get the semester
						int s1 = yi + GUI::One_Semester_Div;
						int s2 = yf - GUI::One_Semester_Div;

						if (y > yi && y < s1) newSem = FALL;
						else if (y > s1 && y < s2) newSem = SPRING;
						else if (y > s2 && y < yf) newSem = SUMMER;
					}
				}

			}
			else {
				//The user clicked outside the region
			}
			if (newYear != NULL) {
				// Delete crs
				pS->DeleteCourse(pCr);
				int year = pCr->getYear();
				SEMESTER sem = pCr->getSemester();
				vector<AcademicYear*>* pPlan = pS->getStudyPlanVector(); // pointer on the plan vector
				list<Course*>* pYr = (*pPlan)[year - 1]->getListOfYears();
				int new_x = 0;
				int new_y = 0;
				graphicsInfo new_gInfo{ new_x, new_y };

				for (int sem = FALL; sem < SEM_CNT; sem++) {
					int iter = 0;
					for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
						// itertate over all courses
						//int iter = pCr->numOfCoursesPerSem[(3 * (year - 1)) + sem] - 1;
						new_gInfo.x = GUI::TitleBarWidth + (iter * CRS_WIDTH);
						new_gInfo.y = GUI::MenuBarHeight + GUI::MyFactor + ((year - 1) * GUI::One_Year_Div) + (sem * GUI::One_Semester_Div) +
							(GUI::MyFactor * (year - 1));
						(*it)->setGfxInfo(new_gInfo);
						iter++;
					}
				}
				// add it again :)
				pS->AddCourse(pCr, newYear, newSem);
				pCr->numOfCoursesPerSem[(3 * (newYear - 1)) + newSem]++;
				pCr->setYear(newYear);
				pCr->setSemester(newSem);
				int iter = pCr->numOfCoursesPerSem[(3 * (newYear - 1)) + newSem] - 1;
				gInfo.x = GUI::TitleBarWidth + (iter * CRS_WIDTH);
				gInfo.y = GUI::MenuBarHeight + GUI::MyFactor + ((newYear - 1) * GUI::One_Year_Div) + (newSem * GUI::One_Semester_Div) +
					(GUI::MyFactor * (newYear - 1));
				pCr->setGfxInfo(gInfo);
			}
			}
		}
	return true;
}