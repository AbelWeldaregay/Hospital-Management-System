#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED
#include "patient.h"
using namespace std;
class record{
private:

    int recordID;///a. id: A unique item number that identifies the record
    string patientID;///b. patient_id: The patient’s id.
    string doctorNotes;///c. Notes: The most recent doctor note about the patient
public:
    void setRecordID(ifstream &inFile){inFile>>recordID;}
    void setPatientID(ifstream &inFile){inFile>>patientID;}
    void setDoctorNotes(ifstream &inFile){inFile>>doctorNotes;}
    int getRecID(){return recordID;}
    string getPatientID(){return patientID;}
    string getDoctorNotes(){return doctorNotes;}
    friend void addRecord(vector <record> &recordType, vector <patient> &patientType);
    friend void updateRecords(vector <record> &recordType);
    record();
};
void printRecords(vector <record> &recordType);
int printRecordMenu();
void deleteRecord(vector <record> &recordType);
void searchRecords(vector <record> &recordType);
#endif // RECORD_H_INCLUDED

