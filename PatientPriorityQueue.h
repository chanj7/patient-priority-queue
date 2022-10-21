// Jordan Chan
// PatientPriorityQueue.h
// PURPOSE: Adds, peeks, and removes Patient objects from the min heap

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H
#include <string>
#include <sstream>
#include "Patient.h"
#include <vector>
#include <iomanip>

using namespace std;

class PatientPriorityQueue {
public:
    PatientPriorityQueue();     // constructor
    void add(const Patient &);  // adds Patients to the heap
    string peek(int);           // shows next Patient to be called
    string remove();            // removes Patient from the top of the heap
    int size();                 // how big the heap is
private:
    int capacity;                   // size of the heap

    vector <Patient> patients;      // vector of Patient objects

    void siftUp(int);               // to order into min heap
    void siftDown(int);             // after removing a Patient
    int getParent(int) const;       // finding parent of a Patient
    int getLeftChild(int) const;    // find left child of a parent
    int getRightChild(int) const;   // find right child of a parent
};

PatientPriorityQueue::PatientPriorityQueue() {
/**
 * Constructor; initializes capacity
 */
    capacity = 0;
}

void PatientPriorityQueue::add(const Patient &newPatient) {
/**
 * add function inserts a Patient object into end of the heap and sifts it up if necessary
 * @param newPatient the Patient object being inserted
 */
    patients.push_back(newPatient);
    siftUp(capacity);
    capacity++;
    //nextPatientNumber++;
}

string PatientPriorityQueue::peek(int index) {
/**
 * peek function returns the highest priority patient without removing it
 * @param index the top of the heap
 * @return the highest priority patient's arrival code, priority code, and name
 */
    stringstream ss;
    string priCode;
    if (patients[index].getPriorityCode() == 1)
        priCode = "immediate";
    else if (patients[index].getPriorityCode() == 2)
        priCode = "emergency";
    else if (patients[index].getPriorityCode() == 3)
        priCode = "urgent";
    else if (patients[index].getPriorityCode() == 4)
        priCode = "minimal";

    ss << setw(5) << patients[index].getArrivalOrder() << setw(20) << priCode
       << setw(15) <<patients[index].getName() << endl;
    return ss.str();
}

string PatientPriorityQueue::remove() {
/**
 * remove function takes the root out of the min heap
 * @return the name of the patient at the top of the heap
 */
    // it's a min heap, so take from the top
    stringstream ss;
    if (!patients.empty()) {
        ss << "This patient will now be seen: " << patients[0].getName() << endl;
        patients.pop_back();
        siftDown(0);
    }
    else
        ss << "There are no patients in the waiting area." << endl;
    return ss.str();
    // then get it back into heap order

}

void PatientPriorityQueue::siftUp(int index) {
/**
 * siftUp function checks to see if a Patient object needs to moved up after being inserted at the end of the heap
 * @param index the index of the Patient object
 */
    int parentIdx;
    vector <Patient> temp;
    if (index != 0) {
        parentIdx = getParent(index);
        if (patients[parentIdx] > patients[index]) {
            temp[parentIdx] = patients[parentIdx];
            patients[parentIdx] = patients[index];
            patients[index] = temp[parentIdx];
            siftUp(parentIdx);
        }
    }
}

void PatientPriorityQueue::siftDown(int index) {
/**
 * siftDown function adjusts the min heap after a Patient is removed
 * @param index the index of the removed Patient object
 */
    int leftIdx, rightIdx, maxIdx;
    vector <Patient> temp;
    leftIdx = getLeftChild(index);
    rightIdx = getRightChild(index);

    // find minIdx
    if (rightIdx >= capacity) {
        if (leftIdx >= capacity)
            return;
        else
            maxIdx = leftIdx;
    } else {
        if (patients[leftIdx] >= patients[rightIdx])
            maxIdx = leftIdx;
        else
            maxIdx = rightIdx;
    }

    // swap?
    if (patients[index] > patients[maxIdx]) {
        temp[index] = patients[maxIdx];
        patients[maxIdx] = patients[index];
        patients[index] = temp[index];
        siftDown(maxIdx);
    }
}

int PatientPriorityQueue::getParent(int index) const {
/**
 * getParent function finds the index of a parent node
 * @param index index of the child
 * @return the index of the parent
 */
    return (index - 1) / 2;
}

int PatientPriorityQueue::getLeftChild(int index) const {
/**
 * getLeftChild function finds left child of a node
 * @param index index of the parent
 * @return the index of the left child
 */
    return 2 * index + 1;
}

int PatientPriorityQueue::getRightChild(int index) const {
/**
 * getRightChild function finds right child of a node
 * @param index index of the parent
 * @return the index of the right child
 */
    return 2 * index + 2;
}

int PatientPriorityQueue::size() {
/**
 * size function returns the size of the heap
 * @return the size of the heap
 */
    return capacity;
}

#endif //P3_PATIENTPRIORITYQUEUE_H
