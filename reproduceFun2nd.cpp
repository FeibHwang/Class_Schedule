#include "stdafx.h"
#include "reproduceFun2nd.h"
int reproduceFun(Population *p, int maxGeneration, double mutationRate, double fitSCore_goal) {
	vector<vector<Population::_course>> newGene; // new generation
												 // this attribute needs to be added to class Population
	int itr = 0;
	// idx of the solution chromosome in the base.
	int slnIdx = -1;
	while (itr<maxGeneration) {
		itr++;
		int pSize = p->get_population_size();
		int selectNum = pSize / 2;
		for (int i = 0; i < selectNum; i++) {
			// randomized selection
			srand((int)time(0));
			pair<int, int> tp1 = p->randSelect();
			// mating + mutation
			vector<vector<Population::_course>> tp2 = p->matingFun(tp1.first, tp1.second, mutationRate);
			newGene.push_back(tp2[0]);
			newGene.push_back(tp2[1]);
		}

		// update the chromosome base, this member function needs to be add to Population
		// current method does not keep low fitScore chromosome for diversity

		p->update_chromosome_base(newGene);
		newGene.clear();

		// fitness test

		p->update_group_fitness();
		vector<double> gpfitScore = p->get_group_fitness();
		double scoreMax = (double)INT_MIN;

		for (int i = 0; i < gpfitScore.size(); i++) {
			if (scoreMax < gpfitScore[i]) {
				slnIdx = i;
				scoreMax = gpfitScore[i];
			}
		}
		cout << "generation #--:" << itr << "highest fitness score in this generation--:" << scoreMax << endl;
		cout << endl;

		// find the solution
		if (scoreMax >= fitSCore_goal) {
			cout << "solution found!";
			return slnIdx;
		}

	}

	if (itr == maxGeneration) {
		cout << "quit reproduction due to reach of max generation" << endl;
		cout << endl;
	}

	return slnIdx;
}