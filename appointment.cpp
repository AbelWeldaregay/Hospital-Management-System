#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>
#include "appointment.h"
#include "windows.h"
#include "patient.h"
#include "doctors.h"
#include "date_time.h"
#include "slots.h"

using namespace std;
///default constructor for appointment
appointment::appointment()
{
    appointmentID=0;
    doctor_id="";
    patient_id="";
    slot_id="";
    diagnosesID=0;
}
///function that prints out the appointment menu
int printAppointmentMenu()
{

    int userChoice;

    cout<<"****************************"<<endl;
    cout<<"1. Schedule a new appointment"<<endl;
    cout<<"2. Show all appointments"<<endl;
    cout<<"3. Update an existing appointment"<<endl;
    cout<<"4. Remove an appointment"<<endl;
    cout<<"5. Show all appointments for a doctor by doctor's name"<<endl;
    cout<<"6. Show all appointments for a patient by patient's name"<<endl;
    cout<<"7. Show all appointments for a patient by patient's email"<<endl;
    cout<<"8. Go back to the Main Menu"<<endl;
    cin >> userChoice;
    system("CLS");
    return userChoice;
}


///function that prints out the dates from the datetime adt given a index
void printDate(vector <date_time> &dateType, int index)
{

    cout<<"DATE OF APPOINTMENT(m/d/y) : "<<dateType[index].getMonthDate()<<"/"<<dateType[index].getDayDate()<<"/"<<dateType[index].getYearDate()<<endl;
    cout<<"TIME OF APPOINTMENT(h/m)   : "<<dateType[index].getHoursDate()<<" : "
        <<dateType[index].getMinutesDate()<<" "<<dateType[index].getAMPM()<<endl;
}
///function that prints out a appointment at a given index
void printAppAtIndex(vector <appointment> &appointmentType, int &i)
{
    cout<<"***************Search Results*********************"<<endl;
    cout<<"Appointment ID                                 : "<<appointmentType[i].getAppointmentID()<<endl;
    cout<<"The doctor ID associated with the appointment  : "<<appointmentType[i].getDoctorID()<<endl;
    cout<<"The patient ID associated with the appointment : "<<appointmentType[i].getPatientID()<<endl;
    cout<<"The slot ID associated with the appointment    : "<<appointmentType[i].getSlotID()<<endl;
    cout<<"The appointment reason                         : "<<appointmentType[i].getAppointmentReason()<<endl;
    cout<<"Prescribed Medication                          : "<<appointmentType[i].getPrescribedMedication()<<endl;
}
///function to search for an appointment, given the doctors name
void searchAppByName(vector <appointment> &appointmentType, vector <doctor> &doctorType)
{
    string tempDocName;
    cout<<"Enter the doctor's name associated with the appointment: ";
    cin>> tempDocName; //stores the doctors name into temdoc name
    system("CLS"); //clears the screen

    for (int i=0; i<appointmentType.size(); i++)  //loops through the appointment vector
    {
        for (int j=0; j<doctorType.size(); j++) //loops through all the doctors
        {
            if (tempDocName==doctorType[j].getDocName())
            {
                if(doctorType[j].getDocID()==appointmentType[i].getDoctorID())
                {
                    printAppAtIndex(appointmentType, i); //if the doctors from the appointment index and doctor index match, it will print doctor information at that matching index
                }
            }
        }
    }
}
///function to search for an appointment by the name of patient associated with the appointment
void searchAppByPatient(vector <appointment> &appointmentType, vector <patient> &patientType, int &caseChoice)
{
    string searchItem;

    if (caseChoice==6)//if the user chooses 6, which is to search by name, this if statement will be executed
    {
        cout<<"Enter the patient's name associated with the appointment: ";
        cin>>searchItem;
        goto searchByName; //after the the user inputs the name of the patient, it will go to the label searchByName to search by name
    }
    if(caseChoice==7) //if the user chooses 7, then it will be prompted an email
    {
        cout<<"Enter the patient's email associated with the appointment: ";
        cin >> searchItem;
        goto searchByEmail; //after storing the patients email inside searchItem, it will go to the label searchByEmail to search and print results
    }

searchByName:
    for (int j=0; j<patientType.size(); j++) //loops through the whole patients vector
    {
        if (searchItem==patientType[j].getPatientName())  //if the patients name matches with one of the patients inside the patients vector
        {
            if(patientType[j].getID()==appointmentType[j].getPatientID()) //then if the patients id in the patients vector is equal to the patient id inside the appointment
            {
                printAppAtIndex(appointmentType, j);  //then it will print the appointment at that index
            }
        }
    }

    goto exit; //inorder to skip the searchByEmail, i put a goto exit, which will skip the searchByEmail

searchByEmail:
    for (int i=0; i<appointmentType.size(); i++)  //will loop through the appointments vector
    {
        for (int j=0; j<patientType.size(); j++)  //will loop through the patients vector
        {
            if (searchItem==patientType[j].getPatientEmail()) //if the email entered matches with the email inside patients vector
            {
                if(patientType[j].getID()==appointmentType[i].getPatientID()) //then if the patient id  matches then patient id inside the appointments
                {
                    printAppAtIndex(appointmentType, i); //prints appointment at the given index
                }
            }
        }
    }


exit:
    cout<<endl;
}

