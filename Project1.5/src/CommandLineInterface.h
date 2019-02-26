/*
 * CommandLineInterface.h
 *
 *  Created on: Feb 22, 2019
 *      Author: Gavin martin for Calvin College cs232
 */

#ifndef COMMANDLINEINTERFACE_H_
#define COMMANDLINEINTERFACE_H_




#include "pthread.h"
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
#include "Model.h"

using namespace std;




class CommandLineInterface {
public:
	CommandLineInterface();
	void say(string aString) const;
	void listOffProcessIDs(vector<pid_t> pids);
	void listOffThreadIDs(vector<long> tids);


private:

};


inline
CommandLineInterface::CommandLineInterface() {
 cout << "\nCommandLineController is using the CommandLineInterface\n\n" << endl;
}

inline
void CommandLineInterface::say(string aString) const{
	cout << aString << endl;
}

inline
void CommandLineInterface::listOffProcessIDs(vector<pid_t> pids){
	cout << "\n" << endl;
	for (unsigned i=0; i < pids.size(); i++){
		cout << "Hello from Child Process: " << pids[i] << endl;
	}
}

inline
void CommandLineInterface::listOffThreadIDs(vector<long> tids){
	cout << "\n" << endl;
	for(unsigned i=0; i < tids.size(); i++){
		cout << "Hello from Child Thread: " << tids[i] << endl;
	}
}


#endif /* COMMANDLINEINTERFACE_H_ */
