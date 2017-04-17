#include "stdafx.h"
#include "Population.h"
#include<iostream>
#include<set>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include<ctime>


using namespace std;

Population::Population()
{
	sch = new Schedule();
}


Population::~Population()
{
	delete sch;
}


vector<Population::_case> Population::get_random_chromosome()
{
	vector<int> _class_id = sch->get_class_id_list();
	vector<Population::_case> res;
	for (int i = 0; i < _class_id.size(); ++i)
	{
		int test_class = _class_id[i];
		res.push_back(_case(test_class, sch->get_random_room(), sch->get_random_time(), sch->get_professor_of_class(test_class)));
	}
	_chromosome = res;
	return res;
}

void Population::add_professor(int i, string name, vector<int> prefer)
{
	sch->add_professor(i, name, prefer);
}


void Population::add_course(int i, string name, string _name_professor)
{
	if (sch->get_professor_id(_name_professor)==-1)
	{
		cout << "Can't locate professor " << _name_professor << endl;
		exit(-1);
	}
	sch->add_course(i, name, sch->get_professor_id(_name_professor));
}

void Population::add_class_room(int i, int seats, int _type)
{
	sch->add_classroom(i, seats, _type);
}

void Population::add_class(int _course_id, string course_name, string professor_name)
{
	sch->add_class(_course_id, course_name, professor_name);
}

void Population::set_time(int i)
{
	sch->set_time(i);
}

void Population::print_chromosome(vector<Population::_case> _chromosome)
{
	for (int i = 0; i < _chromosome.size(); ++i)
	{
		cout << "( " << _chromosome[i]._class_id << "," << _chromosome[i]._room << "," << _chromosome[i]._time_slot << "," << _chromosome[i]._professor_id << ") ";
	}
	cout << endl;
}









void Population::generate_test1()
{
	vector<Population::_case> res;
	res.push_back(_case(1, 2, 2, 1));
	res.push_back(_case(2, 1, 1, 2));
	res.push_back(_case(3, 3, 1, 3));
	res.push_back(_case(4, 3, 1, 4));
	res.push_back(_case(5, 1, 5, 5));
	sch->set_time(5);
	sch->add_classroom(1);
	sch->add_classroom(2);
	sch->add_classroom(3);
	_chromosome = res;
}



/*
double Population::get_fitness_score(void) {

	// default fitness score set to be -1
	double fScore = -1.0;
	// # of overlap in the chromosome: type (a) error
	int Ovrlap = 0;
	// # of the same professor teaching multiple courses at the same time in different rooms: type (b) error
	int multi_c = 0;


	// # of total rooms avaliable
	int roomNum = get_room();
	// # of total time slots
	int col = get_time();
	// # of courses, _chromosome is a private attribute 
	int row = _chromosome.size();

	// Table_Room is a 2D matrix, with its row idx as the course id and its column index as the time_slot id,
	// if a course with id==x is schedule in time_slot id==y in room id==z, then Table_Room[x][y]==z. 
	// this Table_Room is used to check room conflicts, meaning 2 courses schedule at the same time in the same room
	vector<vector<int>> Table_Room(row, vector<int>(col, 0));

	// multi_cMap record the professors' id as the key and the corresponding set of courses' time_slots is stored as the value
	// this hash table is used in further check of the error that the same professor falsely scheduled with multiple 
	// courses at the same time_slot
	unordered_map<int, set<int> > multi_cMap;

	for (int i = 0; i<(int)_chromosome.size(); i++) {
		// note _time_slot starts from 1 to max
		Table_Room[i][_chromosome[i]._time_slot - 1] = _chromosome[i]._room;

		// check if the same professor has multiple courses to teach in the same semester
		// if she does, then check if multiple different courses have been scheduled at the 
		// same time_slot for her. 
		if (multi_cMap.find(_chromosome[i]._professor_id) != multi_cMap.end()) { // the same professor with another course
																				// comparing the existing time_slots with the new time_slot for error (b)
			if (multi_cMap[_chromosome[i]._professor_id].find(_chromosome[i]._time_slot) != multi_cMap[_chromosome[i]._professor_id].end())
			multi_c += 1; // error type (b) found
			else
				multi_cMap[_chromosome[i]._professor_id].insert(_chromosome[i]._time_slot);

		}
		else { // a new professor found, insert <key,<course_id,time_slot>> pair 
			multi_cMap[_chromosome[i]._professor_id].insert(_chromosome[i]._time_slot); // course id is gauranteed to be different 
		}
	}


	// input validation
	if (Table_Room.empty() == true) {
		cout << "error: empty Table_Room input" << endl;
		// if the course time & room matrix is invalid, return -1
		return fScore;
	}

	if (roomNum<1) {
		cout << "error: invalid roomNum input" << endl;
		// if the # of rooms is invalid, return -2
		return (fScore - 1.0);
	}

	// # overlap error
	for (int i = 0; i < col; i++) {
		unordered_set<int> rooms;
		for (int j = 0; j < row; j++) {
			// Ovrlap += ((Table_Room[j][i] == Table_Room[j + 1][i]) && Table_Room[j][i] != 0) ? 1 : 0; 
			// the above line can only find the adjacent overlap error
			
			if (rooms.find(Table_Room[j][i]) != rooms.end()) {
				Ovrlap++;
				//cout << "overlap error in room--" << Table_Room[j][i] << endl;
			}
			else if (Table_Room[j][i] != 0)
				rooms.insert(Table_Room[j][i]);

		}
	}

	// # of the same professor schedule multiple courses at the same time_slot
	fScore = 1.0 / (Ovrlap + multi_c + 1.0);
	// linear fitness Score function
	//fScore = 1.0 - double(Ovrlap + multi_c) / double(2*row);
	
	return fScore;
}
*/

