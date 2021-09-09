#include "StudyPlan.h"
#include"../GUI/GUI.h"
#include"string"
#include "../Rules.h"
#include "../Utils/Utils.h"
#include <fstream>
#include <iterator>
vector<string> StudyPlan::Minor_Course = {};
vector<string> StudyPlan::Double_Minor_Course = {};
int StudyPlan::Count = 0;
int StudyPlan::Count2 = 0;
bool StudyPlan::doubleMajorExists = false;
StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < GUI::NumOfYrs; i++)
		 plan.push_back(new AcademicYear);
}
//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	if (alreadyExistingCourse(pC->getCode(), sem, year) && pC->getCode()[pC->getCode().size() - 1] != 'X') {
		return false;
	}
	else {
		plan[year - 1]->AddCourse(pC, sem);
		TotalCredits += pC->getCredits();
		if (Minor_course_flag == true)
		{
			Minor_Course.push_back(pC->getCode());
			Minor_course_flag = false;
		}
		if (Double_Minor_course_flag == true)
		{
		 Double_Minor_Course.push_back(pC->getCode());
		 Double_Minor_course_flag == false;
		}
		setCourseTypeCredits(pC->getType(), 0, pC->getCredits(), pC->getCode());
		checkOffering(pC->getCode(), year - 1, sem);
		return true;
	}
}
bool StudyPlan::DeleteCourse(Course* pC) {
	plan[pC->getYear() - 1]->DeleteCourse(pC, pC->getSemester());
	TotalCredits -= pC->getCredits();
	setCourseTypeCredits(pC->getType(), 1, pC->getCredits(), pC->getCode());
	if (pC->Erased_Flag && pC->getType() == Minor)
	for (int i=0;i<Minor_Course.size();i++)
	{
		if (Minor_Course.at(i) == pC->getCode())
		{
			Minor_Course.erase(Minor_Course.begin() + i);
			pC->Erased_Flag = false;
			pC->Minor_Erased_Flag = true;
			Count--;
		}
	}
	//added part
	if (pC->Erased_Flag &&  pC->getType() == DoubleMinor)
		for (int i = 0; i < Double_Minor_Course.size(); i++)
		{
			if (Double_Minor_Course.at(i) == pC->getCode())
			{
				Double_Minor_Course.erase(Double_Minor_Course.begin() + i);
				pC->Erased_Flag = false;
				pC->Double_Minor_Erased_Flag = true;
				Count2--;
			}
		}
	// Delete the couurse offering error
	for (int i = 0; i < Course_Offering_Errors.size(); i++) 
		if (Course_Offering_Errors[i].Msg.find(pC->getCode()) != string::npos) {
			Course_Offering_Errors.erase(Course_Offering_Errors.begin() + i);
			break;
		}
	return true;
}
void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);
}
vector<AcademicYear*>* StudyPlan::getStudyPlanVector() {
	return &plan;
}
void StudyPlan::checkPreAndCoReq()
{
	// For each crs
	NOCPS.clear();
	Credits_Of_All_Sems.clear();
	int CrsTotalperSem = 0;
	for (AcademicYear* yr : plan) {
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			if (pYr[sem].size() != 0)
			{
				NOCPS.push_back(pYr[sem].size() - 1);
			}
			else
			{
				NOCPS.push_back(pYr[sem].size());
			}
			CrsTotalperSem = 0;
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
				// Iterate on courses
				Course* pCr = (*it);
				vector<string> preReq = pCr->getPreReq();
				vector<string> coReq = pCr->getCoReq();
				if (pCr->Minor_Erased_Flag)
					for (int i = 0; i < Minor_Course.size(); i++)
					{
						if (Minor_Course.at(i) == pCr->getCode())
						{
							pRules->TotalCHs += (pCr->getCredits());
							pCr->Erased_Flag = false;
							pCr->Minor_Erased_Flag = false;
							break;
						}
					}
				if (pCr->Double_Minor_Erased_Flag)
					for (int i = 0; i < Double_Minor_Course.size(); i++)
					{
						if (Double_Minor_Course.at(i) == pCr->getCode())
						{
							pRules->TotalCHs += (pCr->getCredits());
							pCr->Erased_Flag = false;
							pCr->Double_Minor_Erased_Flag = false;
							break;
						}
					}
				// Co req Check
				for (int i = 0; i < coReq.size(); i++) {
					// For each course in the coreq
					string co_crs = coReq[i];
					bool found = false;
					int currentYr = pCr->getYear() - 1;
					SEMESTER currentSem = pCr->getSemester();
					list<Course*>* pYr2 = plan[currentYr]->getListOfYears();
					for (auto iter = pYr2[currentSem].begin(); iter != pYr2[currentSem].end(); iter++) {
						if ((*iter)->getCode() == co_crs) {
							// FOUND IT
							found = true;
							break;
						}

					}
					// Repititon
					bool repeated = false;
					int currentYear = pCr->getYear() - 1; // its index not its number

					for (int j = currentYear; j >= 0; j--) {
						// check all the years including this year
						list<Course*>* pYr2 = plan[j]->getListOfYears(); // pointer to the year

						int semester_count;
						if (currentYear == j) {
							// in this case only loop on the number of semester
							if (pCr->getSemester() == 0)
								continue; // not to search in the same semester
							semester_count = pCr->getSemester() - 1;
						}
						else {
							// otherwise loop on all 3 semesters
							semester_count = 2;
						}

						for (int k = semester_count; k >= 0; k--) {
							// check all the semester above my semester
							for (auto iter = pYr2[k].begin(); iter != pYr2[k].end(); iter++) {
								if (pCr->repeatedCourse && (*iter)->getCode() == pCr->getCode() && (*iter)->getCoErrorsNumber() == 0) {
									repeated = true;
								}
							}
						}
					}
				

					if (found || repeated) {
						// Safe!
						pCr->removeCoReqErrors(co_crs);
					}
					else {
						// Critical error: (Prereq not found)
						string ErrorMsg = co_crs + " is a corequisite to " + pCr->getCode();
						cout << "ERR :: " << ErrorMsg << endl;
						pCr->AddCoError(CRITICAL, ErrorMsg);
					}
				}
				if (!coReq.empty()) {
					// This course has a coreq
					int err_num = pCr->getCoErrorsNumber(); // number of errors
					int co_num = coReq.size(); // number of prerequisite courses
					if (err_num == 0)
						pCr->changeBorderColor(BLACK);
					else
						pCr->changeBorderColor(GREEN);

				}
				
				//============================================================================
				
				// Pre req Check
				for (int i = 0; i < preReq.size(); i++) {
					// For each course in the prereq
					string pre_crs = preReq[i];
					bool found = false;
					int currentYear = pCr->getYear() - 1; // its index not its number

					for (int j = currentYear; j >= 0; j--) {
						// check all the years including this year
						list<Course*>* pYr2 = plan[j]->getListOfYears(); // pointer to the year

						int semester_count;
						if (currentYear == j) {
							// in this case only loop on the number of semester
							if (pCr->getSemester() == 0)
								continue; // not to search in the same semester
							semester_count = pCr->getSemester() - 1;
						}
						else {
							// otherwise loop on all 3 semesters
							semester_count = 2;
						}

						for (int k = semester_count; k >= 0; k--) {
							// check all the semester above my semester
							for (auto iter = pYr2[k].begin(); iter != pYr2[k].end(); iter++) {
								if ((*iter)->getCode() == pre_crs) {
									// FOUND IT
									found = true;
									break;
								}
								
							}
							if (found) break;
						}
						if (found) break;
					}

					if (found) {
						// Safe!
						
						pCr->removePreReqErrors(pre_crs);
					}
					else {
						// Critical error: (Prereq not found)
						string ErrorMsg = pre_crs + " is a prerequisite to " + pCr->getCode();
						pCr->AddPreError(CRITICAL, ErrorMsg);
						//cout << "ERROR :: " <<ErrorMsg << endl;
						//cout << "Number of errors = " << pCr->getPreErrorsNumber() << endl;
					}

				}
				if (!preReq.empty()) {
					// This course has a prerequisites
					int err_num = pCr->getPreErrorsNumber(); // number of errors
					int pre_num = preReq.size(); // neber of prerequisite courses
					if (err_num == 0)
						pCr->changeBorderColor(BLACK);
					else 
						pCr->changeBorderColor(RED);

				}
				CrsTotalperSem += (*it)->getCredits();
			}
			Credits_Of_All_Sems.push_back(CrsTotalperSem);
		}
	}
}
void StudyPlan::checkCreditHrs(int min, int max)
{
	// For each semester, check if total courses chs are between the range of min n max where min and max are constants from RegRules
	//for (AcademicYear* yr : plan)
	for (int a = 0; a < plan.size(); a++) {
		AcademicYear* yr = plan[a];
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT - 1; sem++) {
			int semCHs = 0; // semester CHs
			string semName;
			int yearNum = a+1;
			switch (sem) {
			case 0: semName = "Fall"; break;
			case 1: semName = "Spring"; break;
			case 2: semName = "Summer"; break;
			}
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
				semCHs += (*it)->getCredits();
				yearNum = (*it)->getYear();
			}
			// If the error does not exist create an error
			bool exists = false;
			string checkMsg = semName + " of year " + to_string(yearNum);
			for (int i = 0; i < CH_Error_List.size(); i++) {
				bool condition = CH_Error_List[i].Msg.find(checkMsg) != string::npos;
				if (condition) {
					exists = true;
				}
			}
			if (semCHs < min) {
				if (!exists) {
					// Error less than
					string errMsg = semName + " of year " + to_string(yearNum) + " has CH's ("+ to_string(semCHs) + ") less than " + to_string(min);
					Error newErr;
					newErr.type = MODERATE;
					newErr.Msg = errMsg;
					Sem_Credits.push_back(semCHs);
					CH_Error_List.push_back(newErr);
				}
				else {
					// Modify its message
					string newErrMsg = semName + " of year " + to_string(yearNum) + " has CH's (" + to_string(semCHs) + ") less than " + to_string(min);
					string checkMsg = semName + " of year " + to_string(yearNum);
					for (int i = 0; i < CH_Error_List.size(); i++) {
						bool condition = CH_Error_List[i].Msg.find(checkMsg) != string::npos;
						if (condition) {
							CH_Error_List[i].Msg = newErrMsg;
						}
					}
				}
			}
			else if (semCHs > max) {
				if (!exists) {
					// Error more than
					string errMsg = semName + " of year " + to_string(yearNum) + " has CH's (" + to_string(semCHs) + ")  more than " + to_string(max);
					Error newErr;
					newErr.type = MODERATE;
					newErr.Msg = errMsg;
					CH_Error_List.push_back(newErr);
					Sem_Credits.push_back(semCHs);
				}
				else {
					// Modify its message
					string newErrMsg = semName + " of year " + to_string(yearNum) + " has CH's (" + to_string(semCHs) + ") more than " + to_string(max);
					string checkMsg = semName + " of year " + to_string(yearNum);
					for (int i = 0; i < CH_Error_List.size(); i++) {
						bool condition = CH_Error_List[i].Msg.find(checkMsg) != string::npos;
						if (condition) {
							CH_Error_List[i].Msg = newErrMsg;
						}
					}
				}
			}
			else {
				// No err (REMOVE IT)
				string checkMsg = semName + " of year " + to_string(yearNum);
				for (int i = 0; i < CH_Error_List.size(); i++) {
					bool condition = CH_Error_List[i].Msg.find(checkMsg) != string::npos;
					if (condition) {
						CH_Error_List.erase(CH_Error_List.begin() + i);
					}
				}
				

			}
		}
	}
}
void StudyPlan::FindPreAndCoReq_ITCSP(Course* pC, GUI* pGUI)
{
	vector<string>CoReq = pC->getCoReq();
	vector<string>PreReq = pC->getPreReq();
	string Code;
	if(!((CoReq.empty())&&(PreReq.empty())))
	for (AcademicYear* yr : plan)
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				if (!((CoReq.size()) == 0))
				for (int i = 0; i < CoReq.size(); i++)
				{
					if (((*it)->getCode() == CoReq[i]) && ((*it) != NULL) && (!(*it)->Cant_Touch_This_Flag) && ((*it)->DrawMe_Flag))
					{
						pGUI->pWind->SetBrush(RED);
						pGUI->pWind->SetPen(RED,2);
						pGUI->DrawCourse_Dependacies((*it), pC);
						break;
				    }
				}
				if (!((PreReq.size())==0))
				for (int i = 0; i < PreReq.size(); i++)
				{
					Code = (*it)->getCode();
					if ((Code == PreReq[i]) && ((*it) != NULL) && (!(*it)->Cant_Touch_This_Flag) && ((*it)->DrawMe_Flag))
					{
						pGUI->pWind->SetBrush(BLUE);
						pGUI->pWind->SetPen(BLUE,2);
						pGUI->DrawCourse_Dependacies((*it), pC);
						break;
					}
				}
			}
		}
	}
}
void StudyPlan::FindPreAndCoReq_ITCSP_Tree(Course* pC, GUI* pGUI)
{
	vector<string>CoReq = pC->getCoReq();
	vector<string>PreReq = pC->getPreReq();
	string Code;
	AllCourseCodeForTree.push_back(pC->getCode());
	if (!((CoReq.empty()) && (PreReq.empty())))
		for (AcademicYear* yr : plan)
		{
			list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
				{
					//if (!((CoReq.size()) == 0))
					//{
					//	for (int i = 0; i < CoReq.size(); i++)
					//	{
					//		if (((*it)->getCode() == CoReq[i]) && ((*it) != NULL) && (!(*it)->Cant_Touch_This_Flag) && ((*it)->DrawMe_Flag))
					//		{
					//			pGUI->pWind->SetBrush(RED);
					//			pGUI->pWind->SetPen(RED, 2);
					//			pGUI->DrawCourse_Dependacies((*it), pC);
					//			AllCourseCodeForTree.push_back((*it)->getCode());
					//			break;
					//		}
					//	}
					//	
					//}
					if (!((PreReq.size()) == 0))
					{
						for (int i = 0; i < PreReq.size(); i++)
						{
							Code = (*it)->getCode();
							if ((Code == PreReq[i]) && ((*it) != NULL) && (!(*it)->Cant_Touch_This_Flag) && ((*it)->DrawMe_Flag))
							{

								pGUI->pWind->SetBrush(BLUE);
								pGUI->pWind->SetPen(BLUE, 2);
								pGUI->DrawCourse_Dependacies((*it), pC);
								AllCourseCodeForTree.push_back((*it)->getCode());
								break;
							}

						}
					
					}
				}
			}
		}
}
void StudyPlan::TreeFiltering()
{
	string Code;
		for (AcademicYear* yr : plan)
		{
			list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
				{
					Code = (*it)->getCode();
					(*it)->DrawMe_Flag = false;
				      for (int i = 0; i < AllCourseCodeForTree.size(); i++)
				      {

					     if (Code == AllCourseCodeForTree[i])
					     {
							 (*it)->DrawMe_Flag = true;
						    break;
					     }
				      }
				}
			}
		}
}
void StudyPlan::TreeUnFiltering()
{
	for (AcademicYear* yr : plan)
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
						(*it)->DrawMe_Flag = true;
			}
		}
	}
}
void StudyPlan::SetTree(vector<Course*> VectorTree)
{
	TreeVector = VectorTree;
}
vector<Course*> StudyPlan::FindPre_ITCSP(Course* pC)
{
	TreeVector.push_back(pC);
	{
		vector<string>PreReq = pC->getPreReq();
		TreeVector.push_back(pC);
		string Code= pC->getCode();
		{
			for (AcademicYear* yr : plan)
			{
				list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
				for (int sem = FALL; sem < SEM_CNT; sem++)
				{
					for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
					{
						PreReq = (*it)->getPreReq();
						if (!((PreReq.size()) == 0))
							for (int i = 0; i < PreReq.size(); i++)
							{
								if ((Code == PreReq[i]) && ((*it) != NULL) && (!(*it)->Cant_Touch_This_Flag) && ((*it)->DrawMe_Flag))
								{
									FindPre_ITCSP((*it));
								}
							}
					}
				}
			}
			return TreeVector;
		}
	}
}
void StudyPlan::ClearTree()
{
	TreeVector.clear();
}
void StudyPlan::ACCFT()
{
	AllCourseCodeForTree.clear();
}
vector<Course*> StudyPlan::Gettree()
{
	return TreeVector;
}
void StudyPlan::checkProgramReq()
{
	// 1) CH checks
	// Check TotalCredits
	string errMsg = "The total CHs (" + to_string(TotalCredits) + ") are less than " + to_string(pRules->TotalCHs);
	string checkMsg = "The total CHs";
	lazyCheck(TotalCredits, pRules->TotalCHs, errMsg, checkMsg);
	
	// Check TotalMajorCredits
	errMsg = "The total major CHs (" + to_string(TotalMajorCredits) + ") are less than " + to_string(pRules->ReqMajorCredits);
	checkMsg = "The total major CHs";
	lazyCheck(TotalMajorCredits, pRules->ReqMajorCredits, errMsg, checkMsg);

	// Check TotalTrackCredits
	errMsg = "The total track CHs (" + to_string(TotalTrackCredits) + ") are less than " + to_string(pRules->ReqTrackCredits);
	checkMsg = "The total track CHs";
	lazyCheck(TotalTrackCredits, pRules->ReqTrackCredits, errMsg, checkMsg);

	// Check TotalUnivCredits
	errMsg = "The total univ CHs (" + to_string(TotalUnivCredits) + ") are less than " + to_string(pRules->ReqUnivCredits);
	checkMsg = "The total univ CHs";
	lazyCheck(TotalUnivCredits, pRules->ReqUnivCredits, errMsg, checkMsg);

	// Check TotalUnivCredits
	errMsg = "The total concentration CHs (" + to_string(TotalUnivCredits) + ") are less than " + to_string(pRules->ReqUnivCredits);
	checkMsg = "The total concentration CHs";
	int ReqConcentrationCredits = 0;
	if (concentrationNumber > 0) {
		// First we need to remove the No Concentrencration error if exists :)
		string concMsg = "No concentration is selected yet!";
		for (int i = 0; i < Program_Req_Errors.size(); i++) {
			if (Program_Req_Errors[i].Msg.find(concMsg) != string::npos)
				Program_Req_Errors.erase(Program_Req_Errors.begin() + i);
		}

		// Then check for the concentration requirements
		ReqConcentrationCredits += pRules->Concentrations[concentrationNumber - 1].CompulsoryCredits;
		ReqConcentrationCredits += pRules->Concentrations[concentrationNumber - 1].ElectiveCredits;
		lazyCheck(TotalConcentrationCredits, ReqConcentrationCredits, errMsg, checkMsg);
	}
	else {
		// No concentration is selected! the user should select one!
		errMsg = "No concentration is selected yet!";
		// Check if this error already exists
		bool exists = false;
		for (int i = 0; i < Program_Req_Errors.size(); i++) {
			if (Program_Req_Errors[i].Msg.find(errMsg) != string::npos) {
				exists = true;
			}
		}
		if (!exists) {
			// The error does not exist so create it !
			/*Error err;
			err.Msg = errMsg;
			err.type = CRITICAL;
			Program_Req_Errors.push_back(err);*/
		}
	}

	// 2) Courses missing
	string checkKeyword = "Uni Compulsory.";
	lazyCheck2(checkKeyword, pRules->UnivCompulsoryCourses);
	
	string checkKeyword2 = "Track Compulsory.";
	doubleMajorExists ? lazyCheck2(checkKeyword2, pRules->CheckDoubleTrackCourses) : lazyCheck2(checkKeyword2, pRules->TrackCompulsoryCourses);
	
	string checkKeyword3 = "Major Compulsory.";
	doubleMajorExists ? lazyCheck2(checkKeyword3, pRules->CheckDoubleMajorCompCourses) : lazyCheck2(checkKeyword3, pRules->MajorCompulsoryCourses);

	// 3) Check Unknown Crs
	string errMsgAgain = "Change the code of XXX elective courses.";
	bool Unknowns = false;
	for (AcademicYear* yr : plan)
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				if ((*it)->getUnknownCrs()) {
					Unknowns = true;
					break;
				}
				if (Unknowns) break;
			}
			if (Unknowns) break;
		}
		if (Unknowns) break;
	}
	if (Unknowns) {
		//Add the error if not exist
		bool there = false;
		for (int i = 0; i < Program_Req_Errors.size(); i++) {
			if (Program_Req_Errors[i].Msg.find(errMsgAgain) != string::npos)
				there = true;
		}
		if (!there) {
			Error err;
			err.Msg = errMsgAgain;
			err.type = CRITICAL;
			Program_Req_Errors.push_back(err);
		}
	}
	else {
		for (int i = 0; i < Program_Req_Errors.size(); i++) {
			if (Program_Req_Errors[i].Msg.find(errMsgAgain) != string::npos)
				Program_Req_Errors.erase(Program_Req_Errors.begin() + i);
		}
	}

}

