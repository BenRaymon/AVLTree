/*
 * MainPhrase.cpp
 *
 *  Created on: Nov 1, 2020
 *      Author: Ben Raymon
 */

#include <iostream>
#include "StudentTreeInfo.hpp"
using namespace std;

int main() {

	StudentTreeInfo *studtree = new StudentTreeInfo("StudentAnswers.txt");
	studtree->Interface();
	return 0;

}


