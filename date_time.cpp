#include <iostream>
#include <vector>
#include <fstream>
#include "date_time.h"

using namespace std;
///default constructor for initializing variables inside the date_time adt
date_time::date_time()
{
    date_id=0;
    day_date=0;
    month_date=0;
    year_date=0;
    hours_date=0;
    minutes_date=0;
    am_pm=' ';
    numOfDates=0;
}
///function to read the dateTime file
void readDatesFile(ifstream &inFile, vector <date_time> &dateType)
{
    date_time dateAccessor; //creates a temporary accessor

    dateAccessor.setNumOfDates(inFile); //reads the number of dates

    int loopVariable=0;
    loopVariable= dateAccessor.getNumOfDates();

    for (int i=0; i<loopVariable; i++) //loops through the amount of dates
    {
        dateType.push_back(date_time()); //creates space inside the vector
        dateType[i].setDateID(inFile);
        dateType[i].setDayDate(inFile);
        dateType[i].setMonthDate(inFile);
        dateType[i].setYearDate(inFile);
        dateType[i].setHoursDate(inFile);
        dateType[i].setMinutesDate(inFile);
        dateType[i].setAmPm(inFile);
    }
}
///Function to print the date_time adt
void printDateTime(vector <date_time> dateType)
{

    for (int i=0; i<dateType.size(); i++) //loops through the date_time vector
    {
        cout<< dateType[i].getDateID()<<endl;
        cout<<dateType[i].getDayDate()<<endl;
        cout<<dateType[i].getMonthDate()<<endl;
        cout<<dateType[i].getYearDate()<<endl;
        cout<<dateType[i].getHoursDate()<<endl;
        cout<<dateType[i].getMinutesDate()<<endl;
        cout<<dateType[i].getAMPM()<<endl;
    }

}