appointment::appointment(vector <slot> &slotType, vector<date_time> &dateType, vector <patient> &patientType, vector<doctor> &docType)
{

    bool checkValidP=false;  //boolean variable used to check if the patient id exists

start:
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"Enter the patient ID you want to book the appointment for: "; //prompting to enter the patient id
    cin >> patient_id; //storing patient id

    ///initialize lab appointment to false, because it is booking a normal appointment.
    labAppointment=false; //to differenciate it from a lab appointment

    for (int i=0; i<patientType.size(); i++)
    {
        if (patient_id==patientType[i].getID())
        {
            checkValidP=true;
        }

    }

    if (checkValidP==false)  //if the patient id does not exist, this will be printed
    {
        system("CLS");
        cout<<"Invalid patient ID, please try again"<<endl;
        system("PAUSE");
        system("CLS");
        goto start;

    }
    system("CLS");
    int indexOfPatient=0;
    string tempSlotID;
    int slotIndex=0;
    int dateID=0;
    int secondSlotIndex=0;

    for (int i=0; i<patientType.size(); i++) //loops through the patients vector
    {
        if (patient_id==patientType[i].getID())  //if the patient id entered is equal to the patient id inside the patients vector
        {
            indexOfPatient=i;  //the index of the vector is i
            break;  //will break out of the loop
        }

    }
    doctor_id=patientType[indexOfPatient].getDocID(); //the doctor id for the appointment is equal to the doctor id from the patient given

promtAgain: //printing all the available slots for the specific patient
    cout<<"***********Listing of Available Slots***********"<<endl;
    for (int i=0; i<slotType.size(); i++)  //looping through the entire slots
    {
        if (doctor_id==slotType[i].getSlotDocID() && slotType[i].getSlotStatus()==true && slotType[i].getSlotDocID()!="99999")  //if the doctor id is equal to the  doc id from the slot and the slot status is equal to true
        {
            slotIndex = i; //slot index is equal to i
            dateID=slotType[i].getDateID();  //the date id is equal to the date id from the slot vector
            cout<<"=========================================="<<endl;
            cout<<"SLOT ID    : "<<slotType[i].getslotID()<<endl;
            cout<<"DATE ID    : "<<slotType[i].getDateID()<<endl;
            cout<<"SLOT STATUS: "<<slotType[i].getSlotStatus()<<endl;
            for (int j=0; j<dateType.size(); j++) //looping through the datetime vector
            {
                if(dateID==dateType[j].getDateID()) //if the date id is equal to the date id from the datetime vector , print the date and times
                {
                    cout<<"DATE OF APPOINTMENT(m/d/y) : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                    cout<<"TIME OF APPOINTMENT(h/m)   : "<<dateType[j].getHoursDate()<<" : "
                        <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;

                    cout<<"=========================================="<<endl;
                }
            }

        }

    }
promptForSlotID: ///promting for the slot id and checking if it is a valid input
    cout<<"\nEnter the slot id you want for your appointment: ";
    cin>>tempSlotID;
    int temp_slot_index;
    for (int i=0; i<slotType.size(); i++)
    {
        if(tempSlotID==slotType[i].getslotID())
        {
            temp_slot_index=i;
            break;
        }
        else
        {
            temp_slot_index=-1;
        }

    }

    if (temp_slot_index==-1)
    {
        cout<<"Invalid slot, please try again"<<endl;
        goto promptForSlotID;
    }

    if (doctor_id==slotType[temp_slot_index].getSlotDocID() && slotType[temp_slot_index].getSlotStatus()==true)
    {
        slot_id=tempSlotID;


    }
    else
    {
        cout<<"Invalid slot ID, you can only choose from the printed list of slots"<<endl;
        system("PAUSE");
        goto promtAgain;
    }


    system("CLS");
    for (int i=0; i< slotType.size(); i++)
    {
        if (tempSlotID==slotType[i].getslotID())
        {
            secondSlotIndex=i;
            break;
        }
    }

    if (slotType[secondSlotIndex].getSlotStatus()==true && doctor_id==slotType[secondSlotIndex].getSlotDocID())
    {
        slot_id=tempSlotID;
        slotType[secondSlotIndex].setSlotStatusToFalse();
        stringstream ss; //gives me the ability to convert a string to an int
        ss << ++appID; //converting the string to an int
        appointmentID=appID; //storing the converted appID to the appointmentID
    }
    else
    { //if the slot id is already taken, this will be printed
        cout<<"The slot id you chose has already been taken, or is not associated with the doctor the patient has, please try again"<<endl;
        goto promtAgain;
    }
    cout<<"What is the reason for the appointment: ";
    cin.ignore(); //clearing the buffer
    getline(cin, appointmentReason); //getting the whole line
    system("CLS");
    //printing the appointment results
    cout<<"Your appointment was booked successfully!"<<endl;
    cout<<"************APPOINTMENT RESULTS*****************"<<endl;
    cout<<"The doctor id associated with the appointment :  "<<doctor_id<<endl;
    cout<<"The patient id associated with the appointment:  "<<patient_id<<endl;
    cout<<"The slot id associated with the appointment   :  "<<slot_id<<endl;
    cout<<"The appointment reason                        :  "<<appointmentReason<<endl;

    for (int i=0; i<slotType.size(); i++) //loops through the slots vector
    {
        if (slot_id==slotType[i].getslotID()) //if the slot id entered is equal to the slot id from the slots
        {
            for (int j=0; j<dateType.size(); j++) //loops through the dateType vector
            {
                if (slotType[i].getDateID()==dateType[j].getDateID())  //if the date id from the slots is equal to the date id from the dateType vector, print the dateType vector
                {
                    cout<<"Date of the appointment(m/d/y)                : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                    cout<<"Time of the appointment(h/m)                  : "<<dateType[j].getHoursDate()<<" : "
                        <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;
                    cout<<"=========================================="<<endl;
                }
            }
        }
    }

    system("PAUSE");
    system("CLS");

}