double Population::get_fitness_score(void) {

	// default fitness score set to be -1
	double fScore = -1.0;
	// # of overlap in the chromosome: type (a) error
	int Ovrlap = 0;
	// # of the same professor teaching multiple courses at the same time in different rooms: type (b) error
	int multi_c = 0;
	// # of the case that does not fit the professors' preference time_slot
	int prefer = 0;

	// # of total rooms avaliable
	int roomNum = get_room();
	// # of total time slots
	int col = get_time();
	// # of courses, _chromosome is a private attribute 
	int row = _chromosome.size();



	// Table_Room is a 2D matrix, with its row idx as the course id and its column index as the time_slot id,
	// if a course with id==x is schedule in time_slot id==y in room id==z, then Table_Room[x][y]==z. 
	// this Table_Room is used to check room conflicts, meaning 2 courses schedule at the same time in the same room
	vector<vector<int>> Table_Room(row, vector<int>(col, 0));

	// multi_cMap record the professors' id as the key and the corresponding set of courses' time_slots is stored as the value
	// this hash table is used in further check of the error that the same professor falsely scheduled with multiple 
	// courses at the same time_slot
	vector<unordered_set<int>> multi_cMap(get_professorNum(), unordered_set<int>{});

	for (int i = 0; i<(int)_chromosome.size(); i++) {

		// note _time_slot starts from 1 to max
		Table_Room[i][_chromosome[i]._time_slot - 1] = _chromosome[i]._room;

		// check if the same professor has multiple courses to teach in the same semester
		// if she does, then check if multiple different courses have been scheduled at the 
		// same time_slot for her. 
		if (multi_cMap[_chromosome[i]._professor_id].empty() != true) { // the same professor with another course
																		// comparing the existing time_slots with the new time_slot for error (b)
			if (multi_cMap[_chromosome[i]._professor_id].find(_chromosome[i]._time_slot) != multi_cMap[_chromosome[i]._professor_id].end())
				multi_c += 1; // error type (b) found
			else
				multi_cMap[_chromosome[i]._professor_id].insert(_chromosome[i]._time_slot);
		}
		else { // a new professor found, insert <key,<course_id,time_slot>> pair 
			multi_cMap[_chromosome[i]._professor_id].insert(_chromosome[i]._time_slot); // course id is gauranteed to be different 
		}

		// check the professors' preference 
		unordered_set<int> preference = get_prof_preference(_chromosome[i]._professor_id);
		if (preference.size() > 1 && preference.find(_chromosome[i]._time_slot) == preference.end())
			prefer += 1;
	}

	/*#########################################################################*/
	// input validation
	if (Table_Room.empty() == true) {
		cout << "error: empty Table_Room input" << endl;
		// if the course time & room matrix is invalid, return -1
		return fScore;
	}

	if (roomNum<1) {
		cout << "error: invalid roomNum input" << endl;
		// if the # of rooms is invalid, return -2
		return (fScore - 1.0);
	}

	// # overlap error
	for (int i = 0; i < col; i++) {
		unordered_set<int> rooms;
		for (int j = 0; j < row; j++) {
			// Ovrlap += ((Table_Room[j][i] == Table_Room[j + 1][i]) && Table_Room[j][i] != 0) ? 1 : 0; 
			// the above line can only find the adjacent overlap error

			if (rooms.find(Table_Room[j][i]) != rooms.end()) {
				Ovrlap++;
				//cout << "overlap error in room--" << Table_Room[j][i] << endl;
			}
			else if (Table_Room[j][i] != 0)
				rooms.insert(Table_Room[j][i]);

		}
	}

	// if fScore == 1, then consider the fitness of professors' preference
	fScore = (1.0 / (Ovrlap + multi_c + 1.0)) < 1.0 ? (1.0 / (Ovrlap + multi_c + 1.0)) : (1.0 + 1.0 / (1 + prefer));

	// linear fitness Score function
	//fScore = 1.0 - double(Ovrlap + multi_c) / double(2*row);

	return fScore;
}



