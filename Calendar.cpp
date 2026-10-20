//Calendar.cpp
#include "Calendar.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib> // For system() to clear the screen.
#include <limits>  // For numeric_limits to ignore input.

Calendar::Calendar() : currentDate() {} // Constructor initializes current date.

// Clears the screen based on OS (Windows/Unix).
void Calendar::ClearScreen() const {
    #ifdef _WIN32
        system("cls"); // Windows.
    #else
        system("clear"); // Unix-based.
    #endif
}

// Main loop for running the calendar program.
void Calendar::Run() {
    ClearScreen(); // Clear the screen initially.

    char choice;
    do {
        Draw(); // Draw the calendar UI.
        std::cout << "\nOptions: ";
		std::cout <<"\nEnter [N] (next month)"; 
		std::cout <<"\nEnter [P] (previous month)";
		std::cout <<"\nEnter [C] (choose month)";
		std::cout <<"\nEnter [A] (add event)";
		std::cout <<"\nEnter [L] (list events)";
		std::cout <<"\nEnter [D] (delete event)";
		std::cout <<"\nEnter [S] (save event)";
		std::cout <<"\nEnter [R] (read from the file)";
		std::cout <<"\nEnter [Q] (quit the program)";
        std::cout <<"\nEnter Your Choice: ";
        std::cin >> choice; // User input for next action.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer.

        ClearScreen(); // Clear screen after choice.

        // Process the user's choice.
        switch (toupper(choice)) {
            case 'N': NextMonth(); break; // Go to next month.
            case 'P': PreviousMonth(); break; // Go to previous month.
            case 'C': JumpToMonth(); break; // Jump to specific month.
            case 'A': CreateEvent(); break; // Create a new event.
            case 'L': ListEvents(); break; // List all events.
            case 'D': DeleteEvent(); break; // Delete an event.
            case 'S': SaveEvents(); break; // Save events to file.
            case 'R': LoadEvents(); break; // Load events from file.
            case 'Q': std::cout << "Goodbye!\n"; break; // Exit the program.
            default: std::cout << "Invalid choice. Try again.\n"; // Invalid input.
        }

        
    } while (toupper(choice) != 'Q'); // Keep running until quit.
}

// Draw the calendar UI.
void Calendar::Draw() const {
    PrintHeader(); // Print header with month and year.
    PrintDays();   // Print days of the current month.
}

// Print the calendar's header with month and year.
void Calendar::PrintHeader() const {
    std::string monthYear = GetMonthName(currentDate.GetMonth()) + "     " + std::to_string(currentDate.GetYear());
    std::cout << CenterString(monthYear, 28) << "\n"; // Center the month/year.
    std::cout << std::string(28,  '*') << "\n"; // Print separator line.
    std::cout << "SU  MO  TU  WE  TH  FR  SA\n"; // Days of the week.
}

// Print the days of the current month.
void Calendar::PrintDays() const {
    Date firstOfMonth(currentDate.GetYear(), currentDate.GetMonth(), 1); // Get the first day of the month.
    int startingDay = firstOfMonth.DayOfWeek(); // Get the weekday of the 1st.
    int daysInMonth = firstOfMonth.DaysInMonth(); // Get number of days in the month.
    
    for (int i = 0; i < startingDay; i++) { // Print empty spaces before the first day.
        std::cout << "    ";
    }
    
    for (int day = 1; day <= daysInMonth; day++) { // Print each day.
        Date currentDay(currentDate.GetYear(), currentDate.GetMonth(), day); // Create date for each day.
        std::cout << std::setw(2) << std::setfill('0')<<day; // Print the day.
        
        bool hasEvents = false; // Check if there are any events on that day.
        for (const auto& event : events) {
            if (event.GetDate().GetYear() == currentDay.GetYear() &&
                event.GetDate().GetMonth() == currentDay.GetMonth() &&
                event.GetDate().GetDay() == currentDay.GetDay()) {
                hasEvents = true; // If event exists for this date, mark it.
                break;
            }
        }
        
        std::cout << (hasEvents ? "*    " : "  "); // Print asterisk if events exist for this day.
        
        // New line after each week, or when the last day is reached.
        if ((day + startingDay) % 7 == 0 || day == daysInMonth) {
            std::cout << "\n";
            PrintEventsForDate(currentDay); // Print events for the day.
        }
    }
}

// Print events for a given date.
void Calendar::PrintEventsForDate(const Date& date) const {
    for (const auto& event : events) {
        if (event.GetDate().GetYear() == date.GetYear() &&
            event.GetDate().GetMonth() == date.GetMonth() &&
            event.GetDate().GetDay() == date.GetDay()) {
            std::cout << "   - " << event.GetDescription() << "\n"; // Print event description.
        }
    }
}

// Move to the next month.
void Calendar::NextMonth() {
    int year = currentDate.GetYear();
    int month = currentDate.GetMonth() + 1;
    
    if (month > 12) { // Wrap around to January if month exceeds 12.
        month = 1;
        year++;
    }
    
    currentDate.SetDate(year, month, 1); // Set new date.
    std::cout << "Switched to next month.\n";
}