///function to print all of the appointments inside the vector appointment
void printAppointments(vector <appointment>  &appointmentType, vector <slot> &slotType, vector <date_time> &dateType, vector <diagnoses> &diagnosesType)
{
    cout<<"***************List of all appointments*********************"<<endl;

    for (int i=0; i<appointmentType.size(); i++) //looping through all the appointments
    {

        if(appointmentType[i].getLabAppointment()==false)  //if it is not a lab appointment, then print the appointment data
        {

            cout<<"Appointment ID                                 : "<<appointmentType[i].getAppointmentID()<<endl;
            cout<<"The doctor ID associated with the appointment  : "<<appointmentType[i].getDoctorID()<<endl;
            cout<<"The patient ID associated with the appointment : "<<appointmentType[i].getPatientID()<<endl;
            cout<<"The slot ID associated with the appointment    : "<<appointmentType[i].getSlotID()<<endl;
            cout<<"The appointment reason                         : "<<appointmentType[i].getAppointmentReason()<<endl;
            cout<<"Prescribed Medication                          : "<<appointmentType[i].getPrescribedMedication()<<endl;
            for (int y=0; y<diagnosesType.size(); y++) //looping through all the diagnosis vector
            {
                if(appointmentType[i].getDiagnosisID()==diagnosesType[y].getDiagnosisID()) //if a diagnosis id from the appointment adt matches the diagnosis from the diagnosis adt, then print the diagnosis
                {
                    cout<<"Diagnoses                              : "<<diagnosesType[y].getDiagnosisName()<<endl;
                }
            }
            for (int j =0; j<slotType.size(); j++) //looping through the slots vector
            {
                if(appointmentType[i].getSlotID()==slotType[j].getslotID()) //if the slot id from the appointment matches the slot id from the slot vector
                {
                    for (int x=0; x<dateType.size(); x++) //then loop through the dateType vector
                    {
                        if (slotType[j].getDateID()==dateType[x].getDateID()) //if the date id from the slots is equal to the date id from the datetype vector, prints all matching date and times
                        {
                            cout<<"DATE OF APPOINTMENT(m/d/y)                     : "<<dateType[x].getMonthDate()<<"/"<<dateType[x].getDayDate()<<"/"<<dateType[x].getYearDate()<<endl;
                            cout<<"TIME OF APPOINTMENT(h/m)                       : "<<dateType[x].getHoursDate()<<" : "
                                <<dateType[x].getMinutesDate()<<" "<<dateType[x].getAMPM()<<endl;
                            cout<<"======================================================"<<endl;
                        }
                    }
                }
            }

        }
    }

}
///function to print the appointment modification menu
int printAppointmentModMenu()
{
    int userChoice=0;
    cout<<"\nChoose one of the followings you want to modify(1-5)"<<endl;
    cout<<"1.Update the appointment reason "<<endl;
    cout<<"2.Reschedule the appointment by changing the slot ID"<<endl;
    cout<<"3.Update the Diagnoses"<<endl;
    cout<<"4.Update the Prescribed Medication"<<endl;
    cout<<"5.Return to the main menu"<<endl;
    cin >> userChoice;
    system("CLS");

    return userChoice;

}
///*********************************************************
///function to update the appointments
void modifyReschedule(vector <appointment> &appointmentType, vector <slot> &slotType, vector <date_time> &dateType, vector <diagnoses> &diagnosesType)
{
    int appointmentID=0;
    int appointmentIndex=0;
    int userChoice=0;
    if (appointmentType.size()==0) //if there are no appointments, then this message will be displayed
    {
        system("CLS");
        cout<<"There are currently no appointments for you to modify/reschedule"<<endl;
        cout<<"Please try again after you schedule an appointment."<<endl;
        system("PAUSE");
        system("CLS");
        goto exit;
    }
    cout<<"These are the list of appointments you can modify/reschedule"<<endl;
    printAppointments(appointmentType, slotType, dateType, diagnosesType); //prints the appointments, so the user can know which ones they can update

firstPrompt:
    cout << "Enter the appointment ID you want to modify/reschedule: ";
    cin >> appointmentID;
    system("CLS");
    for (int i=0; i<appointmentType.size(); i++) //loops through the appointment vector, then finds the index of the appointment the user wants to update
    {

        if (appointmentID==appointmentType[i].getAppointmentID())
        {
            appointmentIndex=i;
            break; //once the appointment id is found inside the appointmentType vector, the break statement out of the loop
        }

    }
    userChoice=printAppointmentModMenu();
    if (userChoice==1)  //if the user chooses one, then the appointment reason update function will be invoked
    {
        modifyAppointmentReason(appointmentType, userChoice, appointmentIndex);
        goto secExit;
    }
    if (userChoice==2) //if the user chooses two, then the reschedule appointment function will be invoked
    {
        rescheduleAppointment(appointmentType, slotType, dateType, userChoice, appointmentIndex);
        goto secExit;
    }
    if(userChoice==3) //if the user chooses three, then the update diagnosis function will be invoked
    {
        updateDiagnoses(appointmentType, diagnosesType, userChoice, appointmentIndex);
        goto secExit;
    }
    if(userChoice==4) //if the user chooses four, then the update prescribed medication function will be invoked
    {
        updatePrescribedMedication(appointmentType, appointmentIndex);
        goto secExit;
    }

secExit:
    system("CLS");

exit:
    cout<<endl;
}

