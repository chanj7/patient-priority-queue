// Jordan Chan
// p3.cpp
// PURPOSE: Driver program creates a min heap of Patient objects using the PatientPriorityQueue; can use commands from
// a directory to navigate the patient queue, including peeking which patient is next, calling the next patient, and
// adding new patient to the queue
// INPUT: User input inlcudes different commands they want to take in director; for adding a patient, user includes
// their priority level and name.
// PROCESS: Program uses different functions based on the command defined from user input.
// OUTPUT: Will affirm an action that was taken after a user has inputted a command or new patient into the queue.

#include "PatientPriorityQueue.h"
#include "Patient.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueue &); 
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.


int main() {
/**
 * main method welcomes the user, reads in the user's input, and passes it into the process function, where different
 * functions can be called depending on the user's command
 */
	// declare variables
	string line;

	// welcome message
	welcome();

	// process commands
	PatientPriorityQueue priQueue;
	do {
		cout << "\ntriage> ";
		getline(cin, line);
	} while (processLine(line, priQueue));

	// goodbye message
	goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
/**
 * processLine function takes the user's input and finds the command; calls function based on the command
 * @param line the user's input
 * @param priQueue the PatientPriorityQueue object
 * @return if there is a command or not
 */
	// get command
	string cmd = delimitBySpace(line);
	if (cmd.length() == 0) {
		cout << "Error: no command given." << endl;
		return false;
	}
	
	// process user input
	if (cmd == "help")
		help();
	else if (cmd == "add")
		addPatientCmd(line, priQueue);
	else if (cmd == "peek")
		peekNextCmd(priQueue);
	else if (cmd == "next")
		removePatientCmd(priQueue);
	else if (cmd == "list")
		showPatientListCmd(priQueue);
	else if (cmd == "load")
		execCommandsFromFileCmd(line, priQueue);
	else if (cmd == "quit")
		return false;
	else
		cout << "Error: unrecognized command: " << cmd << endl;

	return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
/**
 * addPatientCmd function passes a new Patient object into the queue
 * @param line the user's input
 * @param priQueue the PatientPriorityQueue object
 */
    string priority, name;

    // get priority and name
    priority = delimitBySpace(line);
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }
    name = line;
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    int priorityNum = 0;

    if (priority == "immediate")
        priorityNum = 1;
    else if (priority == "emergency")
        priorityNum = 2;
    else if (priority == "urgent")
        priorityNum = 3;
    else if (priority == "minimal")
        priorityNum = 4;
    else
        priorityNum = 5;
    Patient newPatient(name, priorityNum);
    priQueue.add(newPatient);
    cout << "\nAdded patient " << name << " to the priority system" << endl;
}

void peekNextCmd(PatientPriorityQueue &priQueue) {
/**
 * peekNextCmd function shows next patient to be seen
 * @param priQueue the PatientPriorityQueue object
 */
    string name, nextPatient, arriv, priority;
    nextPatient = priQueue.peek(0);
    arriv = delimitBySpace(nextPatient);
    priority = nextPatient;
    name = delimitBySpace(priority);
    cout << "Highest priority patient to be called next: " << name;
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
/**
 * removePatientCmd removes and shows next patient to be seen
 * @param priQueue the PatientPriorityQueue object
 */
    string patientCalled = priQueue.remove();
    cout << patientCalled;
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
/**
 * showPatientListCmd function shows patient detail in heap order
 * @param priQueue the PatientPriorityQueue object
 */
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    for (int i = 0; i < priQueue.size(); i++) {
        cout << priQueue.peek(i);
    }
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
/**
 * execCommandsFromFileCmd function processes input from a file
 * @param filename the name of the file being inputted
 * @param priQueue the PatientPriorityQueue object
 */
	ifstream infile;
	string line;

	// open and read from file
	infile.open(filename);
	if (infile) {
		while (getline(infile, line)) {
			cout << "\ntriage> " << line;
			// process file input 
			processLine(line, priQueue);
		} 
	} else {
		cout << "Error: could not open file.\n";
	}
	// close file
	infile.close();
}

string delimitBySpace(string &s) {
/**
 * delimitBySpace function processes the user's input when adding a new patient
 * @param s the user's input
 * @return the parsed string
 */
	unsigned pos = 0;
	char delimiter = ' ';
	string result = ""; 

	pos = s.find(delimiter);
	if (pos != string::npos) {
		result = s.substr(0, pos);
		s.erase(0, pos + 1);
	}
	return result;
}

void welcome() {
/**
 * welcome function welcomes the user
 */
    cout << "\nWelcome to the Patient Priority System!" << endl;
}

void goodbye() {
/**
 * goodbye function ends the program
 */
    cout << "\nThank you for using the Patient Priority System!" << endl;
}	

void help() {
/**
 * help function displays commands and their functions to the user
 */
	cout << "add <priority-code> <patient-name>\n"
<< "            Adds the patient to the triage system.\n"
<< "            <priority-code> must be one of the 4 accepted priority codes:\n"
<< "                1. immediate 2. emergency 3. urgent 4. minimal\n"
<< "            <patient-name>: patient's full legal name (may contain spaces)\n"
<< "next        Announces the patient to be seen next. Takes into account the\n"
<< "            type of emergency and the patient's arrival order.\n"
<< "peek        Displays the patient that is next in line, but keeps in queue\n"
<< "list        Displays the list of all patients that are still waiting\n"
<< "            in the order that they have arrived.\n"
<< "load <file> Reads the file and executes the command on each line\n"
<< "help        Displays this menu\n"
<< "quit        Exits the program\n";
}
