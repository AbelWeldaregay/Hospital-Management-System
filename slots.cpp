#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include "slots.h"
#include "date_time.h"
#include "appointment.h"
#include "windows.h"

using namespace std;
///default constructor for slots
slot::slot()
{
    slotID="";
    date_id=0;
    doctor_id="";
    slotStatus="";
    numOfSlots=0;
}
///function definition to read the slots file
void readSlotFile(ifstream &inFile, vector <slot> &slotType)
{
    slot slotAccessor;
    string temp;
    slotAccessor.setNumberOfSlots(inFile);

    int numOfSlots = slotAccessor.getNumOfSlots();

    for (int i=0; i<numOfSlots; i++)
    {
        slotType.push_back(slot());
        ///a. id: A unique number that identifies the slot
        slotType[i].setslotID(inFile);
        ///b. date_id: The id number of the date and time of the slot
        slotType[i].setDateID(inFile);
        ///c. doctor_id: The id number of the doctor
        slotType[i].setDocID(inFile);
        ///d. available: The slot status (1 for available, 0 for unavailable)
        inFile>>temp;
        if(temp[0]=='a')
        {
            slotType[i].slotStatus=true;
        }
        else
            slotType[i].slotStatus=false;
    }
}
///function definition to print the slots menu
int printSlotMenu()
{

    int userChoice;

    cout<<"*************************"<<endl;
    cout<<"1. Show available slots"<<endl;
    cout<<"2. Show unavailable slots"<<endl;
    cout<<"3. Add new slot(s)"<<endl;
    cout<<"4. Show slots between two times"<<endl;
    cout<<"5. Show all slots"<<endl;
    cout<<"6. Show all slots for a certain doctor"<<endl;
    cout<<"7. Show available slots for a certain doctor"<<endl;
    cout<<"8. Modify slot information"<<endl;
    cout<<"9. Remove a slot"<<endl;
    cout<<"10. Return to the Main Menu"<<endl;
    cout<<"*************************"<<endl;
    cin>>userChoice;
    system("CLS");
    return userChoice;

}
///function definition to print the unavailable slots
void showAllTheUnavailableSlots(vector <slot>  &slotType, vector <date_time> &dateType)
{
    cout<<"***********************************************"<<endl;
    cout<<"\t\t   UNAVAILABLE SLOTS"<<endl;
    cout<<"***********************************************"<<endl;
    for (int i=0; i<slotType.size(); i++)
    {

        if (slotType[i].getSlotStatus()==false)
        {
            cout<<"\nSlot ID that identifies the slot: "<<slotType[i].getslotID()<<endl;
            for (int j=0; j<dateType.size(); j++)
            {
                if(slotType[i].getDateID()==dateType[j].getDateID())
                {

                    cout<<"\nDate Associated with slot(m/d/y) : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                    cout<<"\nTime associated with slot(h/m)   : "<<dateType[j].getHoursDate()<<" : "
                        <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;
                }

            }
            cout<<"\nThe doctor ID associated with the slot: "<<slotType[i].getSlotDocID()<<endl;
            cout<<"***********************************************"<<endl;
        }
    }

}
///function definition to print all the available slots
void ShowAllTheAvailableSlots(vector <slot> &slotType, vector <date_time> &dateType)
{
    cout<<"***********************************************"<<endl;
    cout<<"\t\t   AVAILABLE SLOTS"<<endl;
    cout<<"***********************************************"<<endl;

    for (int i=0; i<slotType.size()-10; i++)
    {

        if (slotType[i].getSlotStatus()==true && slotType[i].getSlotDocID()!="99999")
        {
            cout<<"\nSlot ID that identifies the slot     : "<<slotType[i].getslotID()<<endl;

            for (int j=0; j<dateType.size(); j++)
            {
                if(slotType[i].getDateID()==dateType[j].getDateID())
                {

                    cout<<"\nDate Associated with slot(m/d/y)      : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                    cout<<"\nTime associated with slot(h/m)        : "<<dateType[j].getHoursDate()<<" : "
                        <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;
                }

            }
            cout<<"\nThe doctor ID associated with the slot: "<<slotType[i].getSlotDocID()<<endl;
            cout<<"***********************************************"<<endl;
        }
    }

}
///function definition to add a new slot
void addANewSlot(vector <slot> &slotType, vector <date_time> &dateType, vector <doctor> &doctorType)
{
    string tempSlotID;
    int tempDateID=0;
    ///int dateID=0;
    int indexOfSlot=0;
    string tempDocID;
    bool checkValid=false;
    static int index=slotType.size()+1;
    int idOfNewDate=dateType.size() +1;
    int tempDay=0;
    int tempmonth=0;
    int tempyear=0;
    int tempHours=0;
    int tempminutes=0;
    char ampm=' ';
start:
    cout<<"Enter the Slot ID for the new Slot: "<<flush;
    cin>>tempSlotID;
    system("CLS");

    for (int i=0; i<slotType.size(); i++)
    {
        if (tempSlotID==slotType[i].getslotID())
        {
            cout<<"The slot ID you entered is already taken, please try again!"<<endl;
            system("PAUSE");
            system("CLS");
            goto start;
        }
    }
    cout<<"Enter the new day of the date for the slot  : ";
    cin>> tempDay;
    system("CLS");
    cout<<"Enter the new month of the date for the slot: ";
    cin>>tempmonth;
    system("CLS");
    cout<<"Enter the new year of the date for the slot : ";
    cin>>tempyear;
    system("CLS");
    cout<<"Enter the hour of the date for the slot     : ";
    cin>>tempHours;
    system("CLS");
    cout<<"Enter the minutes of the date for the slot  : ";
    cin>>tempminutes;
    system("CLS");
    cout<<"Enter A for am or P for pm for the time     : ";
    cin>>ampm;
    system("CLS");

    cout<<"***************************************"<<endl;

thedocID:
    cout<<"\nPlease enter the Doctor ID you want to associate your slot with: ";
    cin >> tempDocID;
    system("CLS");

    for (int i=0; i<slotType.size(); i++)
    {
        if (tempDocID==slotType[i].getSlotDocID())
        {
            checkValid=true;
        }
    }


    if (checkValid==false)
    {
        cout<<"The doctor ID you entered is invalid, please try again"<<endl;
        goto thedocID;
    }
    slotType.push_back(slot());
    slotType.push_back(slot());
    slotType[index].slotID=tempSlotID;
    slotType[index].date_id=idOfNewDate;
    dateType.push_back(date_time());
    dateType[dateType.size()-1].setTheNewDateID(idOfNewDate);
    dateType[dateType.size()-1].setTheNewDayDate(tempDay);
    dateType[dateType.size()-1].setTheNewMonthDate(tempmonth);
    dateType[dateType.size()-1].setNewYearDate(tempyear);
    dateType[dateType.size()-1].setNewHoursDate(tempHours);
    dateType[dateType.size()-1].setNewMinutesDate(tempminutes);
    dateType[dateType.size()-1].setNewAmPm(ampm);
    slotType[index].doctor_id=tempDocID;
    slotType[index].slotStatus=true;
    slotType.erase(slotType.begin()+(index-1));
    index++;

    cout<<"\n\nTHE NEW SLOT HAS BEEN CREATED SUCCESSFULLY!"<<endl;
    system("PAUSE");
    system("CLS");

}
///function definition to show slots between two dates
void ShowSlotsBetweenTwoDates(vector <slot> &slotType, vector <date_time> &dateType)
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

        cout<<"\nDate ID      : "<<dateType[i].getDateID()<<endl;
        cout<<"\nDate (m/d/y) : "<<dateType[i].getMonthDate()<<"/"<<dateType[i].getDayDate()<<"/"<<dateType[i].getYearDate()<<endl;
        cout<<"\nTime (h/m)   : "<<dateType[i].getHoursDate()<<" : "
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

    cout<<"Here is a list of all the slots between "<<dateType[indexOfStartDate].getHoursDate()
        <<":"<<dateType[indexOfStartDate].getMinutesDate()<<" "<<dateType[indexOfStartDate].getAMPM()<<" "<<
        dateType[indexOfStartDate].getMonthDate()
        <<"/"<<dateType[indexOfStartDate].getDayDate()<<"/"<<dateType[indexOfStartDate].getYearDate()
        <<" and "<<dateType[indexOfEndDate].getHoursDate()<<":"<<dateType[indexOfEndDate].getMinutesDate()
        <<" "<<dateType[indexOfEndDate].getAMPM()<<" "<<
        dateType[indexOfEndDate].getMonthDate()<<"/"<<dateType[indexOfEndDate].getDayDate()
        <<"/"<<dateType
        [indexOfEndDate].getYearDate()<<endl;

    cout<<"\n***************************************************"<<endl;
    for (int i=0; i<slotType.size()-10; i++)
    {
        while ((startDateID<=slotType[i].getDateID())&& (slotType[i].getDateID()<=endDateID &&slotType[i].getSlotStatus()==true))
        {
            cout<<"The slot ID that identifies the slot: "<<slotType[i].getslotID()<<endl;
            cout<<"The date ID associated with the slot: "<<slotType[i].getDateID()<<endl;
            for (int j=0; j<dateType.size(); j++)
            {
                if(slotType[i].getDateID()==dateType[j].getDateID())
                {
                    cout<<"Date Associated with slot(m/d/y) : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                    cout<<"Time associated with slot(h/m)   : "<<dateType[j].getHoursDate()<<" : "
                        <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;
                }
            }
            cout<<"***************************************************"<<endl;
            break;
        }
    }

}
///function definition to print all the slots
void showAllSlots(vector <slot> &slotType, vector <date_time> &dateType)
{
    cout<<endl;
    for (int i=0; i<slotType.size(); i++)
    {
        cout<<"Slot ID that identifies the slot: "<<slotType[i].getslotID()<<endl;
        cout<<"Date ID associated with the slot: "<<slotType[i].getDateID()<<endl;
        cout<<"Doctor ID associated with the slot: "<<slotType[i].getSlotDocID()<<endl;
        for (int j=0; j<dateType.size(); j++)
        {

            if(slotType[i].getDateID()==dateType[j].getDateID())
            {

                cout<<"\nDate Associated with slot(m/d/y) : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                cout<<"Time associated with slot(h/m)   : "<<dateType[j].getHoursDate()<<" : "
                    <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;
            }

        }

        cout<<"***********************************************"<<endl;

    }
}
///function definition to print the slot modifications menu
int printSlotModMenu()
{
    int userChoice=0;

    cout<<"Please choose one of the following(1-3)"<<endl;
    ///cout<<"1. Modify/Change slot ID"<<endl;
    cout<<"1. Modify/Change the date ID associated with a slot"<<endl;
    cout<<"2. Modify/Change the doctor ID associated with the slot"<<endl;
    cout<<"3. Modify/Change the slot status"<<endl;
    cin >> userChoice;

    return userChoice;

}
///function definition to modify the slot information
void modifySlotInformation(vector <slot> &slotType)
{
    int userChoice=0;
    int dateID=0;
    string doctorID;
    string theSlotID;
    string newSlotID;
    int indexOfSlot=0;
    string pOfDocIDs[3]= {"369754","784459","744651"};

    cout<<"Enter the ID of the slot you want to modify/change: ";
    cin >> theSlotID;
    system("CLS");
    cout<<endl;

    for (int i=0; i<slotType.size(); i++)
    {
        if (theSlotID==slotType[i].getslotID())
        {
            indexOfSlot=i;
        }
    }
    userChoice=printSlotModMenu();


    if(userChoice==1)
    {

        system("CLS");
        cout<<"Enter the new date ID you want to associate the slot with: ";
        cin >>dateID;
        system("CLS");
        slotType[indexOfSlot].date_id=dateID;
        cout<<"THE DATE ID FOR THE SLOT WAS SUCCESSFULLY UPDATED!"<<endl;
        Sleep(1*2000);
    }
    if(userChoice==2)
    {
start:
        system("CLS");
        cout<<"\nThis is a list of all the doctor ID's"<<endl;
        for (int i=0; i<3; i++)
        {
            cout<<pOfDocIDs[i]<<endl;
        }

        cout<<"Enter the new Doctor ID you want to associate the slot with: ";
        cin >> doctorID;

        if (doctorID==pOfDocIDs[0]||doctorID==pOfDocIDs[1]||doctorID==pOfDocIDs[2])
        {

            goto valid;
        }
        else if (doctorID!=pOfDocIDs[0]||doctorID!=pOfDocIDs[1]||doctorID!=pOfDocIDs[2])
        {
            cout<<"The doctor ID you entered is invalid, please make sure it \n"
                <<"matches the one of the ID's from the list of Doctor ID's"<<endl;
            Sleep(4000*1);
            system("CLS");
            goto start;
        }
valid:
        slotType[indexOfSlot].doctor_id=doctorID;
        cout<<"The slot has been successfully updated with the new doctor ID!"<<endl;
        system("PAUSE");
    }
    if (userChoice==3)
    {
        int caseChoice=0;
        system("CLS");
        cout<<"Please choose one of the following(1-2)"<<endl;
        cout<<"1. Change the slot status to available"<<endl;
        cout<<"2. Change the slot status to unavailable"<<endl;
        cin>>caseChoice;
        if (caseChoice==1)
        {
            slotType[indexOfSlot].slotStatus=true;
            cout<<"The slot status has been successfully updated to available"<<endl;
            system("PAUSE");
            system("CLS");
        }
        if(caseChoice==2)
        {
            slotType[indexOfSlot].slotStatus=false;
            cout<<"The slot status has been successfully updated to unavailable"<<endl;
            system("PAUSE");
            system("CLS");
        }
    }
}
///function definition to print the slots associated to a certain doctor
void showSlotsForDoctor(vector <slot> &slotType, vector <date_time> &dateType)
{
    string doctorID;
    string pOfDocIDs[3]= {"369754","784459","744651"};

    cout<<"In order to show all the slots for a certain doctor, \n"
        <<"you will need to input the doctor ID for that certain doctor you "
        <<"\nwant to display the slots for"<<endl;
    system("PAUSE");
    system("CLS");
start:
    cout<<"\nThis is a list of all the doctor ID's"<<endl;
    for (int i=0; i<3; i++)
    {
        cout<<pOfDocIDs[i]<<endl;
    }
    cout<<"Enter the ID of the doctor you want to display all the slots for: ";
    cin >> doctorID;

    if (doctorID==pOfDocIDs[0]||doctorID==pOfDocIDs[1]||doctorID==pOfDocIDs[2])
    {

        goto valid;
    }
    else if (doctorID!=pOfDocIDs[0]||doctorID!=pOfDocIDs[1]||doctorID!=pOfDocIDs[2])
    {
        cout<<"The doctor ID you entered is invalid, please make sure it \n"
            <<"matches the one of the ID's from the list of Doctor ID's"<<endl;
        Sleep(4000*1);
        system("CLS");
        goto start;
    }
valid:
    for (int i=0; i<slotType.size(); i++)
    {
        if (doctorID==slotType[i].getSlotDocID())
        {
            cout<<"\nSlot ID that identifies the slot: "<<slotType[i].getslotID()<<endl;
            for (int j=0; j<dateType.size(); j++)
            {

                if(slotType[i].getDateID()==dateType[j].getDateID())
                {

                    cout<<"\nDate Associated with slot(m/d/y) : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                    cout<<"\nTime associated with slot(h/m)   : "<<dateType[j].getHoursDate()<<" : "
                        <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;
                }

            }
            cout<<"\nThe doctor ID associated with the slot: "<<slotType[i].getSlotDocID()<<endl;
            cout<<"***********************************************"<<endl;
        }
    }

}
///function definition to show all the available slots by the doctor name
void showAvaliableSlotsForDocByName(vector <slot> &slotType, vector <date_time> &dateType, vector <doctor> &doctorType)
{
    string doctorID;
    string pOfDocIDs[3]= {"DolorisPemberton","SheltonMckeith","CarlynCora"};

    cout<<"In order to show all the available slots for a certain doctor, \n"
        <<"you will need to input the doctor Name for that certain doctor you "
        <<"\nwant to display the slots for"<<endl;
    system("PAUSE");
    system("CLS");
start:
    cout<<"\nThis is a list of all the doctor Names"<<endl;
    for (int i=0; i<3; i++)
    {
        cout<<pOfDocIDs[i]<<endl;
    }
    cout<<"Enter the name of the doctor you want to display all the slots for: ";
    cin >> doctorID;

    if (doctorID==pOfDocIDs[0]||doctorID==pOfDocIDs[1]||doctorID==pOfDocIDs[2])
    {

        goto valid;
    }
    else if (doctorID!=pOfDocIDs[0]||doctorID!=pOfDocIDs[1]||doctorID!=pOfDocIDs[2])
    {
        cout<<"The doctor name you entered is invalid, please make sure it \n"
            <<"matches the one of the names from the list of Doctor names"<<endl;
        Sleep(4000*1);
        system("CLS");
        goto start;
    }
valid:
    string theActualID;
    for (int i=0; i<doctorType.size(); i++)
    {
        if (doctorID==doctorType[i].getDocName())
        {
            theActualID=doctorType[i].getDocID();
        }
    }
    for (int i=0; i<slotType.size(); i++)
    {
        if (theActualID==slotType[i].getSlotDocID() &&slotType[i].getSlotStatus()==true)
        {
            cout<<"\nSlot ID that identifies the slot: "<<slotType[i].getslotID()<<endl;
            for (int j=0; j<dateType.size(); j++)
            {

                if(slotType[i].getDateID()==dateType[j].getDateID())
                {

                    cout<<"\nDate Associated with slot(m/d/y) : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                    cout<<"\nTime associated with slot(h/m)   : "<<dateType[j].getHoursDate()<<" : "
                        <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;
                }

            }
            cout<<"\nThe doctor ID associated with the slot: "<<slotType[i].getSlotDocID()<<endl;
            cout<<"***********************************************"<<endl;
        }
    }



}
///function definition to delete a slot
void removeSlot(vector <slot> &slotType)
{
    string slotIDToBeDeleted;
    int slotIndexToBeDeleted=0;
    bool checkValid=false;

    cout<<"Enter the slot ID you want to remove: ";
    cin >>slotIDToBeDeleted;

    for (int i=0; i<slotType.size(); i++)
    {
        if (slotIDToBeDeleted==slotType[i].getslotID())
        {
            slotIndexToBeDeleted=i;
        }
    }

    if(slotType[slotIndexToBeDeleted].getSlotStatus()==false)
    {
        system("CLS");
        cout<<"THE SLOT SELECTED HAS BEEN ASSOCIATED WITH AN APPOINTMENT,\nPLEASE DELETE THE APPOINTMENT THAT HAS THE SLOT ID "<<slotIDToBeDeleted<<" FIRST!"<<endl;
        system("PAUSE");
        system("CLS");
        goto exit;
    }

    slotType.erase(slotType.begin()+slotIndexToBeDeleted);
    cout<<"The slot has been successfully deleted!"<<endl;
    system("PAUSE");
    system("CLS");
exit:
    cout<<endl;
}