///function to print all the available slots
void printAvailableSlots(vector <slot> &slotType, vector <date_time> &dateType, vector <appointment> &appointmentType, int appointmentIndex)
{
    cout<<"\nListing of all available slots"<<endl;

    for (int i=0; i<slotType.size(); i++) //loops through the slots vector
    {
        if (appointmentType[appointmentIndex].getDoctorID()==slotType[i].getSlotDocID()) //if the doctor id from the appointments matches the doc id from the slots
        {
            if (slotType[i].getSlotStatus()==true) //and the slot status from the slot vector is true
            {
                cout<<"Slot ID that identifies the slot: "<<slotType[i].getslotID()<<endl;

                for (int j=0; j<dateType.size(); j++) //loop through the datetype adt
                {
                    if(slotType[i].getDateID()==dateType[j].getDateID()) //checks if the date id from the slots is equal to the date id from the datetime id, if it is, it prints all the datetimes
                    {

                        cout<<"DATE OF APPOINTMENT(m/d/y) : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                        cout<<"TIME OF APPOINTMENT(h/m)   : "<<dateType[j].getHoursDate()<<" : "
                            <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;
                        cout<<"=========================================="<<endl;
                    }

                }

                cout<<"The doctor ID associated with the slot: "<<slotType[i].getSlotDocID()<<endl;
            }
        }
    }
}
///function to reschedule appointments
void rescheduleAppointment(vector <appointment> &appointmentType, vector <slot> &slotType, vector <date_time> &dateType, int userChoice, int appointmentIndex)
{
    int indexOfOldSlot=0;
    int indexOfNewSlot=0;
    string newSlotID;

    printAvailableSlots(slotType, dateType, appointmentType, appointmentIndex); //prints all the available slots

    if (userChoice==2)
    {
        cout<<"Enter the slot ID you want to reschedule to: ";
        cin >> newSlotID;
        system("CLS");

        for (int i=0; i<slotType.size(); i++) //loops through the slots vector to find the index of the old slot
        {
            if(appointmentType[appointmentIndex].getSlotID()==slotType[i].getslotID())
            {
                indexOfOldSlot=i;
            }
        }
        for (int i=0; i<slotType.size(); i++) //loops through the slots vector to find the index of the new slot
        {
            if (newSlotID == slotType[i].getslotID())
            {
                indexOfNewSlot=i;
            }
        }

        slotType[indexOfOldSlot].setSlotStatusToTrue(); //sets the old slot to available
        slotType[indexOfNewSlot].setSlotStatusToFalse(); //sets the new slot to unavailable
        appointmentType[appointmentIndex].doctor_id=slotType[indexOfNewSlot].getSlotDocID(); //sets the doctorID of the appointment to the matching doctorID from the slot vector
        appointmentType[appointmentIndex].slot_id=slotType[indexOfNewSlot].getslotID(); //sets the slot id of the slots to the matching slot id from the slots vector

        system("CLS");
        cout<<"THE APPOINTMENT WAS SUCCESSFULLY RESCHECDULED"<<endl;
        Sleep(1*2000);  //prints a confirmation message form two seconds
    }
}


