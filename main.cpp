#include <iostream> //gives input output operations
#include <iomanip> //gives formating options
#include <fstream> //includes file manipulation, ifstream, ofstream
#include <vector> //gives me the ability to use vectors
#include <stdlib.h>
#include <windows.h> //gives me the clear screen functionality
#include "appointment.h" //includes all the functionality inside the appointment.h
#include "diagnoses.h" //includes all the functionality inside the diagnosis.h
#include "record.h"  //includes all the functionality inside the record.h
#include "date_time.h" //includes all the functionality inside the date_time.h
#include "slots.h" //includes all the functionality inside the slots.h
#include "doctors.h" //includes all the functionality inside the doctors.h
#include "patient.h" //includes all the functionality inside the patient.h

using namespace std;
///function prototype for printMenu
int printMenu(vector <patient> &patientType, vector <doctor> &doctorType, vector <slot> &slotType, vector <date_time> &dateType,
              vector <appointment> &aptype, vector <diagnoses> &diagnosesType, vector <record> &recordType);
///function prototype for displayAllPatients
void displayAllPatients(vector <patient> &patientType, vector <doctor> &doctorType, vector<diagnoses> &diagnosesType, vector<appointment> &appointmentType);
void searchPatientByDoc(const vector <patient> &patientType, vector <doctor> &doctorType); ///function protype to search patient by doctor
///function prototype to reschedule an appointment
void rescheduleAppointment(vector <appointment> &appointmentType, vector <slot> &slotType, vector <date_time> &dateType, int userChoice, int appointmentIndex);
int appointment::appID=0; ///initializing the member variable appID to 0
void deleteDoctor(vector <doctor> &doctorType, vector <appointment> &appointmentType); ///function prototype to delete a doctor
void showPatientswithAppTimeRange(vector <patient> &patientType, vector <appointment> &appointmentType,
                                  vector <date_time> &dateType, vector <slot> &slotType); ///function prototype to show patients  with app by time range
///function prototype for template that initalizes the diagnosis id
template <class generic>
void initializeDiagnosesID(vector <generic> &genericType);

