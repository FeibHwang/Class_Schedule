#include "stdafx.h"
#include "Interaction.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

Interaction::Interaction()
{
	kernel = new Population;
}


Interaction::~Interaction()
{
	delete kernel;
}


void Interaction::init_time(vector<int> start_hour, vector<int> start_min, vector<int> end_hour, vector<int> end_min, vector<int> days)
{
	if (start_hour.size() != start_min.size() || start_min.size() != end_hour.size() || end_hour.size() != end_min.size())
	{
		cout << "time table size not match!" << endl;
		exit(-1);
	}
	time_slots = {};
	for (int i = 0; i < start_hour.size(); ++i)
	{
		course_time *t = new course_time(start_hour[i], start_min[i], end_hour[i], end_min[i], days[i]);
		time_slots.push_back(*t);
	}
	kernel->set_time(time_slots.size());
	/*
	sort(time_slots.begin(), time_slots.end(), [](course_time a, course_time b) {
		return (a.day < b.day) || (a.start_hour < b.start_hour) || (a.start_minutes < b.start_minutes);
	});
	*/
}



vector<int> Interaction::prefer_time_conv(vector<int> start_hour, vector<int> start_min, vector<int> end_hour, vector<int> end_min, vector<int> days)
{
	//default
	vector<int> rec;
	for (int i = 0; i < start_hour.size(); ++i) rec.push_back(i);
	return rec;
}

void Interaction::add_class_rooms(vector<string> room_name, vector<int> room_id, vector<int> seats, vector<int> types)
{
	//add_class_room
	for (int i = 0; i < room_id.size(); ++i)
	{
		room_table[room_id[i]] = room_name[i];
		if (seats[0] == -1) kernel->add_class_room(room_id[i]);
		else kernel->add_class_room(room_id[i], seats[i], types[i]);
	}
}

void Interaction::add_professors(int id_number, string name, vector<int> start_hour, vector<int> start_min, vector<int> end_hour, vector<int> end_min, vector<int> days)
{
	//add_professor(int i, string _name, vector<int> = {})
	prof_table[id_number] = name;
	kernel->add_professor(id_number, name, prefer_time_conv(start_hour, start_min, end_hour, end_min, days));
}

void Interaction::add_courses(vector<int> course_id, vector<string> course_name, vector<string> professor_name, vector<int> course_type)
{
	//void add_course(int i, string name, string _name_professor)
	for (int i = 0; i < course_id.size(); ++i)
	{
		course_table[course_id[i]] = course_name[i];
		kernel->add_course(course_id[i], course_name[i], professor_name[i]);
	}
}

void Interaction::add_classis(vector<int> class_id, vector<string> course_name, vector<string> professor_name)
{
	//add_class(int _course_id, string course_name, string professor_name)
	for (int i = 0; i < class_id.size(); ++i)
	{
		kernel->add_class(class_id[i], course_name[i], professor_name[i]);
		class_table[class_id[i]] = course_name[i];
	}
}


void Interaction::init_from_text_file(string _name)
{
	return;
}

int Interaction::start_evolution(int _group_size, int maxGeneration, double mutationRate, double fitSCore_goal, double perX, double perY)
{
	int i = 0;
	
	kernel->generate_init_group(_group_size);
	
	kernel->update_group_fitness();
	int index = reproduceFun(kernel, maxGeneration, mutationRate, fitSCore_goal, perX, perY);
	
	kernel->update_group_fitness();
	
	kernel->print_schedule(kernel->get_whole_group()[index], time_slots.size());
	
	auto k = kernel->get_fitness_score();
	
	cout << endl << endl << endl;
	return index;
}

void Interaction::print_valid_table(int index)
{
	kernel->print_schedule(kernel->get_whole_group()[index], time_slots.size());
}

void Interaction::write_to_file(int i)
{
	vector<Population::_case> k = kernel->get_whole_group()[i];
	vector<vector<string>> res(kernel->get_room(), vector<string>());
	for (int i = 0; i < k.size(); ++i)
	{
		int _class_id = k[i]._class_id;
		res[k[i]._room - 1].push_back(class_table[_class_id]+"##"+to_string(k[i]._time_slot));
	}

	ofstream myfile;
	myfile.open("course_schedule.txt");
	//myfile << "Writing this to a file.\n";
	for (int i = 0; i < res.size(); ++i) {
		myfile << room_table[i + 1] + "\n";
		for (int j = 0; j < res[i].size(); ++j)
		{
			myfile << res[i][j] + "\n";
		}
		myfile << "splitline\n";
	}
	myfile.close();
}

void Interaction::print_to_console(int j)
{
	vector<Population::_case> k = kernel->get_whole_group()[j];
	cout << endl << endl;
	for (int i = 0; i < k.size(); ++i)
	{
		int _class_id = k[i]._class_id;
		int _room_id = k[i]._room;
		int t = k[i]._time_slot-1;
		int _prif_id = kernel->get_prof_id_by_course_schedule_id(k[i]._professor_id);
		cout << class_table[_class_id]
			<< "     "
			<< room_table[_room_id]
			<< "     "
			<< time_slots[t].start_hour
			<< ":"
			<< time_slots[t].start_minutes
			<< " ~ " << time_slots[t].end_hour
			<< ":" << time_slots[t].end_minutes
			<< "     "
			<< "Prof."
			<< prof_table[_prif_id] << endl << endl;
	}
}

void Interaction::set_prof_perference(int prof_id, vector<int> perference)
{
	kernel->set_prof_preference(prof_id, perference);
}