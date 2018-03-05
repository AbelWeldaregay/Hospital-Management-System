#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "windows.h"
#include "record.h"
#include "patient.h"
using namespace std;

///default constructor for records
record::record()
{
    recordID=0;

}
///function definition to add a record
void addRecord(vector <record> &recordType, vector <patient> &patientType)
{
    string tempID;
    string doctorNotes;
    bool checkValid=false;
    bool checkduplicate=false;
    int indexOfExistingRecord=0;
    int indexOfPatient=0;
    static int index =0;
start:
    cout<<"Enter the patient ID of the patient you want to update the record id for: ";
    cin >> tempID;
    system("CLS");

    for (int i=0; i<patientType.size(); i++)
    {
        if (tempID==patientType[i].getID())
        {
            checkValid=true;
            indexOfPatient=i;
        }
    }

    if (checkValid==false)
    {
        cout<<"Incorrect patient ID, please try again"<<endl;
        system("PAUSE");
        system("CLS");
        goto start;
    }

    for (int i=0; i<recordType.size(); i++)
    {
        if(tempID==recordType[i].getPatientID())
        {
            checkduplicate=true;
            indexOfExistingRecord=i;
        }
    }

    if (checkValid==true)
    {
        cout<<"Enter the doctor notes: ";
        cin.ignore();
        getline(cin, doctorNotes);
        if (checkduplicate==false)
        {
            recordType.push_back(record());
            recordType[index].recordID=patientType[indexOfPatient].getRecID();
            recordType[index].patientID=patientType[indexOfPatient].getID();
            recordType[index].doctorNotes=doctorNotes;
            index++;
        }
        if(checkduplicate==true)
        {
            recordType[indexOfExistingRecord].recordID=patientType[indexOfPatient].getRecID();
            recordType[indexOfExistingRecord].patientID=patientType[indexOfPatient].getID();
            recordType[indexOfExistingRecord].doctorNotes=doctorNotes;
        }


    }
    system("CLS");
    cout<<"RECORD WAS SUCCESSFULLY ADDED!"<<endl;
    Sleep(1*2000);

}

///function definition to print the record menu
int printRecordMenu()
{

    int userChoice=0;

    cout<<"1.Print Records"<<endl;
    cout<<"2.Add Records"<<endl;
    cout<<"3.Update Records"<<endl;
    cout<<"4.Delete Records"<<endl;
    cout<<"5.Search Records"<<endl;
    cout<<"6.Return to Main Menu"<<endl;
    cin>> userChoice;

    return userChoice;
}
///function definition to print the records menu
void printRecords( vector <record> &recordType)
{
    cout<<"****List of Results****"<<endl;
    for (int i=0; i<recordType.size(); i++)
    {
        cout<<"Record ID    : "<<recordType[i].getRecID()<<endl;
        cout<<"Patient ID   : "<<recordType[i].getPatientID()<<endl;
        cout<<"Doctor Notes : "<<recordType[i].getDoctorNotes()<<endl;
        cout<<"**********************"<<endl;
    }
    system("PAUSE");
    system("CLS");

}
///function definition to update the records
void updateRecords(vector <record> &recordType)
{
    int tempRecID=0;
    bool checkValid=false;
    int indexOfRecord=0;
    int checkIfEmpty=recordType.size()+1;
    string doctorNotes;

    if(recordType.size()==0)
    {
        system("CLS");
        cout<<"There are no records to update, please try again after you add a record"<<endl;
        system("PAUSE");
        system("CLS");
        goto exit;
    }

    start:
    cout<<"Enter the record id you want to update the record for: ";
    cin >> tempRecID;
    system("CLS");

    for (int i=0; i<recordType.size(); i++)
    {
        if (tempRecID==recordType[i].getRecID())
        {
            indexOfRecord=i;
            checkValid=true;
        }
        else if (tempRecID!=recordType[i].getRecID())
        {
            checkValid=false;
        }
    }
    if (checkValid==false)
    {
        cout<<"The record ID is does not exist, please try again"<<endl;
        goto start;

    }

    cout<<"Enter the new note you want to update: ";
    cin.ignore();
    getline(cin, doctorNotes);
    system("CLS");

    cout<<"The record Notes was successfully updated!"<<endl;
    recordType[indexOfRecord].doctorNotes=doctorNotes;
    system("PAUSE");

    exit:
        cout<<endl;
}
///function definition to delete a record
void deleteRecord(vector <record> &recordType)
{
    int tempRecID;
    bool checkValid=false;
    int indexOfRec=0;
    start:
    cout<<"Enter the record id you want to delete: ";
    cin>> tempRecID;

    for (int i=0; i<recordType.size(); i++)
    {
        if (tempRecID==recordType[i].getRecID())
        {
            indexOfRec=i;
            checkValid=true;
        }

    }

    if(checkValid==false)
    {
        system("CLS");
        cout<<"The record ID you entered does not exit, please try again"<<endl;
        Sleep(1000*2);
        goto start;
    }
    else if (checkValid==true)
    {
        recordType.erase(recordType.begin()+indexOfRec);
        system("CLS");
        cout<<"The record with the ID "<<tempRecID<<" has been successfully deleted!"<<endl;
        system("PAUSE");
    }

}
///function definition to print a record at a given index
void printRecordsAtIndex(vector <record> &recordType, int &i)
{
        cout<<"Record ID    : "<<recordType[i].getRecID()<<endl;
        cout<<"Patient ID   : "<<recordType[i].getPatientID()<<endl;
        cout<<"Doctor Notes : "<<recordType[i].getDoctorNotes()<<endl;
        cout<<"**********************"<<endl;
}
///function definition to search for a record
void searchRecords(vector <record> &recordType)
{
    string searchItem;
    int searchRecID=0;
    int userChoice=0;

    system("CLS");
    start:
    cout<<"choose one of the following(1-2)"<<endl;
    cout<<"1.Search Records by patient ID"<<endl;
    cout<<"2.Search Records by Record ID"<<endl;
    cin>>userChoice;
    system("CLS");

    switch(userChoice)
    {
        case 1:
        {
            cout<<"Enter the patient ID associated with the record: ";
            cin >>searchItem;
            system("CLS");
            cout<<"\n***********Search Results************"<<endl;
            for (int i=0; i<recordType.size(); i++)
            {
                if (searchItem==recordType[i].getPatientID())
                {
                    printRecordsAtIndex(recordType, i);
                }
            }
            break;
        }
        case 2:
            {
                cout<<"Enter the record ID associated with the record: ";
                cin >>searchRecID;
                cout<<"\n***********Search Results************"<<endl;

                for(int i=0; i<recordType.size(); i++)
                {
                    if(searchRecID==recordType[i].getRecID())
                    {
                        printRecordsAtIndex(recordType, i);
                    }
                }
                break;
            }
        default:
            {
                system("CLS");
                cout<<"Invalid Input, digit must be between 1-2!"<<endl;
                goto start;
            }
    }
}

