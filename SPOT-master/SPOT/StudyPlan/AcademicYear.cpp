#include "AcademicYear.h"
#include "../GUI/GUI.h"
int AcademicYear::TotalYears = 1;
int AcademicYear::Sem_Counter = 0;
AcademicYear::AcademicYear()
{
	TotalYears++;
}


AcademicYear::~AcademicYear()
{
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	pC->Course_Number = YearCourses[sem].size();
	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();
	if (pC->CCC_Flag == true)
	{
		pC->CCC_Flag = false;
		pC->Distance_Flag = true;
		return true;
	}
	else
	{
		if(!pC->Cant_Touch_This_Flag)
		pC->Distance_Flag = false;
		return true;
	}
}

bool AcademicYear::DeleteCourse(Course* pC, SEMESTER sem) {

	YearCourses[sem].remove(pC);
	TotalCredits -= pC->getCredits();
	Course::numOfCoursesPerSem[(3 * (pC->getYear() - 1)) + sem]--;
	if (pC->CCC_Flag == true)
	{
		pC->CCC_Flag = false;
		return true;
	}
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		int counter = 0;
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->Course_Number = counter;
			if (!pC->Cant_Touch_This_Flag)
			(*it)->Distance_Flag = false;
			counter++;
		}
	}

	return true;
}

void AcademicYear::DrawMe(GUI* pGUI) const
{
	int Counter = 0;
	int Temp_Count = 0;
	if (Sem_Counter == 15)
		Sem_Counter = 0;
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		Counter = 0;
		Temp_Count = 0;
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			if ((YearCourses[sem].size() <= 9))
			{
				pGUI->CPIES[Sem_Counter] = 0;
			}
			(*it)->Cant_Touch_This_Flag = false;
			if (((*it)->Course_Number <= 8) && (pGUI->CPIES[Sem_Counter] == 1))
			{
				(*it)->Cant_Touch_This_Flag =true;
			}
			else if (((*it)->Course_Number >= 9) && (pGUI->CPIES[Sem_Counter] == 0))
			{
				(*it)->Cant_Touch_This_Flag = true;
			}

			if (((*it)->Course_Number <= 8)&&(pGUI->CPIES[Sem_Counter]==0))
			{
				if ((Counter == 0) && (*it != NULL) && ((!(*it)->Distance_Flag)))
				{
					graphicsInfo gInfo_Old = (*it)->getGfxInfo();
					int new_x = 60;
					int new_y = gInfo_Old.y;
					graphicsInfo New_gInfo{ new_x, new_y };
					(*it)->Distance_Flag = true;
					(*it)->setGfxInfo(New_gInfo);

				}
				else if ((Counter > 0) && ((!(*it)->Distance_Flag)) && (*it != NULL))
				{
					graphicsInfo gInfo_Old = (*it)->getGfxInfo();
					int new_x = GUI::TitleBarWidth + (Counter * CRS_WIDTH) + 40 * Counter;
					int new_y = gInfo_Old.y;
					graphicsInfo New_gInfo{ new_x, new_y };
					(*it)->setGfxInfo(New_gInfo);
					(*it)->Distance_Flag = true;
				}
				if (((*it)->DrawMe_Flag))
				{
					(*it)->DrawMe(pGUI); //call DrawMe for each course in this semester
				}
				Counter++;
			}

			else if (((*it)->Course_Number >=9)&&(pGUI->CPIES[Sem_Counter] == 1))
			{
				if ((Temp_Count == 0) && (*it != NULL) && ((!(*it)->Distance_Flag)))
				{
					graphicsInfo gInfo_Old = (*it)->getGfxInfo();
					int new_x = 60;
					int new_y = gInfo_Old.y;
					graphicsInfo New_gInfo{ new_x, new_y };
					(*it)->Distance_Flag = true;
					(*it)->setGfxInfo(New_gInfo);

				}
				else if ((Temp_Count > 0) && ((!(*it)->Distance_Flag)) && (*it != NULL))
				{
					graphicsInfo gInfo_Old = (*it)->getGfxInfo();
					int new_x = GUI::TitleBarWidth + (Temp_Count * CRS_WIDTH) + 40 * Temp_Count;
					int new_y = gInfo_Old.y;
					graphicsInfo New_gInfo{ new_x, new_y };
					(*it)->setGfxInfo(New_gInfo);
					(*it)->Distance_Flag = true;
				}
				if (((*it)->DrawMe_Flag))
				{
					(*it)->DrawMe(pGUI); //call DrawMe for each course in this semester
				}
				Temp_Count++;
			}
		}
		Sem_Counter++;
	}
}

list<Course*>* AcademicYear::getListOfYears() {
	//list<Course*>* ptr = new list<Course*>;
	//return ptr;
	return YearCourses;
}