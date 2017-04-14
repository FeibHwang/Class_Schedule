// Course_Schedule_pt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Population.h"
#include "reproduceFun.h"
#include <iostream>
#include <stdlib.h>
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

using namespace std;

void ECE_schedule_init(Population *t)
{
	t->add_professor(100, "AA"); t->add_professor(101, "AB"); t->add_professor(102, "AC"); t->add_professor(104, "AD");

	t->add_professor(105, "AE"); t->add_professor(106, "AF"); t->add_professor(107, "AG"); t->add_professor(108, "AH");

	t->add_professor(109, "AI"); t->add_professor(110, "AJ"); t->add_professor(111, "AK"); t->add_professor(112, "AL");

	t->add_professor(113, "AM"); t->add_professor(114, "AN"); t->add_professor(115, "AO"); t->add_professor(116, "AP");

	t->add_professor(117, "AQ"); t->add_professor(118, "AR"); t->add_professor(119, "AS"); t->add_professor(120, "AT");

	t->add_professor(121, "AU"); t->add_professor(122, "AV"); t->add_professor(123, "AW"); t->add_professor(124, "AX");

	//t->add_professor(125, "AY"); t->add_professor(126, "AZ");  t->add_professor(127, "BA");

	//t->add_professor(128, "BB"); t->add_professor(129, "BC");


	t->add_course(1, "CL", "AA"); t->add_course(2, "AN", "AB"); t->add_course(3, "IO", "AC"); t->add_course(4, "IRS", "AD");

	t->add_course(5, "ME", "AE"); t->add_course(6, "SPT", "AF"); t->add_course(7, "SIEM", "AG"); t->add_course(8, "EM", "AH");

	t->add_course(9, "HVEL", "AI"); t->add_course(10, "IWN", "AJ"); t->add_course(11, "IDSP", "AK"); t->add_course(12, "MIP", "AL");

	t->add_course(13, "RTDSPL", "AM"); t->add_course(14, "FPMICVS", "AN"); t->add_course(15, "CAD", "AO"); t->add_course(16, "CH", "AP");

	t->add_course(17, "PCS", "AQ"); t->add_course(18, "PM", "AR"); t->add_course(19, "SPDE", "AS"); t->add_course(20, "EFT", "AT");

	t->add_course(21, "ATAVD", "AU"); t->add_course(22, "EP", "AV"); t->add_course(23, "NOA", "AW"); t->add_course(24, "AATD", "AX");



	t->add_class(50, "CL", "AA"); t->add_class(51, "AN", "AB"); t->add_class(52, "IO", "AC"); t->add_class(53, "IRS", "AD");

	t->add_class(54, "ME", "AE"); t->add_class(55, "SPT", "AF"); t->add_class(56, "SIEM", "AG"); t->add_class(57, "EM", "AH");

	t->add_class(58, "HVEL", "AI"); t->add_class(59, "IWN", "AJ"); t->add_class(60, "IDSP", "AK"); t->add_class(61, "MIP", "AL");

	t->add_class(62, "RTDSPL", "AM"); t->add_class(63, "FPMICVS", "AN"); t->add_class(64, "CAD", "AO"); t->add_class(65, "CH", "AP");

	t->add_class(66, "PCS", "AQ"); t->add_class(67, "PM", "AR"); t->add_class(68, "SPDE", "AS"); t->add_class(69, "EFT", "AT");

	t->add_class(70, "ATAVD", "AU"); t->add_class(71, "EP", "AV"); t->add_class(72, "NOA", "AW"); t->add_class(73, "AATD", "AX");
	//t->add_course(25, "ATEM", "AY"); t->add_course(26, "ATPS", "AZ"); t->add_course(27, "HDS", "BA"); t->add_course(28, "SMCES", "BB");

	//t->add_course(29, "ACD", "BC");

	t->add_class_room(1);
	t->add_class_room(2);
	t->add_class_room(3);
	t->add_class_room(4);

	t->set_time(10);
}


int main()
{
	for (int cnt = 0; cnt < 1; ++cnt)
	{
		Population *t1 = new Population;
		ECE_schedule_init(t1);
		t1->generate_init_group(50);
		t1->update_group_fitness();
			
		// int index = reproduceFun(t1, 1000, 0.3, 1);
		int index = reproduceFun(t1, 100000, 0.3, 1, 0.3, 0.05);
		t1->update_group_fitness();
		t1->print_schedule(t1->get_whole_group()[index], 10);
		auto k = t1->get_fitness_score();
		delete t1;
		cout << endl << endl << endl;
	}

	

	system("pause");
	return 0;
}


