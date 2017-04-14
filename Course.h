#include<string>
#include<vector>

using namespace std;

#pragma once
class Course
{
public:
	Course(int _id, string _course_name, int _professor);
	Course();
	~Course();

	inline void set_time(int t) { _course_time = t; }

	inline int get_time() { return _course_time; }

	inline void set_room(int t) { _course_room = t; }

	inline int get_room() { return _course_room; }

	inline int get_course_id() { return _id; }

	inline string get_course_name() { return _course_name; }

	inline int get_frofessor_id() { return _professor; }

private:
	int _id; //course ID
	string _course_name;
	int _professor;  //professoe ID: one professor-> one unique number
	vector<int> _classes;
	int _students;
	int _course_time;
	int _course_room;
};

