
#include "ActionSavePlan.h"
#include "..\Registrar.h"
//#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include "../Utils/Utils.h"
using namespace std;

ActionSavePlan::ActionSavePlan(Registrar* p) : Action(p) {

}
ActionSavePlan::~ActionSavePlan() {
}

bool ActionSavePlan::Execute() {

	StudyPlan* pS = pReg->getStudyPlay(); //pointer to study plan
	GUI* pGUI = pReg->getGUI();
	const string BREAK_LINE = pGUI->BREAK_LINE;
	//pS->importProgramReq();
	cout << "Save button is pressed.\n"; //for debugging
	//importCourseRules();

	//// Save Live Report:
	//string directory1 = "Format Files\\Saved_Live_Report.txt";
	//ofstream liveFile;
	//liveFile.open(directory1);
	//for (string line : pGUI->ReportLines) {
	//	liveFile << line << endl;
	//}
	//liveFile.close();
	//// Save Notes
	//string directory2 = "Format Files\\Saved_Notes.txt";
	//ofstream noteFile;
	//noteFile.open(directory2);
	//for (string line : pGUI->NotesLines) {
	//	noteFile << line << endl;
	//}
	//noteFile.close();

	// Save Plan
	vector<AcademicYear*>* pPlan = pS->getStudyPlanVector(); // pointer on the plan vector
	string directory = SaveFileDialog();
	if (directory == "")
	{
		pReg->Not_Worth_Saving_Flag = true;
		return true; // User Cancels
	}
	// Handle .txt
	vector<string> fileTokens = splitString(directory,"\\");
	string filename = fileTokens.back();
	if (!(filename[filename.size() - 1] == 't' &&
		filename[filename.size() - 2] == 'x' &&
		filename[filename.size() - 3] == 't' &&
		filename[filename.size() - 4] == '.')) {
		directory += ".txt";
	}

	//string directory = "Format Files\\Saved_Plan.txt";

	ofstream outFile;
	outFile.open(directory);
	int numOfYear = 0;
	for (AcademicYear* yr : *pPlan) {
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			int numOfCoursesPreThisSemester = Course::numOfCoursesPerSem[(numOfYear * 3) + sem];
			if (numOfCoursesPreThisSemester != 0) {
				string str_semester = "UNKNOWN";
				switch (sem)
				{
				case FALL:
					str_semester = "Fall";
					break;
				case SPRING:
					str_semester = "Spring";
					break;
				case SUMMER:
					str_semester = "Summer";
					break;
				}
				outFile << "Year " << numOfYear + 1 << ","
					<< str_semester;
				for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
					if ((*it)->hasNoStatus()) {
						// No status
						string delim_comma = ",";
						outFile << delim_comma << (*it)->getCode();
						delim_comma = "";
					}
					else {
						// Has status
						string delim_comma = ",";
						outFile << delim_comma << (*it)->getCode()
							<< "[" << (*it)->getStatus() << ":" << (*it)->getGrade() << "]";
						delim_comma = "";
					}
				}
				outFile << "\n";
			}
		}
		numOfYear++;
	}

	// Save Notes
	outFile << BREAK_LINE;
	outFile << "\nNotes:\n";
	for (string line : pGUI->NotesLines) {
		outFile << line << endl;
	}

	// Save Report
	outFile << BREAK_LINE;
	outFile << "\nLive Report:\n";
	for (string line : pGUI->ReportLines) {
		outFile << line << endl;
	}

	outFile.close();
	cout << "Plan is saved in (" + directory + ") successfully.\n";

	return 1;
}

//void ActionSavePlan::importCourseRules() {
//	// To be implemented in RegRules later.
//	string directory = "Format Files\\Rules.txt";
//	ifstream finput(directory);
//	StudyPlan* pS = pReg->getStudyPlay();
//
//	//line 1
//	string l1;
//	getline(finput, l1);
//	pS->MaxCredits = stoi(l1);
//	cout << "Total Credits = " << pS->MaxCredits << endl;
//
//	//line 2
//	string l2;
//	getline(finput, l2);
//	vector<string> l2_tokens = splitString(l2, ",");
//	pS->TotalUnivCredits = stoi(l2_tokens[0]);
//	pS->TotalMajorCredits = stoi(l2_tokens[1]);
//	cout << "Univ Compulsory = " << pS->TotalUnivCredits << endl;
//	cout << "Univ Elective = " << pS->TotalMajorCredits << endl;
//
//	//line 3
//	string l3;
//	getline(finput, l3);
//	pS->TotalTrackCredits = stoi(l3);
//	cout << "Track Compulsory = " << pS->TotalTrackCredits << endl;
//
//	//line 4
//	string l4;
//	getline(finput, l4);
//	vector<string> l4_tokens = splitString(l4, ",");
//	pS->TotalConcentrationCredits = stoi(l4_tokens[0]);
//	pS->TotalMinorCredits = stoi(l4_tokens[1]);
//	cout << "Major Comm Compulsory = " << pS->TotalConcentrationCredits << endl;
//	cout << "Major comm Elec = " << pS->TotalMinorCredits << endl;
//
//	//line 5
//	string l5;
//	getline(finput, l5);
//	pS->NumberOfConcentrations = stoi(l5);
//	cout << "Number Of Concentrations = " << pS->NumberOfConcentrations << endl;
//
//	//line 6
//	string l6;
//	getline(finput, l6);
//	vector<string> l6_tokens = splitString(l6, ",");
//	pS->ConcentrationMajorCredits = stoi(l6_tokens[0]);
//	pS->ConcentrationMinorCredits = stoi(l6_tokens[1]);
//	cout << "Major Conc Compulsory = " << pS->ConcentrationMajorCredits << endl;
//	cout << "Major Conc Elec = " << pS->ConcentrationMinorCredits << endl;
//
//	//line 7
//	string l7;
//	getline(finput, l7);
//	pS->CompUniCourses = splitString(l7, ",");
//
//	//line 8
//	string l8;
//	getline(finput, l8);
//	pS->ElectiveUniCourses = splitString(l8, ",");
//
//	//line 9
//	string l9;
//	getline(finput, l9);
//	pS->TrackCourses = splitString(l9, ",");
//
//
//	//line 10
//	string l10;
//	getline(finput, l10);
//	pS->CompMajorCourses = splitString(l10, ",");
//
//
//	//line 11
//	string l11;
//	getline(finput, l11);
//	pS->ElectiveMajorCourses = splitString(l11, ",");
//
//	finput.close();
//}
