/*
 * TextMenuInterface.h
 *
 *  Created on: Feb 22, 2019
 *      Author: Gavin Martin @ cs232 at calvin college
 */

#ifndef TEXTMENUINTERFACE_H_
#define TEXTMENUINTERFACE_H_



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
#include "TextMenuController.h"
#include <stdlib.h>

using namespace std;




class TextMenuInterface {
public:
	TextMenuInterface();
	void say(string aString);
	bool askIf(string aString);
	int askForRepetitions();
	void listOffProcessIDs(vector<pid_t> pids);
	void listOffThreadIDs(vector<long> tids);


private:
	bool validResponse(string response);
	long isNumber(string response);

};


inline
TextMenuInterface::TextMenuInterface() {

}

inline
// this makes the textMenuInterface say something
void TextMenuInterface::say(string aString){
	cout << aString << endl;
}

inline
// this asks the user a yes or no question which will be stored on the controller
bool TextMenuInterface::askIf(string aString) {
	string response;
	cout << "\n\n\n\n\n\n\n===============================================" << endl;
	cout << "Welcome to the User-Friendly Text Interface" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "\n Create a " << aString << "?" << endl;
	cout << "  -- 1.) Yes" << endl;
	cout << "  -- 0.) No\n" << endl;
	cout << " (Please Enter a 1 or 0)" << endl;
	cout << "\n ---> " << flush;
	cin >> response;
	while(true){
		if(validResponse(response) == true){
			cout << "\nInput Accepted" << endl;
			if(response == "1"){
				return true;
			} else if(response == "0"){
				return false;
			}
		} else {
			cout << " (Please Enter a 1 or 0)" << endl;
			cout << "\n ---> " << flush;
			cin >> response;
		}
	}
	cout << "\n\n===============================================" << endl;
}

// this asks the textMenuInterface how many repetitions it wants to get the average of
int TextMenuInterface::askForRepetitions() {
	string response;
	cout << "\n\n\n\n\n\n\n===============================================" << endl;
	cout << "Welcome to the User-Friendly Text Interface" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "\n How many repetitions would you like?" << endl;
	cout << "\n ---> " << flush;
	cin >> response;
	while(true){
		if(isNumber(response) != 0){
			cout << "\nInput Accepted" << endl;
			return isNumber(response);
		} else {
			cout << " Please enter a whole number" << endl;
			cout << "\n ---> " << flush;
			cin >> response;
		}
	}
	cout << "\n\n===============================================" << endl;
}

inline
// this determines if its a number, it returns -1 if its not, or the string converted to a long if it is a valid number
long TextMenuInterface::isNumber(string response){
	char* p;
	long converted = strtol(response.c_str(), &p, 10);
	if (*p){
		return -1;
	} else {
		return converted;
	}
}


inline
// this determines if the response was a 1 or a 0, the two valid responses
bool TextMenuInterface::validResponse(string response) {
	if(response == "0" || response == "1"){
		return true;
	} else {
		return false;
	}
}


inline
// this lists off all the process ids stored from the array
void TextMenuInterface::listOffProcessIDs(vector<pid_t> pids){
	for (unsigned i=0; i < pids.size(); i++){
		cout << "Hello from Child Process: " << pids[i] << endl;
	}
}


inline
// this lists off all the thread ids stored from the array
void TextMenuInterface::listOffThreadIDs(vector<long> tids){
	for(unsigned i=0; i < tids.size(); i++){
		cout << "Hello from Child Thread: " << tids[i] << endl;
	}
}

#endif /* TEXTMENUINTERFACE_H_ */