void Population::generate_init_group(int i)
{
	
	_chromosome_base.clear();

	for (int c = 0; c < i; c++)
	{
		get_random_chromosome();
		_chromosome_base.push_back(_chromosome);
	}
}

void Population::update_group_fitness()
{
	int len = _chromosome_base.size();
	group_fitness.resize(len);
	for (int i = 0; i < len; ++i)
	{
		_chromosome = _chromosome_base[i];
		group_fitness[i] = get_fitness_score();
	}
	return;
}



void Population::mutateFun(vector<Population::_case>& chromosome) {
	int courseNum = chromosome.size();
	// randomly select a course to mutate
	int cIdx = rand() % courseNum;
	int RorT = rand() % 2;
	int roomNum = get_room();
	int timeSlot = get_time();
	if (RorT == 0) { // mutate in room
		while (roomNum != 1) {
			int newRoom = (rand() % roomNum) + 1;
			if (newRoom != chromosome[cIdx]._room) {
				chromosome[cIdx]._room = newRoom;
				break;
			}
		}
	}
	else { // mutate in time slot
		while (timeSlot != 1) {
			int newTime = (rand() % timeSlot) + 1;
			if (newTime != chromosome[cIdx]._time_slot) {
				chromosome[cIdx]._time_slot = newTime;
				break;
			}
		}
	}
	return;
}


// the mating function between 2 chromosomes _tp1 & _tp2, and mutation
vector<vector<Population::_case>> Population::matingFun(int id1, int id2, double _mutationRate) {

	vector<vector<_case>> children;
	vector<_case> _tp1(get_whole_group()[id1]);
	vector<_case> _tp2(get_whole_group()[id2]);
	int courseNum = _tp1.size();
	if (courseNum != _tp2.size())
		cout << "error: 2 chromosome vectors have different length" << endl;

	// step 1: randomly select a course to mate
	int courseIdx = rand() % courseNum;
	// step 2: randomly select a room or time slot to swap (cross point)
	int RorT = rand() % 2;
	// swap room 
	if (RorT == 0) {
		int temp = _tp1[courseIdx]._room;
		_tp1[courseIdx]._room = _tp2[courseIdx]._room;
		_tp2[courseIdx]._room = temp;
	}
	else { // swap time slot
		int temp = _tp1[courseIdx]._time_slot;
		_tp1[courseIdx]._time_slot = _tp2[courseIdx]._time_slot;
		_tp2[courseIdx]._time_slot = temp;
	}

	// mutation might happen on the children chromosomes
	double range = _mutationRate * double(INT_MAX);
	double mu = double(rand() % INT_MAX);

	// mu belongs to the range, so _tp1 mutate
	if (mu >= 0 && mu <= range) {
		mutateFun(_tp1);
	}

	mu = double(rand() % INT_MAX);
	// mu belongs to the range, so _tp2 mutate
	if (mu >= 0 && mu <= range) {
		mutateFun(_tp2);
	}

	// after crossover and potential mutation
	children.push_back(_tp1);
	children.push_back(_tp2);

	return children;
}


vector<vector<Population::_case>> Population::pick_random_chromosom()
{
	int pk1 = rand() % _chromosome_base.size();
	int pk2 = rand() % _chromosome_base.size();
	return { _chromosome_base[pk1], _chromosome_base[pk2] };
}

