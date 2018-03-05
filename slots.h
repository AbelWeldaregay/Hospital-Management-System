#ifndef SLOTS_H_INCLUDED
#define SLOTS_H_INCLUDED
#include "patient.h"
#include "doctors.h"
#include "date_time.h"
using namespace std;

class slot{
private:
    string slotID;
    int date_id;
    string doctor_id;
    int numOfSlots;
    bool slotStatus;
public:
    void setslotID(ifstream &inFile){inFile>>slotID;}
    void setDateID(ifstream &inFile){inFile>>date_id;}
    void setDocID(ifstream &inFile){inFile>>doctor_id;}
    void setNumberOfSlots(ifstream &inFile){inFile>>numOfSlots;}
    void setSlotStatus(ifstream &inFile){inFile>>slotStatus;}
    void setSlotStatusToFalse(){slotStatus=false;}
    void setSlotStatusToTrue(){slotStatus=true;}
    string getslotID(){return slotID;}
    int getDateID(){return date_id;}
    string getSlotDocID(){return doctor_id;}
    int getNumOfSlots(){return numOfSlots;}
    bool getSlotStatus(){return slotStatus;}
    friend void readSlotFile(ifstream &inFile, vector <slot> &slotType);
    friend void addANewSlot(vector <slot> &slotType, vector <date_time> &dateType, vector <doctor> &doctorType);
    friend void modifySlotInformation(vector <slot> &slotType);
    friend void removeSlot(vector <slot> &slotType);
    slot();
};

void readSlotFile(ifstream &inFile, vector <slot> &slotType);
int printSlotMenu();
void ShowAllTheAvailableSlots(vector <slot> &slotType, vector <date_time> &dateType);
void showAllTheUnavailableSlots(vector <slot>  &slotType, vector <date_time> &dateType);
void addANewSlot(vector <slot> &slotType, vector <date_time> &dateType, vector <doctor> &doctorType);
void showAllSlots(vector <slot> &slotType, vector <date_time> &dateType);
void ShowSlotsBetweenTwoDates(vector <slot> &slotType, vector <date_time> &dateType);
void showSlotsForDoctor(vector <slot> &slotType, vector <date_time> &dateType);
void modifySlotInformation(vector <slot> &slotType);
void removeSlot(vector <slot> &slotType);
void showAvaliableSlotsForDocByName(vector <slot> &slotType, vector <date_time> &dateType, vector <doctor> &doctorType);
#endif // SLOTS_H_INCLUDED
