#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"
#include "Maestro.h"


//The maestro class for the application
class Registrar
{
	friend class Maestro;
	bool Exit_Program = false;
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	Rules DoubleRegRules; // Double major requirements
     StudyPlan *pSPlan;
	vector<StudyPlan*>List_Of_All_StudyPlans;
	StudyPlan* pS_Old;
	Maestro* pMaestro;
	bool Import_Flag= false;
	bool Delete_Flag = false;
	bool Add_Flag = false;
	bool Erase_Flag = false;
	bool Drag_Flag = false;
	bool Note_Flag = false;
	bool ChangeCode_Flag = false;
	int Current_Study_Plan = 0;
	int MeineNummer;
	int SPSC=2;
	//Updated
	//static vector<CourseInfo> allCourses;

public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	Course* OldpCr = nullptr;
	Course* OldpCr_For_DDOOC = nullptr;
	void Run();
	bool Not_Worth_Saving_Flag = false;
	~Registrar();

	// Updated
	void createAllCourses();
	CourseInfo* inCatalog(string code, bool& exists);
	
	string transformCode(string& code);
	void setCourseOffering();
	void setRules();
	void setDoubleMajorRules();
	Course* interrogateCourse(int x, int y);

	void setCatalogCoursesType();
	void importProgramReq(Rules &savePlace, Major major);
	void Increment_Current_StudyPlan();
	void Increment_Total_Credits(int NUM);
	void Decrement_Current_StudyPlan();
	void Add_To_StudyPlan(StudyPlan &pS_New);
	int GetCurrent_Study_Plan()const;
	vector<StudyPlan*> getStudyPlanVector();
	void combineDoubleMajorCourses();
	void setCrossLinkedCourses();
	void SetMaestroWindowP(Maestro *Pointer);
	int  getMeineNummer()const;
	void getMeineNummer(int num);

};

