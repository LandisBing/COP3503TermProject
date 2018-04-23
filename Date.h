#ifndef GROUPPROJECT_DATE_H
#define GROUPPROJECT_DATE_H
#include <string>

using namespace std;
struct Date
{

    int month;
    int day;
    int year;

    Date(int month, int day, int year);

    Date(Date const &newDate);

    Date();

    string toString();

    int compareTo(Date other) const;

    void setDay(int newDay);

    void setMonth(int newMonth);

    void setYear(int newYear);
};


#endif //GROUPPROJECT_DATE_H