int main()
{
    vector <patient> patientType; ///declares a vector of a class of the data type patient
    vector <doctor> doctorType;   ///declares a vector of a class of the data type doctor
    vector <slot> slotType;       ///declares a vector of a class of the data type slot
    vector <date_time> dateType;   ///declares a vector of a class of the data type date_time
    vector <diagnoses> diagnosesType; ///declares a vector of a class of the data type diagnoses
    vector <appointment> appointmentType; ///declares a vector of a class of the data type appointment
    vector <record> recordType;  ///declares a vector of a class of the data type record
    doctor doctorAccessor; ///declares a temporary object of type doctor to access

    ifstream patientFile, doctorFile, slotsFile, dateFile, diagnosesFile;

    patientFile.open("Patients.txt"); //opens the file patient.txt
    readPatientsFile(patientFile, patientType); //calls the function that reads the patients file
    patientFile.close(); //closing the file

    doctorFile.open("Doctors.txt");//opens the file doctors.txt
    doctorAccessor.readDoctorFile(doctorFile, doctorType); //calls the function that reads the doctors file
    doctorFile.close(); //closing the file

    slotsFile.open("Slots.txt"); //opens the file doctors.txt
    readSlotFile(slotsFile, slotType); //calls the function that reads the slots file
    slotsFile.close(); //closing the file

    dateFile.open("Date_Time.txt"); //opens the file date_time.txt
    readDatesFile(dateFile, dateType); //calls the function that reads the date_time.txt
    dateFile.close(); //closing the file

    diagnosesFile.open("Diagnosis.txt"); //opens the file diagnosis.txt
    readDiagnosisFile(diagnosesFile, diagnosesType); //calls that function that reads the diagnosis.txt file
    diagnosesFile.close(); //closing the file

    initializeDiagnosesID(diagnosesType); //calls the template function to intialize the diagnois id
    initializeDiagnosesID(appointmentType);
    //calling the print menu function to print the menu
    int printFunction= printMenu(patientType, doctorType, slotType, dateType, appointmentType, diagnosesType, recordType);

    return 0;
}
///template definition that initalizes the the diagnosis id's
template <class generic>
void initializeDiagnosesID(vector <generic> &genericType)
{
    static int id=0;

    for (int i=0; i<genericType.size(); i++)
    {
        id++;
        genericType[i].diagnosesID=id;
    }
}
///This function prints the menus and manipulates the users entries to print sub menus and call functions
///****************************************************************
int printMenu(vector <patient> &patientType, vector <doctor> &doctorType, vector <slot> &slotType, vector <date_time> &dateType, vector <appointment> &aptype,
              vector <diagnoses> &diagnosesType, vector <record> &recordType)
{

    int userChoice=0, caseChoice=0;

mainMenu:
    cout<<"WELCOME TO HMS. PLEASE CHOOSE AN ACTION: "<<endl;
    cout<<"1. Manage Appointments"<<endl;
    cout<<"2. Manage Slots"<<endl;
    cout<<"3. Manage Doctors"<<endl;
    cout<<"4. Manage Patients"<<endl;
    cout<<"5. Manage Patients records"<<endl;
    cout<<"6. Manage Lab"<<endl;
    cout<<"7. Exit"<<endl;
    cin>>userChoice;
    int done = 0;

    if (userChoice==1)
    {
        system("CLS");
        caseChoice=printAppointmentMenu();
        if(caseChoice==1)
        {
            aptype.push_back(appointment(slotType, dateType, patientType, doctorType)); //since it is a constructor, i do push back to add appointments each time
            goto mainMenu;
        }
        if(caseChoice==2)
        {
            printAppointments(aptype, slotType, dateType, diagnosesType);
            system("PAUSE");
            system("CLS");
            goto mainMenu;
        }
        if(caseChoice==3)
        {
            modifyReschedule(aptype, slotType, dateType, diagnosesType);
            goto mainMenu;
        }
        if(caseChoice==4)
        {
            removeAppointment(aptype, slotType);
            goto mainMenu;
        }
        if(caseChoice==5)
        {
            searchAppByName(aptype, doctorType);
            goto mainMenu;
        }
        if(caseChoice==6)
        {
            searchAppByPatient(aptype, patientType, caseChoice);
            goto mainMenu;
        }
        if(caseChoice==7)
        {
            searchAppByPatient(aptype, patientType, caseChoice);
            goto mainMenu;
        }
        if(caseChoice==8)
        {
            system("CLS");
            goto mainMenu;
        }
    }
    if(userChoice==2)
    {
        system("CLS");
        caseChoice=printSlotMenu();
        if(caseChoice==1)
        {
            system("CLS");
            ShowAllTheAvailableSlots(slotType, dateType);
            system("PAUSE");
            system("CLS");
            goto mainMenu;
        }
        if(caseChoice==2)
        {   system("CLS");
            showAllTheUnavailableSlots(slotType, dateType);
            system("PAUSE");
            system("CLS");
            goto mainMenu;
        }
        if(caseChoice==3)
        {
            addANewSlot(slotType, dateType, doctorType);
            system("CLS");
            goto mainMenu;
        }
        if(caseChoice==4)
        {
            system("CLS");
            ShowSlotsBetweenTwoDates(slotType, dateType);
            goto mainMenu;
        }
        if(caseChoice==5)
        {
            system("CLS");
            showAllSlots(slotType, dateType);
            goto mainMenu;
        }
        if(caseChoice==6)
        {
            system("CLS");
            showSlotsForDoctor(slotType, dateType);
            goto mainMenu;
        }
        if(caseChoice==7)
           {
                system("CLS");
                showAvaliableSlotsForDocByName(slotType, dateType, doctorType);
                goto mainMenu;
           }
        if(caseChoice==8)
        {
            system("CLS");
            modifySlotInformation(slotType);
            goto mainMenu;

        }
        if(caseChoice==9)
        {
            system("CLS");
            removeSlot(slotType);
            goto mainMenu;
        }
        if(caseChoice==10)
        {
            system("CLS");
            goto mainMenu;
        }
    }
    if(userChoice==3)
    {
        system("CLS");
        caseChoice=printDoctorsMenu();
        if (caseChoice==1)
        {
            system("CLS");
            showAllDoctors(doctorType);
            goto mainMenu;
        }
        if(caseChoice==2)
        {
            system("CLS");
            updateDoctorsInfo(doctorType);
            goto mainMenu;
        }
        if(caseChoice==3)
        {
            system("CLS");
            deleteDoctor(doctorType, aptype);
            goto mainMenu;
        }
        if(caseChoice==4)
        {
            system("CLS");
            searchDoctorByName(doctorType);
            goto mainMenu;
        }
        if(caseChoice==5)
        {
            system("CLS");
            goto mainMenu;
        }
    }
    if(userChoice==4)
    {
        system("CLS");
        caseChoice=printPatientsMenu();
        if (caseChoice==1)
        {
            system("CLS");
            displayAllPatients(patientType, doctorType, diagnosesType, aptype);
            system("PAUSE");
            system("CLS");
            goto mainMenu;
        }
        else if (caseChoice==2)
        {
            system("CLS");
            addANewPatient(patientType);
            goto mainMenu;
        }
        else if (caseChoice==3)
        {
            system("CLS");
            deletePatient(patientType);
            goto mainMenu;
        }
        else if (caseChoice==4)
        {
            system("CLS");
            searchPatient(patientType, caseChoice);
            goto mainMenu;
        }
        else if (caseChoice==5)
        {
            system("CLS");
            searchPatient(patientType, caseChoice);
            goto mainMenu;
        }
        else if (caseChoice==6)
        {
            system("CLS");
            searchPatientByDoc(patientType, doctorType);
            goto mainMenu;
        }
        else if (caseChoice==7)
        {
            system("CLS");
            showPatientswithAppTimeRange(patientType, aptype, dateType, slotType);
            goto mainMenu;
        }
        else if (caseChoice==8)
        {
            system("CLS");
            updatePatientInfo(patientType);
            goto mainMenu;
        }
        else if (caseChoice==9)
        {
            goto mainMenu;
        }
    }
    if(userChoice==5)
    {
        system("CLS");
        caseChoice= printRecordMenu();
        if (caseChoice==1)
        {

            system("CLS");
            printRecords(recordType);
            system("PAUSE");
            goto mainMenu;
        }
        if(caseChoice==2)
        {
            system("CLS");
            addRecord(recordType, patientType);
            goto mainMenu;
        }
        if(caseChoice==3)
        {
            system("CLS");
            updateRecords(recordType);
            goto mainMenu;
        }
        if(caseChoice==4)
        {
            system("CLS");
            deleteRecord(recordType);
            goto mainMenu;
        }
        if(caseChoice==5)
        {
            system("CLS");
            searchRecords(recordType);
            goto mainMenu;
        }
        if(caseChoice==6)
        {
            system("CLS");
            goto mainMenu;
        }

    }
    if(userChoice==6)
    {
        system("CLS");
        caseChoice=printLabMenu();

        if(caseChoice==1)
        {
            system("CLS");
            addLabAppointment(slotType, dateType, patientType, doctorType, aptype);
            goto mainMenu;
        }
        if(caseChoice==2)
        {
            system("CLS");
            deleteLabApptment(aptype, slotType);
            goto mainMenu;
        }
        if(caseChoice==3)
        {
            system("CLS");
            printLabAppointments(aptype, dateType, diagnosesType, slotType);
            system("PAUSE");
            system("CLS");
            goto mainMenu;
        }
        if(caseChoice==4)
        {
            system("CLS");
            updateLabApptments(aptype, diagnosesType);
            goto mainMenu;
        }
        if(caseChoice==5)
        {
            system("CLS");
            goto mainMenu;
        }


    }
    if(userChoice==7)
        system("CLS");
        cout<<"\n\n\nTHANK YOU FOR USING HMS, HAVE A GREAT DAY!"<<endl;

        return 0;

}