///Function to update the diagnoses
void updateDiagnoses( vector <appointment> &appointmentType, vector<diagnoses> &diagnosesType, int &userChoice, int &appointmentIndex)
{
    string tempDiagnoses;

    int indexOfDiagnoes=999;
    if(userChoice==3) //if the user choice is 3, it will update the diagnosis
    {

        printDiagnoses(diagnosesType); //prints all the diagnosis

        cout<<"Enter the name of the new diagnoses (has to exactly match one of the names printed above): ";
        cin.ignore(); //clearing the buffer
        getline(cin, tempDiagnoses); //gets the diagnosis name
    }
    cout<<tempDiagnoses<<endl;
    system("PAUSE");
    for (int i=0; i<diagnosesType.size(); i++) //loops through the diagnosis vector
    {
        if (tempDiagnoses==diagnosesType[i].getDiagnosisName()) //finds the index of the diagnosis
        {
            indexOfDiagnoes=i;
        }
    }

    while(indexOfDiagnoes==999)  //if the variable is still at 999, that means it is an invalid input
    {
        system("CLS");
        cout<<"THE DIAGNOSIS NAME ENTERED DOES NOT MATCH ANY OF THE PRINTED DIAGNOSIS NAMES,\nPLEASE TRY AGAIN"<<endl;
        system("PAUSE");
        system("CLS");
        printDiagnoses(diagnosesType); //prints all the diagnosis
        cout<<"Enter the name of the new diagnoses (has to exactly match one of the names printed above): ";
        //  cin.ignore(); //clearing the buffer
        getline(cin, tempDiagnoses); //gets the diagnosis name
        system("CLS");

        for (int i=0; i<diagnosesType.size(); i++) //loops through the diagnosis vector
        {
            if (tempDiagnoses==diagnosesType[i].getDiagnosisName()) //finds the index of the diagnosis
            {
                indexOfDiagnoes=i;
                cout<<diagnosesType[i].getDiagnosisName()<<endl;
            }
        }
    }

    ///assigning the diagnosis id  the value the user gave
    appointmentType[appointmentIndex].diagnosesID=diagnosesType[indexOfDiagnoes].getDiagnosisID();


    system("CLS");
    cout<<"\n\nTHE DIAGNOIS WAS SUCCESSFULLY UPDATED!"<<endl; //printing the confirmation message
    Sleep(1*2000);
    system("CLS");
}
///function to modify the appointment reason
void modifyAppointmentReason(vector <appointment> &appointmentType, int userChoice, int appointmentIndex)
{
    string appointmentReason;

    if (userChoice==1)
    {
        cout<<"Enter the new reason for the appointment: ";
        cin.ignore(); //clearing the buffer
        getline(cin, appointmentReason); //stores the whole line
        system("CLS");  //clearing the screen

        appointmentType[appointmentIndex].appointmentReason=appointmentReason; //storing the entered appointment reason to the appointment vector at the index of the wanted modification vector

    }
}
///function to delete an appointment
void removeAppointment(vector <appointment> &appointmentType, vector <slot> &slotType)
{
    int appointmentIDtoBeDeleted=0;
    int indexOfAppt=0;
    int indexOfSlot=0;
    cout<<"Enter the ID of the appointment you want to delete: ";
    cin>> appointmentIDtoBeDeleted;
    system("CLS");

    for (int i=0; i<appointmentType.size(); i++) //loops through the appointment vector
    {
        if (appointmentIDtoBeDeleted==appointmentType[i].getAppointmentID())
        {
            indexOfAppt=i;
        }
    }
    for (int i=0; i<slotType.size(); i++) //loops through the slots vector
    {
        if (appointmentType[indexOfAppt].getSlotID()==slotType[i].getslotID())  //if the slot id from the appointment is equal to the slot id from the slots
        {
            indexOfSlot=i; //the index of the slot is equal to i
        }
    }

    slotType[indexOfSlot].setSlotStatusToTrue(); //changes the deleted appointment's slot back to available
    appointmentType.erase(appointmentType.begin()+indexOfAppt);  //deletes the appointment
    //printing out a confirmation message
    cout<<"\n\n\nTHE APPOINTMENT WITH THE ID "<<appointmentIDtoBeDeleted<<" HAS BEEN SUCCESSFULLY DELETED!"<<endl; //prints out confirmation message
    cout<<"\nTHE SLOT WITH THE ID "<<slotType[indexOfSlot].getslotID()<<" IS NOW AVAILABLE!"<<endl;
    system("PAUSE");
    system("CLS");
}

///function to update the prescribed medication
void updatePrescribedMedication(vector <appointment> &appointmentType, int &appointmentIndex)
{
    string tempMedication;

    cout<<"Enter the prescribed medication : ";
    cin.ignore(); //clearing the buffer
    getline(cin, tempMedication); //reading the whole line of the user's input

    appointmentType[appointmentIndex].prescribed_medication=tempMedication; //assigns the prescribed medication in appointments with the user value entered
    system("CLS");
    cout<<"The prescribed medication was successfully updated!"<<endl; //printing out a confirmation message
    system("PAUSE");
}

//printing out the menu for the lab appointments
int printLabMenu()
{
    int userChoice=0;

    cout<<"Choose one of the following options"<<endl;
    cout<<"1.Add new lab appointment"<<endl;
    cout<<"2.Delete lab appointment"<<endl;
    cout<<"3.Show all lab appointments"<<endl;
    cout<<"4.Update Lab Appointments"<<endl;
    cout<<"5.Return to the Main Menu"<<endl;
    cin>>userChoice;

    return userChoice; //returns the user choice
}

