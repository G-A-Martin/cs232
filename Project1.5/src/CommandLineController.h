/* CommandLineController.h provides a command line controller for Project1.5
 *  Created by: Gavin Martin, for CS 232 at Calvin College.
 *
 * CommandLineController.h
 *
 *  Created on: Feb 19, 2019
 *      Author: Gavin martin for cs232 at Calvin college
 */

#ifndef COMMANDLINECONTROLLER_H_
#define COMMANDLINECONTROLLER_H_


#include "pthread.h"
#include <iostream>
#include <iostream>
#include <stdexcept>
#include "Timer.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <bits/stdc++.h>
#include "Model.h"
#include "CommandLineInterface.h"

using namespace std;


class CmdLineCtrl {
public:
	CmdLineCtrl(int numberOfArgs, vector<string> listOfArgs);
	void run();

private:
	bool t_flag;
	bool p_flag;
	double r_num;
	int argc;
	vector<string> argList;
};

inline
CmdLineCtrl::CmdLineCtrl(int numberOfArgs, vector<string> listOfArgs) {
	argc = numberOfArgs;
	argList = listOfArgs;
	t_flag = false;
	p_flag = false;		// if proccesses
	r_num = 1.0; // number of repetitions
}

inline
void CmdLineCtrl::run() {
	Model model;

	// first create the view:
	CommandLineInterface view;

	// this grabs the flags from the arglist
	for(int i=0; i < argc; i++){
		if(argList[i] == "-p" || argList[i] == "-process"){
			p_flag = true;
		} else if (argList[i] == "-t" || argList[i] == "-thread"){
			t_flag = true;
		} else if (argList[i].substr(0,2) == "-r"){
			r_num = atoi( (argList[i].substr(2)).c_str() );
		}
	}

	// this declares all variables:
	double averageProcessTime;		// calculated average proccess creation time
	double averageThreadTime;		// calculated average thread creation time
	vector<pid_t> pidList;  // list of all process ids
	vector<long> tidList; // list of all thread ids

	// this gets information from the model
	if(p_flag == true){
		averageProcessTime = model.getAvgProcessTime(r_num);
		pidList = model.getPids();
	}
	if(t_flag == true){
		averageThreadTime = model.getAvgThreadTime(r_num);
		tidList = model.getTids();
	}

	// this sends information to the view in a neat Command line way
	view.listOffProcessIDs(pidList);
	view.listOffThreadIDs(tidList);
	view.say("\nAverage Process Time: " + to_string(averageProcessTime));
	view.say("\nAverage Thread Time: " + to_string(averageThreadTime ));



}





#endif /* COMMANDLINECONTROLLER_H_ */
