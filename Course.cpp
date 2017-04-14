#include "stdafx.h"
#include "Course.h"


Course::Course(int _idd, string _course_namee, int _professorr)
{
	_id = _idd;
	_course_name = _course_namee;
	_professor = _professorr;
}

Course::Course()
{
	_id = -1;
	_course_name = -1;
	_professor = -1;
}


Course::~Course()
{
}
