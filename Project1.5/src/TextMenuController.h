/* TextMenuController.h provides a text menu controller for Project1.5
 *  Created by: Gavin Martin, for CS 232 at Calvin College.
 *
 * TextMenuController.h
 *
 *  Created on: Feb 22, 2019
 *      Author: Gavin martin
 */

#ifndef TEXTMENUCONTROLLER_H_
#define TEXTMENUCONTROLLER_H_


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
#include "TextMenuInterface.h"

using namespace std;




class TextMenuCtrl {
public:
	TextMenuCtrl(int argc);
	void run();

private:
	// flags
	bool t_flag;
	bool p_flag;
	double r_num;
};


inline
TextMenuCtrl::TextMenuCtrl(int argc) {
	t_flag = false;
	p_flag = false;
	r_num = 1.0;
}

inline
// this runs the textController
void TextMenuCtrl::run(){

	TextMenuInterface view;
	if(view.askIf("Process") == true){
		p_flag = true;
	}
	if(view.askIf("Thread") == true) {
		t_flag = true;
	}
	Model model;
	// if the user wanted a thread
	if(t_flag == true){
		// this gets repetitions from the view
		r_num = view.askForRepetitions();
		// this computes the data from the model
		double averageThreadTime = model.getAvgThreadTime(r_num);
		// this gets the threadIDs from the model
		vector<long> tidList = model.getTids();
		// this prints off the thread ids from the model
		view.listOffThreadIDs(tidList);
		view.say("Average Thread Time: " + to_string(averageThreadTime ));
	}
	// if the user wanted a process
	if (p_flag == true) {
		// this gets the average process time for a process
		double averageProcessTime = model.getAvgProcessTime(r_num);
		//gets process ids
		vector<pid_t> pidList = model.getPids();
		// sends that data to user
		view.listOffProcessIDs(pidList);
		view.say("Average Process Time: " + to_string(averageProcessTime));
	}



}



#endif /* TEXTMENUCONTROLLER_H_ */
