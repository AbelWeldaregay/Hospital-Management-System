#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "patient.h"
#include "doctors.h"
#include "date_time.h"
#include "appointment.h"

using namespace std;
///default constructor for patients
patient::patient()
{
    gender=' ';
    numOfPatients=0;
}
///function definition that reads the patients file
void readPatientsFile(ifstream &inFile, vector <patient> &patientType)
{
    patient patientAccessor;
    patientAccessor.setNumofPatients(inFile);
    int loopVariable = patientAccessor.getNumofPatients();

    for (int i=0; i<loopVariable; i++)
    {
        patientType.push_back(patient());
        ///  A unique item number that identifies the patient
        patientType[i].setID(inFile);
        /// doctor_id: The id number of the patient’s doctor
        patientType[i].setDocID(inFile);
        /// record_id: The id number of the patient’s record
        patientType[i].setRecID(inFile);
        /// name: Patient’s name
        patientType[i].setPatientName(inFile);
        /// phone: Patient’s phone number
        patientType[i].setPhoneNumber(inFile);
        /// gender: The patient’s gender
        patientType[i].setGender(inFile);
        /// email: The patient’s Email
        patientType[i].setPatientEmail(inFile);
        /// Blood_Type: the blood type (A+,O- …etc)
        patientType[i].setBloodType(inFile);
    }

}
///function definition to check if the given record id exists
bool checkValidRecID(vector <patient> &patientType, int &recID)
{
    bool checkInvalid=false;
    for (int i=0; i<patientType.size(); i++)
    {
        if (recID==patientType[i].getRecID())
        {
            checkInvalid=true;
        }
    }

    return checkInvalid;

}
///function to check if the patient id given exists
bool checkValidPatientID(vector <patient> &patienttype, string &tempPatientID)
{
    bool checkInvalid=false;

    for (int i=0; i<patienttype.size(); i++)
    {
        if (tempPatientID==patienttype[i].getID())
        {
            checkInvalid=true;
        }
    }
    return checkInvalid;
}
///function definition to add a new patient
void addANewPatient(vector <patient> &patientType)
{

    string tempDoc;
    string tempPatientID;
    int tempRecID=0;
    string poolOfDocs[3]={"369754","784459","744651"};

    int sizeOfVector = patientType.size();

    for(int i=sizeOfVector; i<(sizeOfVector+1); i++)
    {
        patientType.push_back(patient());
        cout<<"\nEnter the name of the new patient: ";
        cin >> patientType[i].patientName;
        cout<<"\nEnter the new patients phone number: ";
        cin >> patientType[i].phoneNumber;
        cout<<"\nEnter the gender of the new patient('m' for male, 'f' for female): ";
        cin >> patientType[i].gender;
        cout<<"\nEnter the email of the new patient: ";
        cin >> patientType[i].email;
        cout<<"\nEnter the blood type of the new patient: ";
        cin >> patientType[i].blood_Type;
        promptAgainForID:
        cout<<"\nEnter the id of the new patient: ";
        cin>>tempPatientID;

        if(checkValidPatientID(patientType, tempPatientID)==true){
          system("CLS");
            cout<<"THE PATIENT ID ENTERED ALREADY EXISTS, PLEASE TRY AGAIN"<<endl;
            system("PAUSE");
            system("CLS");

           goto promptAgainForID;
        }
        patientType[i].id=tempPatientID;
        promtAgain:
        cout<<"\nEnter the doctor id that is associated with the new patient: ";
        cin >> tempDoc;

        if(tempDoc!=poolOfDocs[0]&&tempDoc!=poolOfDocs[1]&&tempDoc!=poolOfDocs[2])
        {
            system("CLS");
            cout<<"\nTHE DOCTOR ID ENTERED DOES NOT EXIST, PLEASE TRY AGAIN"<<endl;
            system("PAUSE");
            system("CLS");
            goto promtAgain;
        }
      patientType[i].doctor_id=tempDoc;

      promptForRecID:
        cout<<"\nEnter the record id number for the new patient: ";
        cin >> tempRecID;
        if(checkValidRecID(patientType, tempRecID)==true)
        {
            system("CLS");
            cout<<"\nTHE RECORD ID ENTERED IS ALREADY TAKEN, PLEASE TRY AGAIN"<<endl;
            system("PAUSE");
            goto promptForRecID;
        }
         patientType[i].record_id=tempRecID;

    system("CLS");
    cout<<"\n\nPATIENT WAS ADDED SUCCESSFULLY!"<<endl;
    Sleep(1*2000);
    system("CLS");

}
}


