//Event.cpp
#include "Event.h"
#include <iostream>
// Initialize event with date and description.
Event::Event(const Date& d, const std::string& desc) 
    : date(d), description(desc) {}

// Return event date.
Date Event::GetDate() const { 
    return date; 
}

// Return event description.
std::string Event::GetDescription() const { 
    return description; 
}

// Return event as string.
std::string Event::ToString() const {
    return date.ToString() + ": " + description; 
}

