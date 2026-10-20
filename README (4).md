# Console Calendar in C++

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![OOP](https://img.shields.io/badge/Object_Oriented-1F6FEB?style=for-the-badge)
![File I/O](https://img.shields.io/badge/File_I%2FO-2EA44F?style=for-the-badge)

A console calendar application written in C++. It shows a monthly calendar, lets you move between months, and manages events that can be saved to and loaded from a text file.

## Features

- **Monthly view** with the weekdays correctly aligned for any month and year
- **Navigation:** next month, previous month, or jump to any year and month
- **Event management:** add, list (with IDs), and delete events
- **Event markers:** days with events are marked with `*`, and the descriptions are printed under their week
- **Save and load:** events are stored in a plain text file and can be loaded back later
- **Input validation:** invalid dates are rejected, including leap-year handling
- **Cross-platform:** the screen is cleared with the right command on Windows and Unix

## Design

The program is split into three classes, using composition:

- **`Date`:** validation, leap years, days in a month, the weekday of any date (Zeller's congruence), and formatting as `YYYY-MM-DD`
- **`Event`:** a date together with a description
- **`Calendar`:** owns the current `Date` and a `std::vector<Event>`, draws the calendar, and runs the menu loop

## Example Session

Jumping to October 2026, adding an event on the 20th, and listing events:

```
      October     2026
****************************
SU  MO  TU  WE  TH  FR  SA
                01  02  03
04  05  06  07  08  09  10
11  12  13  14  15  16  17
18  19  20*    21  22  23  24
25  26  27  28  29  30  31

List of all events:
------------------
ID: 1 | 2026-10-20: Submit course project
------------------
Total events: 1
```

## Controls

- **N:** next month
- **P:** previous month
- **C:** choose a month
- **A:** add an event
- **L:** list events
- **D:** delete an event
- **S:** save events to a file
- **R:** read events from a file
- **Q:** quit

## Build and Run

```bash
g++ -std=c++11 -o calendar main.cpp Calendar.cpp Date.cpp Event.cpp
./calendar
```

On Windows the executable is `calendar.exe`. The project builds with g++ without warnings.

## Event File Format

One event per line: year, month, day, then the description.

```
2026 10 1 National Day
```

`sample_events.txt` is included. Start the program, press **R**, and enter `sample_events.txt` to load it.

## Repository Structure

```
.
├── main.cpp
├── Calendar.h / Calendar.cpp
├── Date.h / Date.cpp
├── Event.h / Event.cpp
├── sample_events.txt
└── README.md
```

## Skills Demonstrated

C++ · Object-oriented design (encapsulation and composition) · STL (`vector`, `string`) · File I/O · Input validation · Date algorithms

## Author

**Mohammed Al-Zubair**
[github.com/Mohammed-Alzubair](https://github.com/Mohammed-Alzubair)
