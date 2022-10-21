// Jordan Chan
// Patient.h
// PURPOSE: Creates the Patient object, including attributes: name, priority code, and arrival order

#ifndef P3_PATIENT_H
#define P3_PATIENT_H
#include <string>

using namespace std;

class Patient {
public:
    Patient(string &, int);                 // constructor
    ~Patient();                             // destructor
    Patient(string, int, int);              // copy constructor
    bool operator > (const Patient &);      // overloaded > operator
    bool operator >= (const Patient &);     // overloaded >= operator
    bool operator = (const Patient &);  // overloaded = operator
    string getName() const;                 // return name of student
    int getPriorityCode() const;            // return priority code
    int getArrivalOrder() const;            // return arrival order
    void setName(string);                   // mutator
    void setPriorityCode(int);              // mutator
    void setArrivalOrder(int);              // mutator
private:
    string name;                            // name of Patient
    int priorityCode;                       // priority code of Patient
    int arrivalOrder;                       // arrival code of Patient
    static int patientNum;                  // keep count of number of Patients
};

// instantiates static field
int Patient::patientNum = 0;

Patient::Patient(string &patName, int priCode) {
/**
 * Constructor; initializes attributes of Patient object
 * @param patName name of the Patient
 * @param priCode priority code of Patient
 */
    name = patName;
    priorityCode = priCode;
    patientNum++;
    arrivalOrder = patientNum;
}

Patient::~Patient() {
/**
 * Destructor
 */

}

bool Patient::operator > (const Patient &child) {
/**
 * overloaded > operator function overloads the > operator when used in PatientPriorityQueue.h
 * @param child what Patient object is being compared to
 * @return whether or not the statement is true or false
 */
    if (priorityCode > child.priorityCode)
        return true;
    else
        return false;
}

bool Patient::operator >= (const Patient &child) {
/**
 * overloaded >= operator function overloads the >= operator when used in PatientPriorityQueue.h
 * @param child what Patient object is being compared to
 * @return whether or not the statement is true or false
 */
    if (priorityCode >= child.priorityCode)
        return true;
    else
        return false;
}

bool Patient::operator = (const Patient &child) {
/**
 * overloaded = operator function overloads the = operator when used in PatientPriorityQueue.h
 * @param child what Patient object is being compared to
 * @return the Patient object with the right's attributes
 */
    return arrivalOrder == child.arrivalOrder && priorityCode == child.priorityCode && name == child.name;
}

/*Patient::Patient(string patName, int priCode, int arrOrder) {
    name = patName;
    priorityCode = priCode;
    arrivalOrder = arrOrder;
}*/

string Patient::getName() const {
/**
 * getName function is getter for name
 * @return name of Patient
 */
    return name;
}

int Patient::getPriorityCode() const {
/**
 * getPriorityCode function is getter for for priority code
 * @return priority code of Patient
 */
    return priorityCode;
}

int Patient::getArrivalOrder() const {
/**
 * getArrivalOrder function is getter for arrival order
 * @return arrival order of Patient
 */
    return arrivalOrder;
}

void Patient::setName(string patName) {
/**
 * setName function is setter for patient name
 * @param patName name of Patient
 */
    name = patName;
}

void Patient::setPriorityCode(int priCode) {
/**
 * setPriorityCode function is setter for priority code
 * @param priCode priority code of Patient
 */
    priorityCode = priCode;
}

void Patient::setArrivalOrder(int arrOrder) {
/**
 * setArrivalOrder function is setter for arrival order
 * @param arrOrder arrival order of Patient
 */
    arrivalOrder = arrOrder;
}

#endif //P3_PATIENT_H
