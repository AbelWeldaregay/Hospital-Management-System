#ifndef DATE_TIME_H_INCLUDED
#define DATE_TIME_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

class date_time{
private:

    int date_id;///a. id: A unique number that identifies the date
    int day_date;///b. day: of the month (1-31)
    int month_date;///c. month: of the year (1-12)
    int year_date;///d. year: 2 digits (eg. 17 for 2017)
    int hours_date;///e. hours: of the day (1-12)
    int minutes_date;///f. Minutes: (0-59)
    char am_pm;///g. AM_PM: 1 char for morning or afternoon (A for AM and P for PM)
    int numOfDates;
public:
    void setDateID(ifstream &inFile){inFile>>date_id;}
    void setDayDate(ifstream &inFile){inFile>>day_date;}
    void setMonthDate(ifstream &inFile){inFile>>month_date;}
    void setYearDate(ifstream &inFile){inFile>>year_date;}
    void setHoursDate(ifstream &inFile){inFile>>hours_date;}
    void setMinutesDate(ifstream &inFile){inFile>>minutes_date;}
    void setNumOfDates(ifstream &inFile){inFile>>numOfDates;}
    void setAmPm(ifstream &inFile){inFile>>am_pm;}
    int getDateID(){return date_id;}
    int getDayDate(){return day_date;}
    int getMonthDate(){return month_date;}
    int getYearDate(){return year_date;}
    int getHoursDate(){return hours_date;}
    int getMinutesDate(){return minutes_date;}
    int getNumOfDates(){return numOfDates;}
    char getAMPM(){return am_pm;}
    void setTheNewDateID(int dateID){date_id=dateID;}
    void setTheNewDayDate(int dayDate){day_date=dayDate;}
    void setTheNewMonthDate(int monthDate){month_date=monthDate;}
    void setNewYearDate(int yearDate){year_date=yearDate;}
    void setNewHoursDate(int hourDate){hours_date=hourDate;}
    void setNewMinutesDate(int minDate){minutes_date=minDate;}
    void setNewAmPm(char ampm){am_pm=ampm;}
    date_time();
    static int dateID;

};
void readDatesFile(ifstream &inFile, vector <date_time> &dateType);
void printDateTime(vector <date_time> dateType);
#endif // DATE_TIME_H_INCLUDED