void StudyPlan::lazyCheck(int compared, int original, string errMsg, string checkMsg) {
	if (compared < original) {
		// Check if already exists. If so modify its message!
		bool exists = false;
		for (int i = 0; i < Program_Req_Errors.size(); i++) {
			if (Program_Req_Errors[i].Msg.find(checkMsg) != string::npos) {
				exists = true;
				Program_Req_Errors[i].Msg = errMsg; // modify
			}
		}
		if (!exists) {
			// The error does not exist so create it !
			Error err;
			err.Msg = errMsg;
			err.type = CRITICAL;
			Program_Req_Errors.push_back(err);
		}
	}
	else {
		// Does not exist at all!
		for (int i = 0; i < Program_Req_Errors.size(); i++) {
			if (Program_Req_Errors[i].Msg.find(checkMsg) != string::npos)
				Program_Req_Errors.erase(Program_Req_Errors.begin() + i);
		}

	}
}
void StudyPlan::lazyCheck2(string checkKeyword, vector<string> vect)
{
	for (string code : vect) {
		bool exists = false;
		for (AcademicYear* yr : plan)
		{
			list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
				{
					if ((*it)->getCode() == code) {
						exists = true;
						break;
					}
				}
				if (exists) break;
			}
			if (exists) break;
		}
		string newerrMsg = "Missing " + code + " " + checkKeyword;
		if (exists) {
			//Remove error
			for (int i = 0; i < Program_Req_Errors.size(); i++) {
				if (Program_Req_Errors[i].Msg.find(newerrMsg) != string::npos)
					Program_Req_Errors.erase(Program_Req_Errors.begin() + i);
			}
		}
		else {
			// Add it if not there
			bool there = false;
			for (int i = 0; i < Program_Req_Errors.size(); i++) {
				if (Program_Req_Errors[i].Msg.find(newerrMsg) != string::npos)
					there = true;
			}
			if (!there) {
				Error err;
				err.Msg = newerrMsg;
				err.type = CRITICAL;
				Program_Req_Errors.push_back(err);
			}
		}
	}
}
void StudyPlan::checkOffering(string code, int crsYear, SEMESTER sem)
{
	int currentYearNum = 0;
	if (currentYear.empty()) {
		// The user hasen't declared an offering 
		currentYearAvailable = false;
		string errMsg = "Please choose the current year.";
		Error err;
		err.Msg = errMsg;
		err.type = CRITICAL;
		Course_Offering_Errors.push_back(err);
	} 
	else {
		currentYearAvailable = true;
		// First: remove the "Please choose the current year." error
		for (int i = 0; i < Course_Offering_Errors.size(); i++) {
			if (Course_Offering_Errors[i].Msg.find("Please choose the current year.") != string::npos)
				Course_Offering_Errors.erase(Course_Offering_Errors.begin() + i);
		}

		// Then : Check each course
		int index = 0; // default value = 0
		for (int i = 0; i < pRules->OffringsList.size(); i++) {
			if (pRules->OffringsList[i].Year == currentYear) {
				index = i;
				break;
			}
		}
		if (pRules->OffringsList.size() > index + crsYear) {


			vector<Course_Code> crss = (pRules->OffringsList[index + crsYear].Offerings)[sem];
			bool exists = false;
			for (Course_Code c : crss) {
				if (c == code) {
					exists = true;
					break;
				}
			}

			if (!exists) {
				// The current course isnt offered this year!
				Error err;
				string semName;
				switch (sem)
				{
				case FALL:
					semName = "fall";
					break;
				case SPRING:
					semName = "spring";
					break;
				case SUMMER:
					semName = "summer";
					break;
				default:
					semName = "NaN";
					break;
				}
				// This index exists
				string errMsg = code + " isn't offered in " + pRules->OffringsList[index + crsYear].Year
					+ "'s " + semName;
				err.Msg = errMsg;
				err.type = MODERATE;
				Course_Offering_Errors.push_back(err);

			}
		}
		else
			cout << "This year is not incluided in the offering files!" << endl;
			
	}

}
void StudyPlan::setMajor(Major major)
{
	this->major = major;
	majorChanged = true;
	setDoubleMajorExists(false);
}

