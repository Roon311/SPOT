#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include "Utils.h"
#include"../GUI/GUI.h"
#include"../Registrar.h"
#include<iterator>
#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

vector<string> splitString(string str, string delim)
{
	vector<string> output;
	auto start = 0U;
	auto end = str.find(delim);
	while (end != string::npos) {
		output.push_back(str.substr(start, end - start));
		start = end + delim.length();
		end = str.find(delim, start);
	}
	output.push_back(str.substr(start, end));
	return output;
}


wstring s2ws(const string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring r(buf);
	delete[] buf;
	return r;
}

string OpenFileDialog() {

	OPENFILENAME ofn;

	const int MAX_SIZE = 300;
	wchar_t filename[MAX_SIZE]; // Final path

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0'; // No default 
	ofn.nMaxFile = MAX_SIZE;
	ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_NOCHANGEDIR;

	GetOpenFileName(&ofn);
	wstring ws(filename);
	// your new String
	string output(ws.begin(), ws.end());
	return output;
}

string SaveFileDialog() {
	OPENFILENAME ofn;

	const int MAX_SIZE = 300;
	wchar_t filename[MAX_SIZE]; // Final path

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0'; // No default 
	ofn.nMaxFile = MAX_SIZE;
	wstring filters_pre = s2ws("Text Files (*.txt), *.txt");
	LPCWSTR filters = filters_pre.c_str();

	ofn.lpstrFilter = filters; // Extension Filters (.txt, .xls, ...)
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_NOCHANGEDIR;

	GetSaveFileName(&ofn);
	wstring ws(filename);
	// your new String
	string output(ws.begin(), ws.end());
	return output;
}