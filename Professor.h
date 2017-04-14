#include<string>
#include<vector>

using namespace std;


#pragma once
class Professor
{
public:
	Professor(int _id, string _name, vector<int> prefer);

	Professor();

	~Professor();

	inline int getid() const { return _idd; }

	inline string getName() const { return _namee; }

	inline vector<int> get_forbid_time() const { return _forbit_time; }

	inline vector<int> get_prefer_time() const { return _prefer_time; }

	void set_forbit_time(vector<int> ftime);


private:
	int _idd;
	string _namee;
	vector<int> _prefer_time;
	vector<int> _forbit_time;
};

