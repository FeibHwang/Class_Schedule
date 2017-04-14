#pragma once
class Course_Class
{
public:
	Course_Class(int a, int b, int c);
	Course_Class();
	~Course_Class();

	inline int get_class_id() {return _class_id;};

	inline int get_course_id() { return _course_id; };

	inline int get_professor_id() { return _professor_id; };

private:
	int _class_id;
	int _course_id;
	int _professor_id;
};