///function to search for a patient
void searchPatient(vector <patient> patientType, int caseChoice)
{
    string patientTobeSearched;
    int indexOfwantedPatient=99999;

    if (caseChoice==4)
    {
        cout<<"Enter the name of the patient you want to search for: ";
        cin >> patientTobeSearched;

        for (int i=0; i<patientType.size(); i++)
        {
            if (patientTobeSearched==patientType[i].patientName)
            {
                indexOfwantedPatient=i;
                printSearchResult(indexOfwantedPatient, patientType);
            }
        }
        if(indexOfwantedPatient==99999)
        {
            system("CLS");
            cout<<"A PATIENT BY THAT NAME DOES NOT EXIST!"<<endl;
            system("PAUSE");
            system("CLS");
            goto exit;

        }
         system("PAUSE");
         system("CLS");


    }
    else if (caseChoice==5)
    {
        cout<<"Enter the email of the patient you want to search for: ";
        cin >> patientTobeSearched;
          for (int i=0; i<patientType.size(); i++)
          {
             if (patientTobeSearched==patientType[i].getPatientEmail())
             {
                indexOfwantedPatient=i;
                printSearchResult(i, patientType);
             }
          }
        if(indexOfwantedPatient==99999)
        {
            system("CLS");
            cout<<"NO PATIENT WITH THAT EMAIL EXISTS!"<<endl;
            system("PAUSE");
            system("CLS");
            goto exit;
        }
          system("PAUSE");
         system("CLS");
    }




    exit:
        cout<<endl;
}
///function definition to print the patients menu
int printPatientsMenu()
{
    int userChoice;
    cout<<"*******************************"<<endl;
    cout<<"1. show all patients"<<endl;
    cout<<"2. Add a new patient"<<endl;
    cout<<"3. Delete a patient"<<endl;
    cout<<"4. Search for a patient by his/her name"<<endl;
    cout<<"5. Search for a patient by his/her email"<<endl;
    cout<<"6. Show patients assigned to a certain doctor, by the doctor name"<<endl;
    cout<<"7. Show all patients who have appointments within a date and time range"<<endl;
    cout<<"8. Update patient information"<<endl;
    cin >> userChoice;
    return userChoice;
}
///function definition to check if the doctor id from a patient is equal to the doctor id from the doctor vector
int checkPatientDocMatch(vector <patient> &patientType, vector <doctor> &doctorType, int searchIndex)
{

    for (int i=0; i< doctorType.size(); i++)
    {
        if (patientType[searchIndex].getDocID()==doctorType[i].getDocID())
        {

            return i;
        }

    }

    return -1;
}
///function definition to display all the patients
void displayAllPatients(vector <patient> &patientType, vector <doctor> &doctorType, vector<diagnoses> &diagnosesType, vector<appointment> &appointmentType)
{

    int docIndex=0;

    for (int i=0; i<patientType.size(); i++)
    {
        cout<<"****************************"<<endl;
        cout<<"The Patients name         :  "<<patientType[i].getPatientName()<<endl;
        cout<<"Patient ID                :  "<<patientType[i].getID();
        ///cout<<"ID of Patient's doctor    :  "<<patientType[i].getDocID();

        docIndex=checkPatientDocMatch(patientType, doctorType, i);
        if(docIndex==-1)
        {
            cout<<"\tDoctor associated has been deleted"<<endl;
        }
        else
        {
            cout<<"\nID of Patient's doctor    :  "<<patientType[i].getDocID()<<endl;
            cout<<"Patient's doctor          :  "<<doctorType[docIndex].getDocName()<<endl;
        }
         cout<<"Record ID of patient      :  "<<patientType[i].getRecID()<<endl;
        cout<<"The patient's phone number:  "<<patientType[i].getPhoneNumber()<<endl;
        cout<<"The patient's gender      :  "<<patientType[i].getPatientGender()<<endl;
        cout<<"The patient's email       :  "<<patientType[i].getPatientEmail()<<endl;
        cout<<"The patient's blood Type  :  "<<patientType[i].getPatientBloodType()<<endl;

        for (int j=0; j<appointmentType.size(); j++)
        {
            if (patientType[i].getID()==appointmentType[j].getPatientID())
            {
                for (int x=0; x<diagnosesType.size(); x++)
                {
                    if (appointmentType[j].getDiagnosisID()==diagnosesType[x].getDiagnosisID())
                    {

                        if(diagnosesType[x].getDiagnosisName()=="")
                        {
                            cout<<"Diagnosis Name: Not assigned yet"<<endl;
                        }
                        else
                            cout<<"Diagnosis Name          : "<<diagnosesType[x].getDiagnosisName()<<endl;
                    }
                }
            }
        }
        cout<<"****************************"<<endl;
    }
}
///function definition to display all the patients
int displayPatientUpdateMenu()
{
    int userChoice=0;
    cout<<"Choose what you want to update"<<endl;
    cout<<"1. The patients name"<<endl;
    cout<<"2. The patients ID"<<endl;
    cout<<"3. ID of Patient's doctor"<<endl;
    cout<<"4. Record ID of patient"<<endl;
    cout<<"5. The patient's phone number"<<endl;
    cout<<"6. The patients gender"<<endl;
    cout<<"7. The patients email"<<endl;
    cout<<"8. The patients blood type"<<endl;
    cout<<"9. Return to main menu"<<endl;
    cin >> userChoice;
    return userChoice;
}
///function definition to check if the given patient name exists
bool checkValidName(vector <patient> &patientType, string &patientName)
{
    bool checkValidName=false;
     for (int i=0; i<patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            checkValidName=true;
        }
    }

    return checkValidName;

}
///function definition to update the patients information
void updatePatientInfo(vector <patient> &patientType)
{
    string patientName;

    int userChoice=0;
    start:
    cout<<"Enter the name of the patient you want to update: ";
    cin>> patientName;

    if(checkValidName(patientType, patientName)==false)
    {
        system("CLS");
        cout<<"PATIENT NAME ENTERED DOES NOT EXIST! PLEASE TRY AGAIN!"<<endl;
        system("PAUSE");
        system("CLS");
        goto start;
    }
    system("CLS");
    userChoice = displayPatientUpdateMenu();




    switch(userChoice)
    {
    case 1:
    {
        system("CLS");
        findUpdateName(patientType, patientName);
        break;
    }

    case 2:
    {
        system("CLS");
        findUpdateID(patientType, patientName);
        break;
    }
    case 3:
    {
        system("CLS");
        findUpdateDocPatientID(patientType, patientName);
        break;
    }
    case 4:
    {
        system("CLS");
        findUpdatePatientRecID(patientType, patientName);
        break;
    }
    case 5:
    {
        system("CLS");
        findUpdatePhoneNum(patientType, patientName);
        break;
    }
    case 6:
    {
        system("CLS");
        findUpdateGender(patientType, patientName);
        break;
    }
    case 7:
    {
        system("CLS");
        findUpDateEmail(patientType, patientName);
        break;
    }
    case 8:
    {
        system("CLS");
        findUpDateBloodType(patientType, patientName);
        break;
    }
    case 9:
        {
            system("CLS");
            break;
        }
    }

}
///function definition to delete a patient
void deletePatient(vector <patient> &patientType)
{

    string patientTobeDeleted;
    int indexOfPatientTobeDeleted;
    cout<<"\nEnter the name of the patient you want to delete: ";
    cin >> patientTobeDeleted;

    for (int i=0; i<patientType.size(); i++)
    {
        if (patientTobeDeleted==patientType[i].patientName)
        {
            indexOfPatientTobeDeleted=i;
        }
    }

    patientType.erase(patientType.begin()+indexOfPatientTobeDeleted);
    system("CLS");
    cout<<"THE PATIENT WAS SUCCESSFULLY DELETED!"<<endl;
    Sleep(2*1000);
}
///function definition to update the patients blood type
void findUpDateBloodType(vector <patient> &patientType, string patientName)
{
    int indexOfPatient=0;
    string newBloodType;

    for (int i=0; i< patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            indexOfPatient=i;
            cout<<"Enter the new blood type of patient: ";
            cin >> newBloodType;
        }

    }
     patientType[indexOfPatient].blood_Type=newBloodType;
    system("CLS");
    cout<<"PATIENT BLOOD TYPE WAS SUCCESSFULLY UPDATED!"<<endl;
    Sleep(1*2000);
    system("CLS");
}
///function definition to update the patients email
void findUpDateEmail(vector <patient> &patientType, string patientName)
{
    int indexOfPatient=0;
    string newEmail;

    for (int i=0; i< patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            indexOfPatient=i;
            cout<<"Enter the new email of patient: ";
            cin>>newEmail;
        }
    }
     patientType[indexOfPatient].email=newEmail;
    system("CLS");
    cout<<"PATIENT EMAIL WAS SUCCESSFULLY UPDATED!"<<endl;
    Sleep(1*2000);
    system("CLS");
}
///function definition to update the patients gender
void findUpdateGender(vector <patient> &patientType, string patientName)
{
    int indexOfPatient=0;
    char newGender=' ';

    for (int i=0; i< patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            indexOfPatient=i;
            cout<<"Enter the new gender(m for male, f for female): ";
            cin>>newGender;
        }

    }

     patientType[indexOfPatient].gender=newGender;
    system("CLS");
    cout<<"PATIENT GENDER WAS SUCCESSFULLY UPDATED!"<<endl;
    Sleep(1*2000);
    system("CLS");
}
///function definition to update the patients phone number
void findUpdatePhoneNum(vector <patient> &patientType, string patientName)
{
    int indexOfPatient=0;
    string newPhoneNum;

    for (int i=0; i<patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            indexOfPatient=i;
            cout<<"Enter the new Phone Number of the Patient: ";
            cin >> newPhoneNum;
        }
    }
     patientType[indexOfPatient].phoneNumber=newPhoneNum;
     system("CLS");
     cout<<"PATIENT PHONE NUMBER WAS SUCCESSFULLY UPDATED!"<<endl;
     Sleep(1*2000);
     system("CLS");
}
///function definition to update the patients record id
void findUpdatePatientRecID(vector <patient> &patientType, string patientName)
{
    int indexOfPatient=0;
    int newID;

promptForRecID:
    for (int i=0; i<patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            indexOfPatient=i;
            cout<<"Enter the new records ID(number cannot be greater than 9999): ";
            cin>>newID;
        }
    }
     if(checkValidRecID(patientType, newID)==true)
        {
            system("CLS");
            cout<<"\nTHE RECORD ID ENTERED IS ALREADY TAKEN, PLEASE TRY AGAIN"<<endl;
            system("PAUSE");
            goto promptForRecID;
        }
    patientType[indexOfPatient].record_id=newID;
    system("CLS");
    cout<<"THE RECORD ID FOR PATIENT "<<patientName<<" WAS SUCCESSFULLY UPDATED!"<<endl;
    Sleep(1*2000);
}
///function definition to update the patients doctor id
void findUpdateDocPatientID(vector <patient> &patientType, string patientName)
{
    int indexOfPatient=0;
    string newID;
     string poolOfDocs[3]={"369754","784459","744651"};

     promtAgain:
    for (int i=0; i< patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            indexOfPatient=i;
            cout<<"Enter the new doctors ID: ";
            cin>>newID;
        }
    }
     if(newID!=poolOfDocs[0]&&newID!=poolOfDocs[1]&&newID!=poolOfDocs[2])
        {
            system("CLS");
            cout<<"\nTHE DOCTOR ID ENTERED DOES NOT EXIST, PLEASE TRY AGAIN"<<endl;
            system("PAUSE");
            system("CLS");
            goto promtAgain;
        }

     patientType[indexOfPatient].doctor_id=newID;
     system("CLS");
     cout<<"THE DOCTOR ID FOR PATIENT "<<patientName<<" WAS SUCCESSFULLY UPDATED!"<<endl;
     Sleep(1*2000);
     system("CLS");
}
///function definition to update the patients id
void findUpdateID(vector <patient> &patientType, string patientName)
{
    int indexOfPatient=0;
    string newID;
    promptAgainForID:
    for (int i=0; i< patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            indexOfPatient=i;
            cout<<"Enter the new ID: ";
            cin>>newID;
            system("CLS");
        }
    }
    if(checkValidPatientID(patientType, newID)==true)
    {
        if(checkValidPatientID(patientType, newID)==true)
        {
          system("CLS");
            cout<<"THE PATIENT ID ENTERED ALREADY EXISTS, PLEASE TRY AGAIN"<<endl;
            system("PAUSE");
            system("CLS");

           goto promptAgainForID;
        }
    }

    patientType[indexOfPatient].id=newID;
    system("CLS");
    cout<<"THE PATIENT ID FOR PATIENT "<<patientName<<" WAS SUCCESSFULLY UPDATED!"<<endl;
    Sleep(1*2000);
    system("CLS");
}
///function definition to update the patients name
void findUpdateName(vector <patient> &patientType, string patientName)
{

    int indexOfPatient=0;

    for (int i=0; i<patientType.size(); i++)
    {
        if (patientName==patientType[i].getPatientName())
        {
            indexOfPatient=i;
            cout<<"Enter the new name: ";
            cin>>patientName;
        }
    }
    patientType[indexOfPatient].patientName=patientName;

    system("CLS");
    cout<<"PATIENT NAME WAS SUCCESSFULLY UPDATED!"<<endl;
    Sleep(1*2000);
    system("CLS");

}
///function definition to print the search results
void printSearchResult(int indexOfwantedPatient, vector <patient> patientType)
{

    cout<<"***************Search Result***************"<<endl;
    cout<<"Name of patient        : "<<patientType[indexOfwantedPatient].patientName<<endl;
    cout<<"ID of patient          : "<<patientType[indexOfwantedPatient].id<<endl;
    cout<<"Doctor id of patient   : "<<patientType[indexOfwantedPatient].doctor_id<<endl;
    cout<<"Record id of patient   : "<<patientType[indexOfwantedPatient].record_id<<endl;
    cout<<"Phone number of patient: "<<patientType[indexOfwantedPatient].phoneNumber<<endl;
    cout<<"Gender of patient      : "<<patientType[indexOfwantedPatient].gender<<endl;
    cout<<"Email of patient       : "<<patientType[indexOfwantedPatient].email<<endl;
    cout<<"Blood Type of patient  : "<<patientType[indexOfwantedPatient].blood_Type<<endl;
    cout<<"*******************************************"<<endl;

}
///function definition to search patient by the doctor
void searchPatientByDoc(const vector <patient> &patientType, vector <doctor> &doctorType)
{
    string doctorToBeSearched;
    string docID;

    cout<<"Enter the name of the doctor associated with the patient: ";
    cin >> doctorToBeSearched;

    for (int i=0; i<doctorType.size(); i++)
    {
        if(doctorToBeSearched==doctorType[i].getDocName())
        {
            docID = doctorType[i].getDocID();
        }
    }

    for (int i=0; i<patientType.size(); i++)
    {
        if (docID==patientType[i].getDocID())
        {
            printSearchResult(i, patientType);
        }
    }

}
///function definition to print all patients with appointment with a certain time an range
void showPatientswithAppTimeRange(vector <patient> &patientType, vector <appointment> &appointmentType,vector <date_time> &dateType, vector <slot> &slotType)
{

    int startDateID=0;
    int endDateID=0;
    int indexOfStartDate=0;
    int indexOfEndDate=0;

    cout<<"In order to select a time range, look at the list that will be printed after\n"
        <<"you press any key to continue, and find the date id that coordinates with your \n"
        <<"starting date and time and your ending date and time, then input those values when prompted"<<endl;
    system("PAUSE");
    system("CLS");
    cout<<"**********************************************"<<endl;
    for (int i=0; i<dateType.size(); i++)
    {

        cout<<"\nDate ID associated wit the slot  : "<<dateType[i].getDateID()<<endl;
        cout<<"\nDate Associated with slot(m/d/y) : "<<dateType[i].getMonthDate()<<"/"<<dateType[i].getDayDate()<<"/"<<dateType[i].getYearDate()<<endl;
        cout<<"\nTime associated with slot(h/m)   : "<<dateType[i].getHoursDate()<<" : "
            <<dateType[i].getMinutesDate()<<" "<<dateType[i].getAMPM()<<endl;
        cout<<"**********************************************"<<endl;
    }

    cout<<"Enter the Date ID for the beginning of the range: ";
    cin >>startDateID;
    cout<<"\nEnter the Date ID for the end of the range    : ";
    cin >>endDateID;
    system("CLS");

    for (int i=0; i<dateType.size(); i++)
    {
        if (startDateID==dateType[i].getDateID())
        {
            indexOfStartDate=i;
        }
        if (endDateID==dateType[i].getDateID())
        {
            indexOfEndDate=i;
        }
    }

    cout<<"***************************************************"<<endl;
    for (int i=0; i<slotType.size(); i++)
    {
        while ((startDateID<=slotType[i].getDateID())&& (slotType[i].getDateID()<=endDateID))
        {

            for (int j=0; j<appointmentType.size(); j++)
            {
                if(slotType[i].getslotID()==appointmentType[j].getSlotID())
                {
                    for (int x=0; x<patientType.size(); x++)
                    {
                        if(appointmentType[j].getPatientID()==patientType[x].getID())
                        {
                            cout<<"Patient's name      : "<<patientType[x].getPatientName()<<endl;
                            cout<<"Patient's gender    : "<<patientType[x].getPatientGender()<<endl;
                            cout<<"Patient's Blood Type: "<<patientType[x].getPatientBloodType()<<endl;
                            cout<<"Patient's ID        : "<<patientType[x].getID()<<endl;
                            cout<<"Patient's doctor    : "<<patientType[x].getDocID()<<endl;
                            cout<<"Patient's record ID : "<<patientType[x].getRecID()<<endl;
                            cout<<"Patient's phone#    : "<<patientType[x].getPhoneNumber()<<endl;
                            cout<<"Patient's Email     : "<<patientType[x].getPatientEmail()<<endl;
                            cout<<"***************************************************"<<endl;


                        }
                    }

                }
            }

            break;
        }

    }
}
