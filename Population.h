/*
* 2017-4-9 Feibai Huang
* Chromosome Class
*/


#include<vector>
#include"Schedule.h"

using namespace std;

#pragma once
class Population
{
public:
	struct _case
	{
		int _class_id;  // course ID: real class id i.e 21342
		int _room;       // room ID: real room id i.e DL226 -> a unique number for diffrent room
		int _time_slot;  // time slot: real time, set by add_time
		int _professor_id; //professor ID
		
		_case(int a, int b, int c, int d) : _class_id(a), _room(b), _time_slot(c), _professor_id(d) { };
	};

	Population();
	~Population();


	void add_professor(int i, string _name, vector<int> = {});
	/*
	add professor function
	intput: 
	i-> real professor ID, use real ID, the system will assign storage ID automatically
	name-> real professor Name
	*/

	void add_course(int i, string name, string _name_professor);
	/*
	add a course:
	input:
	i-> real course ID
	name: real course name
	_name_professor: real name of the professor who taught the course, the function will check the database and match with the professor base
	*/

	void add_class_room(int i, int seats = 50, int _type = 1);
	/*
	add a class room
	input:
	i: real room number
	seats: how many seats the room has, default is 50
	_type: some special type of the classroom, the meaning can be set, 1 means ordinary classroom
	*/

	void add_class(int _course_id, string course_name, string professor_name);

	void set_time(int _slots);
	/*
	set the real time, as long as the input is different, the time will be abstract as a TIME SLOT
	*/

	void print_chromosome(vector<_case> i);


	inline int get_room() { return sch->get_class_room(); };  
	//get number of classrooms

	inline int get_time() { return sch->get_time_size(); };
	//get number of classrooms

	inline vector<double> get_group_fitness() { return group_fitness; };

	vector<_case> get_random_chromosome();
	/*
	generate a valid _chromosome
	*/

	void generate_test1();

	void generate_init_group(int i);

	void update_group_fitness();

	double get_fitness_score(void);

	vector<vector<_case>> matingFun(int id1, int id2, double _mutationRate);

	vector<vector<_case>> pick_random_chromosom();

	inline vector<vector<_case>> get_whole_group() { return _chromosome_base; };

	pair<int,int> randSelect();

	void print_schedule(vector<_case> sch, int _time_slot);

	inline int get_population_size() { return _chromosome_base.size(); }
	
	inline void update_chromosome_base(vector<vector<_case>> newGene) {
		_chromosome_base.clear(); 
		_chromosome_base = newGene; 
	}

	inline int get_professorNum() { return sch->get_professor_size(); }

	void set_prof_preference(int prof_id, vector<int> _time);

	unordered_set<int> get_prof_preference(int prof_id);

	inline int get_prof_id_by_course_schedule_id(int _local_id) { return sch->get_prof_id_by_index(_local_id); }
private:

	Schedule *sch;
	//Schedual Class hold the whole database

	vector<_case> _chromosome;
	// a tempory value that can hold ONE chromosome

	vector<vector<_case>> _chromosome_base;

	vector<double> group_fitness;

	void mutateFun(vector<_case>& chromosome);

	int binarySearch(vector<int> section, int idx);
	
	int binarySearchNew(vector<int> section, int idx, int range);
};

