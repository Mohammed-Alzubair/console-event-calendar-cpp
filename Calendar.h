//Calendar.h
#ifndef CALENDAR_H
#define CALENDAR_H

#include "Date.h"
#include "Event.h"
#include <vector>
#include <string>

// Class to manage calendar and events.
class Calendar {
public:
    Calendar(); // Constructor.

    void Run(); // Start calendar.

private:
    Date currentDate; // Current date.
    std::vector<Event> events; // List of events.

    void ClearScreen() const; // Clear screen.
    void Draw() const; // Draw calendar.
    void NextMonth(); // Go to next month.
    void PreviousMonth(); // Go to previous month.
    void JumpToMonth(); // Jump to specific month.
    void CreateEvent(); // Create event.
    void ListEvents() const; // List events.
    void DeleteEvent(); // Delete event.
    void SaveEvents() const; // Save events.
    void LoadEvents(); // Load events.

    void PrintHeader() const; // Print header.
    void PrintDays() const; // Print days.
    void PrintEventsForDate(const Date& date) const; // Print events for date.

    static std::string GetMonthName(int month); // Get month name.
    static std::string CenterString(const std::string& s, int width); // Center string.
};

#endif // CALENDAR_H
