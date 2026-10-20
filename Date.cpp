//Date.cpp
#include "Date.h"
#include <iostream>
#include <stdexcept>

// Constructor that initializes the date to the current system date.
Date::Date() {
    time_t t = time(0); // Get the current time.
    struct tm* now = localtime(&t); // Convert to local time.
    year = now->tm_year + 1900; // Adjust year (tm_year is years since 1900).
    month = now->tm_mon + 1; // Adjust month (tm_mon is zero-based).
    day = now->tm_mday; // Get the current day of the month.
}

// Constructor that initializes the date with specific values.
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

// Get the year.
int Date::GetYear() const { return year; }

// Get the month.
int Date::GetMonth() const { return month; }

// Get the day.
int Date::GetDay() const { return day; }

// Set the date with new values.
void Date::SetDate(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
}

// Validate if the date is correct.
bool Date::IsValid() const {
    if (year < 1 || month < 1 || month > 12 || day < 1)
        return false; // Invalid if out of bounds.
    return day <= DaysInMonth(); // Ensure day is within the correct range for the month.
}

// Check if the year is a leap year.
bool Date::IsLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); // Leap year logic.
}

// Return the number of days in the current month.
int Date::DaysInMonth() const {
    switch (month) { // Use a switch-case to handle different months.
        case 4: case 6: case 9: case 11:
            return 30; // April, June, September, November have 30 days.
        case 2:
            return IsLeapYear() ? 29 : 28; // February: 29 if leap year, else 28.
        default:
            return 31; // All other months have 31 days.
    }
}

// Calculate the day of the week using Zeller's formula.
int Date::DayOfWeek() const {
    int y = month < 3 ? year - 1 : year; // Adjust the year for Jan/Feb.
    int m = month < 3 ? month + 12 : month; // Adjust the month for Jan/Feb.
    int d = day; // Keep day unchanged.
    
    int c = y / 100; // Century part of the year.
    y = y % 100; // Year within the century.
    
    // Zeller's congruence to calculate the day of the week.
    int week = (d + 26 * (m + 1) / 10 + y + y / 4 + c / 4 - 2 * c) % 7;
    return (week + 6) % 7; 
}

// Convert the date to a string in "YYYY-MM-DD" format.
std::string Date::ToString() const {
    return std::to_string(year) + "-" + 
           (month < 10 ? "0" : "") + std::to_string(month) + "-" + 
           (day < 10 ? "0" : "") + std::to_string(day);
}