void StudyPlan::setconcentrationNumber(int concentration)
{
	concentrationNumber = concentration;
}
void StudyPlan::setDoubleconcentrationNumber(int n)
{
	DoubleconcentrationNumber = n;
}
int StudyPlan::getConcentration() const
{
	return concentrationNumber;
}
int StudyPlan::getDoubleConcentration() const
{
	return DoubleconcentrationNumber;
}
Major StudyPlan::getMajor() const
{
	return major;
}
void  StudyPlan::setCourseTypeCredits(Type type, int mode, int hours, string code)
{
	// Code for elective detection
	// If mode is 0 => Add Course 
	// If mode is 1 => Delete Course 
	switch (type)
	{
	case maj:
		(mode == 0) ? TotalMajorCredits += hours : TotalMajorCredits -= hours;
		break;
	case Elective:
		if (code[0] == 'S' && code[1] == 'C' && code[2] == 'H') {
			(mode == 0) ? TotalUnivCredits += hours : TotalUnivCredits -= hours;
		}
		else {
			(mode == 0) ? TotalMajorCredits += hours : TotalMajorCredits -= hours;
		}
		(mode == 0) ? TotalElectiveCredits += hours : TotalElectiveCredits -= hours;
		break;
	case Minor:
		(mode == 0) ? TotalMinorCredits += hours : TotalMinorCredits -= hours;
		break;
	case concentration:
		(mode == 0) ? TotalConcentrationCredits += hours : TotalConcentrationCredits -= hours;
		break;
	case Track:
		(mode == 0) ? TotalTrackCredits += hours : TotalTrackCredits -= hours;
		break;
	case Uni:
		(mode == 0) ? TotalUnivCredits += hours : TotalUnivCredits -= hours;
		break;
	case NOTYPE:
		break;
	default:
		break;
	}
}
void  StudyPlan::LiveReport(GUI* pGUI, int Min_Crs, int Max_Crs)
{
	int Co_Error_Number, Pre_Error_Number;
	vector<Error> Co_Errors; 
	vector<Error> Pre_Errors;
	Set_Report_Lines();
	pGUI->setReport_Start(-1);
	pGUI->setReport_Stop(11);
	for (AcademicYear* yr : plan)
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				Co_Error_Number=(*it)->getCoErrorsNumber();
				Pre_Error_Number=(*it)->getPreErrorsNumber();
				if (Co_Error_Number != 0)
				{
					Co_Errors = (*it)->getCoReqErrors();
					for (int i = 0; i < Co_Errors.size(); i++)
					{
						pGUI->AddCriticalErrorLines(Co_Errors[i]);
						increment_Report_Lines(2);
					}

				}
				else if (Pre_Error_Number != 0)
				{
					Pre_Errors = (*it)->getPreReqErrors();
					for (int i = 0; i < Pre_Errors.size(); i++)
					{
						pGUI->AddCriticalErrorLines(Pre_Errors[i]);
						increment_Report_Lines(2);
					}
				}
			}
		}
	}

	for (int i = 0; i < Program_Req_Errors.size(); i++)
	{
		pGUI->AddCriticalErrorLines(Program_Req_Errors[i]);
		increment_Report_Lines(2);
	}

	for (int i = 0; i < Course_Offering_Errors.size(); i++)
	{
		pGUI->AddModerateErrorLines(Course_Offering_Errors[i]);
		increment_Report_Lines(2);
	}

	for (int i = 0; i < CH_Error_List.size(); i++)
	{
		pGUI->AddModerateErrorLines(CH_Error_List[i], Sem_Credits[i], Min_Crs, Max_Crs);
		increment_Report_Lines(3);
	}
	Set_Page_Number((pGUI->Y_div/45)-2);
	pGUI->Total_Number_Pages_In_Report = (Get_Page_Number());
}
void  StudyPlan::GenerateStudentLevel(GUI* pGUI)
{
	//loop over the whole study plan, if the course is done and a token created in course class is true..... set the token to true,and increment total done hours with course credits
	// the function of this token is to prevent the ddition of coursee credits multiple times as this function is caled in the while loop in side the registrar
	for (AcademicYear* yr : plan) {
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
				// Iterate on courses
				Course* pCr = (*it);
				if (pCr->getCoursedone() == true && pCr->getToken()==false)
				{
					pCr->setToken(true);
					int credits = pCr->getCredits();
					TotalDoneHours = TotalDoneHours + credits;

				}
			}
		}
	}
	//checks on the student, to set the level
	if (TotalDoneHours <= 32)
	{
		StudentLevel = "Foundation";
	}
	else if (TotalDoneHours<=67 && TotalDoneHours >= 32)
	{
		StudentLevel = "Sophomore";
	}
	else if (TotalDoneHours <=101 && TotalDoneHours >= 67)
	{
		StudentLevel = "Junior";
	}
	else if (TotalDoneHours <=135 && TotalDoneHours >= 101)
	{
		StudentLevel = "SeniorI";
	}
	else if (TotalDoneHours <= 162 && TotalDoneHours >= 135)
	{
		StudentLevel = "SeniorII";
	}
	//pGUI->studentLevel = StudentLevel;
	//cout << TotalDoneHours << endl;//debugging 
	//cout << StudentLevel << endl;//debugging 
	//cout << TotalDoneHours << endl;//debugging 
	//cout << "Generate student level called"<<endl;//debugging
	
	//pass the student level to the GUI
	pGUI->Student_Level =StudentLevel;
	string str = to_string(TotalDoneHours);//convert int to string and pass it the the GUI
	pGUI->Done_Credits = str;
}
int   StudyPlan::Get_Page_Number()const
{
	return No_Of_Pages;
}
void  StudyPlan::increment_Report_Lines(int Number_Of_Inc)
{
	Report_Lines += Number_Of_Inc;
}
int   StudyPlan::get_Report_Lines()const
{
	return Report_Lines;
}
void  StudyPlan::Set_Report_Lines()
{
	Report_Lines = 0;
}
void  StudyPlan::Set_Course_Type()
{
	string Code = "";
	for (AcademicYear* yr : plan)
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				Code = (*it)->getCode();
				(*it)->Set_Type(NOTYPE);
				if (!doubleMajorExists) {
					for (int i = 0; i < pRules->UnivCompulsoryCourses.size(); i++)
					{
						if (Code == pRules->UnivCompulsoryCourses[i])
						{

							if (Code == pRules->UnivCompulsoryCourses[i])
							{
								(*it)->Set_Type(Uni);
								if ((*it)->getColor() == BLACK)
								{
									break;
								}
								(*it)->changeColor(SLATEGREY);
								break;
							}
						}
					}
					for (int i = 0; i < pRules->UnivElectiveCourses.size(); i++)
					{
						if (Code == pRules->UnivElectiveCourses[i])
						{
							if (Code == pRules->UnivElectiveCourses[i])
							{
								(*it)->Set_Type(Elective);
								if ((*it)->getColor() == BLACK)
								{
									break;
								}
								(*it)->changeColor(FIREBRICK);
								break;
							}
						}
					}
					for (int i = 0; i < pRules->TrackCompulsoryCourses.size(); i++)
					{
						if (Code == pRules->TrackCompulsoryCourses[i])
						{
							if (Code == pRules->TrackCompulsoryCourses[i])
							{
								(*it)->Set_Type(Track);
								if ((*it)->getColor() == BLACK)
								{
									break;
								}
								(*it)->changeColor(DARKGREEN);
								break;
							}
						}
					}
					for (int i = 0; i < pRules->MajorCompulsoryCourses.size(); i++)
					{
						if (Code == pRules->MajorCompulsoryCourses[i])
						{
							if (Code == pRules->MajorCompulsoryCourses[i])
							{
								(*it)->Set_Type(maj);
								if ((*it)->getColor() == BLACK)
								{
									break;
								}
								(*it)->changeColor(GOLDENROD);
								break;
							}
						}
					}
					for (int i = 0; i < pRules->MajorElectiveCourses.size(); i++)
					{
						if (Code == pRules->MajorElectiveCourses[i])
						{
							if (Code == pRules->MajorElectiveCourses[i])
							{
								(*it)->Set_Type(Elective);
								if ((*it)->getColor() == BLACK)
								{
									break;
								}
								(*it)->changeColor(FIREBRICK);
								break;
							}
						}
						if (pRules->NumOfConcentrations != 0)
						{
							for (int i = 0; i < pRules->Concentrations[0].ConcentrationCompulsoryCourses.size(); i++)
							{
								if (Code == pRules->Concentrations[0].ConcentrationCompulsoryCourses[i])
								{
									(*it)->Set_Type(concentration);
									if ((*it)->getColor() == BLACK)
									{
										break;
									}
									(*it)->changeColor(DARKMAGENTA);
									break;
								}
							}
							for (int i = 0; i < pRules->Concentrations[0].ConcentrationElectiveCourses.size(); i++)
							{
								if (Code == pRules->Concentrations[0].ConcentrationElectiveCourses[i])
								{
									(*it)->Set_Type(Elective);
									if ((*it)->getColor() == BLACK)
									{
										break;
									}
									(*it)->changeColor(FIREBRICK);
									break;
								}
							}
						}
					}
					//for (int i = 0; i < pRules->Concentrations[0].ConcentrationCompulsoryCourses.size(); i++)
					//{
					//	if (Code == pRules->Concentrations[0].ConcentrationCompulsoryCourses[i])
					//	{
					//		(*it)->Set_Type(concentration);
					//		break;
					//	}
					//}
					//for (int i = 0; i < pRules->Concentrations[0].ConcentrationElectiveCourses.size(); i++)
					//{
					//	if (Code == pRules->Concentrations[0].ConcentrationElectiveCourses[i])
					//	{
					//		(*it)->Set_Type(Elective);
					//		break;
					//	}
					//}
					for (int i = 0; i < Minor_Course.size(); i++)
					{
						if (Code == Minor_Course[i])
						{
							(*it)->Set_Type(Minor);
							if ((*it)->getColor() == BLACK)
							{
								break;
							}
							(*it)->changeColor(ORANGERED);
							break;
						}
					}
					//added
					for (int i = 0; i < Double_Minor_Course.size(); i++)
					{
						if (Code == Double_Minor_Course[i])
						{
							(*it)->Set_Type(DoubleMinor);
							if ((*it)->getColor() == BLACK)
							{
								break;
							}
							(*it)->changeColor(YELLOWGREEN);
							break;
						}
					}
				}
				else {
				for (int i = 0; i < pRules->UnivCompulsoryCourses.size(); i++)
				{
					if (Code == pRules->UnivCompulsoryCourses[i])
					{

						if (Code == pRules->UnivCompulsoryCourses[i])
						{
							(*it)->Set_Type(Uni);
							if ((*it)->getColor() == BLACK)
							{
								break;
							}
							(*it)->changeColor(SLATEGREY);
							break;
						}
					}
				}
				for (int i = 0; i < pRules->UnivElectiveCourses.size(); i++)
				{
					if (Code == pRules->UnivElectiveCourses[i])
					{
						if (Code == pRules->UnivElectiveCourses[i])
						{
							(*it)->Set_Type(Elective);
							if ((*it)->getColor() == BLACK)
							{
								break;
							}
							(*it)->changeColor(FIREBRICK);
							break;
						}
					}
				}
				for (int i = 0; i < pRules->CheckDoubleTrackCourses.size(); i++)
				{
					if (Code == pRules->CheckDoubleTrackCourses[i])
					{
						if (Code == pRules->CheckDoubleTrackCourses[i])
						{
							(*it)->Set_Type(Track);
							if ((*it)->getColor() == BLACK)
							{
								break;
							}
							(*it)->changeColor(DARKGREEN);
							break;
						}
					}
				}
				for (int i = 0; i < pRules->CheckDoubleMajorCompCourses.size(); i++)
				{
					if (Code == pRules->CheckDoubleMajorCompCourses[i])
					{
						if (Code == pRules->CheckDoubleMajorCompCourses[i])
						{
							(*it)->Set_Type(maj);
							if ((*it)->getColor() == BLACK)
							{
								break;
							}
							(*it)->changeColor(GOLDENROD);
							break;
						}
					}
				}
				for (int i = 0; i < pRules->CheckDoubleMajorElectiveCourses.size(); i++)
				{
					if (Code == pRules->CheckDoubleMajorElectiveCourses[i])
					{
						if (Code == pRules->CheckDoubleMajorElectiveCourses[i])
						{
							(*it)->Set_Type(Elective);
							if ((*it)->getColor() == BLACK)
							{
								break;
							}
							(*it)->changeColor(FIREBRICK);
							break;
						}
					}
					if (pRules->NumOfConcentrations != 0)
					{
						for (int i = 0; i < pRules->Concentrations[0].ConcentrationCompulsoryCourses.size(); i++)
						{
							if (Code == pRules->Concentrations[0].ConcentrationCompulsoryCourses[i])
							{
								(*it)->Set_Type(concentration);
								if ((*it)->getColor() == BLACK)
								{
									break;
								}
								(*it)->changeColor(DARKMAGENTA);
								break;
							}
						}
						for (int i = 0; i < pRules->Concentrations[0].ConcentrationElectiveCourses.size(); i++)
						{
							if (Code == pRules->Concentrations[0].ConcentrationElectiveCourses[i])
							{
								(*it)->Set_Type(Elective);
								if ((*it)->getColor() == BLACK)
								{
									break;
								}
								(*it)->changeColor(FIREBRICK);
								break;
							}
						}
					}
				}
				//for (int i = 0; i < pRules->Concentrations[0].ConcentrationCompulsoryCourses.size(); i++)
				//{
				//	if (Code == pRules->Concentrations[0].ConcentrationCompulsoryCourses[i])
				//	{
				//		(*it)->Set_Type(concentration);
				//		break;
				//	}
				//}
				//for (int i = 0; i < pRules->Concentrations[0].ConcentrationElectiveCourses.size(); i++)
				//{
				//	if (Code == pRules->Concentrations[0].ConcentrationElectiveCourses[i])
				//	{
				//		(*it)->Set_Type(Elective);
				//		break;
				//	}
				//}
				//---------------------------------------Repeated Code--------------------------------------------//
			/*	for (int i = 0; i < Minor_Course.size(); i++)
				{
					if (Code == Minor_Course[i])
					{
						(*it)->Set_Type(Minor);
						if ((*it)->getColor() == BLACK)
						{
							break;
						}
						(*it)->changeColor(ORANGERED);
						break;
					}
				}*/
				//------------------------------------------------------------------------------------------------//
				}
				
			}
	}
}

