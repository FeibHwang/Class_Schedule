#include "stdafx.h"
#include "reproduceFun.h"
#include <utility>
int reproduceFun(Population *p, int maxGeneration, double mutationRate, double fitSCore_goal) {
	vector<vector<Population::_case>> newGene; // new generation
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
			vector<vector<Population::_case>> tp2 = p->matingFun(tp1.first, tp1.second, mutationRate);
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



vector<vector<Population::_case>> passDown(double perX, double perY, vector<vector<Population::_case>> prevGene, vector<double> prevFScore) {
	vector<pair<double, int>> fScore_idx;

	for (int i = 0; i<prevFScore.size(); i++) {
		fScore_idx.push_back(pair<double, int>{prevFScore[i], i});
	}
	sort(fScore_idx.begin(), fScore_idx.end(), [](pair<double, int> a, pair<double, int> b) {return (a.first > b.first) ? 1 : 0; });

	double len = double(fScore_idx.size());
	int X = int(perX*len);
	int Y = int(perY*len);

	vector<vector<Population::_case>> oldChromo;

	for (int i = 0; (i <= X && i<fScore_idx.size()); i++) {
		oldChromo.push_back(prevGene[fScore_idx[i].second]);
	}

	for (int i = fScore_idx.size() - 1, cnt = Y; (i >= 0 && cnt >= 0); i--, cnt--) {
		oldChromo.push_back(prevGene[fScore_idx[i].second]);
	}

	return oldChromo;
}


// overloaded function
// perX represents the percentage of high fScore chromosomes from previous generation were selected to pass to next generation to keep high fScores 
// perY represents the percentage of low fScoure chromosomes from previous generation were selected to pass to next generation to keep diversity
int reproduceFun(Population *p, int maxGeneration, double mutationRate, double fitSCore_goal,double perX, double perY) {
	
												 
	// perZ represents the percentage of new chromosomes generated through matingFun()
	double perZ = 1 - (perX + perY);

	int itr = 0;
	// idx of the solution chromosome in the base.
	int slnIdx = -1;
	
	while (itr<maxGeneration) {
		
		itr++;
		vector<double> prevFScore = p->get_group_fitness(); // previous generation's fScore
		vector<vector<Population::_case>> prevGene = p->get_whole_group(); // previous generation's chromosome_base
		vector<vector<Population::_case>> newGene = passDown(perX, perY, prevGene, prevFScore); // new generation
		
		
		double pSize = double(p->get_population_size());
		int selectNum = int ( (pSize*perZ) / 2);
		for (int i = 0; i < selectNum; i++) {
			// randomized selection
			srand((int)time(0)+i);
			
			pair<int, int> tp1 = p->randSelect();
			// mating + mutation
			
			vector<vector<Population::_case>> tp2 = p->matingFun(tp1.first, tp1.second, mutationRate);
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