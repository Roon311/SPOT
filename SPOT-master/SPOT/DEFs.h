#pragma once
//This header file contains some defenitions to be used all over the application
#include <string>
#include<vector>
using namespace std;
typedef string Course_Code;


//Semesters
enum SEMESTER
{
	FALL,
	SPRING,
	SUMMER,
	SEM_CNT	//number of semesters 
};

enum Type
{
	maj,
	Elective,
	Minor,
	concentration,
	Track,
	Uni,
	DoubleMinor,
	NOTYPE
};
//All possible actions
enum ActionType
{
	ADD_CRS,	//Add a course to study plan
	DEL_CRS,	//Delete a course from study plan
	IMPORT_PLAN, //Import plan
	ERASE,		 //Remove all courses
	COURSE_INFO,
	CHANGE_CODE,	//changes course code
	DECLARE_MAJOR,
	DECLARE_MINOR,
	CRS_DEP,
	PLAN_DEP,
	CAL_GPA,		//Calculate GPA
	Filter,			//apply Filter
	Exit,
	SAVE,		//Save a study plan to file
	LOAD,		//Load a study plan from a file
	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled
	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area
	ADD_Note,   // Add notes
	CANCEL,		//ESC key is pressed

	//TODO: Add more action types

};

//to sotre data related to the last action
struct ActionData
{
	ActionType actType;
	int x, y;
	
};

//Errors
enum ErrorType {
	CRITICAL,
	MODERATE
};
struct Error
{
	ErrorType type;
	string Msg;
};

struct NumOfErrors {
	int Critical_errors;
	int Moderate_errors;
};

enum Major {
	// Engineering
	CIE,
	ENV,
	NANENG,
	REE,
	SPC,
	// Science
	BMS,
	PEU,
	MATSCI,
	NANSCI
};
enum Concentrations {

	NANOFABRICATION,
	NANOVLSI,
	NANOPHOTONICS
};

struct Concentration {
	int ID; // number of concentration
	int CompulsoryCredits, ElectiveCredits; // Chs of such concentrations

	// Courses
	vector<Course_Code> ConcentrationCompulsoryCourses;
	vector<Course_Code> ConcentrationElectiveCourses;
};

struct CrossLinked {
	string left, reight;
};