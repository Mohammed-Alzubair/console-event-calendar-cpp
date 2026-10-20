//Event.h
#ifndef EVENT_H
#define EVENT_H

#include "Date.h"
#include <string>

// Class to represent an event with a date and description.
class Event {
public:
    Event(const Date& d, const std::string& desc); // Constructor.

    Date GetDate() const; // Get event date.
    std::string GetDescription() const; // Get event description.
    std::string ToString() const; // Convert to string.

private:
    Date date; // Event date.
    std::string description; // Event description.
};

#endif // EVENT_H

