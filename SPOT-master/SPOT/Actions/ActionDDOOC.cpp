#include "ActionDDOOC.h"
#include "..\Registrar.h"
#include <iostream>
#include"../GUI/GUI.h"
#include"../Utils/Utils.h"
ActionDDOOC::ActionDDOOC(Registrar* P) :Action(P)
{
}
bool  ActionDDOOC::Execute()
{
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	if (pGUI->getDDFOOCF())
	{
		pGUI->setDDFOOCF(false);
		pGUI->setDDFOC(false);
		pS->TreeUnFiltering();
		return true;
	}
	if (pGUI->getDDFOC())
    {
		vector<Course*>Tree = pS->Gettree();
		for (int i = 0; i < Tree.size(); i++)
		{
			pS->FindPreAndCoReq_ITCSP_Tree(Tree[i], pGUI);
		}
	return true;
    }
	ActionData actData = pGUI->GetUserAction("Select the course you want to see its Dependancies");
	int x, y;
	x = actData.x;
	y = actData.y;
	Course* pCr = pReg->interrogateCourse(x, y);
	if (pCr == nullptr) {
		pGUI->setDDFOC(false);
		pS->TreeUnFiltering();
		return true;
	}
	else
	{
		pReg->OldpCr_For_DDOOC = pCr;
		pGUI->setDDFOC(true);
		pS->ClearTree();
		pS->ACCFT();
		vector<Course*>Tree=pS->FindPre_ITCSP(pCr);
		int counter = 0;
		for (int i = 0; i < Tree.size(); i++)
		{
			for (int j = 0; j < Tree.size(); j++)
			{
				if(Tree[j]->getCode()== Tree[i]->getCode())
				counter++;
				if ((counter > 1)&&(Tree[j]->getCode() == Tree[i]->getCode()))
				{
					Tree.erase(Tree.begin()+j);
				}
			}
			counter = 0;
		}
		pS->SetTree(Tree);
		for (int i = 0; i < Tree.size(); i++)
		{
			pS->FindPreAndCoReq_ITCSP_Tree(Tree[i], pGUI);
		}
		pS->TreeFiltering();
	}
	return true;
}
ActionDDOOC::~ActionDDOOC()
{

}
