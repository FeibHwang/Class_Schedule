#include<string>
#include<vector>

using namespace std;

#pragma once
class Classes
{
public:
	Classes(int _id, int _students, int _course, int _professor);
	~Classes();

private:
	int _id;
	int _students;
	int _course;
	int _professor;
};

