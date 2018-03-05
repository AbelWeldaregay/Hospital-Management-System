#include <iostream>
#include <fstream>
#include <vector>
#include "diagnoses.h" //including all the data inside the diagnosis.h file

using namespace std;

///function to read the diagnosis file into the diagnoses adt
void readDiagnosisFile(ifstream &inFile, vector <diagnoses> &diagnosesType)
{
    diagnoses diagnosesAccessor;

    diagnosesAccessor.setNumofDiagnoses(inFile);
    int numOfItterrations= diagnosesAccessor.getNumofDiagnosis();

    string temp;

    for (int i=0; i<numOfItterrations; i++)
    {
        diagnosesType.push_back(diagnoses());
        getline(inFile, temp);
        diagnosesType[i].setDiagnosesName(inFile);
    }
}
///default constructor for diagnoses adt
diagnoses::diagnoses()
{

    numOfDiagnoses=0;
    diagnosesID=0;

}
///function to print all the diagnoses
void printDiagnoses(vector <diagnoses> &diagnosesType)
{
    int diagnosesID;
    std::string diagnosesName;
    cout<<"************List of Diagnoses***************"<<endl;

    for (int i=0; i<diagnosesType.size(); i++) //loops through the diagnosis vector and prints them out
    {
        cout<<"Diagnoses ID: "<<diagnosesType[i].getDiagnosisID()<<endl;
        cout<<"Diagnoses Name: "<<diagnosesType[i].getDiagnosisName()<<endl;
        cout<<"********************************************"<<endl;
    }
}
