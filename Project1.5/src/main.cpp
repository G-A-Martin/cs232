//============================================================================
// Name        : Project1.5.cpp
// Author      : Gavin Martin
// Version     :
// Copyright   : Plagerism of this will result in death
//============================================================================

#include <pthread.h>
#include <iostream>
#include <iostream>
#include <stdexcept>
#include "Timer.h"
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "CommandLineController.h"
#include "TextMenuController.h"
using namespace std;



/*
g++ Project1.cpp -o main -lpthread -std=c++11
./main test the world
 */



/**
 * @description: this is the main function, it determines average time to create proccesses and threads
 */
int main ( int argc, char *argv[] ) {
	bool cl_flag = false;

	if(argc > 1){
		// this isn't processing, its to get the -cl prefix
		vector<string> argList;
		for (int i=0; i < argc; i++) {
			// push every arg into a vector of args
			argList.push_back( argv[i] );
			// this gets the prefix flag of the arguments entered
			string prefix = argList[i].substr(0,3);
			// this means the command line was specified
			if(prefix == "-cl"){
				cl_flag = true;
			}
		}
		if(cl_flag == true){
			CmdLineCtrl clController(argc, argList);
			clController.run();
		} else {
			TextMenuCtrl txtController(argc);
			txtController.run();
		}
	} else {
		TextMenuCtrl txtController(argc);
		txtController.run();
	}
	return 0;
}

