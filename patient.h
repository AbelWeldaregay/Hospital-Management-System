#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED
#include "doctors.h"

using namespace std;

class patient{
private:
    string id;
    string doctor_id;
    int record_id;
    string patientName;
    string phoneNumber;
    char gender;
    string email;
    string blood_Type;
    int numOfPatients;
public:
    void setID(ifstream &inFile){inFile >>id;}
    void ceeinID(int &newIDs){id=newIDs;}
    void setDocID(ifstream &inFile){inFile>>doctor_id;}
    void setRecID(ifstream &inFile){inFile>>record_id;}
    void setPatientName(ifstream &inFile){inFile>>patientName;}
    void setPhoneNumber(ifstream &inFile){inFile>>phoneNumber;}
    void setGender(ifstream &inFile){inFile>>gender;}
    void setPatientEmail(ifstream &inFile){inFile>>email;}
    void setBloodType(ifstream &inFile){inFile>>blood_Type;}
    void setNumofPatients(ifstream &inFile){inFile>>numOfPatients;}
    string getID(){return id;}
    string getDocID()const{return doctor_id;}
    int getRecID(){return record_id;}

    string getPatientName(){return patientName;}
    string getPhoneNumber(){return phoneNumber;}
    char getPatientGender(){return gender;};
    string getPatientEmail(){return email;}
    string getPatientBloodType(){return blood_Type;}
    int getNumofPatients(){return numOfPatients;}
    void readPatientsFile(ifstream &inFile, vector <patient> patientType);
    void printpatient();
    friend void addANewPatient(vector <patient> &patientType);
    friend void deletePatient(vector <patient> &patientType);
    friend void searchPatient(vector <patient> patientType, int caseChoice);
    friend void printSearchResult(int indexOfwantedPatient, vector <patient> patientType);
    friend void findUpdateName(vector <patient> &patientType, string patientName);
    friend void findUpdateID(vector <patient> &patientType, string patientName);
    friend void findUpdateDocPatientID(vector <patient> &patientType, string patientName);
    friend void findUpdatePatientRecID(vector <patient> &patientType, string patientName);
    friend void findUpdatePhoneNum(vector <patient> &patientType, string patientName);
    friend void findUpdateGender(vector <patient> &patientType, string patientName);
    friend void findUpDateEmail(vector <patient> &patientType, string patientName);
    friend void findUpDateBloodType(vector <patient> &patientType, string patientName);
    patient();
};
void readPatientsFile(ifstream &inFile, vector <patient> &patientType);
void addANewPatient(vector <patient> &patientType);
void searchPatient(vector <patient> patientType, int caseChoice);
int printPatientsMenu();
void updatePatientInfo(vector <patient> &patientType);
int displayPatientUpdateMenu();
void deletePatient(vector <patient> &patientType);
void findUpDateBloodType(vector <patient> &patientType, string patientName);
void findUpDateEmail(vector <patient> &patientType, string patientName);
void findUpdateGender(vector <patient> &patientType, string patientName);
void findUpdatePhoneNum(vector <patient> &patientType, string patientName);
void findUpdatePatientRecID(vector <patient> &patientType, string patientName);
void findUpdateDocPatientID(vector <patient> &patientType, string patientName);
void findUpdateID(vector <patient> &patientType, string patientName);
void findUpdateName(vector <patient> &patientType, string patientName);
void printSearchResult(int indexOfwantedPatient, vector <patient> patientType);

#endif // PATIENT_H_INCLUDED
