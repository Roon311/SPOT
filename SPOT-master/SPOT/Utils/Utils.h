#pragma once
#include<fstream>
#include<iostream>
#include<vector>
#include"../Rules.h"
#include"../GUI/Drawable.h"
#include"../Registrar.h"

using namespace std;
vector<string> splitString(string str, string delim); // returns vector of tokens
string OpenFileDialog(); // Open Browse Window
string SaveFileDialog(); // Save Browse Window

