#include "Registrar.h"
#include<iostream>
#include"Maestro.h"
#include<Windows.h>
#include"GUI/CMUgraphicsLib/CMUgraphics.h"
#include "GUI/CMUgraphicsLib/auxil.h"	// where Pause is found
using namespace std;

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

int main()
{
	//HideConsole();
	// WIll be used later to have the same window resolution for each user local machine
	HWND hd = GetDesktopWindow();
	RECT rect;
	GetClientRect(hd, &rect);
	int Client_Width = (rect.right - rect.left);
	//int Client_Height = (rect.bottom - rect.top);
	cout << "Client Width = " << Client_Width << "px\n";
	HideConsole();
	Maestro test;
	test.Run();
	//Registrar Reg;
	//Reg.Run();
}