///FUNCTION TO ADD A LAB APPOINTMENT
void addLabAppointment(vector <slot> &slotType, vector<date_time> &dateType, vector <patient> &patientType, vector<doctor> &docType, vector <appointment> &appointmentType)
{

    bool checkValidP=false;
    string tempPatientID;
    string tempDocID;
    string appointmentReason;
    int appointmentID=appointmentType.size()+50;
    //  static int indexOfApptToAdd=appointmentType.size();
start:
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"Enter the patient ID you want to book the Lab Appointment for: ";
    cin >> tempPatientID;

    //looping through the patient vector and checking if the user input for patient id matches one of the patient type vector patient id
    for (int i=0; i<patientType.size(); i++)
    {
        if (tempPatientID==patientType[i].getID())
        {
            checkValidP=true; //if it is found then checkvalidp is equal to true
        }

    }

// if it is not found it means that it is false, so then i will print an error message and use labels to go back and prompt the user again for a valid id
    if (checkValidP==false)
    {
        system("CLS");
        cout<<"Invalid patient ID, please try again"<<endl;
        system("PAUSE");
        system("CLS");
        goto start;
    }

    system("CLS");
    int indexOfPatient=0;
    string tempSlotID;
    int slotIndex=0;
    int dateID=0;
    int secondSlotIndex=0;

    //looping through the patient vector to find the index of the patient
    for (int i=0; i<patientType.size(); i++)
    {
        if (tempPatientID==patientType[i].getID())
        {
            indexOfPatient=i;
            break;
        }

    }

    tempDocID=patientType[indexOfPatient].getDocID(); //storing the doctor id from the patient at the found index into the tempDocID, which will be used in the pushback

promtAgain:
    cout<<"***********Listing of Available Slots***********"<<endl;
    for (int i=30; i<slotType.size(); i++) //i only want to print from 31-40 slots, so i has to start at 30
    {
        if (slotType[i].getSlotStatus()==true) //if the slot is available
        {
            slotIndex = i;
            dateID=slotType[i].getDateID();
            cout<<"=========================================="<<endl;
            cout<<"SLOT ID    : "<<slotType[i].getslotID()<<endl;
            cout<<"DATE ID    : "<<slotType[i].getDateID()<<endl;
            cout<<"SLOT STATUS: "<<slotType[i].getSlotStatus()<<endl;
            for (int j=0; j<dateType.size(); j++) //looping through the dateType vector and printing out the values.
            {
                if(dateID==dateType[j].getDateID())
                {
                    cout<<"DATE OF APPOINTMENT(m/d/y) : "<<dateType[j].getMonthDate()<<"/"<<dateType[j].getDayDate()<<"/"<<dateType[j].getYearDate()<<endl;
                    cout<<"TIME OF APPOINTMENT(h/m)   : "<<dateType[j].getHoursDate()<<" : "
                        <<dateType[j].getMinutesDate()<<" "<<dateType[j].getAMPM()<<endl;

                    cout<<"=========================================="<<endl;
                }
            }

        }

    }
promptForSlotID:
    cout<<"\nEnter the slot id you want for your appointment(Must be greater than 30): ";
    cin>>tempSlotID;
    system("CLS");
    int temp_slot_index;
    for (int i=30; i<slotType.size(); i++) //looping through the slots from 30 to 40
    {
        if(tempSlotID==slotType[i].getslotID())
        {
            temp_slot_index=i; //if the slot id matches then the temp_slot_index is equal to i.
            break;
        }
        else
        {
            temp_slot_index=-1; //if it is not equal then the temp_slot_index is equal to -1, indicating it does not exist
        }

    }

    if (temp_slot_index==-1) //if the temp_slot_index is equal to -1, then i know it is invalid, so i will print a error message, and use a label to go back to the label promptForSlotID
    {
        cout<<"Invalid slot, please try again"<<endl;
        goto promptForSlotID;
    }

///this part of the program checks if the date of the appointment the user is trying to book is already used
    int indexOfDateIDGiven=0;
    bool checkDuplicate=false;  //since the user can only book one lab appointment a day, i use a boolean to check if there is another duplicate date
///first i find the index of the dateType
    for (int i=0; i<dateType.size(); i++)
    {
        if(slotType[temp_slot_index].getDateID()==dateType[i].getDateID())
        {
            indexOfDateIDGiven=i;
        }
    }
///now i compare all the date id from the appointments with  the date id i found above, if there are duplicates, i initialize checkDuplicate to true
    for (int i=0; i<appointmentType.size(); i++) //loops through the appointment vector
    {
        if(appointmentType[i].getLabAppointment()==true)  //if it is a lab appointment
        {
            for (int j =0; j<slotType.size(); j++) //loops through the whole slot
            {
                if(appointmentType[i].getSlotID()==slotType[j].getslotID()) //if the slot id from the appointment vector is equal to the slot id from the slot vector
                {
                    for (int x=0; x<dateType.size(); x++) //loops through the date vector
                    {
                        if (slotType[j].getDateID()==dateType[x].getDateID()) //if the date id from the slot vector is equal to the date id from the date vector
                        {
                            if (dateType[indexOfDateIDGiven].getYearDate()==dateType[x].getYearDate()  //if the month, day, and year from the date the user is trying to book, is equal to
                                    && dateType[indexOfDateIDGiven].getMonthDate()==dateType[x].getMonthDate() //the the month, day, year from all the appointments, then checkDuplicate=true
                                    && dateType[indexOfDateIDGiven].getDayDate()==dateType[x].getDayDate())
                            {
                                checkDuplicate=true;
                            }
                        }
                    }
                }
            }
        }
    }

    ///now if the check duplicate is true, i know there is two lab appointments with the same date, so i print an error statement and go to the label promptforSlotID
    if(checkDuplicate==true)
    {
        cout<<"There is already a lab appointment booked for the date at the slot, please choose a new slot"<<endl;
        system("PAUSE");
        system("CLS");
        goto promptForSlotID;
    }


    cout<<"What is the reason for the appointment: ";
    cin.ignore(); //clearing the buffer
    getline(cin, appointmentReason); //getting the whole line
    system("CLS");
///now adding all the valid values to the lab appointment vector
    appointmentType.push_back(appointment());
    int indexOfApptToAdd=appointmentType.size()-1;
    appointmentType[indexOfApptToAdd].patient_id=tempPatientID;
    appointmentType[indexOfApptToAdd].slot_id=tempSlotID;
    appointmentType[indexOfApptToAdd].doctor_id=tempDocID;
    appointmentType[indexOfApptToAdd].appointmentID=appointmentID;
    appointmentType[indexOfApptToAdd].appointmentReason=appointmentReason;
    appointmentType[indexOfApptToAdd].labAppointment=true;
    slotType[temp_slot_index].setSlotStatusToFalse();

    system("CLS");
    cout<<"\n\nTHE LAB APPOINTMENT WAS SUCCESSFULLY ADDED!"<<endl; //prints out a confirmation for two seconds
    Sleep(1*2000);
    system("CLS");
}
///***********************************************************************************************************************************************
///Function to print out the lab appointments
void printLabAppointments(vector <appointment> &appointmentType, vector <date_time> dateType, vector <diagnoses> &diagnosesType, vector <slot> &slotType)
{
    cout<<"***************List of All Lab Appointments*********************"<<endl;

    for (int i=0; i<appointmentType.size(); i++) //loops through the whole lab appointments vector
    {

        if(appointmentType[i].getLabAppointment()==true) //if the lab appointment if true, then it is a lab appointment and will print out the labs
        {

            cout<<"Appointment ID associated with LAB APPOINTMENT : "<<appointmentType[i].getAppointmentID()<<endl;
            cout<<"The doctor ID associated with LAB APPOINTMENT  : "<<appointmentType[i].getDoctorID()<<endl;
            cout<<"The patient ID associated with LAB APPOINTMENT : "<<appointmentType[i].getPatientID()<<endl;
            cout<<"The slot ID associated with LAB APPOINTMENT    : "<<appointmentType[i].getSlotID()<<endl;
            cout<<"The appointment reason for LAB APPOINTMENT     : "<<appointmentType[i].getAppointmentReason()<<endl;
            cout<<"Prescribed Medication                          : "<<appointmentType[i].getPrescribedMedication()<<endl;
            for (int y=0; y<diagnosesType.size(); y++) //loops through the diagnosis
            {
                if(appointmentType[i].getDiagnosisID()==diagnosesType[y].getDiagnosisID()) //if the diagnosis from the appointment type vector is equal to the diagnoisis id from the diagnoiss vector
                {
                    cout<<"Diagnoses                             : "<<diagnosesType[y].getDiagnosisName()<<endl;
                }
            }

            for (int j =0; j<slotType.size(); j++) //loops through the slots vector
            {
                if(appointmentType[i].getSlotID()==slotType[j].getslotID()) //if the slot id from the appointment vector is equal to the slot id from the slot vector
                {
                    for (int x=0; x<dateType.size(); x++) //loops through the dateType vector
                    {
                        if (slotType[j].getDateID()==dateType[x].getDateID()) //if the date id from the slot is equal to the date id from the dateType vector, it prints out all the date and times
                        {
                            cout<<"DATE OF APPOINTMENT(m/d/y)                    : "<<dateType[x].getMonthDate()<<"/"<<dateType[x].getDayDate()<<"/"<<dateType[x].getYearDate()<<endl;
                            cout<<"TIME OF APPOINTMENT(h/m)                      : "<<dateType[x].getHoursDate()<<" : "
                                <<dateType[x].getMinutesDate()<<" "<<dateType[x].getAMPM()<<endl;
                            cout<<"======================================================"<<endl;
                        }
                    }
                }
            }

        }
    }

}
///function to print out the modifications menu for the lab
int printsubModLabMenu()
{
    int userChoice=0;
    system("CLS");
    cout<<"Please choose one of the following (1-2)"<<endl;
    cout<<"1.Update the prescribed medication for the lab appointment"<<endl;
    cout<<"2.Update the diagnosis for the lab appointment"<<endl;
    cin>>userChoice;

    return userChoice;
}
///function to update the lab appointments
void updateLabApptments(vector <appointment> &appointmentType, vector <diagnoses> &diagnosesType)
{
    int labID=0;
    bool checkValid=false;
    int userChoice=0;
    int counter=0;
    int indexOfAppt=0;
    userChoice=printsubModLabMenu();
    ///first i check if there are any lab appointments, so i loop through the appointment vector, and check if the bool labAppointment is equal to true, if it is i increment counter
    for (int i=0; i<appointmentType.size(); i++)
    {
        if(appointmentType[i].getLabAppointment()==true)
        {
            counter++;
        }
    }
    //since i am incrementing counter, if counter is zero, i know there are no lab appointment, so i print out a error statement and exit the function
    if(counter==0)
    {
        system("CLS");
        cout<<"There are no lab appointments to update, please try again after you book a lab appointment"<<endl;
        goto exit;
    }

promptLabID:
    cout<<"Enter the Lab appointment ID for the lab you want to update: ";
    cin >>labID;
//check and find the index of the lab appointment id the user entered
    for (int i=0; i<appointmentType.size(); i++)
    {
        if(appointmentType[i].getLabAppointment()==true)
        {
            if(labID==appointmentType[i].getAppointmentID())
            {
                checkValid=true; //if it is found it is true
                indexOfAppt=i;
            }
        }
    }
    //if checkValid is equal to false, i print out an error statement and go to the label promptLabID
    if(checkValid==false)
    {
        cout<<"The lab appointment ID you entered does not exit, try again"<<endl;
        system("PAUSE");
        goto promptLabID;
        system("CLS");
    }
//if the userChoice is equal to 1, then i update the prescribed medication
    if(userChoice==1)
    {
        string prescribedMed;

        system("CLS");
        cout<<"Enter the prescribed medication: ";
        cin.ignore();
        getline(cin, prescribedMed);

        appointmentType[indexOfAppt].prescribed_medication=prescribedMed;
        system("CLS");
        cout<<"The prescribed medication for the lab appointment has been successfully updated!"<<endl;
        system("PAUSE");
    }
//if the userChoice is equal to 2 then i update the diagnosis
    if(userChoice==2)
    {
        int diagnosesID=0;
        bool checkDiagnosis=false;
        int indexOfDiagnosis=0;
        printDiagnoses(diagnosesType);

promptDiagnosis:
        cout<<"Enter the diagnosis ID that matches with the diagnosis name: ";
        cin >> diagnosesID;

        for (int i=0; i<diagnosesType.size(); i++)
        {
            if(diagnosesID==diagnosesType[i].getDiagnosisID())
            {
                checkDiagnosis=true;
                indexOfDiagnosis=i;
            }

        }
        if(checkDiagnosis==false)
        {
            cout<<"The Diagnosis ID you entered is invalid, please try again";
            system("PAUSE");
            goto promptDiagnosis;
            system("CLS");
        }
        appointmentType[indexOfAppt].diagnosesID=diagnosesID;
        system("CLS");
        cout<<"The Diagnosis ID was successfully updated!"<<endl;
        system("PAUSE");
        system("CLS");
    }



exit:
    cout<<endl;


}
///function to delete a lab appointment
void deleteLabApptment(vector <appointment> &appointmentType, vector <slot> &slotType)
{
    int apptID=0;
    int indexToBeDeleted=0;
    bool checkValid=false;
promptAgain:
    cout<<"Enter the Lab appointment ID you want to delete: ";
    cin >> apptID;
//i find the index of the lab appointment
    for (int i=0; i<appointmentType.size(); i++) //loops through the appointment vector
    {
        if (appointmentType[i].getLabAppointment()==true) // if the bool labAppointment is true
        {
            if (apptID==appointmentType[i].getAppointmentID())
            {
                indexToBeDeleted=i;
                checkValid=true;
            }
        }

    }
//if the checkValid is still false, i print an error statement, and go to the label promptAgain
    if(checkValid==false)
    {
        system("CLS");
        cout<<"The Lab Appointment ID you entered does not exit, please try again"<<endl;
        system("PAUSE");
        goto promptAgain;
    }

    for (int i=0; i<slotType.size(); i++) //loops though the slotType vector
    {
        if (appointmentType[indexToBeDeleted].getSlotID()==slotType[i].getslotID()) //if the slot id of the appointment to be deleted is equal to a slot id from the slot id from the slots vector
        {
            slotType[i].setSlotStatusToTrue(); //then i set the slot status to true,
        }
    }

    appointmentType.erase(appointmentType.begin()+indexToBeDeleted);
    system("CLS");
    cout<<"The lab appointment with the ID "<<apptID<<" has been successfully deleted!"<<endl;
    system("PAUSE");
    system("CLS");
}