// Move to the previous month.
void Calendar::PreviousMonth() {
    int year = currentDate.GetYear();
    int month = currentDate.GetMonth() - 1;
    
    if (month < 1) { // Wrap around to December if month is less than 1.
        month = 12;
        year--;
    }
    
    currentDate.SetDate(year, month, 1); // Set new date.
    std::cout << "Switched to previous month.\n";
}

// Jump to a specific month.
void Calendar::JumpToMonth() {
    int year, month;
    std::cout << "Enter year: ";
    std::cin >> year; // User inputs year.
    std::cout << "Enter month (1-12): ";
    std::cin >> month; // User inputs month.
    
    if (month < 1 || month > 12) { // Validate month.
        std::cout << "Invalid month. Using current month instead.\n";
        return;
    }
    
    currentDate.SetDate(year, month, 1); // Set the new date.
    std::cout << "Jumped to selected month.\n";
}

// Create a new event.
void Calendar::CreateEvent() {
    int year, month, day;
    std::string description;
    
    std::cout << "Enter year: ";
    std::cin >> year; // User inputs year.
    std::cout << "Enter month (1-12): ";
    std::cin >> month; // User inputs month.
    std::cout << "Enter day: ";
    std::cin >> day; // User inputs day.
    std::cin.ignore(); // Clear input buffer.
    
    Date eventDate(year, month, day); // Create event date.
    if (!eventDate.IsValid()) { // Validate event date.
        std::cout << "Invalid date. Event not created.\n";
        return;
    }
    
    std::cout << "Enter event description: ";
    std::getline(std::cin, description); // Get event description.
    
    events.emplace_back(eventDate, description); // Add event.
    std::cout << "Event added successfully.\n";
}

// List all events in the calendar.
void Calendar::ListEvents() const {
    if (events.empty()) {
        std::cout << "No events found.\n";
        return;
    }
    
    std::cout << "List of all events:\n";
    std::cout << "------------------\n";
    for (size_t i = 0; i < events.size(); i++) {
        std::cout << "ID: " << i + 1 << " | " << events[i].ToString() << "\n"; // Print events with ID.
    }
    std::cout << "------------------\n";
    std::cout << "Total events: " << events.size() << "\n"; // Display total events.
}

// Delete an event by ID.
void Calendar::DeleteEvent() {
    ListEvents(); // List all events.
    if (events.empty()) return; // No events to delete.
    
    int id;
    std::cout << "Enter event ID to delete: ";
    std::cin >> id; // User inputs event ID.
    
    if (id < 1 || id > static_cast<int>(events.size())) { // Validate ID.
        std::cout << "Invalid ID.\n";
        return;
    }
    
    events.erase(events.begin() + id - 1); // Remove event by ID.
    std::cout << "Event deleted successfully.\n";
}

// Save events to a file.
void Calendar::SaveEvents() const {
    if (events.empty()) {
        std::cout << "No events to save.\n";
        return;
    }
    
    std::string filename;
    std::cout << "Enter filename to save events: ";
    std::cin >> filename; // User inputs filename.
    
    std::ofstream outFile(filename); // Open file for writing.
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n"; // Error handling.
        return;
    }
    
    for (const auto& event : events) {
        Date d = event.GetDate();
        outFile << d.GetYear() << " " << d.GetMonth() << " " << d.GetDay() << " "
                << event.GetDescription() << "\n"; // Write event data to file.
    }
    
    outFile.close(); // Close the file.
    std::cout << events.size() << " events saved to '" << filename << "' successfully.\n";
}

// Load events from a file.
void Calendar::LoadEvents() {
    std::string filename;
    std::cout << "Enter filename to load events from: ";
    std::cin >> filename; // User inputs filename.
    
    std::ifstream inFile(filename); // Open file for reading.
    if (!inFile) {
        std::cerr << "Error opening file '" << filename << "' for reading.\n"; // Error handling.
        return;
    }
    
    std::vector<Event> loadedEvents; // Temp storage for loaded events.
    int year, month, day;
    std::string description;
    int count = 0;
    
    while (inFile >> year >> month >> day) {
        std::getline(inFile >> std::ws, description); // Read event description.
        Date eventDate(year, month, day); // Create date.
        if (eventDate.IsValid()) {
            loadedEvents.emplace_back(eventDate, description); // Add valid events.
            count++;
        }
    }
    
    inFile.close(); // Close the file.
    
    if (count > 0) {
        events = loadedEvents; // Update events with loaded ones.
        std::cout << count << " events loaded from '" << filename << "' successfully.\n";
    } else {
        std::cout << "No valid events found in '" << filename << "'.\n";
    }
}

// Get the name of a month.
std::string Calendar::GetMonthName(int month) {
    static const std::string months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return (month >= 1 && month <= 12) ? months[month - 1] : "Unknown"; // Return month name.
}

// Center a string in a specific width.
std::string Calendar::CenterString(const std::string& s, int width) {
    int padding = (width - static_cast<int>(s.length())) / 2; // Calculate padding.
    if (padding < 0) padding = 0; // Ensure no negative padding.
    return std::string(padding, ' ') + s; // Center the string.
}