void  StudyPlan::Set_Page_Number( int Number_Of_lines)
{
	No_Of_Pages=Report_Lines/ Number_Of_lines;
}
vector<int> StudyPlan::get_Sem_Credits()const
{
	return Sem_Credits;
}
vector<int> StudyPlan::get_Of_All_Sems_Credits()const
{
	return Credits_Of_All_Sems;
}
void StudyPlan::Set_Plan_Rules(Rules &RegRules)
{
	pRules = &RegRules;
}
StudyPlan::StudyPlan(const StudyPlan& CopiedSP):Drawable()
{
	PlanNotes = CopiedSP.PlanNotes;
	Report_Lines = CopiedSP.Report_Lines;
	No_Of_Pages = CopiedSP.No_Of_Pages;
	TotalDoneHours = CopiedSP.TotalDoneHours;
	ConcentrationMinorCredits = CopiedSP.ConcentrationMinorCredits;
	ConcentrationMajorCredits = CopiedSP.ConcentrationMajorCredits;
	NumberOfConcentrations = CopiedSP.NumberOfConcentrations;
	MaxCredits = CopiedSP.MaxCredits;
	TotalMinorCredits = CopiedSP.TotalMinorCredits;
	TotalDoubleMinorCredits = CopiedSP.TotalDoubleMinorCredits;
	TotalConcentrationCredits = CopiedSP.TotalConcentrationCredits;
	TotalTrackCredits = CopiedSP.TotalTrackCredits;
	TotalMajorCredits = CopiedSP.TotalMajorCredits;
	TotalUnivCredits = CopiedSP.TotalUnivCredits;
	TotalCredits = CopiedSP.TotalCredits;
	StudentLevel = CopiedSP.StudentLevel;
	major = CopiedSP.major;
	pRules = CopiedSP.pRules;
	for (int i = 0; i < CopiedSP.Sem_Credits.size(); i++)
	{
		Sem_Credits.push_back(CopiedSP.Sem_Credits[i]);
	}
	for (int i = 0; i < CopiedSP.CH_Error_List.size(); i++)
	{
		CH_Error_List.push_back(CopiedSP.CH_Error_List[i]);
	}
	for (int i = 0; i < CopiedSP.CompUniCourses.size(); i++)
	{
		CompUniCourses.push_back(CopiedSP.CompUniCourses[i]);
	}
	for (int i = 0; i < CopiedSP.ElectiveUniCourses.size(); i++)
	{
		ElectiveUniCourses.push_back(CopiedSP.ElectiveUniCourses[i]);
	}
	for (int i = 0; i < CopiedSP.TrackCourses.size(); i++)
	{
		TrackCourses.push_back(CopiedSP.TrackCourses[i]);
	}
	for (int i = 0; i < CopiedSP.CompMajorCourses.size(); i++)
	{
		CompMajorCourses.push_back(CopiedSP.CompMajorCourses[i]);
	}
	for (int i = 0; i < CopiedSP.ElectiveMajorCourses.size(); i++)
	{
		ElectiveMajorCourses.push_back(CopiedSP.ElectiveMajorCourses[i]);
	}
	for (int i = 0; i < CopiedSP.CompConcentrationCourses.size(); i++)
	{
		CompConcentrationCourses.push_back(CopiedSP.CompConcentrationCourses[i]);
	}
	for (int i = 0; i < CopiedSP.ElectiveConcentrationCourses.size(); i++)
	{
		ElectiveConcentrationCourses.push_back(CopiedSP.ElectiveConcentrationCourses[i]);
	}
	//for (int i = 0; i < CopiedSP.Minor_Course.size(); i++)
	//{
	//	Minor_Course.push_back(CopiedSP.Minor_Course[i]);
	//}
	//for (int i = 0; i < CopiedSP.Double_Minor_Course.size(); i++)
	//{
	//	Double_Minor_Course.push_back(CopiedSP.Double_Minor_Course[i]);
	//}

}
StudyPlan StudyPlan::operator=(const StudyPlan& CopiedSP)
{
	PlanNotes = CopiedSP.PlanNotes;
	Report_Lines = CopiedSP.Report_Lines;
	No_Of_Pages = CopiedSP.No_Of_Pages;
	TotalDoneHours = CopiedSP.TotalDoneHours;
	ConcentrationMinorCredits = CopiedSP.ConcentrationMinorCredits;
	ConcentrationMajorCredits = CopiedSP.ConcentrationMajorCredits;
	NumberOfConcentrations = CopiedSP.NumberOfConcentrations;
	MaxCredits = CopiedSP.MaxCredits;
	TotalMinorCredits = CopiedSP.TotalMinorCredits;
	TotalDoubleMinorCredits = CopiedSP.TotalDoubleMinorCredits;//added
	TotalConcentrationCredits = CopiedSP.TotalConcentrationCredits;
	TotalTrackCredits = CopiedSP.TotalTrackCredits;
	TotalMajorCredits = CopiedSP.TotalMajorCredits;
	TotalUnivCredits = CopiedSP.TotalUnivCredits;
	TotalCredits = CopiedSP.TotalCredits;
	StudentLevel = CopiedSP.StudentLevel;
	major = CopiedSP.major;
	pRules = CopiedSP.pRules;
	for (int i = 0; i < CopiedSP.Sem_Credits.size(); i++)
	{
		Sem_Credits.push_back(CopiedSP.Sem_Credits[i]);
	}
	for (int i = 0; i < CopiedSP.CH_Error_List.size(); i++)
	{
		CH_Error_List.push_back(CopiedSP.CH_Error_List[i]);
	}
	for (int i = 0; i < CopiedSP.CompUniCourses.size(); i++)
	{
		CompUniCourses.push_back(CopiedSP.CompUniCourses[i]);
	}
	for (int i = 0; i < CopiedSP.ElectiveUniCourses.size(); i++)
	{
		ElectiveUniCourses.push_back(CopiedSP.ElectiveUniCourses[i]);
	}
	for (int i = 0; i < CopiedSP.TrackCourses.size(); i++)
	{
		TrackCourses.push_back(CopiedSP.TrackCourses[i]);
	}
	for (int i = 0; i < CopiedSP.CompMajorCourses.size(); i++)
	{
		CompMajorCourses.push_back(CopiedSP.CompMajorCourses[i]);
	}
	for (int i = 0; i < CopiedSP.ElectiveMajorCourses.size(); i++)
	{
		ElectiveMajorCourses.push_back(CopiedSP.ElectiveMajorCourses[i]);
	}
	for (int i = 0; i < CopiedSP.CompConcentrationCourses.size(); i++)
	{
		CompConcentrationCourses.push_back(CopiedSP.CompConcentrationCourses[i]);
	}
	for (int i = 0; i < CopiedSP.ElectiveConcentrationCourses.size(); i++)
	{
		ElectiveConcentrationCourses.push_back(CopiedSP.ElectiveConcentrationCourses[i]);
	}
	int counter =0;

	for (AcademicYear* yr : CopiedSP.plan)
	{
		/*plan.push_back(new AcademicYear);*/
		list<Course*>* pYr = yr->getListOfYears();// pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			counter = 0;
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				pCrs = new Course;
				pCrs = (*it);
				Course* pcrs = new Course;
				*pcrs = *pCrs;
				pcrs->setGfxInfo((*it)->getGfxInfo());
				counter++;
				AddCourse(pcrs, pcrs->getYear(), pcrs->getSemester());
				/*delete pCrs;*/

			}

		}
	}
	//for (int i = 0; i < CopiedSP.Minor_Course.size(); i++)
	//{
	//	Minor_Course.push_back(CopiedSP.Minor_Course[i]);
	//}
	//for (int i = 0; i < CopiedSP.Double_Minor_Course.size(); i++)
	//{
	//	Double_Minor_Course.push_back(CopiedSP.Double_Minor_Course[i]);
	//}
	return (*this);
}

