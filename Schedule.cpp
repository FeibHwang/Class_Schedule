#include "stdafx.h"
#include "Schedule.h"
#include <vector>
#include <iostream>

using namespace std;


Schedule::Schedule()
{
}


Schedule::~Schedule()
{
}


void Schedule::add_professor(int _id, string _name, vector<int> perfer)
{
	Professor *t = new Professor(_id, _name, perfer);
	int _local_id;
	if (prof_pool.empty()) _local_id = prof_NO++;
	else
	{
		_local_id = prof_pool.front();
		prof_pool.pop();
	}
	if (_professor_id_check.find(_name) != _professor_id_check.end())
	{
		cout << "detect same professor name! error place: Schedule.cpp" << endl;
	}
	_professor_id_check[_name] = _local_id;
	_professor_table[_local_id] = *t;
	_professor_local_index[_id] = _local_id;
}

void Schedule::add_course(int _id, string _course_name, int _professor)
{
	Course *c = new Course(_id, _course_name, _professor);
	int _local_id;
	if (course_pool.empty()) _local_id = course_NO++;
	else
	{
		_local_id = course_pool.front();
		course_pool.pop();
	}
	_course_id_check[_course_name] = _local_id;
	_course_table[_local_id] = *c;
}

void Schedule::add_classroom(int _id, int _seats, int _type)
{
	Classroom *cl = new Classroom(_id, _seats, _type);
	int _local_id;
	if (class_pool.empty()) _local_id = class_NO++;
	else
	{
		_local_id = class_pool.front();
		class_pool.pop();
	}
	_classroom_table[_local_id] = *cl;
}

void Schedule::set_time(int slots)
{
	_time_table.clear();
	int i = 0;
	while (i < slots)
	{
		_time_table[i] = ++i;
	}
}


void Schedule::add_class(int _class_id, string course, string professor)
{
	if (_class_table.find(_class_id) != _class_table.end())
	{
		cout << "duplicate class is detect" << endl;
	}
	Course_Class* _Class = new Course_Class(_class_id, get_course_id(course), get_professor_id(professor));
	_class_table[_class_id] = *_Class;
}

vector<vector<int>> Schedule::get_schedule()
{
	vector<vector<int>> sc(_course_table.size(), vector<int>(_time_table.size(), 0));
	int time_slot = _time_table.size();
	int room_slot = _classroom_table.size();
	for (auto i : _course_table)
	{
		int t = rand() % time_slot;
		int r = rand() % room_slot + 1;
		i.second.set_time(t);
		i.second.set_room(r);
		sc[i.first][t] = r;
	}
	return sc;
}


inline int Schedule::get_class_room()
{
	return _classroom_table.size();
}

inline int Schedule::get_time_size()
{
	return _time_table.size();
}

int Schedule::get_random_time()
{
	auto i = _time_table.begin();
	int step = rand() % get_time_size();
	advance(i, step);
	return i->second;
}

int Schedule::get_random_room()
{
	auto i = _classroom_table.begin();
	int step = rand() % get_class_room();
	advance(i, step);
	return i->second.get_room_id();
}

vector<int> Schedule::get_course_id_list()
{
	vector<int> res;
	for (auto i : _course_table)
	{
		res.push_back(i.second.get_course_id());
	}

	return res;
}

vector<int> Schedule::get_class_id_list()
{
	{
		vector<int> res;
		for (auto i : _class_table)
		{
			res.push_back(i.second.get_class_id());
		}

		return res;
	}
}