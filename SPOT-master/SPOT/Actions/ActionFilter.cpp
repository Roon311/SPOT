#include "ActionFilter.h"
#include "..\Registrar.h"
#include <iostream>
#include"../Utils/Utils.h"
#include"../GUI/GUI.h"
#include <algorithm>
#include"../GUI/Drawable.h"
ActionFilter::ActionFilter(Registrar* p) :Action(p)
{
}
ActionFilter::~ActionFilter()
{
}
void ActionFilter::Filteringyear(int inputyear)
{
	//loop over study plan 
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
	for (int i = 0; i < pPlan->size(); i++)//
	{
		AcademicYear* yr = (*pPlan)[i]; // 0 , 1, 2, 3, 4
		if (i == inputyear) continue; //skips inputyear to prevent it from being hidden
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				// Iterate on courses
				Course* pCr = (*it);
				pCr->DrawMe_Flag = false; // draw me flag that was created by omar for the dependencies
			}
		}
	}
}
void ActionFilter::Filteringsemester(int inputsem)
{
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
	for (AcademicYear* yr : *pPlan)//
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int i=0; i< SEM_CNT; i++)
		{
			if (i == inputsem) continue; //skips semester to prevent it from being hidden
			for (auto it = pYr[i].begin(); it != pYr[i].end(); it++)
			{
				// Iterate on courses
				Course* pCr = (*it);
				pCr->DrawMe_Flag = false;
			}
		}
	}
}
//was turned off and another one was made for the type
void ActionFilter::Filteringcolour(color col)
{
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
	for (AcademicYear* yr : *pPlan)//
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int i = 0; i < SEM_CNT; i++)
		{
			for (auto it = pYr[i].begin(); it != pYr[i].end(); it++)
			{
				// Iterate on courses
				Course* pCr = (*it);
				if (pCr->getColor() != col) 
				{
					pCr->DrawMe_Flag = false;
				}
			}
		}
	}
}
//filtering using course type
void ActionFilter::FilteringType(Type type)
{
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
	for (AcademicYear* yr : *pPlan)//
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int i = 0; i < SEM_CNT; i++)
		{
			for (auto it = pYr[i].begin(); it != pYr[i].end(); it++)
			{
				// Iterate on courses
				Course* pCr = (*it);
				if (pCr->getType() != type)// through course pointer, get the course type and compare it the input type 
				{
					pCr->DrawMe_Flag = false;
				}
			}
		}
	}
}
void ActionFilter::FilteringDoneOrNot(bool Input)
{
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
	for (AcademicYear* yr : *pPlan)//
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int i = 0; i < SEM_CNT; i++)
		{
			for (auto it = pYr[i].begin(); it != pYr[i].end(); it++)
			{
				// Iterate on courses
				Course* pCr = (*it);
				if (pCr->getCoursedone() != Input)// through course pointer, get the course type and compare it the input type 
				{
					pCr->DrawMe_Flag = false;
				}
			}
		}
	}
}
//void ActionFilter::FilteringStatus(string s)
//{
//	StudyPlan* plan = pReg->getStudyPlay();
//	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
//	for (AcademicYear* yr : *pPlan)
//	{
//		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
//		for (int i = 0; i < SEM_CNT; i++)
//		{
//			for (auto it = pYr[i].begin(); it != pYr[i].end(); it++)
//			{
//				// Iterate on courses
//				Course* pCr = (*it);
//				
//					pCr->DrawMe_Flag = false;
//				
//			}
//		}
//	}
//}