void StudyPlan::setMajorChanged(bool state)
{
	majorChanged = state;
}
bool StudyPlan::getMajorChanged() const
{
	return majorChanged;
}
void StudyPlan::setDoubleMajor(Major major)
{
	doubleMajor = major;
	doubleMajorOptimize = true; // start optimizing	
	doubleMajorExists = true;
}
Major StudyPlan::getDoubleMajor() const
{
	return doubleMajor;
}
void StudyPlan::setDoubleMajorExists(bool state)
{
	doubleMajorExists = state;
}
bool StudyPlan::getDoubleMajorExists() const
{
	return doubleMajorExists;
}

void StudyPlan::setDoubleMajorOptimize(bool state)
{
	doubleMajorOptimize = state;
}
bool StudyPlan::getDoubleMajorOptimize() const
{
	return doubleMajorOptimize;
}
void StudyPlan::Set_Double_Major_Plan_Rules(Rules& DoubleRegRules)
{
	pDoubleMajorRules = &DoubleRegRules;

}
bool StudyPlan::alreadyExistingCourse(string code, SEMESTER newSem, int newYear)
{
	for (AcademicYear* yr : plan)
	{
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++)
			{
				if ((*it)->getCode() == code  && (*it)->getSemester() == newSem && (*it)->getYear() == newYear)
					return true;
			}
		}
	}
	return false;
}
void StudyPlan::setMinor_course_flag(bool cond)
{
	Minor_course_flag = cond;
}
//added
void StudyPlan::setDouble_Minor_course_flag(bool cond)
{
	Double_Minor_course_flag = cond;
}

