#pragma once
#include <vector>
#include<string>
#include<iterator>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
#include"../Rules.h"

//A full study plan for as student
class StudyPlan:public Drawable
{
private:
	vector<Error> CH_Error_List; // Holds all the modirate errors for the CH issues
	vector<Error> Program_Req_Errors; // Holds all the critical program requirements errors
	vector<Error> Course_Offering_Errors; // Holds all the modirate errors for adding a course out of offering list
	vector<int> Credits_Of_All_Sems;
	vector<int> Sem_Credits;
	int Report_Lines;
	Course* pCrs;
	Major major;
	Major Doublemajor;
	//Concentrations concentrations;
	Concentrations Doubleconcentrations;
	bool Minor_course_flag;
	bool Double_Minor_course_flag;
	Rules* pRules;
	int concentrationNumber = 0; // Indicates which concentration is sellected (0 = no conc selected yet)
	int DoubleconcentrationNumber = 0;
	bool currentYearAvailable; // true if user chose a current year. false if not.
	string currentYear = "2020\\2021"; // Current Year of offerings (In date)
	vector<Course*>TreeVector;
	bool majorChanged = false;

	// Double Major
	static bool doubleMajorExists;
	bool doubleMajorOptimize = false; // to control the update in registrar
	Major doubleMajor;
	Rules* pDoubleMajorRules;
	vector<string>AllCourseCodeForTree;
	void lazyCheck(int compared, int original, string errMsg, string checkMsg);
	void lazyCheck2(string checkKeyword, vector<string> vect);

	vector<string> repeatedCoursesVector;

public:
	int TotalCredits = 0,				// Total no. of credit hours for courses registred in this year 1
		TotalMajorCredits = 0,		// Univ Elective 3
		TotalElectiveCredits = 0,
		TotalMinorCredits = 0,		// Major comm Elec 6
		TotalDoubleMinorCredits=0,
		TotalConcentrationCredits = 0,// Major Comm Compulsory 5
		TotalTrackCredits = 0,		// Track Compulsory 4
		TotalUnivCredits = 0,			// Univ Compulsory 2
		MaxCredits = 0;
	int NumberOfConcentrations = 0,
		ConcentrationMajorCredits = 0,
		ConcentrationMinorCredits = 0;
	int TotalDoneHours=0;
	string StudentLevel;
	vector<Course_Code> CompUniCourses,
		ElectiveUniCourses,
		TrackCourses,
		CompMajorCourses,
		ElectiveMajorCourses,
		CompConcentrationCourses,
		ElectiveConcentrationCourses;
	int No_Of_Pages;
	string PlanNotes="";
	vector<AcademicYear*> plan;	//plan is a list of academic years
	static vector<string>Double_Minor_Course;//vector for double minor courses
	static vector<string>Minor_Course;
	vector<int>NOCPS;
	static int Count;
	static int Count2;
	StudyPlan();
	bool AddCourse(Course* , int year, SEMESTER);
	bool DeleteCourse(Course* pC);
	void virtual DrawMe(GUI*) const;
	vector<AcademicYear*>* getStudyPlanVector();
	void checkPreAndCoReq();
	void Set_Course_Type();
	void checkCreditHrs(int min, int max);
	void LiveReport(GUI* pGUI,int min,int max);
	void FindPreAndCoReq_ITCSP(Course* pC, GUI* pGUI);
	void FindPreAndCoReq_ITCSP_Tree(Course* pC, GUI* pGUI);
	vector<Course*>FindPre_ITCSP(Course* pC);
	void checkProgramReq();
	void setMinor_course_flag(bool cond);
	void setDouble_Minor_course_flag(bool cond);
	void setMajor(Major major);
	void setDoubleconcentrationNumber(int n);
	void setconcentrationNumber(int concentration);
	//void setDoubleConcentration(Concentrations concentration);
	Major getMajor() const;
	int getConcentration()const;
	int getDoubleConcentration() const;
	void Set_Plan_Rules(Rules& RegRules);
	void setCourseTypeCredits(Type type, int mode, int hours, string);
	void checkOffering(string code, int crsYear, SEMESTER sem);
	void GenerateStudentLevel(GUI* pGUI);
	void increment_Report_Lines(int Number_Of_Inc);
	void ClearTree();
	void ACCFT();
	void TreeFiltering();
	void TreeUnFiltering();
	void SetTree(vector<Course*> VectorTree);
	vector<Course*> Gettree();
	int get_Report_Lines()const;
	vector<int> get_Sem_Credits()const;
	vector<int> get_Of_All_Sems_Credits()const;
	void Set_Report_Lines();
	void Set_Page_Number(int Number_Of_lines);
	int Get_Page_Number()const;
	StudyPlan(const StudyPlan& CopiedSP);
	StudyPlan operator=(const StudyPlan& CopiedSP);
	void setMajorChanged(bool state);
	bool getMajorChanged() const;

	//Double Major
	void setDoubleMajor(Major major);
	Major getDoubleMajor() const;

	void setDoubleMajorExists(bool state);
	bool getDoubleMajorExists() const;
	
	void setDoubleMajorOptimize(bool state);
	bool getDoubleMajorOptimize() const;

	void Set_Double_Major_Plan_Rules(Rules& DoubleRegRules);
	bool alreadyExistingCourse(string code, SEMESTER, int);

	void handleRepetition();
	virtual ~StudyPlan();
};


