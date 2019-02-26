
//============================================================================
// Name        : Project1.cpp
// Author      : Gavin Martin
// Version     : 1.0
// Copyright   : Any attempt at copyrighting this, would be plagerism and is punishable by death, or worse, expulsion
// Description : Project1
//============================================================================

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
#include <pthread.h>
using namespace std;

// argc is argument count and argv is argument vector


/*
g++ Project1.cpp -o main -lpthread
./main test the world
 */


/**
 * @param: int n - the nth process created in the loop
 * @param: NanoTimer &timer - the timer object that stores time to create a process
 * @description: this creates a process, asks it to say something, and terminates
 */
void createProccess(int counter, NanoTimer &timer){
	// timer is started to record fork time
	timer.start();
	// a child process is forked from the parent
	pid_t pid = fork();
	timer.stop();
	// if it hasn't reached the n repititions specified in r, and its a child:
	if((counter > 0) && pid == 0){
		// print out the Proccess ID of the child
		cout << "Hello from the child process (PID = " << getpid() << ")" << endl;
		// recursivly call it again with a counter of 1 less
		createProccess(counter - 1, timer);
		// if this is the last child
	} else if (counter == 0 && pid == 0){
		// do nothing
		return;
		// if this is a parent
	} else if (pid != 0){
		// die
		exit(0);
	}
}


/**
 * @param: void *id: this is the threadID
 * @description: this prints the thread's id upon its creation
 */
void *declareThread(void *id){
	long tid;
	tid = (long)id;
	cout << "\n" << "Hello from the child thread (TID = " << tid << ")" << endl;
	// the thread kills itself
	pthread_exit(NULL);
}


/**
 * @param: int counter - the rn of repititions to create
 * @param: NanoTimer &timer - the timer to record the thread creation time
 * @param: pthread_t &thread - the original thread created for this function
 * @description: this creates counter number of threads
 */
void createThread(int counter, NanoTimer &timer, pthread_t &thread) {
	// rc is created for error handling
	int rc;
	int i;
	// threads are placed in an array
	pthread_t threads[counter];
	// for rn repitions
	for( i = 0; i < counter; i++ ) {
		timer.start();
		// create a thread and declare it
		rc = pthread_create(&threads[i], NULL, declareThread, (void *)i );
		timer.stop();
		// otherwise if error, show the error
		if (rc) {
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}
}



/**
 * @description: this is the main function, it determines average time to create proccesses and threads
 */
int main ( int argc, char *argv[] ) {

	// set flags to false until otherwise changed
	bool r_flag = false;
	bool t_flag = false;
	bool p_flag = false;
	// default of r_num is set to 1
	double r_num = 1.0;

	// initialize tiemrs
	NanoTimer pTimer;
	NanoTimer tTimer;

	cout << "You have entered " << argc
			<< " arguments:" << "\n";
	// if another arg was entered
	if(argc > 1){
		vector<string> argList;
		for (int i=0; i < argc; i++) {
			// push every arg into a vector of args
			argList.push_back( argv[i] );
			cout << argList[i] << endl;
			// this gets the prefix flag of the arguments entered
			string prefix = argList[i].substr(0,2);
			cout << "prefix: " << prefix << endl;
			if(prefix == "-r"){
				r_flag = true;
				// this gets the -r number if its flag was set to true
				r_num = atoi( (argList[i].substr(2)).c_str() );
				// if the p flag was called
			} else if (prefix == "-p"){
				p_flag = true;
				// if the t flag was called
			} else if (prefix == "-t"){
				t_flag = true;
			} else if (prefix == "./"){
				// do nothing if this its the first argument
				continue;
			} else {
				throw invalid_argument( "Use a Flag: -rn, -p, or -t");
			}
			cout << "" << endl;
		}
		// creates r_num processes with a timer to time their creation
		if(p_flag == true){
			createProccess(r_num, pTimer);
		}
		// creates r_num threads with a timer to time their creation
		if(t_flag == true) {
			pthread_t newthread;
			createThread(r_num, tTimer, newthread);
		}
	}


	if(p_flag == true){
		// gets the average proccess and prints it
		double averagePTime = pTimer.asDouble() / r_num;
		cout << "Processes took an average of: " << averagePTime << " seconds per processes with an average of " << r_num << " repetitions" << endl;
	}
	if(t_flag == true){
		// gets the average thread creation time and prints it
		double averageTTime = tTimer.asDouble() / r_num;
		cout << "Thread took an average of: " << averageTTime << " seconds per processes with an average of " << r_num << " repetitions" << endl;
	}
	return 0;
}

