#include "ActionImportPlan.h"
#include "..\Registrar.h"
#include <iostream>
#include"../GUI/GUI.h"
#include"../Utils/Utils.h"

ActionImportPlan::ActionImportPlan(Registrar* p) : Action(p)
{
}

ActionImportPlan::~ActionImportPlan()
{
}

bool ActionImportPlan::Execute() {
	cout << "Import button is pressed.\n"; // for debugging
	GUI* pGUI = pReg->getGUI();
	// Get the directory
	string directory = OpenFileDialog();
	if (directory == "")
	{
		pReg->Not_Worth_Saving_Flag = true;
		return true; // User Cancels
	}
	// First we need to erase the current plan (Until i know how to call another action from here)
	vector<Course*> allCourses;
	StudyPlan* pS = pReg->getStudyPlay();
	vector<AcademicYear*>* pPlan = pS->getStudyPlanVector(); // pointer on the plan vector
	for (AcademicYear* yr : *pPlan) {
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
				allCourses.push_back(*it);
			}
		}
	}
	for (Course* pCr : allCourses)
		pS->DeleteCourse(pCr);
	// Delete Notes
	pS->PlanNotes = "";

	//StudyPlan* pS = pReg->getStudyPlay();
	//vector<AcademicYear*>* pPlan = pS->getStudyPlanVector(); // pointer on the plan vector
	//for (AcademicYear* yr : *pPlan) {
	//	list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
	//	for (int sem = FALL; sem < SEM_CNT; sem++) {
	//		pYr[sem].clear();
	//	}
	//}
	//fill(Course::numOfCoursesPerSem.begin(), Course::numOfCoursesPerSem.end(), 0);
	//string directory = "Format Files\\StudyPlan-ENV.txt";
	//string directory = "D:\\College\\2_2020_Fall\\C++ - CIE 202\\Project\\SPOT\\SPOT\\Format Files\\StudyPlan-CIE.txt";

	// Start reading
	ifstream finput(directory);
	const int size = 300;
	char line[size];
	char* token; // pointer to char (tokens)
	char* context = nullptr; // used in strtok_s function as a context
	int i = 0; // for each line we have one course with index i

	while (finput.getline(line, size)) {
		vector<string> tokens;
		token = strtok_s(line, ",", &context);
		while (token != NULL) {
			tokens.push_back(token);
			token = strtok_s(NULL, ",", &context);
		}

		if (tokens[0] == pGUI->BREAK_LINE) {
			string nextLine;
			getline(finput, nextLine);
			if (nextLine == "Notes:") {
				// Read Notes
				string noteLine;
				while (noteLine != pGUI->BREAK_LINE) {
				getline(finput, noteLine);
				if (noteLine == pGUI->BREAK_LINE) break;
				pGUI->Notes = noteLine;
				if (pGUI->Notes == " ")
				{
					pReg->Not_Worth_Saving_Flag = true;
					return true;
				}
				pS->PlanNotes = pS->PlanNotes + " " + pGUI->Notes;
				pGUI->Notes = pS->PlanNotes;
				pGUI->NotesLines.clear();
				pGUI->SegmentNotes();
				pGUI->Total_Number_Pages_In_Notes = (pGUI->NotesLines.size() / ((pGUI->NotesHeight / 15) - 2));
				/*pGUI->NotesLines.push_back(noteLine);
				pS->PlanNotes += noteLine + " ";*/
				}
				break;
			}
		}

		// Get the year
		int year = stoi(tokens[0].erase(0, 5));
		// Get the semester
		SEMESTER sem;
		if (tokens[1][0] == 'F') sem = FALL;
		else if (tokens[1][0] == 'S' && tokens[1][1] == 'p') sem = SPRING;
		else sem = SUMMER;
		// remove first two tokens
		tokens.erase(tokens.begin(), tokens.begin() + 2);
		int iter = 0;
		for (string token : tokens) {
			// take the [] part out
			bool gradeTokenFlag = false;
				string Grade_And_Status;
			if (token.back() == ']') {
				size_t pos = token.find("[");
				Grade_And_Status = token.substr(pos);
				token = string(&token[0], &token[pos]);
				gradeTokenFlag = true;
			}
			bool exists;
			CourseInfo* pCInfo = pReg->inCatalog(token, exists);
			pCInfo = pReg->inCatalog(token, exists);
			if (exists) {
				StudyPlan* pS = pReg->getStudyPlay();
				string title = pCInfo->Title; 
				int crd = pCInfo->Credits; 
				vector<Course_Code> PreReq = pCInfo->PreReqList; 
				vector<Course_Code> CoReq = pCInfo->CoReqList; 
				Course* pC = new Course(token, title, crd, PreReq, CoReq, year, sem);
				if (gradeTokenFlag) {
					Grade_And_Status = Grade_And_Status.substr(1, Grade_And_Status.size() - 2);
					vector<string> GradeNStatusVector = splitString(Grade_And_Status, ":");
					pC->setStatus(GradeNStatusVector[0]);
					pC->setGrade(GradeNStatusVector[1]);
					// Wet Code Part :}
					if (pC->getCoursedone() == true)
					{
						pGUI->CourseStatus = "Course Status: Done";

					}
					else if (pC->getCourseinprogress() == true)
					{
						pGUI->CourseStatus = "Course Status: Inprogress";
					}
					else if (pC->getCoursepending() == true)
					{
						pGUI->CourseStatus = "Course Status: Pending ";
					}
					else if (pC->getCourseExempted() == true)
					{
						pGUI->CourseStatus = "Course Status: Exempted (Done) ";
					}
					else if (pC->getCourseReplaced() == true)
					{
						pGUI->CourseStatus = "Course Status: Replaced (Done) ";
					}
					else if (pC->getCourseCreditsTransfered() == true)
					{
						pGUI->CourseStatus = "Course Status: CreditsTransfered (Done) ";
					}
					else
					{
						pGUI->CourseStatus = "Course Status: Not Taken ";
					}
				}
				pC->Set_Type(pCInfo->type);
				pS->AddCourse(pC, year, static_cast<SEMESTER>(sem));
				int x = 0;
				int y = 0;
				graphicsInfo gInfo{ x, y };
				gInfo.x = gInfo.x = GUI::TitleBarWidth + (iter * CRS_WIDTH);
				gInfo.y = GUI::MenuBarHeight + GUI::MyFactor + ((year - 1) * GUI::One_Year_Div) + (sem * GUI::One_Semester_Div) +
					(GUI::MyFactor * (year - 1));
				pC->setGfxInfo(gInfo);
				iter++;
			}
			else {

				if (token[token.size() - 1] == 'X' && token[token.size() - 2] == 'X' && token[token.size() - 3] == 'X') {
				vector<Course_Code> PreReq;
				vector<Course_Code> CoReq;

				Course* pC = new Course(token, "", 0, PreReq, CoReq, year, sem);
				pS->AddCourse(pC, year, static_cast<SEMESTER>(sem));

					pC->changeColor(RED);
					pC->setUnknownCrs(true);
				int x = 0;
				int y = 0;
				graphicsInfo gInfo{ x, y };
				gInfo.x = gInfo.x = GUI::TitleBarWidth + (iter * CRS_WIDTH);
				gInfo.y = GUI::MenuBarHeight + GUI::MyFactor + ((year - 1) * GUI::One_Year_Div) + (sem * GUI::One_Semester_Div) +
					(GUI::MyFactor * (year - 1));
				pC->setGfxInfo(gInfo);
				iter++;
				}
				else {
					// Invalid course (Deal with it later)
				}
			}
		}
		i++;
	}
	finput.close();
	return true;
}



