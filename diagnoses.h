#ifndef DIAGNOSES_H_INCLUDED
#define DIAGNOSES_H_INCLUDED
#include "diagnoses.h"
using namespace std;

class diagnoses
{
private:
    int numOfDiagnoses;
    int diagnosesID;
    std::string diagnosesName;
public:
    void setNumofDiagnoses(ifstream &inFile){inFile>>numOfDiagnoses;}
    void setDiagnosesName(ifstream &inFile){getline(inFile, diagnosesName);}
    int getNumofDiagnosis(){return numOfDiagnoses;}
    int getDiagnosisID(){return diagnosesID;}
    std::string  getDiagnosisName(){return diagnosesName;}
    void setDName(string name){diagnosesName=name;}
    diagnoses();
    template <class generic>
    friend void initializeDiagnosesID(vector <generic> &genericType);
};

void readDiagnosisFile(ifstream &inFile, vector <diagnoses> &diagnosesType);
void printDiagnoses(vector <diagnoses> &diagnosesType);
#endif // DIAGNOSES_H_INCLUDED
