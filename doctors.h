#ifndef DOCTORS_H_INCLUDED
#define DOCTORS_H_INCLUDED
#include "patient.h"

using namespace std;

class doctor{
private:
    string doc_ID;
    string doc_userName;
    string doc_password;
    string doc_name;
    string doc_phone;
    string doc_speciality;
    int numOfDoctors;
public:
    void setdocID(ifstream &inFile){inFile>>doc_ID;}
    void setdocUserName(ifstream &inFile){inFile>>doc_userName;}
    void setDocPassword(ifstream &inFile){inFile>>doc_password;}
    void setDocName(ifstream &inFile){inFile>>doc_name;}
    void setDocPhone(ifstream &inFile){inFile>>doc_phone;}
    void setDocSpeciality(ifstream &inFile){inFile>>doc_speciality;}
    void setNumOfDoctors(ifstream &inFile){inFile>>numOfDoctors;}
    string getDocID(){return doc_ID;}
    string getdocUserName(){return doc_userName;}
    string getDocPassword(){return doc_password;}
    string getDocName(){return doc_name;}
    string getDocPhone(){return doc_phone;}
    string getDocSpeciality(){return doc_speciality;}
    int getNumOfDoctors(){return numOfDoctors;}
    void readDoctorFile(ifstream &inFile, vector <doctor> &doctorType);
    friend void updateDoctorsInfo(vector <doctor> &doctorType);
    doctor();
};
void printDoctorsFile(vector <doctor> doctorType);
int printDoctorsMenu();
void showAllDoctors(vector <doctor> doctorType);
void updateDoctorsInfo(vector <doctor> &doctorType);
void searchDoctorByName(vector <doctor> &doctorType);

#endif // DOCTORS_H_INCLUDED