pair<int,int> Population::randSelect() {
	vector<double> gp_fitScore = get_group_fitness();
	double fitScoreSum = 0;
	for (auto d : gp_fitScore)
		fitScoreSum += d;

	vector<double> fitScore_Percentage;
	double mini = 1; // record the minimum percentage
	for (auto d : gp_fitScore) {
		fitScore_Percentage.push_back(d / fitScoreSum);
		mini = min(mini,fitScore_Percentage.back()); 
	}
	
		
	// 	section_resolution is the minimum section for randSelect()
	double section_resolution = 5.0;

	double range = section_resolution/mini;

	// section is the vectorized roulette wheel with each element in the vector represents an 
	// upper bound of the corresponding section, for each section: (prev,current element]
	vector<int> section;

	int tpsc = 0;
	for (auto p : fitScore_Percentage) {
		int tp = int(p*range);

		if (tp == INT_MAX)
			cout << "overflow in conversion from percentage to section" << endl;
		if (tp == 0)
			cout << "empty section found with percentage--" << (p * 100) << "%" << endl;
		tpsc += tp;
		section.push_back(tpsc);
	}

	// randomly generates 2 indices fallen into the 
	// 1~range wheel. Then find the corresponding indices of 
	// chromosomes in the wheel
	int id1, id2;
	int test1 = int(range);
	while (1) {
		srand((int)time(0));
		int idx1 = rand() % test1 + 1;
		int idx2 = rand() & test1 + 1;
		// testing the new binary search
		id1 = binarySearchNew(section, idx1,int(range)+1);
		id2 = binarySearchNew(section, idx2, int(range)+1);
		/*id1 = binarySearch(section, idx1);
		id2 = binarySearch(section, idx2);*/
		// valid id1 & id2
		if (id1 >= 0 && id1< int(_chromosome_base.size()) && id2 >= 0 && id2<int(_chromosome_base.size()))
			break;
	}

	
	return pair<int, int>{id1,id2};
}


int Population::binarySearch(vector<int> section, int idx) {
	for (int i = 0; i<section.size(); i++) {
		if (idx <= section[i] && i == 0)
			return i;
		if (idx <= section[i] && section[i - 1]<idx)
			return i;
	}
	return section.size()-1; // in case brute force failed

}

int Population::binarySearchNew(vector<int> section, int idx, int range) {
	if (section.empty())
	{
		cout << "empty section" << endl;
		exit(-1);
	}
	
	if (idx <= section[0]) return 0;
	if (idx > section.back()) return section.size() - 1;
	
	int low = 0;
	int high = section.size(); // high is always excluded in the searching range

	// valid input
	if (idx < 1) {
	cout << "error: invalid idx, idx < lower bound" << endl;
	//return -1; force to return a valid value
	return 1;
	}
	else if (idx > range) {
	cout << "error: invalid idx, idx > upper bound" << endl;
	//return -2; force to return a valid value
	return section.size() - 1;
	}

	int itrMax = section.size();
	int itr = 0;
	while (low < high) {
		itr++;
		if (itr>itrMax) {
			cout << "sth is wrong with current binary search, switch to brute force search" << endl;
			break;
		}
		if (high < section.size() && section[low] == section[high])
		{
			return high;
		}
		int mid = (low + high) / 2;
		if (idx <= section[mid] && mid == 0) {
			return mid;
		}
		else if (idx <= section[mid] && section[mid - 1]<idx) {
			return mid;
		}
		else if (idx < section[mid]) {
			high = mid;
		}
		else { // idx> section[mid]
			low = mid;
		}
	}
	if (itr > itrMax)
		cout << "the new binary search is failed" << endl;

	return section.size() - 1; // in case brute force failed
}




void Population::print_schedule(vector<Population::_case> sch, int _time_s)
{
	int room_num = get_room();
	vector<vector<int>> table(room_num,vector<int>(_time_s,0));
	cout << endl;
	for (int i = 0; i < sch.size(); ++i)
	{
		table[sch[i]._room - 1][sch[i]._time_slot - 1] = sch[i]._class_id;
	}
	for (int i = 0; i < table.size(); ++i)
	{
		for (int j = 0; j < table[0].size(); ++j)
		{
			if (j == 0) cout << "|";
			if (table[i][j] == 0) cout << "     |";
			else cout << " " << (table[i][j] < 10 ? " " : "") << table[i][j] << "  |";
		}
		cout << endl;
	}
	_chromosome = sch;// calculate fitness score
	cout << get_fitness_score() << endl;
}

void Population::set_prof_preference(int prof_id, vector<int> _time)
{
	sch->set_prof_preference(prof_id, _time);
}

unordered_set<int> Population::get_prof_preference(int prof_id)
{
	return sch->get_prof_preference(prof_id);
}