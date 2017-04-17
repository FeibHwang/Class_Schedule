#include<string>
#include<vector>
#include<unordered_set>
#include <iterator>

using namespace std;


#pragma once
class Professor
{
public:
	Professor(int _id, string _name, vector<int> prefer);

	Professor();

	~Professor();

	inline int getid() { return _idd; }

	inline string getName() { return _namee; }

	inline vector<int> get_forbid_time() { return _forbit_time; }

	inline unordered_set<int> get_prefer_time() { return _prefer_time; }

	

	void set_forbit_time(vector<int> ftime);

	inline void set_prefer_time(vector<int> ptime) { 
		_prefer_time.clear();
		copy(ptime.begin(), ptime.end(), inserter(_prefer_time, _prefer_time.end()));
	}



private:
	int _idd;
	string _namee;
	unordered_set<int> _prefer_time;
	vector<int> _forbit_time;
};

