#include "Professor.h"
#include "Classes.h"
#include "Classroom.h"
#include "Course.h"
#include "Course_Class.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>



using namespace std;

#pragma once
class Schedule
{
public:
	Schedule();
	~Schedule();

	void add_professor(int _id, string _name, vector<int> perfer);
	void add_course(int _id, string _course_name, int _professor);
	void add_classroom(int _id, int _seats = 50, int _type = 1);
	void set_time(int slots);
	void add_class(int _class_id, string course, string professor);

	int get_class_room();
	int get_time_size();

	vector<vector<int>> get_schedule();


	int get_random_time();

	int get_random_room();

	vector<int> get_course_id_list();

	vector<int> get_class_id_list();

	inline int get_professor_id(string s) { return _professor_id_check.find(s)!= _professor_id_check.end() ? _professor_id_check[s]:-1; }
	//return professor ID, if not found, return -1; 

	inline int get_professor_of_course(int i) { return _course_table[i].get_frofessor_id(); };

	inline int get_professor_of_class(int i) { return _class_table[i].get_professor_id(); };

	inline int get_course_id(string s) { return _course_id_check[s]; }




private:
	unordered_map<int, Course> _course_table;
	unordered_map<int, Professor> _professor_table;
	unordered_map<int, Classroom> _classroom_table;
	unordered_map<int, int> _time_table;
	unordered_map<int, Course_Class> _class_table;

	unordered_map<string, int> _professor_id_check;  // check the professor ID by name
	unordered_map<string, int> _course_id_check; //check the course ID by name

	int course_NO = 0;
	int prof_NO = 0;
	int class_NO = 0;
	int time_NO = 0;

	queue<int> course_pool;
	queue<int> prof_pool;
	queue<int> class_pool;
	queue<int> time_pool;


};

