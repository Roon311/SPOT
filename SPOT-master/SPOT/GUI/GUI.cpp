#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>
#include <iostream>
#include"../Registrar.h"
using namespace std;
vector<window*> GUI::LOFWIND = {};
GUI::GUI()
{ 
	for (int i = 0; i < 15; i++)
	{
		CPIES.push_back(0);
	}
	pWind = new window(WindWidth, WindHeight,wx,wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}
//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight -StatusBarHeight);

}
void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}
void GUI::ClearReportArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(SideBarX1, ReportAreaY1+27, SideBarX2, ReportAreaY1 + ReportAreaHeight);
	pWind->SetPen(BLACK);
	pWind->DrawRectangle(SideBarX1, ReportAreaY1, SideBarX2, ReportAreaY1 + ReportAreaHeight, FRAME);
}
void GUI::ClearNotesArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(SideBarX1, NotesY1 + 27, SideBarX2, NotesY1 + NotesHeight);
	pWind->SetPen(BLACK);
	pWind->DrawRectangle(SideBarX1, NotesY1, SideBarX2, NotesY1 + NotesHeight, FRAME);
}
void GUI::ClearInfoArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(SideBarX1, CourseInfoY1 + 27, SideBarX2, CourseInfoY1 + NotesHeight);
	pWind->SetPen(BLACK);
	pWind->DrawRectangle(SideBarX1, CourseInfoY1, SideBarX2, CourseInfoY1 + CourseInfoHeight, FRAME);
}
void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);

	//You can draw the menu icons any way you want.

	//First prepare List of images paths for menu item
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\menu_add.jpg";
	MenuItemImages[ITM_DELETE] = "GUI\\Images\\Menu\\menu_delete.jpg";
	if ((Current_StudyPlan > 0) && (Current_StudyPlan < Total_Number_Study_Plans))
	{
		MenuItemImages[ITM_UNDO] = "GUI\\Images\\Menu\\menu_undo.jpg";
		MenuItemImages[ITM_REDO] = "GUI\\Images\\Menu\\menu_redo.jpg";
	}
	else if ((Current_StudyPlan == 0) && (1<Total_Number_Study_Plans))
	{
		MenuItemImages[ITM_UNDO] = "GUI\\Images\\Menu\\menu_undo_gray.jpg";
		MenuItemImages[ITM_REDO] = "GUI\\Images\\Menu\\menu_redo.jpg";
	}
	else
	{
		MenuItemImages[ITM_UNDO] = "GUI\\Images\\Menu\\menu_undo_gray.jpg";
		MenuItemImages[ITM_REDO] = "GUI\\Images\\Menu\\menu_redo_gray.jpg";
	}
	if ((Current_StudyPlan == Total_Number_Study_Plans-1)&&(Current_StudyPlan!=0))
	{
		MenuItemImages[ITM_UNDO] = "GUI\\Images\\Menu\\menu_undo.jpg";
		MenuItemImages[ITM_REDO] = "GUI\\Images\\Menu\\menu_redo_gray.jpg";
	}
	MenuItemImages[ITM_SAVE] = "GUI\\Images\\Menu\\menu_save.jpg";
	MenuItemImages[ITM_IMPORT] = "GUI\\Images\\Menu\\menu_import.jpg";
	MenuItemImages[ITM_EXCHANGE] = "GUI\\Images\\Menu\\menu_exchange.jpg";
	/*MenuItemImages[ITM_Note] = "GUI\\Images\\Menu\\menu_notes.jpg";*/
	MenuItemImages[ITM_ERASE] = "GUI\\Images\\Menu\\menu_erase.jpg";
	MenuItemImages[ITM_MAJOR] = "GUI\\Images\\Menu\\menu_major.jpg";
	MenuItemImages[ITM_MINOR] = "GUI\\Images\\Menu\\MinorDecleration.jpg";
	MenuItemImages[ITM_CRS_DEP] = "GUI\\Images\\Menu\\menu_crs_dep.jpg";
	MenuItemImages[ITM_PLAN_DEP] = "GUI\\Images\\Menu\\menu_plan_dep.jpg";
	MenuItemImages[ITM_Filter] = "GUI\\Images\\Menu\\menu_filter.jpg";
	MenuItemImages[ITM_GPA]= "GUI\\Images\\Menu\\menu_gpa.jpg";
	MenuItemImages[ITM_EXIT]= "GUI\\Images\\Menu\\menu_quit.jpg";


	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i < ITM_CNT; i++) {
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth +(MenuItemWidthGap*i), 0, MenuItemWidth, MenuBarHeight);
	}
}
////////////////////////    Output functions    ///////////////////
//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	pWind->ChangeTitle("Study-Plan Organizational Tool (SPOT) NO "+ to_string(SpotNumber));
	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	ClearReportArea();
	ClearNotesArea();
	ClearInfoArea();
	DrawNoteArea(); 
	DrawInfoArea();
	DrawReportArea();
	DrawInfoPages();
	pWind->DrawRectangle(60,MenuBarHeight+5,SideBarX1-9,WindHeight-StatusBarHeight-4,FRAME);
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}
//////////////////////////////Drawing functions//////////////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	pWind->SetBrush(pCrs->getColor());
	graphicsInfo gInfo = pCrs->getGfxInfo();
	pWind->SetPen(pCrs->getBorderColor(), 1);
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 1);
	else
	{
		pWind->SetPen(pCrs->getBorderColor(), 1);
		if (pCrs->getType() == Elective)
		{
			pWind->SetBrush(BLUEVIOLET);
			pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT, FILLED, 10, 10);
		}
		else if ((pCrs->getType() == NOTYPE) && ((pCrs->getColor() != RED)) && (!pCrs->isUnknown()))
		{
			pWind->SetBrush(MYCYAN);
			pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
		}
		else if ((pCrs->getType() == NOTYPE) && (pCrs->isUnknown()) && !(pCrs->getColor() == BLACK))
		{
			pWind->SetBrush(RED);
			pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
		}
		else
			pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	}

	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);
	pWind->DrawLine(gInfo.x+ (CRS_WIDTH/3)+10, gInfo.y + CRS_HEIGHT / 2, gInfo.x + (CRS_WIDTH / 3) + 10, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x+ ((2*CRS_WIDTH)/ 3)+5, gInfo.y + CRS_HEIGHT / 2, gInfo.x + ((2 * CRS_WIDTH) / 3) + 5, gInfo.y + CRS_HEIGHT);
	//Write the course code and credit hours.
	int Code_y = gInfo.y + (CRS_HEIGHT * 0.05)+ 2;
	int Code_x = gInfo.x + (CRS_WIDTH * 0.15) - 7;
	if (size(pCrs->getCode()) < 10)
	{
		pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	}
	else
	{
		pWind->SetFont(CRS_HEIGHT * 0.4-2 , BOLD, BY_NAME, "Gramound");
	}
	pWind->SetPen(CourseCodeColor);

	ostringstream crd;
	crd<< "C:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(gInfo.x + (CRS_WIDTH / 3) + 17, Code_y + CRS_HEIGHT / 2, pCrs->getGrade());
	pWind->DrawString(gInfo.x + ((2 * CRS_WIDTH) / 3) + 8, Code_y + CRS_HEIGHT / 2, pCrs->getStatus());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT/2, crd.str());
}
void GUI::DrawCourse(const Course* pCrs, int x, int y)
{
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 1);
	else
		pWind->SetPen(pCrs->getBorderColor(), 1);
	pWind->SetBrush(pCrs->getColor());
	graphicsInfo gInfo = pCrs->getGfxInfo();
	pWind->DrawRectangle(x, y,x + CRS_WIDTH, y + CRS_HEIGHT);
	pWind->DrawLine(x, y + CRS_HEIGHT / 2, x + CRS_WIDTH, y + CRS_HEIGHT / 2);

	//Write the course code and credit hours.
	int Code_x = x + CRS_WIDTH * 0.15;
	int Code_y = y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(CourseCodeColor);

	ostringstream crd;
	crd << "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());
}
void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	graphicsInfo gInfo = pY->getGfxInfo();

	//Draw All years Rectangles
	pWind->SetBrush(WHITE);
	pWind->SetPen(BLACK);

	//pWind->DrawRectangle(Year_X1,pY->StartingY + (pY->i * pY->YearHeight) + MyFactor, 	Year_X2, (pY->StartingY + (pY->i * pY->YearHeight)) + pY->YearHeight, FRAME);

	//Titles bar
	pWind->DrawRectangle(0, MenuBarHeight + MyFactor, TitleBarWidth, TitleBarY2);

	// Separators
	pWind->SetPen(BLACK, 9);
	for (int i = 1; i <= NumOfYrs-1; i++)
		pWind->DrawLine(0, //x1
			MenuBarHeight + (i * (Y_div/ NumOfYrs)), //y1
			Year_X2 - MyFactor, //x2
			MenuBarHeight + (i * (Y_div / NumOfYrs))); //y2
	pWind->SetPen(BLACK);

	// Vertical Separator
	pWind->DrawLine(VerticalSeparatorX, MenuBarHeight + MyFactor, VerticalSeparatorX, 
		MenuBarHeight + Y_div - MyFactor);

	//Semester Separations
	for (int i = 1; i <= NumOfYrs ; i++) {
		pWind->DrawLine(VerticalSeparatorX,
			MenuBarHeight + ((i - 1) * (One_Year_Div+MyFactor)) + (1 * One_Semester_Div),
			Year_X2,
			MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + (1 * One_Semester_Div));
		pWind->DrawLine(VerticalSeparatorX,
			MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + (2 * One_Semester_Div) + MyFactor,
			Year_X2,
			MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + (2 * One_Semester_Div) + MyFactor
		);
	}

	//Draw years (Until Finding a Way to be implemented dynamically)
	pWind->DrawImage("GUI\\Images\\Years\\Year_One.jpg",
		1, (1 * One_Year_Div) - YearImgMidSubtractor + (0 * MyFactor), 18, 50);
	pWind->DrawImage("GUI\\Images\\Years\\Year_Two.jpg",
		1, (2 * One_Year_Div) - YearImgMidSubtractor + (1 * MyFactor), 18, 50);
	pWind->DrawImage("GUI\\Images\\Years\\Year_Three.jpg",
		1, (3 * One_Year_Div) - YearImgMidSubtractor + (2 * MyFactor), 18, 50);
	pWind->DrawImage("GUI\\Images\\Years\\Year_Four.jpg",
		1, (4 * One_Year_Div) - YearImgMidSubtractor + (3 * MyFactor), 18, 50);
	pWind->DrawImage("GUI\\Images\\Years\\Year_Five.jpg",
		1, (5 * One_Year_Div) - YearImgMidSubtractor + (4 * MyFactor), 18, 50);
	if (NumOfYrs > 5) {
		pWind->DrawImage("GUI\\Images\\Years\\Year_Six.jpg",
			1, (6 * One_Year_Div) - YearImgMidSubtractor + (5 * MyFactor), 18, 50);
	}
	
	// Draw Semesters 
	pWind->SetFont(15, BOLD, BY_NAME, "Times New Rome");
	pWind->SetPen(BLACK);
	int counter = 0;
	for (int i = 1; i <= NumOfYrs; i++) {
		pWind->DrawString(29,MenuBarHeight+((i - 1)*(One_Year_Div + MyFactor))+SemesterMidFactor,"Fall");
		if (((NOCPSIAYs[counter] > 8) && (CPIES[counter] == 0)))
		{
			pWind->DrawImage("GUI\\Images\\Years\\RA.jpg", SideBarX1 - 37, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor - 10);
		}
		else if (((NOCPSIAYs[counter] > 8) && (CPIES[counter] == 1)))
		{
			pWind->DrawImage("GUI\\Images\\Years\\LA.jpg", SideBarX1 - 37, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor - 10);
		}
		counter++;
		pWind->DrawString(20,MenuBarHeight+((i - 1)*(One_Year_Div + MyFactor))+SemesterMidFactor+(1 * One_Semester_Div),"Spring");
		if (((NOCPSIAYs[counter] > 8) && (CPIES[counter] == 0)))
		{
			pWind->DrawImage("GUI\\Images\\Years\\RA.jpg", SideBarX1 - 37, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (1 * One_Semester_Div) - 10);
		}
		else if (((NOCPSIAYs[counter] > 8) && (CPIES[counter] == 1)))
		{
			pWind->DrawImage("GUI\\Images\\Years\\LA.jpg", SideBarX1 - 37, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (1 * One_Semester_Div) - 10);
		}
		counter++;
		pWind->DrawString(20,MenuBarHeight+((i - 1)*(One_Year_Div + MyFactor))+SemesterMidFactor+(2 * One_Semester_Div),"Summ");
		if (((NOCPSIAYs[counter] > 8) && (CPIES[counter] == 0)))
		{
			pWind->DrawImage("GUI\\Images\\Years\\RA.jpg", SideBarX1 - 37, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (2 * One_Semester_Div) - 10);
		}
		else if (((NOCPSIAYs[counter] > 8) && (CPIES[counter] == 1)))
		{
			pWind->DrawImage("GUI\\Images\\Years\\LA.jpg", SideBarX1 - 37, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (2 * One_Semester_Div) -10);
		}
		counter++;
	}
	counter = 0;
	pWind->SetFont(12, BOLD, BY_NAME, "Times New Rome");
	if(!CrsPerSemester.empty())
	for (int i = 1; i <= NumOfYrs; i++) 
	{
		pWind->DrawString(22, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor - MyFactor * 4, "("+to_string(CrsPerSemester[counter])+")Crs");
		counter++;
		pWind->DrawString(22, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (1 * One_Semester_Div) - MyFactor * 4, "(" + to_string(CrsPerSemester[counter]) + ")Crs");
		counter++;
		pWind->DrawString(22, MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (2 * One_Semester_Div)-MyFactor*4, "(" + to_string(CrsPerSemester[counter]) + ")Crs");
		counter++;
	}
}
////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg)
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;


	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	PrintMsg(msg);
		int X, Y;

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);
		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}
		if (ktInput == ASCII)
		{
			if (cKeyData == 97)
				return ActionData{ ADD_CRS };
			else if (cKeyData == 100)
				return ActionData{ DEL_CRS };
			else if (cKeyData == 109)
				return ActionData{ DECLARE_MINOR };
			else if (cKeyData == 106)
				return ActionData{ DECLARE_MAJOR };
			else if (cKeyData == 99)
				return ActionData{ CHANGE_CODE };
			else if (cKeyData == 115)
				return ActionData{ SAVE };
			else if (cKeyData == 105)
				return ActionData{ IMPORT_PLAN };
			else if (cKeyData == 101)
				return ActionData{ ERASE };
			else if (cKeyData == 103)
				return ActionData{ CAL_GPA };
			else if (cKeyData == 102)
				return ActionData{ Filter };
			else if (cKeyData == 122)
				return ActionData{ UNDO };
			else if (cKeyData == 120)
				return ActionData{ REDO };

		}
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar

			if (y >= 0 && y < MenuBarHeight)
			{
				XCoord = x; YCoord = y;
				Last_CLick = ctInput;
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / (MenuItemWidth + MenuItemWidthGap));
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	break;//Add course
				case ITM_DELETE: return ActionData{ DEL_CRS }; break; //Delete course
				case ITM_SAVE: return ActionData{ SAVE }; break; //Save Plan
				//case ITM_Note: return ActionData{ ADD_Note }; break; //Add Notes
				case ITM_IMPORT: return ActionData{ IMPORT_PLAN }; break; //Import Plan
				case ITM_ERASE: return ActionData{ ERASE }; break;
				case ITM_EXCHANGE: return ActionData{ CHANGE_CODE }; break;
				case ITM_MAJOR: return ActionData{ DECLARE_MAJOR }; break;
				case ITM_MINOR: return ActionData{ DECLARE_MINOR }; break;
				case ITM_EXIT: return ActionData{ Exit }; break;
				case ITM_GPA:return ActionData{ CAL_GPA }; break;

					if (Current_StudyPlan < Total_Number_Study_Plans - 1)
					{
				case ITM_REDO:return ActionData{ REDO }; break;
					}
					if (Current_StudyPlan != 0)
					{
				case ITM_UNDO:return ActionData{ UNDO }; break;
					}
				case ITM_Filter:return ActionData{ Filter }; break;
				case ITM_CRS_DEP:
				{
					if ((Draw_Dependacies_For_One_Course == false) && (Draw_Dependacies_For_One_Course_Flag == false))
					{
						Draw_Dependacies_For_One_Course = false;
						return ActionData{ CRS_DEP }; break;
					}
					else if ((Draw_Dependacies_For_One_Course == true) && (Draw_Dependacies_For_One_Course_Flag == false))
					{
						Draw_Dependacies_For_One_Course_Flag = true;
						return ActionData{ CRS_DEP }; break;
					}
				}
				case ITM_PLAN_DEP:
				{
					if (Draw_Dependacies_Flag == true)
						Draw_Dependacies_Flag = false;
					else
						Draw_Dependacies_Flag = true;
					return ActionData{ PLAN_DEP }; break;
				}

				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				XCoord = x; YCoord = y;
				Last_CLick = ctInput;
				if ((x >= (SideBarX1 + 2)) && (x <= (SideBarX1 + 24)) && (y >= (ReportAreaY1 + 2)) && (y <= (ReportAreaY1 + 24)))
				{
					if ((Current_Page_Report <= Total_Number_Pages_In_Report) && (Current_Page_Report != 0))
					{
						Current_Page_Report--;
					}
				}
				else if ((x >= (SideBarX2 - 24)) && (x <= (SideBarX2 - 2)) && (y >= ReportAreaY1 + 2) && (y <= ReportAreaY1 + 24))
				{
					if (Current_Page_Report < Total_Number_Pages_In_Report)
					{
						Current_Page_Report++;
					}
				}

				if ((x >= (SideBarX1 + 2)) && (x <= (SideBarX1 + 24)) && (y >= (NotesY1 + 2)) && (y <= (NotesY1 + 24)))
				{
					if ((Current_Page_Notes <= Total_Number_Pages_In_Notes) && (Current_Page_Notes != 0))
					{
						Current_Page_Notes--;
					}
				}
				else if ((x >= (SideBarX2 - 24)) && (x <= (SideBarX2 - 2)) && (y >= NotesY1 + 2) && (y <= NotesY1 + 24))
				{
					if (Current_Page_Notes < Total_Number_Pages_In_Notes)
					{
						Current_Page_Notes++;
					}
				}
				if ((x >= (SideBarX1)) && (x <= (SideBarX2)) && (y >= (NotesY1 + 30)) && (y <= (NotesY1 + NotesHeight - 10)))
				{
					return ActionData{ ADD_Note };
				}
				if ((x >= (SideBarX1 + 2)) && (x <= (SideBarX1 + 24)) && (y >= (CourseInfoY1 + 2)) && (y <= (CourseInfoY1 + 24)))
				{
					if ((Current_Page_Info <= Total_Number_Pages_In_Info) && (Current_Page_Info != 0))
					{
						Current_Page_Info--;
					}
				}
				else if ((x >= (SideBarX2 - 24)) && (x <= (SideBarX2 - 2)) && (y >= CourseInfoY1 + 2) && (y <= CourseInfoY1 + 24))
				{
					if ((Current_Page_Info < Total_Number_Pages_In_Info) && (Current_Page_Info != Total_Number_Pages_In_Info))
					{
						Current_Page_Info++;
					}
				}
				if (Current_Page_Info == 0)
				{
					if ((x >= (InfoX1 + 5)) && (x <= (SideBarX2 - 20)) && (y >= InfoY1 - 10) && (y <= InfoY1 + 5))
					{
						Current_Page_Info = 1;
					}
					else if ((x >= (InfoX1 + 5)) && (x <= (SideBarX2 - 20)) && (y >= InfoY1 - 20 + (Y_div / 24) * 2) && (y <= InfoY1 - 5 + (Y_div / 24) * 2))
					{
						Current_Page_Info = 2;
					}
					else if ((x >= (InfoX1 + 5)) && (x <= (SideBarX2 - 20)) && (y >= InfoY1 - 20 + (Y_div / 21) * 3) && (y <= InfoY1 - 5 + (Y_div / 21) * 3))
					{
						Current_Page_Info = 3;
					}
					else if ((x >= (InfoX1 + 5)) && (x <= (SideBarX2 - 20)) && (y >= InfoY1 - 20 + (Y_div / 15.5) * 3) && (y <= InfoY1 - 5 + (Y_div / 15.5) * 3))
					{
						Current_Page_Info = 4;
					}
					else if ((x >= (InfoX1 + 5)) && (x <= (SideBarX2 - 20)) && (y >= InfoY1 - 20 + (Y_div / 12) * 3) && (y <= InfoY1 - 5 + (Y_div / 12) * 3))
					{
						Current_Page_Info = 5;
					}
				}
				int counter = 0;
				for (int i = 1; i <= NumOfYrs; i++) {
					if ((x >= SideBarX1 - 37) && (x <= SideBarX1 - 11) && (y >= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor))) && (y <= (MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + 26)) && (NOCPSIAYs[counter] > 8) && (CPIES[counter] == 0))
					{
						CPIES[counter] = 1;
						break;
					}
					else if ((x >= SideBarX1 - 37) && (x <= SideBarX1 - 11) && (y >= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor - 10) && (y <= (MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + 16)) && (NOCPSIAYs[counter] > 8) && (CPIES[counter] == 1))
					{
						CPIES[counter] = 0;
						break;
					}
					counter++;
					if ((x >= SideBarX1 - 37) && (x <= SideBarX1 - 11) && (y >= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (1 * One_Semester_Div) - 10) && (y <= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (1 * One_Semester_Div) + 16) && (NOCPSIAYs[counter] > 8) && (CPIES[counter] == 0))
					{
						CPIES[counter] = 1;
						break;
					}
					else if ((x >= SideBarX1 - 37) && (x <= SideBarX1 - 11) && (y >= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (1 * One_Semester_Div) - 10) && (y <= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (1 * One_Semester_Div) + 16) && (NOCPSIAYs[counter] > 8) && (CPIES[counter] == 1))
					{
						CPIES[counter] = 0;
						break;
					}
					counter++;
					if ((x >= SideBarX1 - 37) && (x <= SideBarX1 - 11) && (y >= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (2 * One_Semester_Div) - 10) && (y <= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (2 * One_Semester_Div) + 16) && (NOCPSIAYs[counter] > 8) && (CPIES[counter] == 0))
					{
						CPIES[counter] = 1;
						break;
					}
					else if ((x >= SideBarX1 - 37) && (x <= SideBarX1 - 11) && (y >= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (2 * One_Semester_Div) - 10) && (y <= MenuBarHeight + ((i - 1) * (One_Year_Div + MyFactor)) + SemesterMidFactor + (2 * One_Semester_Div) + 16) && (NOCPSIAYs[counter] > 8) && (CPIES[counter] == 1))
					{
						CPIES[counter] = 0;
						break;
					}
					counter++;
				}
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}
			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
		if (ctInput == RIGHT_CLICK)	//mouse left click
		{
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				XCoord = x; YCoord = y;
				Last_CLick = ctInput;
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}
		}
		X = 0; Y = 0;
		//if (!LOFWIND.empty())
		//{
		//	for (int i = 0; i < LOFWIND.size(); i++)
		//	{
		//		if ((LOFWIND[i]->GetMouseClick(X, Y)) && (LOFWIND[i] != pWind))
		//		{
		//			LOFWIND[i]->SetClicked(true);
		//			Maestro_Click = true;
		//			break;
		//		}
		//	}
		//	if (Maestro_Click)
		//		break;
		//}
		if (pMaestrowind->GetMouseClick(X, Y))
		{
			Maestro_Click = true;
			break;
		}
	}//end while
}
string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER". ---->STAR ROON
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput="";
	vector<char>KeyInput{'|'};
	char Cursor = '|';
	vector<char>Letter{};
	vector<string>courses{};
	bool exists;
	int Cursor_Position = 0;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return " "; //returns nothing as user has cancelled the input
		case 13://ENTER key is pressed
		{
			KeyInput.erase(KeyInput.begin() + Cursor_Position);
			userInput = "";
			for (int i = 0; i < KeyInput.size(); i++)
			{
				userInput += KeyInput[i];
			}
			return userInput;
		}
		case 8:		//BackSpace is pressed
			if ((KeyInput.size() != 0)&&(Cursor_Position != 0))
			{
				KeyInput.erase(KeyInput.begin() + Cursor_Position-1);
				Cursor_Position--;
			}
			break;
		case 6:// arrow right
		{
			if (Cursor_Position == KeyInput.size() - 1)
				break;
			KeyInput.erase(KeyInput.begin() + Cursor_Position);
			KeyInput.insert(KeyInput.begin()+ Cursor_Position+1, Cursor);
			Cursor_Position++;
			break;
		}
		case 2:
		{break; }

		case 4:// arrow left
		{
			if (Cursor_Position ==0)
				break;
			KeyInput.erase(KeyInput.begin() + Cursor_Position);
			KeyInput.insert(KeyInput.begin() + Cursor_Position-1, Cursor);
			Cursor_Position--;
			break;
		}

		default:
		{
			if (Cursor_Position == KeyInput.size()-1)
			{
				KeyInput.erase(KeyInput.begin() + Cursor_Position);
				KeyInput.push_back(Key);
				KeyInput.push_back(Cursor);
				Cursor_Position++;
			}
			else if (Cursor_Position < KeyInput.size() - 1)
			{
				KeyInput.insert(KeyInput.begin() + Cursor_Position, Key);
				Cursor_Position++;
			}
		}
		};
		userInput = "";
		for (int i = 0; i < KeyInput.size(); i++)
		{
			userInput += KeyInput[i];
		}
		PrintMsg(userInput);
	}

}
string GUI::GetSrting( string Text)
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar


	string userInput = Text;
	vector<char>KeyInput;
	char Cursor = '|';
	for (int i = 0; i < size(Text); i++)
	{
		KeyInput.push_back(Text[i]);
	}
	KeyInput.push_back(Cursor);
	int Cursor_Position = size(Text);
	char Key;
	PrintMsg(Text);
	while (1)
	{
		pWind->WaitKeyPress(Key);
		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return Notes; //returns the same notes
		case 13://ENTER key is pressed
		{
			KeyInput.erase(KeyInput.begin() + Cursor_Position);
			userInput = "";
			for (int i = 0; i < KeyInput.size(); i++)
			{
				userInput += KeyInput[i];
			}
			return userInput;
		}
		case 8:		//BackSpace is pressed
			if ((KeyInput.size() != 0) && (Cursor_Position != 0))
			{
				KeyInput.erase(KeyInput.begin() + Cursor_Position - 1);
				Cursor_Position--;
			}
			break;
		case 6:// arrow right
		{
			if (Cursor_Position == KeyInput.size() - 1)
				break;
			KeyInput.erase(KeyInput.begin() + Cursor_Position);
			KeyInput.insert(KeyInput.begin() + Cursor_Position + 1, Cursor);
			Cursor_Position++;
			break;
		}
		case 2:
		{break; }

		case 4:// arrow left
		{
			if (Cursor_Position == 0)
				break;
			KeyInput.erase(KeyInput.begin() + Cursor_Position);
			KeyInput.insert(KeyInput.begin() + Cursor_Position - 1, Cursor);
			Cursor_Position--;
			break;
		}

		default:
		{
			if (Cursor_Position == KeyInput.size() - 1)
			{
				KeyInput.erase(KeyInput.begin() + Cursor_Position);
				KeyInput.push_back(Key);
				KeyInput.push_back(Cursor);
				Cursor_Position++;
			}
			else if (Cursor_Position < KeyInput.size() - 1)
			{
				KeyInput.insert(KeyInput.begin() + Cursor_Position, Key);
				Cursor_Position++;
			}
		}
		};
		userInput = "";
		for (int i = 0; i < KeyInput.size(); i++)
		{
			userInput += KeyInput[i];
		}
		PrintMsg(userInput);
	}

}
void GUI::SegmentNotes()
{
	string msg = Notes;
	int Size = size(msg);
	int Test_Msg=0;
    NotesLines.clear();
	int Start =1, End = string_Max_Width;
	if(Notes.size()!=0)
		for (int i = 0; i < ((Size/string_Max_Width)+1); i++)
	    {
		  if (Test_Msg > Size-1)
		  {
			End = Size-i-Start;
		  }
		  NotesLines.push_back(msg.substr(Start, End));
		  Start += string_Max_Width;
		  Test_Msg= Start+ string_Max_Width;
		  End = string_Max_Width;
	    }
}
void GUI::DrawNoteArea()const
{
	pWind->SetFont(15, ITALICIZED, BY_NAME, "Times New Rome");
	pWind->SetBrush(WHITE);
	pWind->SetPen(BLACK);
	pWind->DrawRectangle(SideBarX1, NotesY1, SideBarX2, NotesY1 + NotesHeight, FRAME);
	pWind->SetBrush(WHITE);
	pWind->DrawLine(SideBarX1, NotesY1 + 25, SideBarX2, NotesY1 + 25);
	pWind->DrawRectangle(SideBarX1, NotesY1, SideBarX2, NotesY1 + 25);
	string str = to_string(Current_Page_Notes+1);
	pWind->DrawString(SideBarX1 + myNotesFactor- (10 * MyFactor), NotesY1 + 6,("My Notes Page "+str + " Of " + to_string(Total_Number_Pages_In_Notes+1)));
	pWind->DrawImage("GUI\\Images\\Menu\\Edit_Notes.jpeg", SideBarX1+(SideBarX2- SideBarX1)/2-45, 10, 100, 30);
	if ((Current_Page_Notes == 0) && (Total_Number_Pages_In_Notes >=1))
	{
		pWind->DrawImage("GUI/Images/Menu/prevgray.jpg", SideBarX1 + 2, NotesY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextblue.jpg", SideBarX2 - 24, NotesY1 + 2);
	}
	else if ((Current_Page_Notes > 0) && (Total_Number_Pages_In_Notes > Current_Page_Notes))
	{
		pWind->DrawImage("GUI/Images/Menu/prevblue.jpg", SideBarX1 + 2, NotesY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextblue.jpg", SideBarX2 - 24, NotesY1 + 2);
	}
	else if ((Current_Page_Notes > 0) && (Total_Number_Pages_In_Notes == Current_Page_Notes))
	{
		pWind->DrawImage("GUI/Images/Menu/prevblue.jpg", SideBarX1 + 2, NotesY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextgray.jpg", SideBarX2 - 24, NotesY1 + 2);
	}
	else
	{
		pWind->DrawImage("GUI/Images/Menu/prevgray.jpg", SideBarX1 + 2, NotesY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextgray.jpg", SideBarX2 - 24, NotesY1 + 2);
	}
}
void GUI::DrawReportArea() const
{
	pWind->SetFont(15, ITALICIZED, BY_NAME, "Times New Rome");
	pWind->SetBrush(WHITE);
	pWind->SetPen(BLACK);
	pWind->DrawRectangle(SideBarX1, ReportAreaY1, SideBarX2, ReportAreaY1 + ReportAreaHeight, FRAME);
	pWind->SetBrush(WHITE);
	pWind->DrawLine(SideBarX1, ReportAreaY1 + 25, SideBarX2, ReportAreaY1 + 25);
	pWind->DrawRectangle(SideBarX1, ReportAreaY1, SideBarX2, ReportAreaY1 + 25);
	string str = to_string(Current_Page_Report + 1);
	if (Total_Number_Pages_In_Report == 0)
		str = "1";
	pWind->DrawString(SideBarX1 + myReportFactor-(10*MyFactor+5), ReportAreaY1 + 6, ("Live Report Page "+str+" Of "+to_string(Total_Number_Pages_In_Report+1)));
	if ((Current_Page_Report == 0)&&(Total_Number_Pages_In_Report>1))
	{
		pWind->DrawImage("GUI/Images/Menu/prevgray.jpg", SideBarX1 + 2, ReportAreaY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextblue.jpg", SideBarX2 - 24, ReportAreaY1 + 2);
	}
	else if ((Current_Page_Report > 0) && (Total_Number_Pages_In_Report > Current_Page_Report))
	{
		pWind->DrawImage("GUI/Images/Menu/prevblue.jpg", SideBarX1 + 2, ReportAreaY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextblue.jpg", SideBarX2 - 24, ReportAreaY1 + 2);
	}
	else if ((Current_Page_Report > 0) && (Total_Number_Pages_In_Report== Current_Page_Report))
	{
		pWind->DrawImage("GUI/Images/Menu/prevblue.jpg", SideBarX1 + 2, ReportAreaY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextgray.jpg", SideBarX2 - 24, ReportAreaY1 + 2);
	}
	else
	{
		pWind->DrawImage("GUI/Images/Menu/prevgray.jpg", SideBarX1 + 2, ReportAreaY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextgray.jpg", SideBarX2 - 24, ReportAreaY1 + 2);
	}
	//pWind->DrawImage("GUI\\Images\\Menu\\Edit_Notes.jpeg", SideBarX1 + (SideBarX2 - SideBarX1) / 2 - 45, 10, 100, 30);
}
void GUI::AddCriticalErrorLines(Error Er)
{
	string msg = Er.Msg;
	ReportLines.push_back("CRITICAL ERROR:");
	ReportLines.push_back(msg);
}
void GUI::AddModerateErrorLines(Error Er, int Sem_Total_Crs,int Min_Crs,int Max_Crs)
{
	string msg = Er.Msg;
	ReportLines.push_back("MODERATE ERROR:");
	ReportLines.push_back(msg);
	if (Sem_Total_Crs < Min_Crs)
	{
		ReportLines.push_back("You May Need An Underload Petition");
	}
	else if ((Sem_Total_Crs > Max_Crs))
	{
		ReportLines.push_back("You May Need An Overload Petition");
	}
}
void GUI::AddModerateErrorLines(Error Er)
{
	string msg = Er.Msg;
	ReportLines.push_back("MODERATE ERROR:");
	ReportLines.push_back(msg);
}
void GUI::DrawInfoArea()const
{
	pWind->SetFont(15, ITALICIZED, BY_NAME, "Times New Rome");
	pWind->SetBrush(WHITE);
	pWind->SetPen(BLACK);
	pWind->DrawRectangle(SideBarX1, CourseInfoY1, SideBarX2, CourseInfoY1 + CourseInfoHeight, FRAME);
	pWind->DrawRectangle(SideBarX1, CourseInfoY1, SideBarX2, CourseInfoY1 + 25);
	pWind->DrawLine(SideBarX1, CourseInfoY1 + 25, SideBarX2, CourseInfoY1 + 25);
	if (Current_Page_Info == 0)
	{
	pWind->DrawString(SideBarX1 + courseInfoFactor-20, CourseInfoY1 + 6, "Table Of Content Page 1");
	}
	else if (Current_Page_Info == 1)
	{
	pWind->DrawString(SideBarX1 + courseInfoFactor-25, CourseInfoY1 + 6, "Course Information Page 2");
	}
	else if (Current_Page_Info == 2)
	{
	pWind->DrawString(SideBarX1 + courseInfoFactor-25, CourseInfoY1 + 6, "Student Information Page 3");
	}
	else if (Current_Page_Info == 3)
	{
	pWind->DrawString(SideBarX1 + courseInfoFactor, CourseInfoY1 + 6, "Transcript Page 4");
	}
	else if (Current_Page_Info == 4)
	{
		pWind->DrawString(SideBarX1 + courseInfoFactor, CourseInfoY1 + 6, "User Manual Page 5");
	}
	else if (Current_Page_Info == 5)
	{
		pWind->DrawString(SideBarX1 + courseInfoFactor, CourseInfoY1 + 6, "Shortcuts Page 6");
	}

	if ((Current_Page_Info == 0) && (Total_Number_Pages_In_Info > 1))
	{
		pWind->DrawImage("GUI/Images/Menu/prevgray.jpg", SideBarX1 + 2, CourseInfoY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextblue.jpg", SideBarX2 - 24,CourseInfoY1 + 2);
	}
	else if ((Current_Page_Info > 0) && (Total_Number_Pages_In_Info > Current_Page_Info))
	{
		pWind->DrawImage("GUI/Images/Menu/prevblue.jpg", SideBarX1 + 2, CourseInfoY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextblue.jpg", SideBarX2 - 24,CourseInfoY1 + 2);
	}
	else if ((Current_Page_Info > 0) && (Total_Number_Pages_In_Info == Current_Page_Info))
	{
		pWind->DrawImage("GUI/Images/Menu/prevblue.jpg", SideBarX1 + 2, CourseInfoY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextgray.jpg", SideBarX2 - 24,CourseInfoY1 + 2);
	}
	else
	{
		pWind->DrawImage("GUI/Images/Menu/prevgray.jpg", SideBarX1 + 2, CourseInfoY1 + 2);
		pWind->DrawImage("GUI/Images/Menu/nextgray.jpg", SideBarX2 - 24,CourseInfoY1 + 2);
	}
}
void GUI::DrawLiveReportPages(int Number_Lines, int Page_Number)
{
	ClearReportArea();
	int MsgX = NotesX1 + 5;
    int MsgY = NotesY1 + MyFactor * 10 + 5 + NotesHeight * 2;
	int Counter = 0;
	Report_Start = 0;
	Report_Stop = 11;
	Report_Start += Number_Lines * Page_Number ;
	Report_Stop += Number_Lines * Page_Number;

	if (Report_Stop > ReportLines.size())
		Report_Stop = ReportLines.size();
	if (!ReportLines.empty())
	{
		for (int i = Report_Start; i < Report_Stop; i++)
		{
			if (ReportLines[i] == "MODERATE ERROR:")
			{
				pWind->SetBrush(GOLDENROD);
				pWind->SetPen(GOLDENROD);
				pWind->DrawRectangle(NotesX1 + 5, MsgY + 15 * Counter, MsgX + MyFactor * 25, MsgY + 15 * Counter + 14, FILLED);
				pWind->SetPen(WHITE);
				pWind->SetFont(12, BOLD, BY_NAME, "Times New Rome");
				pWind->DrawString(NotesX1 + 5, MsgY + 15 * Counter, ReportLines[i]);
				Counter++;
			}
			else if (ReportLines[i] == "CRITICAL ERROR:")
			{
				pWind->SetBrush(RED);
				pWind->SetPen(RED);
				pWind->DrawRectangle(NotesX1 + 5, MsgY + 15 * Counter, MsgX + MyFactor * 22, MsgY + 15 * Counter + 14, FILLED);
				pWind->SetPen(WHITE);
				pWind->SetFont(12, BOLD, BY_NAME, "Times New Rome");
				pWind->DrawString(NotesX1 + 5, MsgY + 15 * Counter, ReportLines[i]);
				Counter++;
			}
			else
			{
				pWind->SetPen(BLACK);
				pWind->SetFont(11, BOLD, BY_NAME, "Times New Rome");
				pWind->DrawString(NotesX1 + 5, MsgY + 15 * Counter, ReportLines[i]);
				Counter++;
			}
		}
	}
}
void GUI::DrawNotesPages(int Number_Lines, int Page_Number)
{
	ClearNotesArea();
	int MsgX = NotesX1+5;
    int MsgY = NotesY1+MyFactor*6+5;
	int Counter = 0;

	Notes_Start = 0;
	Notes_Stop = 11;
	Notes_Start += Number_Lines * Page_Number;
    Notes_Stop += Number_Lines * Page_Number;
	
	if (Notes_Stop > NotesLines.size())
		Notes_Stop = NotesLines.size();

	if (!NotesLines.empty())
	{
		for (int i = Notes_Start; i < Notes_Stop; i++)
		{

			pWind->SetFont(14, BOLD, BY_NAME, "Times New Rome");
	        pWind->SetPen(BLACK);
			pWind->DrawString(NotesX1 + 5, MsgY + 15 * Counter, NotesLines[i]);
			Counter++;
		}
	}
}
void GUI::DrawInfoPages()const
{
	if     (Current_Page_Info == 0)
	{
		int MsgX = InfoX1 + 5;
		int MsgY = InfoY1 - 20;
		if (WindWidth <= 1200)
		{
			pWind->SetFont(14, ITALICIZED, BY_NAME, "Times New Rome");
		}
		else
		{
			pWind->SetFont(15, ITALICIZED, BY_NAME, "Times New Rome");
		}
		pWind->SetPen(BLACK);
		pWind->DrawString(MsgX, MsgY+10, "• Course Information In Page 2");
		pWind->DrawString(MsgX, MsgY+10, "____________________________");
		pWind->DrawString(MsgX, MsgY + (Y_div/24)   * 2, "• Student Information In Page 3");
		pWind->DrawString(MsgX, MsgY + (Y_div / 24) * 2, "____________________________");
		pWind->DrawString(MsgX, MsgY + (Y_div / 21) * 3, "• Transcript Information In Page 4");
		pWind->DrawString(MsgX, MsgY + (Y_div / 21) * 3, "____________________________");
		pWind->DrawString(MsgX, MsgY + (Y_div / 15.5) * 3, "• User Manual In Page 5");
		pWind->DrawString(MsgX, MsgY + (Y_div / 15.5) * 3, "____________________________");
		pWind->DrawString(MsgX, MsgY + (Y_div / 12) * 3, "• Shortcuts In Page 6");
		pWind->DrawString(MsgX, MsgY + (Y_div / 12) * 3, "____________________________");
	}
	else if(Current_Page_Info == 1)
	{
		int MsgX = InfoX1 + 5;
		int MsgY = InfoY1 - 20;
		string msg1 = CourseTitle;
		int Size = size(msg1);
		int Test_Msg = 0;
		int Start = 0, End = string_Max_Width;
		pWind->SetFont(15, BOLD, BY_NAME, "Times New Rome");
		pWind->SetPen(BLACK);
		if (Size > string_Max_Width)
			for (int i = 0; i < ((Size / (string_Max_Width)) + 1); i++)
			{
				if (Test_Msg > Size)
				{
					End = Size - Start;
				}
				pWind->DrawString(MsgX, MsgY + 15 * i, msg1.substr(Start, End));
				Start += string_Max_Width;
				Test_Msg = Start + string_Max_Width;
				End = string_Max_Width;
			}

		else
		{
			pWind->DrawString(MsgX, MsgY, msg1);
		}

		string msg2 = CourseCode;
		pWind->DrawString(MsgX, MsgY + 60, msg2);
		string msg3 = CourseCredit;
		pWind->DrawString(MsgX, MsgY + 90, msg3);
		string msg4 = CourseStatus;
		pWind->DrawString(MsgX, MsgY + 120, msg4);
		string msg5 = CourseGrade;
		pWind->DrawString(MsgX, MsgY + 150, msg5);
	}
	else if(Current_Page_Info == 2)
	{
		int MsgX = InfoX1 + 5;
		int MsgY = InfoY1 - 20;
		pWind->SetFont(15, BOLD, BY_NAME, "Times New Rome");
		pWind->SetPen(BLACK);
		pWind->DrawString(MsgX, MsgY,     "• Student Level: "+Student_Level);
		pWind->DrawString(MsgX, MsgY+20,  "• Student GPA: "+GPA);
		pWind->DrawString(MsgX, MsgY+40,  "• Done Credits: "+Done_Credits);
		pWind->DrawString(MsgX, MsgY+60,  "• Student Major: "+Your_Major);
		pWind->DrawString(MsgX, MsgY+80,  "• Concentration: "+ Your_Concentration);
		pWind->DrawString(MsgX, MsgY+100, "• Minor : "+ Your_Minor);
		pWind->DrawString(MsgX, MsgY+120, "• Double  Major: "+Double_Major);
		pWind->DrawString(MsgX, MsgY+140, "• Double Concentration: "+Double_Concentration);

	}
	else if(Current_Page_Info == 3)
	{
		int MsgX = 2+(SideBarX2 -SideBarX1)/5;
		int MsgY = InfoY1 - 20;
		if (WindWidth <= 1200)
		{
			pWind->SetFont(14, ITALICIZED, BY_NAME, "Times New Rome");
		}
		else
		{
			pWind->SetFont(15, ITALICIZED, BY_NAME, "Times New Rome");
		}

		pWind->DrawString(4+InfoX1+  MsgX * 0, MsgY, "Year 1");
		pWind->DrawLine(InfoX1-2 + MsgX * 1, CourseInfoY1 + 25, InfoX1-2+ MsgX * 1, CourseInfoY1+CourseInfoHeight);
		pWind->DrawString(InfoX1 + MsgX * 1, MsgY,  "Year 2");
		pWind->DrawLine(InfoX1 - 4 + MsgX * 2, CourseInfoY1 + 25, InfoX1 - 4 + MsgX * 2, CourseInfoY1 + CourseInfoHeight);
		pWind->DrawString(InfoX1 + MsgX * 2, MsgY,  "Year 3");
		pWind->DrawLine(InfoX1 - 4 + MsgX * 3, CourseInfoY1 + 25, InfoX1 - 4 + MsgX * 3, CourseInfoY1 + CourseInfoHeight);
		pWind->DrawString(InfoX1 -2+ MsgX * 3, MsgY,  "Year 4");
		pWind->DrawLine(InfoX1 - 6 + MsgX *4, CourseInfoY1 + 25, InfoX1 - 6 + MsgX * 4, CourseInfoY1 + CourseInfoHeight);
		pWind->DrawString(InfoX1 + MsgX * 4-4, MsgY, "Year 5");
		pWind->DrawLine(SideBarX1, InfoY1-5, SideBarX2, InfoY1-5);
		string Sem = "Fall";
		int X = 30  ;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < NumOfYrs; i++)
			{
				if (j == 0)
				{
					Sem = "  Fall";
					X;
					pWind->DrawLine(SideBarX1, InfoY1 - 5 + X - 15, SideBarX2, InfoY1 - 5 + X - 15);
					pWind->DrawLine(SideBarX1, InfoY1 - 5 + X, SideBarX2, InfoY1 - 5 + X);
				}
				else if (j == 1)
				{
					Sem = "Spring";
					X =10+ CourseInfoHeight/3;
					pWind->DrawLine(SideBarX1, InfoY1 - 5 + X - 15, SideBarX2, InfoY1 - 5 + X - 15);
					pWind->DrawLine(SideBarX1, InfoY1 - 5 + X+1, SideBarX2, InfoY1 - 5 + X+1);
				}
				else if (j == 2)
				{

					Sem = "Summ";
					X =1.9*CourseInfoHeight / 3;
					pWind->DrawLine(SideBarX1, InfoY1 - 5 + X - 15, SideBarX2, InfoY1 - 5 + X - 15);
					pWind->DrawLine(SideBarX1, InfoY1 - 5 + X+1, SideBarX2, InfoY1 - 5 + X+1);
				}
				if (i == 0)
				{
					pWind->DrawString(2+InfoX1 + MsgX * i, MsgY + X, Sem);
				}
				else if (i == (NumOfYrs - 1))
				{
					pWind->DrawString(InfoX1-4+ MsgX * i, MsgY + X, Sem);
				}
				else if (i == (NumOfYrs - 2))
				{
					pWind->DrawString(InfoX1 - 2 + MsgX * i, MsgY + X, Sem);
				}
				else
				{
					pWind->DrawString(InfoX1 + MsgX * i, MsgY + X, Sem);
				}
			}
		}

		int Counter = 0;
		if(!GPA_Semesters.empty())
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < NumOfYrs; i++)
			{
				if (j == 0)
				{
					X=55;
				}
				else if (j == 1)
				{
					X = 35 + CourseInfoHeight / 3;
				}
				else if (j == 2)
				{
					X = 25+1.9 * CourseInfoHeight / 3;
				}

				pWind->DrawString(InfoX1+1 + MsgX * i, MsgY + X, GPA_Semesters[Counter]);
				Counter++;
			}
		}
		//if (NumOfYrs == 6)
		//{
		//pWind->DrawString(MsgX + 100, MsgY, "Year 6");


		//}
	}
	else if(Current_Page_Info == 4)
	{

	int gInfo_y = InfoY1-10 ;
	int gInfo_x = InfoX1 + MyFactor*18;
	pWind->SetBrush(MYCYAN);
	pWind->SetPen(BLACK, 1);
	pWind->DrawRectangle(gInfo_x, gInfo_y, gInfo_x + CRS_WIDTH, gInfo_y + CRS_HEIGHT);
	pWind->DrawLine(gInfo_x, gInfo_y + CRS_HEIGHT / 2, gInfo_x + CRS_WIDTH, gInfo_y + CRS_HEIGHT / 2);
	pWind->DrawLine(gInfo_x + (CRS_WIDTH / 3) + 10, gInfo_y + CRS_HEIGHT / 2, gInfo_x + (CRS_WIDTH / 3) + 10, gInfo_y + CRS_HEIGHT);
	pWind->DrawLine(gInfo_x + ((2 * CRS_WIDTH) / 3) + 5, gInfo_y + CRS_HEIGHT / 2, gInfo_x + ((2 * CRS_WIDTH) / 3) + 5, gInfo_y + CRS_HEIGHT);
	//Write the course code and credit hours.
	int Code_y = gInfo_y + (CRS_HEIGHT * 0.05) + 2;
	int Code_x = gInfo_x + (CRS_WIDTH * 0.15) - 7;
	pWind->SetPen(WHITE);
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->DrawString(Code_x+15, Code_y, "CIE 202");
	pWind->DrawString(gInfo_x + (CRS_WIDTH / 3) + 17, Code_y + CRS_HEIGHT / 2, "A");
	pWind->DrawString(gInfo_x + ((2 * CRS_WIDTH) / 3) + 8, Code_y + CRS_HEIGHT / 2, "DN");
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2,"Crs:3");
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(BLACK);
	pWind->DrawTriangle(gInfo_x-1, gInfo_y + CRS_HEIGHT / 2 - 7, gInfo_x-5, gInfo_y + CRS_HEIGHT / 2 - 3, gInfo_x-5, gInfo_y + CRS_HEIGHT / 2 - 12);
	pWind->DrawTriangle(gInfo_x - 1, gInfo_y + CRS_HEIGHT  - 7, gInfo_x - 5, gInfo_y + CRS_HEIGHT  - 3, gInfo_x - 5, gInfo_y + CRS_HEIGHT  - 12);
	pWind->DrawTriangle(gInfo_x + CRS_WIDTH - 1, gInfo_y + CRS_HEIGHT - 7, gInfo_x + CRS_WIDTH + 5, gInfo_y + CRS_HEIGHT - 3, gInfo_x + CRS_WIDTH + 5, gInfo_y + CRS_HEIGHT - 12);
	pWind->DrawTriangle(gInfo_x + (CRS_WIDTH / 3) + 19, gInfo_y + CRS_HEIGHT, gInfo_x + (CRS_WIDTH / 3) + 16, gInfo_y + CRS_HEIGHT + 4, gInfo_x + (CRS_WIDTH / 3) + 24,gInfo_y + CRS_HEIGHT + 4);
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(gInfo_x, gInfo_y + CRS_HEIGHT / 2-7, gInfo_x - CRS_WIDTH/2+2, gInfo_y + CRS_HEIGHT / 2 - 7);
	pWind->DrawLine(gInfo_x, gInfo_y + CRS_HEIGHT - 7, gInfo_x - CRS_WIDTH / 2+12, gInfo_y + CRS_HEIGHT  - 7);
	pWind->DrawLine(gInfo_x + CRS_WIDTH, gInfo_y + CRS_HEIGHT - 7, gInfo_x +CRS_WIDTH+ CRS_WIDTH / 2-2, gInfo_y + CRS_HEIGHT - 7);
	pWind->DrawLine(gInfo_x + (CRS_WIDTH / 3) + 20, gInfo_y + CRS_HEIGHT, gInfo_x + (CRS_WIDTH / 3) + 20, gInfo_y + CRS_HEIGHT +15);
	pWind->DrawString(gInfo_x - CRS_WIDTH / 2 - 25, gInfo_y + CRS_HEIGHT / 2 - 13, "Code");
	pWind->DrawString(gInfo_x - CRS_WIDTH / 2 - 25, gInfo_y + CRS_HEIGHT - 13, "Credits");
	pWind->DrawString(gInfo_x + CRS_WIDTH + CRS_WIDTH / 2, gInfo_y + CRS_HEIGHT - 13, "Status");
	pWind->DrawString(gInfo_x + (CRS_WIDTH / 3) + 6, gInfo_y + CRS_HEIGHT + 15, "Grade");
	//-------------------------------------------------------------Title Course Colour Code----------------------------------------
	pWind->SetPen(BLACK, 1);
	pWind->SetFont(15, BOLD, BY_NAME, "Times New Rome");
	pWind->DrawLine(InfoX1, InfoY1 + CourseInfoHeight / 3.8, SideBarX2, InfoY1 + CourseInfoHeight / 3.8);
	pWind->DrawString(SideBarX1 + courseInfoFactor - 10, InfoY1 + CourseInfoHeight / 3.8, "Course Colour Code");
	pWind->DrawLine(InfoX1, InfoY1 + CourseInfoHeight / 3, SideBarX2, InfoY1 + CourseInfoHeight / 3);
	//---------------------------------------------------------------------Color Code-----------------------------------------------
	pWind->SetFont(12, BOLD, BY_NAME, "Times New Rome");
	pWind->SetBrush(GOLDENROD);
	pWind->SetPen(BLACK, 1);
	pWind->DrawRectangle(InfoX1+MyFactor*2, InfoY1 + CourseInfoHeight / 2.8,InfoX1 + MyFactor * 2 +20, InfoY1 + CourseInfoHeight / 2.8 +20,FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 2 + 23, InfoY1 + CourseInfoHeight / 2.8+3, "Major");
	pWind->SetBrush(FIREBRICK);
	pWind->DrawRectangle(InfoX1 + MyFactor * 17, InfoY1 + CourseInfoHeight / 2.8, InfoX1 + MyFactor * 17 + 20, InfoY1 + CourseInfoHeight / 2.8 + 20, FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 17 + 23, InfoY1 + CourseInfoHeight / 2.8 + 3, "Elective");
	pWind->SetBrush(ORANGERED);
	pWind->DrawRectangle(InfoX1 + MyFactor * 36, InfoY1 + CourseInfoHeight / 2.8, InfoX1 + MyFactor * 36 + 20, InfoY1 + CourseInfoHeight / 2.8 + 20, FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 36 + 23, InfoY1 + CourseInfoHeight / 2.8 + 3, "Minor");

	pWind->SetBrush(DARKGREEN);
	pWind->DrawRectangle(InfoX1 + MyFactor * 2, InfoY1 + CourseInfoHeight / 2, InfoX1 + MyFactor * 2 + 20, InfoY1 + CourseInfoHeight / 2 + 20, FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 2 + 23, InfoY1 + CourseInfoHeight / 2 + 3, "Track");
	pWind->SetBrush(SLATEGREY);
	pWind->DrawRectangle(InfoX1 + MyFactor * 17, InfoY1 + CourseInfoHeight / 2, InfoX1 + MyFactor * 17 + 20, InfoY1 + CourseInfoHeight / 2 + 20, FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 17 + 23, InfoY1 + CourseInfoHeight / 2 + 3, "University");
	pWind->SetBrush(DARKMAGENTA);
	pWind->DrawRectangle(InfoX1 + MyFactor * 36, InfoY1 + CourseInfoHeight / 2, InfoX1 + MyFactor * 36 + 20, InfoY1 + CourseInfoHeight / 2 + 20, FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 36 + 23, InfoY1 + CourseInfoHeight / 2 , "Concent-");
	pWind->DrawString(InfoX1 + MyFactor * 36 + 23, InfoY1 + CourseInfoHeight / 2 +8, "ration");

	pWind->SetBrush(MYCYAN);
	pWind->DrawRectangle(InfoX1 + MyFactor * 2, InfoY1 + CourseInfoHeight / 1.5-5, InfoX1 + MyFactor * 2 + 20, InfoY1 + CourseInfoHeight / 1.5 + 15, FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 2 + 23, InfoY1 + CourseInfoHeight / 1.5-2, "Default");
	pWind->SetBrush(RED);
	pWind->DrawRectangle(InfoX1 + MyFactor * 17, InfoY1 + CourseInfoHeight / 1.5-5, InfoX1 + MyFactor * 17 + 20, InfoY1 + CourseInfoHeight / 1.5 + 15, FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 17 + 23, InfoY1 + CourseInfoHeight / 1.5-2, "Unknown");
	pWind->SetBrush(YELLOWGREEN);
	pWind->DrawRectangle(InfoX1 + MyFactor * 36, InfoY1 + CourseInfoHeight / 1.5 - 5, InfoX1 + MyFactor * 36 + 20, InfoY1 + CourseInfoHeight / 1.5 + 15, FILLED);
	pWind->DrawString(InfoX1 + MyFactor * 36 + 23, InfoY1 + CourseInfoHeight / 1.5-5, "2nd");
	pWind->DrawString(InfoX1 + MyFactor * 36 + 23, InfoY1 + CourseInfoHeight / 1.5 + 3, "Minor");
    }
	else if(Current_Page_Info == 5)
	{
	int MsgX = InfoX1 + 5;
	int MsgY = InfoY1 - 20;
	int F= 14;
	pWind->DrawString(MsgX, MsgY + 5 + F*0, "Press  a  To Add A Course");
	pWind->DrawString(MsgX, MsgY + 5 + F*1,  "Press  d  To Delete A Course");
	pWind->DrawString(MsgX, MsgY + 5 + F*2,  "Press  c  To Change Course Code");
	pWind->DrawString(MsgX, MsgY + 5 + F*3,  "Press  s  To Save Plan");
	pWind->DrawString(MsgX, MsgY + 5 + F*4,  "Press  i  To Import Plan");
	pWind->DrawString(MsgX, MsgY + 5 + F*5,  "Press  e  To Erase Plan");
	pWind->DrawString(MsgX, MsgY + 5 + F*6, "Press  m  To Declare Minor");
	pWind->DrawString(MsgX, MsgY + 5 + F*7, "Press  j  To Declare Major");
	pWind->DrawString(MsgX, MsgY + 5 + F*8, "Press  g  To Caluclate GPA");
	pWind->DrawString(MsgX, MsgY + 5 + F*9, "Press  f  To Filter");
	pWind->DrawString(MsgX, MsgY + 5 + F*10, "Press  z  To Undo");
	pWind->DrawString(MsgX, MsgY + 5 + F*11, "Press  x  To Redo");
    }
}
void GUI::DrawCourse_Dependacies(Course* pCr, Course* DpCr)
{
	//pWind->SetBrush(BLACK);
	//pWind->SetPen(BLACK);
	graphicsInfo gInfo_Of_PreOrCo = pCr->getGfxInfo();
	graphicsInfo gInfo_Of_DepCr = DpCr->getGfxInfo();
	if ((gInfo_Of_DepCr.y == gInfo_Of_PreOrCo.y)&&((abs(gInfo_Of_DepCr.x+CRS_WIDTH-gInfo_Of_PreOrCo.x)==40)))
	{
		pWind->DrawTriangle(gInfo_Of_DepCr.x + CRS_WIDTH, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x + CRS_WIDTH + 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 - 5, gInfo_Of_DepCr.x + CRS_WIDTH + 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 + 5, FILLED);
		pWind->DrawLine(gInfo_Of_DepCr.x + CRS_WIDTH, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_PreOrCo.x, gInfo_Of_PreOrCo.y + CRS_HEIGHT / 2);
	}
	else if ((gInfo_Of_DepCr.y == gInfo_Of_PreOrCo.y) && ((abs(gInfo_Of_PreOrCo.x + CRS_WIDTH - gInfo_Of_DepCr.x) == 40)))
	{
		pWind->DrawTriangle(gInfo_Of_DepCr.x, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x - 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 - 5, gInfo_Of_DepCr.x - 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 + 5, FILLED);
		pWind->DrawLine(gInfo_Of_PreOrCo.x + CRS_WIDTH, gInfo_Of_PreOrCo.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x, gInfo_Of_DepCr.y + CRS_HEIGHT / 2);
	}
	else
	{
		if (gInfo_Of_DepCr.x == gInfo_Of_PreOrCo.x)
		{
			pWind->DrawTriangle(gInfo_Of_DepCr.x + CRS_WIDTH, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x + CRS_WIDTH + 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 - 5, gInfo_Of_DepCr.x + CRS_WIDTH + 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 + 5, FILLED);
			//pWind->SetPen(BLACK, 2);
			pWind->DrawBezier(gInfo_Of_DepCr.x + CRS_WIDTH, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x + CRS_WIDTH + 100, gInfo_Of_DepCr.y + 20, gInfo_Of_PreOrCo.x + CRS_WIDTH - 10, gInfo_Of_PreOrCo.y + CRS_HEIGHT - 10, gInfo_Of_PreOrCo.x + CRS_WIDTH / 2, gInfo_Of_PreOrCo.y + CRS_HEIGHT);
		}
		else if (gInfo_Of_DepCr.x > gInfo_Of_PreOrCo.x)
		{
			pWind->DrawTriangle(gInfo_Of_DepCr.x, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x - 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 - 5, gInfo_Of_DepCr.x - 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 + 5, FILLED);
			//pWind->SetPen(BLACK, 2);
			pWind->DrawBezier(gInfo_Of_DepCr.x, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x - 70, gInfo_Of_DepCr.y, gInfo_Of_PreOrCo.x + CRS_WIDTH / 2, gInfo_Of_PreOrCo.y + 120, gInfo_Of_PreOrCo.x + CRS_WIDTH / 2, gInfo_Of_PreOrCo.y + CRS_HEIGHT);
		}
		else if (gInfo_Of_DepCr.x < gInfo_Of_PreOrCo.x)
		{
			pWind->DrawTriangle(gInfo_Of_DepCr.x + CRS_WIDTH, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x + CRS_WIDTH + 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 - 5, gInfo_Of_DepCr.x + CRS_WIDTH + 5, gInfo_Of_DepCr.y + CRS_HEIGHT / 2 + 5, FILLED);
			//pWind->SetPen(BLACK, 2);
			pWind->DrawBezier(gInfo_Of_DepCr.x + CRS_WIDTH, gInfo_Of_DepCr.y + CRS_HEIGHT / 2, gInfo_Of_DepCr.x + CRS_WIDTH + 60, gInfo_Of_DepCr.y + 20, gInfo_Of_PreOrCo.x + CRS_WIDTH - 10, gInfo_Of_PreOrCo.y + CRS_HEIGHT - 10, gInfo_Of_PreOrCo.x + CRS_WIDTH / 2, gInfo_Of_PreOrCo.y + CRS_HEIGHT);
		}
	}
}
void GUI::setWindWidth(int width)
{
	//this->WindWidth = width;
}
//Dimention getters
int  GUI::getMenuBarHeight() {
	return MenuBarHeight;
}
int  GUI::getY_div() {
	return Y_div;
}
int  GUI::getYDivStartingPos() {
	return (WindHeight - StatusBarHeight);
}
void GUI::SetMaestroWindowP(window* Pointer)
{
	pMaestrowind = Pointer;
}
bool GUI::GetMaestroClick()const
{
	return Maestro_Click;
}
void GUI::SetMaestroClick(bool input)
{
	Maestro_Click = input;
}
void GUI::GetVecOfWindows(vector<window*>input)
{
	LOFWIND = input;
}
void GUI::setSpotNumber(int input)
{
	SpotNumber = input;
}
bool GUI::getDDFOOCF()const
{
	return Draw_Dependacies_For_One_Course_Flag;
}
void GUI::setDDFOOCF(bool input)
{
	Draw_Dependacies_For_One_Course_Flag = input;
}
bool GUI::getDDFOC()const
{
	return Draw_Dependacies_For_One_Course;
}
void GUI::setDDFOC(bool input)
{
	Draw_Dependacies_For_One_Course = input;
}
bool GUI::getDDF()const
{
	return Draw_Dependacies_Flag;
}
void GUI::setDDF(bool input)
{
	Draw_Dependacies_Flag = input;
}
int  GUI::getXCoord()const
{
	return XCoord;
}
int  GUI::getYCoord()const
{
	return YCoord;
}
clicktype GUI::GetLastClick()const
{
	return Last_CLick;
}
int  GUI::getCurrent_Page_Report()const
{
	return Current_Page_Report;
}
void GUI::setCurrent_Page_Report(int input)
{
	Current_Page_Report = input;
}
int  GUI::getCurrent_Page_Notes()const
{
	return Current_Page_Notes;
}
void GUI::setCurrent_Page_Notes(int input)
{
	Current_Page_Notes = input;
}
int  GUI::getCurrent_Page_Info()const
{
	return Current_Page_Info;
}
void GUI::setCurrent_Page_Info(int input)
{
	Current_Page_Info = input;
}
int  GUI::getReport_Stop()const
{
	return Report_Stop;
}
void GUI::setReport_Stop(int input)
{
	Report_Stop = input;
}
int  GUI::getReport_Start()const
{
	return Report_Start;
}
void GUI::setReport_Start(int input)
{
	Report_Start = input;
}
int  GUI::getNotes_Stop()const
{
	return Notes_Stop;
}
void GUI::setNotes_Stop(int input)
{
	Notes_Stop = input;
}
GUI::~GUI()
{
	delete pWind;
}