//returns drawme flag to true, therefore the course would be drawn
void ActionFilter::UNFiltering()
{
	StudyPlan* plan = pReg->getStudyPlay();
	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
	for (int i = 0; i < pPlan->size(); i++)//
	{
		AcademicYear* yr = (*pPlan)[i]; // 0 , 1, 2, 3, 4
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				// Iterate on courses
				Course* pCr = (*it);
				pCr->DrawMe_Flag = true;
			}
		}
	}
}
bool ActionFilter::Execute()
{
	cout << "Filter button is pressed.\n"; // for debugging
	GUI* pGUI = pReg->getGUI();//pointer to GUI
	ActionData actData = pGUI->GetUserAction("Select what you want to filter");
	int x, y;
	int year;
	SEMESTER sem;
	Type type;
	color color= WHITESMOKE;
	double One_Year_Div = pGUI->One_Year_Div;
	double YearImgMidSubtractor = pGUI->YearImgMidSubtractor;
	double MyFactor = pGUI->MyFactor;
	if (actData.actType == DRAW_AREA)
	{
		x = actData.x;
		y = actData.y;
		keytype key;
		char c=NULL;
		key = pGUI->pWind->GetKeyPress(c);
		//filter year
		if (((x >= 1) && (x <= 19)) && (y >= ((1 * One_Year_Div) - YearImgMidSubtractor + (0 * MyFactor))) && (y <= (82 + ((6 * One_Year_Div) - YearImgMidSubtractor + (5 * MyFactor)))))
		{
			if ((y >= (((1 * One_Year_Div) - YearImgMidSubtractor + (0 * MyFactor)))) && (y <= (83 + (((1 * One_Year_Div) - YearImgMidSubtractor + (0 * MyFactor))))))
			{
				year = 1;//now i am holding the year number
				Filteringyear(year - 1);
				pReg->UpdateInterface();

			}
			if ((y >= (((2 * One_Year_Div) - YearImgMidSubtractor + (1 * MyFactor)))) && (y <= (83 + (((2 * One_Year_Div) - YearImgMidSubtractor + (1 * MyFactor))))))
			{
				year = 2;//now i am holding the year number
				Filteringyear(year - 1);
				pReg->UpdateInterface();
			}
			if ((y >= (((3 * One_Year_Div) - YearImgMidSubtractor + (2 * MyFactor)))) && (y <= (83 + (((3 * One_Year_Div) - YearImgMidSubtractor + (2 * MyFactor))))))
			{
				year = 3;//now i am holding the year number
				Filteringyear(year - 1);
				pReg->UpdateInterface();
			}
			if ((y >= (((4 * One_Year_Div) - YearImgMidSubtractor + (3 * MyFactor)))) && (y <= (83 + (((4 * One_Year_Div) - YearImgMidSubtractor + (3 * MyFactor))))))
			{
				year = 4;//now i am holding the year number
				Filteringyear(year - 1);
				pReg->UpdateInterface();
			}
			if ((y >= (((5 * One_Year_Div) - YearImgMidSubtractor + (4 * MyFactor)))) && (y <= (83 + (((5 * One_Year_Div) - YearImgMidSubtractor + (4 * MyFactor))))))
			{
				year = 5;//now i am holding the year number
				Filteringyear(year - 1);
				pReg->UpdateInterface();
			}
			if ((y >= (((6 * One_Year_Div) - YearImgMidSubtractor + (5 * MyFactor)))) && (y <= (83 + (((6 * One_Year_Div) - YearImgMidSubtractor + (5 * MyFactor))))))
			{
				year = 6;//now i am holding the year number
				Filteringyear(year - 1);
				pReg->UpdateInterface();
			}
		}
		//filter Semester
		if(x>=(20)&& x<=(GUI::Year_X1))
		{
		for (int i = 1; i <= GUI::NumOfYrs; i++)
		{
			int yi = (GUI::MenuBarHeight + (i * GUI::MyFactor) + ((i - 1) * GUI::One_Year_Div));
			int yf = (GUI::MenuBarHeight + (i * GUI::MyFactor) + (i * GUI::One_Year_Div));

			if (y > yi && y < yf)
			{
				// Get the semester
				int s1 = yi + GUI::One_Semester_Div;
				int s2 = yf - GUI::One_Semester_Div;

				if (y > yi && y < s1)
				{
					sem = FALL;
					Filteringsemester(sem);
					pReg->UpdateInterface();

				}
				else if (y > s1 && y < s2)
				{
					sem = SPRING;
					Filteringsemester(sem);
					pReg->UpdateInterface();


				}
				else if (y > s2 && y < yf)
				{
					sem = SUMMER;
					Filteringsemester(sem);
					pReg->UpdateInterface();

				}
			}
		}
	}
		//filtering based on colour AKA Filtering Major Track Concentration Minor Extra
		/*if(x>=(GUI::Year_X1)&&x<=(GUI::Year_X2))
			{
				color = pGUI->pWind->GetColor(x, y);
				while (color == WHITESMOKE)
				{
					actData=pGUI->GetUserAction("Select what you want to filter");
					if (actData.actType == DRAW_AREA)
					{
						x = actData.x;
						y = actData.y;
						color = pGUI->pWind->GetColor(x, y);
					}
				}
				Filteringcolour(color);
				pReg->UpdateInterface();

			}*/
		//filtering based on type
		bool Flag=false;
		//filtering based Done or Not
		if (x >= (GUI::Year_X1) && x <= (GUI::Year_X2))
		{
			Course* pCr = pReg->interrogateCourse(x, y);
			if (pCr != nullptr)
			{
				graphicsInfo gInfo = pCr->getGfxInfo();
				if ((x>=gInfo.x + ((2 * CRS_WIDTH) / 3))&&(x <= gInfo.x +CRS_WIDTH)&&(y>= gInfo.y+CRS_HEIGHT/2)&&(y <= gInfo.y + CRS_HEIGHT))
				{
					if (pCr->getCoursedone())
					{
						FilteringDoneOrNot(true);
					}
					else
					{
						FilteringDoneOrNot(false);
					}
				}
				else
				{
					type = pCr->getType();
					FilteringType(type);
				}
			}
			else
				Flag = true;
			pReg->UpdateInterface();
		}
		while ((c==NULL))
			{
				if (Flag == true)
					break;
				char FLAG;
				c = pGUI->pWind->GetKeyPress(FLAG);
			}
		UNFiltering();
	}
	return true;
}