#include "ActionDeclareMinor.h"
#include "..\Registrar.h"
#include <iostream>
#include"../GUI/GUI.h"
#include"../Utils/Utils.h"
#include<sstream>  
#include <algorithm>


ActionDeclareMinor::ActionDeclareMinor(Registrar* P) :Action(P)
{


}
bool ActionDeclareMinor::Execute()
{

	GUI* pGUI = pReg->getGUI();
	StudyPlan* plan = pReg->getStudyPlay();
	char c;//define a character c 
	keytype key = NO_KEYPRESS;// keytype iss a enum


	//static int count = 0;//count to check the user enters 5 courses start from negative one caue i increment first therefore i could store in poition zero in an array
	static int counter = 0;//to check if the course is present in the plan 
	static int TNOMCTBA = 0;//total number of minor credits to be added
	bool done = false; // this is a temp variable that would work in parallel with the key variable 
	//static string Minor = "No Minor";

	//--------------------------Double Minor Stuff------------------------------------------//
	int token = 0;//this variable is responsible for the window loop
	static int TNODMCTBA = 0;
	static bool answer = false; //to record the user answer
	//counter is onefull
	static bool token3 = false;//to control 2nd minor stuff "eve"
	static int counter2 = 0;//to count for the 2nd minor 
	//-------------------------------SAMPLE-------------------------------------------------//

	//string MinorAlternatives[6] = { "ENV 357","ENV 359","ENV 319","CIE 202","ENV 303","ENV 357" };//sample for testing 
	//bool flag;
	//static string MinorCourses[5] = {};
	//int dummy=0; //for the test sample 

	//we get the key press
	key = pGUI->pWind->GetKeyPress(c);

	//cout << Minor << endl;			//debugging

	//----------------------------------------------------------------------------------//
	// Those counts are in the study plan, they are to trace the number of minor courses added and output specific messages for the 1st minor  
	if (plan->Count == 0)
	{
		pGUI->PrintMsg("Input 5 Minor Courses ");
	}
	else if (plan->Count == 1)
	{
		pGUI->PrintMsg(" 4 Courses to be in a minor ");

	}
	else if (plan->Count == 2)
	{
		pGUI->PrintMsg(" 3 Courses to be in a minor ");
	}
	else if (plan->Count == 3)
	{
		pGUI->PrintMsg(" 2 Courses to be in a minor ");

	}
	else if (plan->Count == 4)
	{
		pGUI->PrintMsg(" 1 Courses to be in a minor ");
		answer = false;

	}
	else if (plan->Count == 5)
	{
		//pGUI->GetUserAction(" Congratulations You are now in a Minor ");
		if (answer != true)//to prevent opening the window if the answer is true--->now we have the following cases to take care of

			//1.The user declared a double minor, then he deleted 1 course of the first minor(This means he is no longer in a minor) is the other minor is complete consider it his minor
			//2.Minor courses will have minor colors only if all minor courses are placed....before that we could color them with a different color (temp color)
			//3.if 2 minors are completly declared and the user deleted course of the 2nd ....the 2nd would be temp color and the first would remain a minor,don't pop the window
			//4.if the user deletes all the 2nd minor courses, answer=false,token3=false
		{
			//if the count reaches 5, pop up a window asking the user wheather he would like to delete the minor or add a double minor
			pMinorWind = new window(MinorWindWidth, MinorWindowHeight, StartX, StartY);
			//pMajorWind->SetBrush(GRAY);
			UpdateWind();
			pMinorWind->ChangeTitle("Minor Declaration");
			//ClearDrawingArea();

			pMinorWind->SetFont(30, ITALICIZED, SCRIPT, "Times New Rome");
			pMinorWind->SetPen(ORANGE);
			pMinorWind->DrawString(35, 20, "Would you like to double minor?");
			pMinorWind->DrawImage("GUI\\Images\\Minor_images\\Yes.jpg", MinorWindWidth * 60 / 500, 0.5 * MinorWindowHeight);
			pMinorWind->DrawImage("GUI\\Images\\Minor_images\\No.jpg", 300, 0.5 * MinorWindowHeight);
			while (token == 0)
			{
				clicktype ctInput;
				int x, y;
				pMinorWind->GetMouseClick(x, y);
				if ((pMinorWind->GetGreen(x, y) == 0.8) && (pMinorWind->GetRed(x, y) == 0.8) && (pMinorWind->GetBlue(x, y) == 0.8))
				{
					answer = false;
					token = 1;
					delete pMinorWind;
					pMinorWind = nullptr;
					return true;

				}
				//cout << x << "This is the  x" << endl;
				//cout << y << "THis is the y" << endl;
				if ((x >= (60)) && (x <= 155) && (y >= 100) && (y <= (127)))
				{
					answer = true;
					token = 1;
					delete pMinorWind;
					pMinorWind = nullptr;
				}
				if ((x >= (300)) && (x <= 395) && (y >= 100) && (y <= (127)))
				{
					answer = false;
					token = 1;
					delete pMinorWind;
					pMinorWind = nullptr;
					return true;

				}

			}

			//to give the ability to have a double minor 
			// i will open a window that pops up 2 buttons
			//1st option would u likee to join a double minor 
			//option 2 delete current minor 

			plan->Minor_Course.at(0);
			//cout << plan->Minor_Course.at(0) << endl; //debugging
			//cout << plan->Minor_Course.at(1) << endl; //debugging
			//cout << plan->Minor_Course.at(2) << endl; //debugging
			//cout << plan->Minor_Course.at(3) << endl; //debugging
			//cout << plan->Minor_Course.at(4) << endl; //debugging
			//cout << "Minor Already Declared"<<endl;//to be changed if we want
			//cout << Minor<<endl; //debugging

		}
	}
	//----------------------------------------------------------------------------------//
	// Those counts are in the study plan, they are to trace the number of minor courses added and output specific messages for the 2nd minor
	//--------------------if 1st minor is full checks on 2nd minor----------------------//
	if ((plan->Count == 5) && (plan->Count2 == 0))
	{
		pGUI->PrintMsg(" 5 Courses to double minor ");
	}
	else if ((plan->Count == 5) && (plan->Count2 == 1))
	{
		pGUI->PrintMsg(" 4 Courses to double minor ");

	}
	else if ((plan->Count == 5) && (plan->Count2 == 2))
	{
		pGUI->PrintMsg(" 3 Courses to double minor ");
	}
	else if ((plan->Count == 5) && (plan->Count2 == 3))
	{
		pGUI->PrintMsg(" 2 Courses to double minor ");

	}
	else if ((plan->Count == 5) && (plan->Count2 == 4))
	{
		pGUI->PrintMsg(" 1 Courses to double minor ");

	}
	else if ((plan->Count == 5) && (plan->Count2 == 5))
	{
		pGUI->GetUserAction("Congratulations, You are Double Minoring ! :) ");
		return true;
	}

	//we get the course code from the user
	string coursecode = pGUI->GetSrting();
	//turn the code from small to capital through to upper function
	for_each(coursecode.begin(), coursecode.end(), [](char& c)
		{
			c = ::toupper(c);
		});

	//----------------------------------------------------------------------------------//
	//From ADD course 
	//Input validations
	if (coursecode == " ")//to exit when the user presses escape
	{
		return true;
	}
	pReg->transformCode(coursecode);

	//Check if exists
	bool exists;
	CourseInfo* pCInfo = pReg->inCatalog(coursecode, exists);
	while (exists == 0)
	{
		pGUI->PrintMsg("ERROR: " + coursecode + " is an invalid course code! Enter a valid one:");
		coursecode = pGUI->GetSrting();
		if (coursecode == " ")//to exit when the user presses escape
			return true;
		pReg->transformCode(coursecode);
		pCInfo = pReg->inCatalog(coursecode, exists);

	}

	//----------------------------------------------------------------------------------//

	//check that the course doesn't exist in the array
	if(plan->Count<5)
	for (int j = 0; j < plan->Minor_Course.size(); j++)//looping through the vector 
	{
		if (plan->Minor_Course.at(j) == coursecode)//if the course code entered is already found in the vector 
		{
			pGUI->GetUserAction("Course Already entered as a Minor Course");
			return true;
		}
	}

	if ((plan->Count ==5)&&(plan->Count2<5))
		for (int j = 0; j < plan->Double_Minor_Course.size(); j++)//looping through the vector 
		{
			if (plan->Double_Minor_Course.at(j) == coursecode)//if the course code entered is already found in the vector 
			{
				pGUI->GetUserAction("Course Already entered as a Double Minor Course");
				return true;
			}
		}
	//----------------------------------------------------------------------------------//


	//----------------------------------------------------------------------------------//

	//if the course exists we loop through all thecourses in the studyplan

	vector<AcademicYear*>* pPlan = plan->getStudyPlanVector(); // pointer on the plan vector
	//check if the course is already present in the study plan;
	for (AcademicYear* yr : *pPlan)
	{
		/*if (plan->Count < 5)
		{
			if (counter > 1)
			{
				pGUI->GetUserAction("You can't have more than 1 common course in the minor");
				cout << "You can't have more than 1 common course in the minor" << endl;
				return true;
				break;


			}
		}
		else if ((plan->Count== 5)&&(plan->Count2<5))
		{
			if (counter2 > 1)
			{
				pGUI->GetUserAction("You can't have more than 1 common course in the minor");
				cout << "You can't have more than 1 common course in the minor" << endl;
				break;

			}
		}*/
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int i = 0; i < SEM_CNT; i++)
		{
			for (auto it = pYr[i].begin(); it != pYr[i].end(); it++)
			{
				// Iterate on courses
				Course* pCr = (*it);
				//if code was found in the studyplan
				if (coursecode == pCr->getCode())
				{
					//increment the static counter by 1

					//if statement to know which counter to increment 
					if (plan->Count < 5)
					{
						counter = counter + 1;
						pCr->Set_Type(Minor);
					}
					//case for counter2
					else if ((plan->Count == 5) && (plan->Count2 < 5))
					{
						counter2++;
						pCr->Set_Type(DoubleMinor);
					}

					//check before adding the course
					if (plan->Count < 5)
					{
						if (counter > 1)
						{
							pGUI->GetUserAction("You can't have more than 1 common course in the minor");
							return true;
							break;


						}
					}
					else if ((plan->Count == 5) && (plan->Count2 < 5))
					{
						if (counter2 > 1)
						{
							pGUI->GetUserAction("You can't have more than 1 common course in the minor");
							return true;
							break;

						}
					}
					if (plan->Count < 5)
					{
						if (counter <= 1)
						{
							plan->Count = plan->Count + 1;
							//if counter not greater than 1//
							//add 2 if conditions if count <5 or if count2<5 and count =5//

							//add a case for the double minor here "Count2"
						}
					}
					else if ((plan->Count == 5) && (plan->Count2 < 5))
					{
						if (counter2 <= 1)
						{
							plan->Count2 = plan->Count2 + 1;
							//if counter2 not greater than 1//
							//add 2 if conditions if count <5 or if count2<5 and count =5//

						}

						
					
					}
					//flag = false;
					return true;//--------------->might me a bug 
				}
			}
		}
	}
	//----------------------------------------------------------------------------------//
	/*if (counter <= 1)
	{*/

	//------------------------------ADD COURSE------------------------------------------//

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
		if (x > GUI::VerticalSeparatorX && x < GUI::Year_X2)
		{
			// The click X is inside the boundaries

			//Get the Year
			for (int i = 1; i <= GUI::NumOfYrs; i++)
			{
				int yi = (GUI::MenuBarHeight + (i * GUI::MyFactor) + ((i - 1) * GUI::One_Year_Div));
				int yf = (GUI::MenuBarHeight + (i * GUI::MyFactor) + (i * GUI::One_Year_Div));

				if (y > yi && y < yf)
				{
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
		else
		{
			//The user clicked outside the region
		}
		//add the course
		if (year != NULL && pCInfo != nullptr)
		{
			StudyPlan* pS = pReg->getStudyPlay();
			string Title = pCInfo->Title;
			int crd = pCInfo->Credits;
			vector<Course_Code> PreReq = pCInfo->PreReqList;
			vector<Course_Code> CoReq = pCInfo->CoReqList;
			Course* pC = new Course(coursecode, Title, crd, PreReq, CoReq, year, semester);
			//------------------------------------------------------------------------------------------------------------------------//
			if (plan->Count < 5)
			{
				plan->setMinor_course_flag(true);
			}
			else if ((plan->Count == 5) && (plan->Count2 < 5))
			{
				plan->setDouble_Minor_course_flag(true);
			}
//-----------------------------------------------------------------------------------------------------------------------------------//
			if (plan->Count < 5) TNOMCTBA += pCInfo->Credits;//calculate minor credits to be added
			//Debugging
			//cout << "This is the total 1st minor credits" << TNOMCTBA << endl;
			if ((plan->Count == 5) && (plan->Count2)) TNODMCTBA += pCInfo->Credits;//calculate Double minor credits to be added
			//Debugging
			//cout << "This is the total 2nd minor credits" << TNODMCTBA << endl;
			//-----------------------------------------------------------------------------------------------------------------------//
			//if(plan->Count<5) plan->Minor_Course.push_back(coursecode);
			//if ((plan->Count == 5) && (plan->Count2))plan->Double_Minor_Course.push_back(coursecode);
			pS->AddCourse(pC, year, static_cast<SEMESTER>(semester));
			pReg->Increment_Total_Credits(pC->getCredits());
			//cout << coursecode << " is added to year " << year << " semester " << semester << endl;
			pC->setYear(year);
			pC->setSemester(semester);
			pC->setUnknownCrs(false);
			int iter = pC->numOfCoursesPerSem[(3 * (year - 1)) + semester] - 1;
			gInfo.x = GUI::TitleBarWidth + (iter * CRS_WIDTH);
			gInfo.y = GUI::MenuBarHeight + GUI::MyFactor + ((year - 1) * GUI::One_Year_Div) + (semester * GUI::One_Semester_Div) +
				(GUI::MyFactor * (year - 1));
			pC->setGfxInfo(gInfo);
			if (plan->Count < 5)
			{
				plan->Count = plan->Count + 1;// increment the course count by 1
			}
			else if ((plan->Count == 5) && (plan->Count2 < 5))
			{
				plan->Count2 = plan->Count2 + 1;
			}
			done = true;
			pReg->UpdateInterface();


		}
	}
	//----------------------------------------------------------------------------------//
	//---------------------------IF USER PRESSES ESCAPE--------------------------------------//
	// to escape if no course is entered	
	while (key != 4 && done == false)
	{
		key = pGUI->pWind->GetKeyPress(c);
	}	
//	plan->Minor_Course.push_back(coursecode);
	return true;
}

//destructor 
ActionDeclareMinor::~ActionDeclareMinor()
{

}

// window stuff
void ActionDeclareMinor::UpdateWind() const
{
	pMinorWind->SetBuffering(1);
	ClearDrawingArea();
	pMinorWind->UpdateBuffer();
	pMinorWind->SetBuffering(0);
}

void ActionDeclareMinor::ClearDrawingArea() const
{
	pMinorWind->SetBrush(BackgroundColor);
	//pMajorWind->SetPen(BackgroundColor);
	pMinorWind->DrawRectangle(0, 0, MinorWindWidth, MinorWindowHeight, FILLED);
}