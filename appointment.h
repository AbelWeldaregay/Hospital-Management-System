#ifndef APPOINTMENT_H_INCLUDED
#define APPOINTMENT_H_INCLUDED
#include "patient.h"
#include "doctors.h"
#include "date_time.h"
#include "slots.h"
#include "diagnoses.h"

using namespace std;


class appointment{
private:
    int appointmentID;
    string doctor_id;
    string patient_id;
    string slot_id;
    string appointmentReason;
    int diagnosesID;
    string prescribed_medication;
    bool labAppointment;
public:
    void setappointmentID();
    void setDoctorID();
    void setPatientID();
    void setSlotID();
    void setAppointmentReason();
    int getAppointmentID(){return appointmentID;}
    int getDiagnosisID(){return diagnosesID;}
    string getDoctorID(){return doctor_id;}
    string getPatientID(){return patient_id;}
    string getSlotID(){return slot_id;}
    string getAppointmentReason(){return appointmentReason;}
    friend void modifyAppointmentReason(vector <appointment> &appointmentType, int userChoice, int appointmentIndex);
    friend void rescheduleAppointment(vector <appointment> &appointmentType, vector <slot> &slotType, vector <date_time> &dateType, int userChoice, int appointmentIndex);
    appointment();
    static int appID;
    friend void removeAppointment(vector <appointment> &appointmentType, vector <slot> &slotType);
    appointment(vector <slot> &slotType, vector<date_time> &dateType, vector <patient> &patientType, vector<doctor> &docType);
    friend void updateDiagnoses( vector <appointment> &appointmentType, vector<diagnoses> &diagnosesType, int &userChoice, int &appointmentIndex);
    template <class generic>
    friend void initializeDiagnosesID(vector <generic> &genericType);
    friend void updatePrescribedMedication(vector <appointment> &appointmentType, int &appointmentIndex);
    string getPrescribedMedication(){return prescribed_medication;}
    bool getLabAppointment(){return labAppointment;}
    friend void addLabAppointment(vector <slot> &slotType, vector<date_time> &dateType, vector <patient> &patientType, vector<doctor> &docType, vector <appointment> &appointmentType);
    friend void updateLabApptments(vector <appointment> &appointmentType, vector <diagnoses> &diagnosesType);
    friend void deleteLabApptment(vector <appointment> &appointmentType, vector <slot> &slotType);
};
int printAppointmentMenu();
void matchDocPatientID(vector <patient> &patientType, vector <doctor> &doctorType, vector<slot> &slotType, vector<date_time> dateType, vector <appointment> &appointmentType);
void modifyReschedule(vector <appointment> &appointmentType, vector <slot> &slotType, vector <date_time> &dateType, vector <diagnoses> &diagnosesType);
void printAppointments(vector <appointment>  &appointmentType, vector <slot> &slotType, vector <date_time> &dateType, vector <diagnoses> &diagnosesType);
void rescheduleAppointment(vector <appointment> &appointmentType, vector <slot> &slotType, vector <date_time> &dateType, int userChoice, int appointmentIndex);
void updateDiagnoses( vector <appointment> &appointmentType, vector<diagnoses> &diagnosesType, int &userChoice, int &appointmentIndex);
void searchAppByName(vector <appointment> &appointmentType, vector <doctor> &doctorType);
void searchAppByPatient(vector <appointment> &appointmentType, vector <patient> &patientType, int &caseChoice);
void addLabAppointment(vector <slot> &slotType, vector<date_time> &dateType, vector <patient> &patientType, vector<doctor> &docType, vector <appointment> &appointmentType);
void printLabAppointments(vector <appointment> &appointmentType, vector <date_time> dateType, vector <diagnoses> &diagnosesType, vector <slot> &slotType);
void updateLabApptments(vector <appointment> &appointmentType, vector <diagnoses> &diagnosesType);
void deleteLabApptment(vector <appointment> &appointmentType, vector <slot> &slotType);
int printLabMenu();
#endif // APPOINTMENT_H_INCLUDED
