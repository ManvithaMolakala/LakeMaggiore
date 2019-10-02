//============================================================================
// Name        : main_lakemaggiore.cpp
// Author      : MatteoG
// Version     :
// Copyright   : Your copyright notice
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <fstream>
#include<ctime>
#include "../src/model_lakemaggiore.h"
#include "../src/moeaframework.h"

using namespace std;


int main(int argc, char* argv[]) {

	// user input file
	string input_file = argv[1];

	// Lake Maggiore Problem
	model_lakemaggiore lakemaggioreProblem(input_file);
	int nvars = lakemaggioreProblem.getNvar();
	int nobjs = lakemaggioreProblem.getNobj();
	double vars[nvars];
	double objs[nobjs];

	// optimization
	clock_t start, end;
	start = clock();

	MOEA_Init(nobjs, 0);
	while (MOEA_Next_solution() == MOEA_SUCCESS) {
		MOEA_Read_doubles(nvars, vars);
		lakemaggioreProblem.evaluate(vars, objs);
		MOEA_Write(objs, NULL);
	}
	end = clock();
	cout << "time elapsed: " << ((end - start)/double(CLOCKS_PER_SEC)) << " seconds" << endl;

	return EXIT_SUCCESS;

}
