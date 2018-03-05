#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "windows.h"
#include "doctors.h"
#include "appointment.h"

using namespace std;

///default constructor for doctors adt
doctor::doctor()
{
    numOfDoctors=0;
}
///function to read the doctors file
void doctor::readDoctorFile(ifstream &inFile, vector <doctor> &doctorType)
{

    setNumOfDoctors(inFile);
    int loopVariable=0;
    loopVariable= getNumOfDoctors(); //reading the first line from the file, which is the number of doctors and use that as a loop variable

    for (int i=0; i<loopVariable; i++)
    {
        doctorType.push_back(doctor());
        doctorType[i].setdocID(inFile);
        doctorType[i].setdocUserName(inFile);
        doctorType[i].setDocPassword(inFile);
        doctorType[i].setDocName(inFile);
        doctorType[i].setDocPhone(inFile);
        doctorType[i].setDocSpeciality(inFile);
    }
}
//function to print the doctors adt
void printDoctorsFile(vector <doctor> doctorType)
{
    for (int i=0; i<doctorType.size(); i++)
    {
        cout<<doctorType[i].getDocID()<<endl;
        cout<<doctorType[i].getdocUserName()<<endl;
        cout<<doctorType[i].getDocPassword()<<endl;
        cout<<doctorType[i].getDocName()<<endl;
        cout<<doctorType[i].getDocPhone()<<endl;
        cout<<doctorType[i].getDocSpeciality()<<endl;
        cout<<"=================================="<<endl;
    }
}
///function to print the doctors menu
int printDoctorsMenu()
{
    int userChoice;

    cout<<"*******************************"<<endl;
    cout<<"1. Show all doctors"<<endl;
    cout<<"2. Update Doctor's info"<<endl;
    cout<<"3. Delete a Doctor"<<endl;
    cout<<"4. Search for a doctor by Name"<<endl;
    cout<<"5. Return to the main menu"<<endl;
    cout<<"*******************************"<<endl;
    cin >> userChoice;

    return userChoice;
}
//function to print all the doctors
void showAllDoctors(vector <doctor> doctorType)
{

    cout<<"***************************************"<<endl;
    cout<<"***********List of Doctors*************"<<endl;
    for (int i=0; i<doctorType.size(); i++)
    {
        cout<<"The Doctor's Name     : "<<doctorType[i].getDocName()<<endl;
        cout<<"The Doctor's User Name: "<<doctorType[i].getdocUserName()<<endl;
        cout<<"The Doctor's ID       : "<<doctorType[i].getDocID()<<endl;
        cout<<"The Doctor's Password : "<<doctorType[i].getDocPassword()<<endl;
        cout<<"The Doctor's Phone#   : "<<doctorType[i].getDocPhone()<<endl;
        cout<<"The Doctor's specialty: "<<doctorType[i].getDocSpeciality()<<endl;
        cout<<"***************************************"<<endl;
    }

    system("PAUSE");
    system("CLS");
}
///function to update the doctors menu
int printUpdateDocMenu()
{
    int userChoice=0;

    cout<<"Please choose one of the following(1-6)"<<endl;
    cout<<"1.Update the Doctor's Name"<<endl;
    cout<<"2.Update the Doctor's Password"<<endl;
    cout<<"3.Update the Doctor's Phone Number"<<endl;
    cout<<"4.Update the Doctor's specialty"<<endl;
    cout<<"5. Return to the main menu"<<endl;
    cin>>userChoice;

    return userChoice;
}
///function to update the doctors info
void updateDoctorsInfo(vector <doctor> &doctorType)
{
    string docToBupDated;
    int indexOfDocToBeUpDated=0;
    int userChoice=0;
    cout<<"Enter the name or ID of the doctor you want to update: ";
    cin >> docToBupDated;
    system("CLS");

    for (int i=0; i<doctorType.size(); i++) //loops through the doctors vector
    {
        if(docToBupDated==doctorType[i].getDocID()||  //if the doctor
                docToBupDated==doctorType[i].getDocName())
        {
            indexOfDocToBeUpDated=i;
        }
    }

    userChoice=printUpdateDocMenu();
    system("CLS");

    if(userChoice==1)
    {
        string newName;
        system("CLS");
        cout<<"Enter the new doctor name: ";
        cin>>newName;
        system("CLS");
        doctorType[indexOfDocToBeUpDated].doc_name=newName;
        cout<<"The doctor's name has been successfully updated!"<<endl;
        system("PAUSE");
    }
    if(userChoice==2) //if the user chooses 2, then passward is updated
    {
        string oldPassword;
        string newPassword;
start:
        cout<<"For security reasons, enter the old password first: ";
        cin>> oldPassword;

        if(oldPassword==doctorType[indexOfDocToBeUpDated].doc_password) //checks if doctor passward exists
        {
            system("CLS");
            cout<<"Enter the new password: ";
            cin>>newPassword;

            doctorType[indexOfDocToBeUpDated].doc_password=newPassword; //updates the password
            system("CLS");
            cout<<"The doctor's password has been successfully updated!"<<endl;
            system("PAUSE");
            system("CLS");
        }
        else if (oldPassword!=doctorType[indexOfDocToBeUpDated].doc_password) //if the old password does not match, it prompts to enter again
        {
            cout<<"The old password does not match the password in the database, please try again"<<endl;
            goto start;
            system("CLS");
        }

    }
    if(userChoice==3) //if the user chooses 3, it updates the phone number
    {
        string newPhoneNumber;
        cout<<"Enter the new phone number of the doctor: ";
        cin >> newPhoneNumber;
        system("CLS");
        doctorType[indexOfDocToBeUpDated].doc_phone=newPhoneNumber; //updates the phone number
        cout<<"The doctor's Phone Number has been successfully updated!"<<endl;
        system("PAUSE");
        system("CLS");
    }
    if(userChoice==4) //if the user choice is 4 then the doctor's specialty's is updated
    {
        string newSpeciality;

        cout<<"Enter the doctor's new specialty: ";
        cin >> newSpeciality;
        system("CLS");
        doctorType[indexOfDocToBeUpDated].doc_speciality=newSpeciality; //updates the doctor speciality
        cout<<"The doctor's specialty has been successfully updated!"<<endl;
        system("PAUSE");
        system("CLS");
    }
    if(userChoice==5) //if the user chooses 5, then it goes to exit, which exits the function
    {
        goto exit;
    }
exit:
    cout<<endl;

}
///function to delete a doctor, i first check if there is an appointment scheduled associated with the doctor
///if there is then the user cannot delete a doctor
void deleteDoctor(vector <doctor> &doctorType, vector <appointment> &appointmentType)
{
    string doctorID;
    int indexOfDoctor=0;
start:
    cout<<"Enter the ID of the doctor you want to delete: ";
    cin >> doctorID;
    system("CLS");
///checks if the doctor id exists, if it does not, then i prompt the user to enter a new doctor id
    if (doctorID==doctorType[0].getDocID()||doctorID==doctorType[1].getDocID()||doctorID==doctorType[2].getDocID())
    {
        goto valid;
    }
    else
    {
        system("CLS");
        cout<<"The doctor ID you entered does not exit, please try again."<<endl;
        goto start;
    }
valid:
    for (int i=0; i<doctorType.size(); i++)
    {
        if (doctorID==doctorType[i].getDocID())
        {
            indexOfDoctor=i;
        }
    }
///checks if there is a appointment associated with the doctor, if there is this message will be printed
    for (int i=0; i<appointmentType.size(); i++)
    {
        if (doctorID==appointmentType[i].getDoctorID())
        {
            system("CLS");
            cout<<"Doctor "<<doctorType[indexOfDoctor].getDocName()<<" cannot be deleted because he/she\n"
                <<"has an appointment, please delete the appointment with the ID "<<appointmentType[i].getAppointmentID()<<"\n"
                <<"in order to delete Doctor "<<doctorType[indexOfDoctor].getDocName()<<endl;
            system("PAUSE");
            system("CLS");
            goto exit;
        }
    }
///if everything works out, this confirmation message will be printed
    system("CLS");
    cout<<"Doctor "<<doctorType[indexOfDoctor].getDocName()<<" "<<"has been successfully deleted!"<<endl;
    doctorType.erase(doctorType.begin()+indexOfDoctor);
    system("PAUSE");
    system("CLS");

    exit:
        system("CLS");
}
///function to search the doctor vector by doctor name
void searchDoctorByName(vector <doctor> &doctorType)
{
    string doctorNametoBeSearched;

    cout<<"Enter the name of the doctor you want to search for: ";
    cin >> doctorNametoBeSearched;
    system("CLS");
    cout<<"***************************************"<<endl;
    cout<<"***********Search Results**************"<<endl;
    for (int i=0; i<doctorType.size(); i++) //loops through the whole doctor vector
    {
        if (doctorNametoBeSearched==doctorType[i].getDocName()) //if the doctor name entered and the doctor name from the doctorType vector, then print
        {
            cout<<"The Doctor's Name     : "<<doctorType[i].getDocName()<<endl;
            cout<<"The Doctor's User Name: "<<doctorType[i].getdocUserName()<<endl;
            cout<<"The Doctor's ID       : "<<doctorType[i].getDocID()<<endl;
            cout<<"The Doctor's Password : "<<doctorType[i].getDocPassword()<<endl;
            cout<<"The Doctor's Phone#   : "<<doctorType[i].getDocPhone()<<endl;
            cout<<"The Doctor's specialty: "<<doctorType[i].getDocSpeciality()<<endl;
            cout<<"***************************************"<<endl;
        }
    }

    system("PAUSE");
    system("CLS");
}
