#pragma once

//This file contains data sturctures required to store all registration RULES
#include <vector>
#include<iostream>
using namespace std;
#include "DEFs.h"


//Information for each course
//Title, code, credit hours, and pre-req list, type
struct CourseInfo
{
	string Title;
	Course_Code	Code;
	vector<Course_Code> PreReqList;	//Pre-requesite list of courses codes
	vector<Course_Code> CoReqList;	//Co-requesite list of courses codes
	int Credits;
	Type type;	//Univ, track, major course
	void printCourse() {
		cout << "Displaying the course info.\n"
			<< "Course ID: " << Code << endl
			<< "Course Title: " << Title << endl
			<< "CH: " << Credits << endl
			<< "Prerequisites: ";
		for (Course_Code i : PreReqList) {
			cout << i << " ";
		}
		cout << endl << "Corequesites: ";
		for (Course_Code i : CoReqList) {
			cout << i << " ";
		}
		cout << endl << endl;
	}
};

struct AcademicYearOfferings
{
	string Year; //academic year of the offerings e.g. 2019-2020


	//Each year has an array of of 3 vectors of courses CODE. 
	//Each vector cossrsponds to a semester
	//So Offerings[FALL] is a vector of courses offered in FALL in THAT year
	//So Offerings[SPRING] is a vector of courses offered in SPRING in THAT year
	//So Offerings[SUMMER] is a vector of courses offered in SUMMER in THAT year
	vector<Course_Code> Offerings[SEM_CNT];
};

struct Rules	//contains all objects for registrations rules
{
	vector<CourseInfo> CourseCatalog;	//List of ALL courses with full info

	vector<AcademicYearOfferings> OffringsList;	//all offerings for all acedmic years
	//AcademicYearOfferings OffringsList;	//// for now we will leave it one year

	int SemMinCredit,		//min no. of credit hours per semester
		SemMaxCredit;		//max no. of credit hours per semester

	int TotalCHs;			// Number of CHs should be done

	int	UnivCompulsoryCredits,   // min no. of CHs of comp univ courses
		UnivElectiveCredits,	 // min no. of CHs of elective univ courses
		ReqUnivCredits; 
	    //Total no. of credits req by Univ courses (comp + elective)

	int ReqTrackCredits;	//Total no. of credits req by Track courses (Only Comp)

	int MajorCompulsoryCredits, // min no. of CHs of comp major courses
		MajorElectiveCredits, // min no. of CHs of elective major courses
		ReqMajorCredits;	
		//Total no. of credits req by Major courses (comp + elective)

	int NumOfConcentrations; // Number of concentrations in major

	vector<Course_Code> UnivCompulsoryCourses;	//Univ Compulsory courses
	vector<Course_Code> UnivElectiveCourses;	//Univ Elective courses

	vector<Course_Code> TrackCompulsoryCourses;//Track Compulsory courses

	vector<Course_Code> MajorCompulsoryCourses;//Major Compulsory courses
	vector<Course_Code> MajorElectiveCourses;	//Major Elective courses

	vector<Concentration> Concentrations; // Concentrations

	//Checks
	vector<Course_Code> CheckDoubleTrackCourses; // Track Unique Courses
	vector<Course_Code> CheckDoubleMajorCompCourses; // Major Comp Unique Courses
	vector<Course_Code> CheckDoubleMajorElectiveCourses; // Major Elective Unique Courses

	// CrossLinking
	vector<CrossLinked> CrossLinkedCourses;
};
