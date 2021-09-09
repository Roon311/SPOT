#include "ActionCourseInfo.h"
#include "..\Registrar.h"
#include <iostream>
#include"../GUI/GUI.h"
#include"../Utils/Utils.h"
#include<sstream>  
#include <algorithm>


ActionCourseInfo::ActionCourseInfo(Registrar* P) :Action(P)
{
}
bool ActionCourseInfo::Execute()
{

	GUI* pGUI = pReg->getGUI();
	int x, y;
	x = pGUI->getXCoord();
	y = pGUI->getYCoord();
		Course* pCr = pReg->interrogateCourse(x, y);
		if (pCr == nullptr) {
			return false;
		}
		else
		{
			pCr->changeColor(BLACK);
			if ((pReg->OldpCr != nullptr) && (pReg->OldpCr != pCr))
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
			string Title = "Course Title: " + pCr->getTitle();
			string code = "Course Code: " + pCr->getCode();
			int credits = pCr->getCredits();
			stringstream ss;
			ss << credits;
			string String_Credits;
			ss >> String_Credits;
			pGUI->CourseTitle = Title;
			pGUI->CourseCode = code;
			pGUI->CourseCredit = "Course Credits: " + String_Credits;
			pGUI->CourseGrade= "Course Grade: " + pCr->getGrade();
			pGUI->CourseStatus = "Course Status: " + pCr->getStatus();
			//-------------------------------------------------------------------------------------------------------------------//
			//Course Status
			bool cond0 = false;
			if (pReg->OldpCr == pCr)// 2 clicks on the course	//omar edited this part so that the user needs to click 2 times rather than 1 click that was already implemented  
			{
				{
					pGUI->PrintMsg("Input Course Status (Pending/Done/IN Progress/Replaced/Exempted/Credits Transferred)");
					string msg = pGUI->GetSrting();//get string from the ser through the status bar
					//To upper function used to convert the input of the user to uppercase string
					for_each(msg.begin(), msg.end(), [](char& c)
						{
							c = ::toupper(c);
						});
					//------------------------Checks----------------------------------//
					//--------------------------------Course Done---------------------//
					if (msg == "TRUE" || msg == "YES" || msg == "DONE" || msg == "D" || msg == "1")
					{
						pCr->setCoursedone(true);
						pCr->setCoursepending(false);
						pCr->setCourseinprogress(false);
						pCr->setCourseExempted(false);
						pCr->setCourseReplaced(false);
						pCr->setStatus("DN");
						pGUI->CourseGrade = "Course Grade: ";
						cond0 = true;
						//if course is Done,Input its grade
						bool cond = false;
						do
						{
							pGUI->PrintMsg("Input Course Grade");
							string grademsg = pGUI->GetSrting();
							for_each(grademsg.begin(), grademsg.end(), [](char& c)
								{
									c = ::toupper(c);
								});

							/*if (grademsg == "A" || grademsg == "A minus" || grademsg == "A-" || grademsg == "Aminus" || grademsg == "B" || grademsg == "B minus" || grademsg == "B-" || grademsg == "Bminus" || grademsg == "C" || grademsg == "C minus" || grademsg == "C-" || grademsg == "Cminus" || grademsg == "F")
							{
								pGUI->CourseGrade = grademsg;
							}*/
							if (grademsg == "A" || grademsg == "B" || grademsg == "C" || grademsg == "F")
							{
								pGUI->CourseGrade += grademsg;
								pCr->setGrade(grademsg);
								cond = true;
							}
							else if (grademsg == "A MINUS" || grademsg == "A-" || grademsg == "AMINUS")
							{
								grademsg = "A-";
								pGUI->CourseGrade += grademsg;
								pCr->setGrade(grademsg);
								cond = true;
							}
							else if (grademsg == "B MINUS" || grademsg == "B-" || grademsg == "BMINUS")
							{
								grademsg = "B-";
								pGUI->CourseGrade += grademsg;
								pCr->setGrade(grademsg);
								cond = true;
							}
							else if (grademsg == "B PLUS" || grademsg == "B+" || grademsg == "BPLUS")
							{
								grademsg = "B+";
								pGUI->CourseGrade += grademsg;
								pCr->setGrade(grademsg);
								cond = true;
							}
							else if (grademsg == "C PLUS" || grademsg == "C+" || grademsg == "CPLUS")
							{
								grademsg = "C+";
								pGUI->CourseGrade += grademsg;
								pCr->setGrade(grademsg);
								cond = true;
							}
							else if (grademsg == "C MINUS" || grademsg == "C-" || grademsg == "CMINUS")
							{
								grademsg = "C-";
								pGUI->CourseGrade += grademsg;
								pCr->setGrade(grademsg);
								cond = true;
							}
							else
							{
								pGUI->PrintMsg("Wrong grade");
								cond = false;
							}
						} while (cond == false);
					}
					//--------------------------------Course pending---------------------//
					else if (msg == "PENDING" || msg == "P" || msg == "STILL" || msg == "NO" || msg == "PEND")
					{
						pCr->setCoursepending(true);
						pCr->setCoursedone(false);
						pCr->setCourseinprogress(false);
						pCr->setCourseExempted(false);
						pCr->setCourseReplaced(false);
						pCr->setCourseCreditsTransfered(false);
						pCr->setToken(false);
						pCr->setStatus("PN");
						pGUI->CourseGrade += "Null";
						cond0 = true;

					}
					//--------------------------------Course in progress---------------------//
					else if (msg == "I" || msg == "IN" || msg == "IN PROGRESS" || msg == "INPROGRESS")
					{
						pCr->setCoursedone(false);
						pCr->setCoursepending(false);
						pCr->setCourseinprogress(true);
						pCr->setCourseExempted(false);
						pCr->setCourseReplaced(false);
						pCr->setCourseCreditsTransfered(false);
						pCr->setToken(false);
						pCr->setStatus("IN");
						pGUI->CourseGrade += "Null";
						cond0 = true;
					}
					//--------------------------------Course Exempted---------------------//
					else if (msg == "E" || msg == "EXEMPTED" || msg == "EX" || msg == "EXMPTED")
					{
						pCr->setCoursedone(true);
						pCr->setCoursepending(false);
						pCr->setCourseinprogress(false);
						pCr->setCourseExempted(true);
						pCr->setCourseReplaced(false);
						pCr->setCourseCreditsTransfered(false);
						pCr->setStatus("EX");
						pGUI->CourseGrade += "passed";
						cond0 = true;
					}
					//--------------------------------Course Replaced---------------------//
					else if (msg == "R" || msg == "REPLACED" || msg == "REPLACE" || msg == "REP")
					{
						pCr->setCoursedone(true);
						pCr->setCoursepending(false);
						pCr->setCourseinprogress(false);
						pCr->setCourseExempted(false);
						pCr->setCourseReplaced(true);
						pCr->setCourseCreditsTransfered(false);
						pCr->setStatus("RP");
						pGUI->CourseGrade += "---";
						cond0 = true;
					}
					//--------------------------------Course Credits Transferred---------------------//
					else if (msg == "T" || msg == "CREDITS TRANSFERED" || msg == "TRANSFERED" || msg == "CT")
					{
						pCr->setCoursedone(true);
						pCr->setCoursepending(false);
						pCr->setCourseinprogress(false);
						pCr->setCourseExempted(false);
						pCr->setCourseReplaced(false);
						pCr->setCourseCreditsTransfered(true);
						pCr->setStatus("CT");
						pGUI->CourseGrade += "---";
					 }

					else
					{
						/*pGUI->PrintMsg("Wrong input)");*/
					}
				}
			}
			//----------Printing on the GUI-------------//
			if (pCr->getCoursedone() == true)
			{
				pGUI->CourseStatus = "Course Status: Done";

			}
			else if (pCr->getCourseinprogress() == true)
			{
				pGUI->CourseStatus = "Course Status: Inprogress";
			}
			else if (pCr->getCoursepending() == true)
			{
				pGUI->CourseStatus = "Course Status: Pending ";
			}
			else if (pCr->getCourseExempted() == true)
			{
				pGUI->CourseStatus = "Course Status: Exempted (Done) ";
			}
			else if (pCr->getCourseReplaced() == true)
			{
				pGUI->CourseStatus = "Course Status: Replaced (Done) ";
			}
			else if (pCr->getCourseCreditsTransfered() == true)
			{
				pGUI->CourseStatus = "Course Status: CreditsTransfered (Done) ";
			}
			else
			{
				pGUI->CourseStatus ="Course Status: Not Taken ";
			}

		}
		//-----------------Part regarding the clicks--------------//
		if (pReg->OldpCr != pCr)
		pReg->OldpCr = pCr;
		if (pReg->OldpCr == nullptr)
			pReg->OldpCr = pCr;

		pGUI->setCurrent_Page_Info(1);
	return true;
}

ActionCourseInfo::~ActionCourseInfo()
{
}