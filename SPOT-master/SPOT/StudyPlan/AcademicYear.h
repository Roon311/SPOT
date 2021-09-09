#pragma once
#include <list>

#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"
#include "../GUI/GUI.h"

//Represent one year in the student's study plan
class AcademicYear:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;
	static int Sem_Counter;
	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	
public:
	list<Course*> YearCourses[SEM_CNT];
	// Some constans for academic year
	static const int
		Year_X1 = 0,
		Year_X2 = 1200;
	static int
		TotalYears;
	int i = TotalYears - 1;
	int
		AvailableY = GUI::Y_div,
		StartingY = GUI::MenuBarHeight,
		YearHeight = AcademicYear::AvailableY / GUI::NumOfYrs;

	/*static int Year_Y, Year_height, Year_Number, Code_x;
	int Year_y = Year_Y, Year_Height = Year_height, Actual_Year_Number = Year_Number;*/

	AcademicYear();
	virtual ~AcademicYear();

	bool AddCourse(Course*, SEMESTER );
	bool DeleteCourse(Course*, SEMESTER);

	list<Course*>* getListOfYears() ;
	void virtual DrawMe(GUI*) const;
};

