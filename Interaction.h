#include"Population.h"
#include "reproduceFun.h"
#include <math.h>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_set>
#include <functional>
#include<ctime>

#pragma once
class Interaction
{
public:
	Interaction();
	~Interaction();

	void init_time(vector<int> start_hour, vector<int> start_min, vector<int> end_hour, vector<int> end_min, vector<int> days);

	vector<int> prefer_time_conv(vector<int> start_hour, vector<int> start_min, vector<int> end_hour, vector<int> end_min, vector<int> days);

	void add_class_rooms(vector<string> room_name, vector<int> room_id, vector<int> seats = { -1 }, vector<int> types = {-1});

	void add_professors(int id_number, string name, vector<int> start_hour = { -1 }, vector<int> start_min = { -1 }, vector<int> end_hour = { -1 }, vector<int> end_min = { -1 }, vector<int> days = { -1 });

	void add_courses(vector<int> course_id, vector<string> course_name, vector<string> professor_name, vector<int> course_type = {-1});

	void add_classis(vector<int> class_id, vector<string> course_name, vector<string> professor_name);

	void init_from_text_file(string _name);

	int start_evolution(int _group_size, int maxGeneration, double mutationRate, double fitSCore_goal, double perX, double perY);

	void print_valid_table(int index);

	void set_prof_perference(int prof_id, vector<int> perference);

	void write_to_file(int i);
	void print_to_console(int i);

private:
	Population *kernel;

	struct course_time
	{
		int start_hour;
		int start_minutes;
		int end_hour;
		int end_minutes;
		int day;
		course_time(int a, int b, int c, int d, int e):
			start_hour(a), start_minutes(b),
			end_hour(c), end_minutes(d), day(e){}
	};

	vector<course_time> time_slots;

	unordered_map<int, string> room_table;
	unordered_map<int, string> prof_table;
	unordered_map<int, string> course_table;
	unordered_map<int, string> class_table;
};

