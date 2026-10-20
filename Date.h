//Date.h 
#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <string>

// Class for managing a date.
class Date {
public:
    Date(); // Default constructor (sets current date).
    Date(int y, int m, int d); // Constructor with date.

    int GetYear() const; // Get year.
    int GetMonth() const; // Get month.
    int GetDay() const; // Get day.

    void SetDate(int y, int m, int d); // Set date.
    bool IsValid() const; // Check if valid.
    bool IsLeapYear() const; // Check leap year.
    int DaysInMonth() const; // Get days in month.
    int DayOfWeek() const; // Get day of week.

    std::string ToString() const; // Return date as string.

private:
    int year, month, day; // Date attributes.
};

#endif // DATE_H
