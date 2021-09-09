#pragma once
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#pragma warning(disable: 26495)
#pragma warning(disable: 26812)
#pragma warning(disable: 4101)
#pragma warning(disable: 4018)
#include <string>
using namespace std;
#include<iostream>
#include "..\DEFs.h"
#include<vector>
#include "CMUgraphicsLib\CMUgraphics.h"
#include <algorithm>

class Course;
class AcademicYear;
//user interface class
class GUI
{

	enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_ADD,		//Add a new course
		ITM_DELETE,		//Delete a course
		ITM_UNDO,		//Undo last action
		ITM_REDO,		//Redo last action
		ITM_SAVE,		//Save the current splan
		ITM_IMPORT,		//Import a pre-made plan or a default study plan
		ITM_EXCHANGE,
		ITM_ERASE,		//Clear all the data (courses)
		ITM_MAJOR,
		ITM_MINOR, //Minor decleration
		ITM_CRS_DEP,
		ITM_PLAN_DEP,
		ITM_GPA,		//gpa item
		ITM_Filter,		//Filter item
		ITM_EXIT,
		ITM_CNT,		//no. of menu items ==> This should be the last line in this enum
		ITM_Note	//Add notes
		
	};

	color DrawColor = BLACK;		//Drawing color
	color FillColor = MYCYAN;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = BLACK;			//Messages color
	color BkGrndColor = WHITESMOKE;	//Background color
	color StatusBarColor = WHITE;//statusbar color
	color CourseCodeColor = WHITE;
	string WindTitle = "Study-Plan Organizational Tool (SPOT)";
	bool Maestro_Click=false;
	int SpotNumber;
    int Report_Stop, Report_Start,Notes_Stop, Notes_Start, Info_Start,Info_Stop;
    int Current_Page_Report;
	int Current_Page_Notes;
	int Current_Page_Info;
	int XCoord, YCoord;
	bool Draw_Dependacies_Flag;
	bool Draw_Dependacies_For_One_Course;
	bool Draw_Dependacies_For_One_Course_Flag;
	clicktype Last_CLick;
