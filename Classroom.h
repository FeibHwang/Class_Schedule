#include<string>
#include<vector>

#pragma once
class Classroom
{
public:
	Classroom(int _id, int _seats, int _type);
	Classroom();

	inline int get_room_id() { return _id; }

	~Classroom();

private:
	int _id;
	int _seats;
	int _type;

};

