#pragma once
#include <string>
#include <list>
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"
#include<vector>

//Base class for all types of courses
class Course : public Drawable
{
private:
	color MyColor; // Color
	color MyBorderColor;
	bool UnknownCRS; // for courses with XXX
	Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	Type type= NOTYPE;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	bool pending;	//Course Pending"Currently taking"
	bool inprogress;//course in progress
	bool Exempted;//course exempted
	bool Replaced;//course replaced
	bool CreditsTransfered;//course credits transferred
	bool studentleveltoken;
	string Grade="--";//Holds the course Grade
	string Status = "NT";
	vector<Course_Code> PreReq;	//list of prerequisites
	vector<Course_Code> CoReq;	//list of prerequisites
	//Curret year and semester
	int year;
	SEMESTER sem;
	
	// Errors
	vector<Error> Prereq_Error_List;
	vector<Error> Coreq_Error_List;
public:
	//string coursestatus;
	int Course_Number=0;
	bool DrawMe_Flag=true;
	bool CCC_Flag = false;
	bool Distance_Flag = false;
	bool Erased_Flag = false;
	bool Minor_Erased_Flag = false;
	bool Double_Minor_Erased_Flag = false;
	bool Cant_Touch_This_Flag = false;
	static vector<int> numOfCoursesPerSem;
	//Constructors
	Course();
	//Course(Course_Code r_code,string r_title, int crd);
	Course(Course_Code r_code, string r_title, int crd,
		vector<Course_Code> r_PreReq, vector<Course_Code> r_CoReq,int r_year, SEMESTER r_sem);
	// Setters
	void setToken(bool Case);
	void setCode(Course_Code i_code);
	void setTitle(string i_title);
	void setCredits(int i_cr);
	void setPreReq(vector<string> vector);
	void setCoReq(vector<string> vector);
	void setYear(int inputYear);
	void setSemester(SEMESTER inputSem);
	void Set_Type(Type intype);
	void changeColor(color newColor);
	void changeBorderColor(color newColor);
	void setUnknownCrs(bool unknown);
	void setCoursedone(bool Case);//set course to (wither done or not done) 
	void setCoursepending(bool Case);
	void setCourseinprogress(bool Case);
	void setGrade(string grade);
	void setStatus(string Status);
	void setCourseExempted(bool Case);
	void setCourseReplaced(bool Case);
	void setCourseCreditsTransfered(bool CT);


	//Getters
	string getGrade()const;
	string getStatus()const;
	bool getToken()const;
	bool getCourseReplaced()const;
	bool getCourseExempted()const;
	bool getCourseCreditsTransfered()const;
	bool getCoursedone()const;
	bool getCoursepending()const;
	bool getUnknownCrs() const;
	bool getCourseinprogress()const;
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	vector<string> getPreReq() const;
	vector<string> getCoReq() const;
	vector<Error> getPreReqErrors() const;
	vector<Error> getCoReqErrors() const;
	int getYear() const;
	SEMESTER getSemester() const;
	Type getType()const;
	color getColor() const;
	color getBorderColor() const;
	bool isUnknown() const;
	static int getNumOfCrsPerSem(int year, SEMESTER sem);

	//ERRORS
	void AddPreError(ErrorType Type, string msg);
	void AddCoError(ErrorType Type, string msg);
	void removePreReqErrors(string code);
	void removeCoReqErrors(string code);
	int getPreErrorsNumber() const;
	int getCoErrorsNumber() const;
	void DrawMe(GUI*) const;
	Course(const Course& CopiedCrs);
	Course operator=(const Course& CopiedCrs);
	void printCourse() const;
	Course* getCoursePtr();	

	bool hasNoStatus();

	// Handle repetition
	bool repeatedCourse;
	int repeatedTimes;
	bool repetitionCheked;

	virtual ~Course();
};