void StudyPlan::handleRepetition()
{
	// Loop on All courses
	for (AcademicYear* yr : plan) {
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
				// For each course loop down till you find its repeated one
				Course* pCr = (*it);
				if (pCr->repetitionCheked) {
					continue;
				}
				pCr->repeatedCourse = false;
				pCr->repeatedTimes = 0;
				for (string code : repeatedCoursesVector) {
					if (code == pCr->getCode())
						pCr->repeatedCourse = true;
				}
				for (int j = pCr->getYear() - 1; j < GUI::NumOfYrs; j++) {
					// check all the years including this year
					list<Course*>* pYr2 = plan[j]->getListOfYears(); // pointer to the year

					int semester_count;
					if (pCr->getYear() - 1 == j) {
						// The same year
						// in this case only loop on the number of semester
						if (pCr->getSemester() == 2)
							continue; // not to search in the same year
						semester_count = pCr->getSemester() + 1;
					}
					else {
						// otherwise loop on all 3 semesters
						semester_count = 0;
					}

					for (int k = semester_count; k <= 2; k++) {
						// check all the semesters below my semester
						for (auto iter = pYr2[k].begin(); iter != pYr2[k].end(); iter++) {
							if (pCr->getCode() == (*iter)->getCode()) {
								// Repetition ;)
								repeatedCoursesVector.push_back(pCr->getCode());
								pCr->repeatedCourse = true;
								pCr->repeatedTimes++;
								pCr->repetitionCheked = true;
							}
						}
					}
				}
			}
		}
	}

	for (AcademicYear* yr : plan) {
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
				// For each course loop down till you find its repeated one
				Course* pCr = (*it);
				pCr->repetitionCheked = false;
			}
		}
	}
	repeatedCoursesVector.clear();
}

//void StudyPlan::getDoubleConcentration() const
//{
//
//}
StudyPlan::~StudyPlan()
{
	for (AcademicYear* yr : plan) {
		list<Course*>* pYr = yr->getListOfYears(); // pointer to the year
		for (int sem = FALL; sem < SEM_CNT; sem++) {
			for (auto it = pYr[sem].begin(); it != pYr[sem].end(); it++) {
				delete (*it);
				(*it) = nullptr;
			}
		}
	}
}