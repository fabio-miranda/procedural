#ifndef RANDOM_H
#define RANDOM_H

#include <iostream> 
#include <ctime> 
#include <cstdlib>

using namespace std;

static class Random
{
public:
	static void Init(){
		//srand((unsigned)time(0));
		srand(0);

	}

	static int Next(int bottom, int top){
		
		


		int range = (top - bottom) +1;
		
		int int_random = bottom + int(range * rand()/(RAND_MAX + 1.0));

		//cout << int_random;
		//cout << "\n";

		return int_random;

		

		

	}
};

#endif