public:
	window* pWind;
	window* pMaestrowind;
	//Some constants for GUI (My default = 1600 x 880 with aspect ratio 20:11)

	static const int WindWidth = 1300, WindHeight = WindWidth * (11.0 / 20.0),	//Window width and height
		wx = 15, wy = 15,		//Window starting coordinates
		StatusBarHeight = 60,	//Status Bar Height
		MenuBarHeight = 51,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 51,		//Width of each item in the menu
		MenuItemWidthGap = 20,  //Gap width between items
		NumOfYrs = 5, // total years (to be implemented dynamically)
		Y_div = (WindHeight - StatusBarHeight - MenuBarHeight), // 1 div from 5 equal divisions in y
		MyFactor = 4, // used in some refinings
		//Title Bar
		TitleBarWidth = 60,
		TitleBarY2 = Y_div + MenuBarHeight - 4,
		//Years Rectangle
		Year_X1 = TitleBarWidth,
		Year_X2 = WindWidth * 0.8125,
		//Separators
		VerticalSeparatorX = 20,
		//Semesters
		One_Year_Div = (Y_div - (NumOfYrs * MyFactor)) / NumOfYrs,
		One_Semester_Div = One_Year_Div / 3,
		YearImgMidSubtractor = (One_Year_Div - 50) / 2.0,
		SemesterMidFactor = 20,
		//Side Bar
		SideBarX1 = Year_X2 + 10,
		SideBarX2 = WindWidth - 20,
		/*// Add Notes
		NotesY1 = MenuBarHeight + MyFactor,
		NotesHeight = 250,
		// Course Info
		CourseInfoY1 = NotesY1 + NotesHeight + MyFactor,
		CourseInfoHeight = 250,
		myNotesFactor = WindWidth * (1.0 / 16.0),
		courseInfoFactor = WindWidth * (13.0/320.0),*/
		// Add Notes
		NotesY1 = MenuBarHeight + MyFactor,
		NotesHeight = (Y_div / 3) - MyFactor * 2,
		NotesY2 = NotesHeight - NotesHeight * 0.65,
		NotesX1 = WindWidth - (WindWidth - Year_X2 - 10),
		string_Max_Width = ((WindWidth - NotesX1) / 6)-11,
		myNotesFactor = (SideBarX2 - SideBarX1 - 40) / 2.0,
		courseInfoFactor = (SideBarX2 - SideBarX1 - 95) / 2.0,
		InfoX1 = WindWidth - (WindWidth - Year_X2 - 10),
		InfoY1 = NotesHeight + MenuBarHeight + NotesY1;
	// Course Info
	int CourseInfoY1 = NotesY1 + NotesHeight + MyFactor;
	string Notes, CourseTitle, CourseCode, CourseCredit, CourseStatus,CourseGrade,
	Student_Level = "---",GPA="---",Done_Credits = "---",Your_Major = "---",Your_Minor = "---",Your_Concentration = "---",Double_Major = "---",Double_Concentration = "---";
	int CourseInfoHeight = Y_div/3;
	vector<string>ReportLines;
	vector<string>NotesLines;
	vector<string>GPA_Semesters;
	// Report Area
	int ReportAreaY1 = CourseInfoY1 + CourseInfoHeight + MyFactor,
		ReportAreaHeight = (Y_div / 3) - MyFactor,
		myReportFactor = (SideBarX2 - SideBarX1 - 52) / 2.0;

	const string BREAK_LINE = "========================================";

	GUI();
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar
	void ClearReportArea() const;
	void ClearNotesArea() const;
	void ClearInfoArea() const;
	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar
	void DrawNoteArea() const;
	void SegmentNotes();
	void DrawInfoArea() const;
	void DrawInfoPages()const;
	void DrawReportArea() const;
	void AddCriticalErrorLines(Error Er);
	void AddModerateErrorLines(Error Er, int Sem_Total_Crs,int Min_Crs,int Max_Crs);
	void AddModerateErrorLines(Error Er);
	//Drawing functions
	void DrawCourse(const Course* );
	void DrawCourse(const Course* ,int x,int y);
	void DrawAcademicYear(const AcademicYear*);
	void UpdateInterface() const;
	void DrawCourse_Dependacies(Course* pCr, Course* DpCr);
	void DrawLiveReportPages(int Number_Lines,int Page_Number);
	void DrawNotesPages(int Number_Lines, int Page_Number);
	//input functions
	ActionData GUI::GetUserAction(string msg = "");
	string GetSrting() const;
	string GetSrting(string MSG);
	static int getYDivStartingPos();
	int Total_Number_Pages_In_Report;
	int Total_Number_Pages_In_Notes;
	int Total_Number_Pages_In_Info=5;
	int Total_Number_Study_Plans, Current_StudyPlan;
	vector<int>NOCPSIAYs;
	vector<int>CPIES;
	vector<int>CrsPerSemester;
	//Dimention getters

	void setWindWidth(int width);

	static int getMenuBarHeight();
	static int getY_div();
	void SetMaestroWindowP(window* Pointer);
	bool GetMaestroClick()const;
	void SetMaestroClick(bool input);
	void GetVecOfWindows(vector<window*>input);
	void setSpotNumber(int input);
	static vector<window*>LOFWIND;
	 bool getDDFOOCF()const;
	 void setDDFOOCF(bool input);
	 bool getDDFOC()const;
	 void setDDFOC(bool input);
	 bool getDDF()const;
	 void setDDF(bool input);
	 int getXCoord()const;
	 int getYCoord()const;
	 clicktype GetLastClick()const;
	 int getCurrent_Page_Report()const;
	 void setCurrent_Page_Report(int input);
	 int getCurrent_Page_Notes()const;
	 void setCurrent_Page_Notes(int input);
	 int getCurrent_Page_Info()const;
	 void setCurrent_Page_Info(int input);
	 int getReport_Stop()const;
	 void setReport_Stop(int input);
	 int getReport_Start()const;
	 void setReport_Start(int input);
	 int getNotes_Stop()const;
	 void setNotes_Stop(int input);
	~GUI();
};