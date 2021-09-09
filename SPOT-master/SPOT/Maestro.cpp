#include"Maestro.h"
#include <cstdlib>
window* Maestro::pMaestroWind = NULL;
Maestro::Maestro()
{
	pMaestroWind = new window(MaestroWindWidth, MaestroWindowHeight, StartX, StartY);
	pMaestroWind->ChangeTitle("Spot Master Interface");
	ClearDrawingArea();
}
void Maestro::AddSpot()
{

	pReg = new Registrar;
	pReg->MeineNummer = List_Of_Spots.size()+1;
	pReg->SetMaestroWindowP(this);
	GUI* pGUI = pReg->getGUI();
	List_Of_windows.push_back(pGUI->pWind);
	pGUI->GetVecOfWindows(List_Of_windows);
	List_Of_Spots.push_back(pReg);
	pReg = NULL;
}
void Maestro::DeleteSpot(int Number)
{

}
void Maestro::Run() 
{
	pMaestroWind->SetIcon("app.ico");
	while (true)
	{
		int x, y;
		pMaestroWind->SetFont(30, PLAIN, BY_NAME, "Arial");
		pMaestroWind->SetPen(MYCYAN, 1);
		pMaestroWind->DrawString(25, 0, "Study Plan Organization Tool");
		pMaestroWind->DrawImage("GUI\\Images\\Add_SPOT.jpg", 90, 40, 70, 70);
		pMaestroWind->SetFont(20, PLAIN, BY_NAME, "Arial");
		pMaestroWind->SetPen(MYCYAN, 1);
		pMaestroWind->DrawString(90+70, 40+20, "Add New SPOT");
		pMaestroWind->GetMouseClick(x, y);
		//if ((pMaestroWind->GetGreen(x, y) == 0.8) && (pMaestroWind->GetRed(x, y) == 0.8) && (pMaestroWind->GetBlue(x, y) == 0.8))
		if(!pMaestroWind->isWindowStillAlive())
		{
			exit(0);
			break;
		}
		if ((x >= (90)) && (x <= ((90+70)) && (y >= (40)) && (y <= (40+70))))
		{
			
			AddSpot();
		}
		if (List_Of_Spots.size() > 0)
		{
			for (int i = 0; i < List_Of_Spots.size(); i++)
			{
			pReg = List_Of_Spots[i];
			pReg->MeineNummer = i+1;
			GUI* pGUI = pReg->getGUI();
			//if ((pGUI->pWind->GetGreen(x, y) == 0.8) && (pGUI->pWind->GetRed(x, y) == 0.8) && (pGUI->pWind->GetBlue(x, y) == 0.8))
			if(!pGUI->pWind->isWindowStillAlive())
			{
				List_Of_Spots.erase(List_Of_Spots.begin()+i);
				List_Of_windows.erase(List_Of_windows.begin()+i);
			}
			if (pGUI->pWind->GetClicked())
			{
				pGUI->pWind->SetClicked(false);
				pReg->Run();
			}
			if (pGUI->pWind->GetMouseClick(x, y))
				pReg->Run();
			}

		}
	}
}
void  Maestro::UpdateWind()
{
	pMaestroWind->SetBuffering(1);
	ClearDrawingArea();
	pMaestroWind->UpdateBuffer();
	pMaestroWind->SetBuffering(0);
}
void  Maestro::ClearDrawingArea()
{
	pMaestroWind->SetBrush(BackgroundColor);
	pMaestroWind->DrawRectangle(0, 0, MaestroWindWidth, MaestroWindowHeight, FILLED);
}
//bool Maestro::ExecuteAction(Action*)
//{
//
//}
Maestro::~Maestro()
{

}