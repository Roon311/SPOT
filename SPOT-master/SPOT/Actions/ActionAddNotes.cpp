#include "ActionAddNotes.h"
#include "../Registrar.h"
#include <string>
#include <iostream>

ActionAddNotes::ActionAddNotes(Registrar*P):Action(P)
{
}
bool ActionAddNotes::Execute()
{

	cout << "Notes button is pressed.\n"; // for debugging
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay(); //pointer to study plan
	    if (((pGUI->getYCoord() >= 10) && (pGUI->getYCoord() <= 30) && ((pGUI->getXCoord()) >= (pGUI->SideBarX1 - 45 + (pGUI->SideBarX2 - pGUI->SideBarX1) / 2)) && (pGUI->getXCoord() <= (pGUI->SideBarX1 - 45 + 100 + (pGUI->SideBarX2 - pGUI->SideBarX1) / 2))) && (pGUI->GetLastClick() == LEFT_CLICK))
		{
			if (pS->PlanNotes.size() == 0)
				return true;
			pS->PlanNotes=pGUI->GetSrting(pS->PlanNotes);
			pGUI->Notes = pS->PlanNotes;
			pGUI->NotesLines.clear();
			pGUI->SegmentNotes();
		}
		else
		{
			StudyPlan* pS = pReg->getStudyPlay(); //pointer to study plan
			pGUI->PrintMsg("Add Notes For The Study Plan");
			pGUI->Notes = pGUI->GetSrting();
			if (pGUI->Notes==" ")
			{
				pReg->Not_Worth_Saving_Flag = true;
				return true;
			}
			pS->PlanNotes = pS->PlanNotes + " " + pGUI->Notes;
			pGUI->Notes = pS->PlanNotes;
			pGUI->NotesLines.clear();
			pGUI->SegmentNotes();
			pGUI->Total_Number_Pages_In_Notes = (pGUI->NotesLines.size() / ((pGUI->NotesHeight / 15) - 2));
			return true;
		}
}

ActionAddNotes::~ActionAddNotes()
{
}