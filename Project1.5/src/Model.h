/*
 * Model.h provides a model to proccess data from the controllers
 *  Created by: Gavin Martin, for CS 232 at Calvin College.
 *
 * Model.h
 *
 *  Created on: Feb 19, 2019
 *      Author: Gavin martin
 */

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
#include <sys/types.h>
#include <bits/stdc++.h>



#ifndef MODEL_H_
#define MODEL_H_


class Model {
public:
	Model();
	// proccess functions
	double getAvgProcessTime(double repetitions);
	double createProcess( double repetitions);
	// thread functions
	double getAvgThreadTime(double repetitions);
	double createThread( int repetitions);
	// store ids into an array functions
	vector<pid_t> getPids() const;
	vector<long> getTids() const;




private:
	NanoTimer pTimer;
	NanoTimer tTimer;
	vector<long> threadIDs;
	vector<pid_t> processIDs;
};

// starts the model creation
Model::Model(){
}



/**
 * @param: double repetitions - the nth process created in the loop
 * @description: this creates a process, asks it to say something, and terminates
 * @returns: the recursive function that eventually gives the total time needed to create all processes
 */
double Model::createProcess( double repetitions) {
	// timer is reset to assure its holds a valid time
	pTimer.reset();
	// timer is started to record fork time
	pTimer.start();
	// a child process is forked from the parent
	pid_t pid = fork();
	// the timer is stopped
	pTimer.stop();
	// if it hasn't reached the n repititions specified in r, and its a child:
	if(pid == 0 && repetitions > 0){
		// print out the Proccess ID of the child
		processIDs.push_back(getpid());
		//cout << "Hello from the child process (PID = " << getpid() << ")" << endl;
		// recursivly call it again with a counter of 1 less
		return createProcess(repetitions - 1);
		// if one repetition was specified, use the child from that fork
	} else if (pid != 0){
		exit(0);
		// if its the last child
	} else if (pid == 0 || repetitions == 0){
		return pTimer.asDouble();
	}
}


/**
 * @param: double repetitions - the nth process created in the loop
 * @description: this starts the process to get average processing time
 */
inline
double Model::getAvgProcessTime(double repetitions) {
	// timer is reset to assure its holds a valid time
	pTimer.reset();
	processIDs.clear();
	double totalTime = createProcess(repetitions);
	return (totalTime / repetitions);
}

inline
// a getter function to give controllers all processIds
vector<pid_t> Model::getPids() const {
	return processIDs;
}

inline
// a getter function to give controllers all threadIds
vector<long> Model::getTids() const {
	return threadIDs;
}



/**
 * @param: void *id: this is the threadID
 * @description: this returns the id to be added to a vector upon creation
 */
void* declareThread(void* id){
	long tid;
	tid = (long)id;
	//cout << "\n" << "Hello from the child thread (TID = " << tid << ")" << endl;
	return (void *) tid;

}



/**
 * @param: int repetitions - the rn of repititions to create
 * @description: this creates repetitions number of threads recursively
 */
inline
double Model::createThread( int repetitions) {
	// err is created for error handling
	int err;
	long i;
	// threads are placed in an array
	pthread_t threads[repetitions];

	// for all repitions
	for( i = 0; i < repetitions; i++ ) {
		// this saves the ids in status
		void *status;
		tTimer.start();
		// create a thread and declare it
		pthread_create(&threads[i], NULL, declareThread, (void*)i );
		tTimer.stop();
		// joins pthread back again saving its id in status
		err = pthread_join(threads[i], &status);
		if(err == 0){
			long tid = *((long *)&status);
			// adds id to vector to return later
			threadIDs.push_back(tid);
			// otherwise if error, show the error
		} else if(err == -1) {
			cout << "Error:something went wrong," << err << endl;
			exit(-1);
		}
	}
	return tTimer.asDouble();
}


inline
// this function starts the process to determien average thread time
double Model::getAvgThreadTime(double repetitions) {
	tTimer.reset();
	long reps = (long) repetitions;
	double totalThreadTime = createThread(reps);
	// this is the average time per thread creation
	return totalThreadTime / reps;
}


#endif /* MODEL_H_ */
