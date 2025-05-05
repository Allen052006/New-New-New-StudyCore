#include <iostream>
#include "functionDeclarations.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <limits>
//-----------------File Pathing-----------------------
#include <filesystem>
// ----------------added for deadline manager------------------
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <algorithm>
//------------------added for detox reminder-------------------
#include <thread>
#include <atomic>
//-------------------------------------------------------------
using namespace std;
atomic<bool> detoxActive(false);
namespace fs = filesystem;

string currentUser;

void createUserDirectory(const string& username) {
    string path = "data/" + username;
    fs::create_directories(path); // Directory is created if it doesn't exist
}

void title() {
    cout << "                       _______ _______ __   __ ______  __   __ _______ _______ ______   _______ \n";
    cout << "                       |       |       |  | |  |      ||  | |  |       |       |    _ | |       |\n";
    cout << "                       |  _____|_     _|  | |  |  _    |  |_|  |       |   _   |   | || |    ___|\n";
    cout << "                       | |_____  |   | |  |_|  | | |   |       |      _|  | |  |   |_||_|   |___ \n";
    cout << "                       |_____  | |   | |       | |_|   |_     _|     | |  |_|  |    __  |    ___|\n";
    cout << "                        _____| | |   | |       |       | |   | |     |_|       |   |  | |   |___ \n";
    cout << "                       |_______| |___| |_______|______|  |___| |_______|_______|___|  |_|_______|\n\n";
}

void desc(){
    cout << "                          Welcome to studyCore! Where we create a comprehensive environment " << endl;
    cout << "                                  encompassing aspects of student life and study tools." << endl << endl;
}

void VirtualPet::mainMenu() {
    cout << "sCore Points: " << points;
}

bool isValidPassword(const string& password) {
    if (password.length() < 8) {
        cout << endl << "-> Password must be at least:\n   - 8 characters long\n   - Include at least one number\n   - Include a special character." << endl << endl;
        return false;
    }

    bool hasNumber = false, hasSpecialChar = false;
    string specialChars = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~";

    for (char c : password) {
        if (isdigit(c)) hasNumber = true;
        if (specialChars.find(c) != string::npos) hasSpecialChar = true;
    }

    if (!hasNumber) {
        cout << endl << "-> Password must include at least one number." << endl << endl;
        return false;
    }
    if (!hasSpecialChar) {
        cout << endl << "-> Password must include at least one special character. (Ex. &, *, %, $, #)" << endl << endl;
        return false;
    }

    return true;
}

void saveSession(const string& username) {
    ofstream sessionFile("session.txt");
    sessionFile << username;
    sessionFile.close();
}

bool isUserLoggedIn(string& username) {
    ifstream sessionFile("session.txt");
    if (sessionFile.is_open()) {
        getline(sessionFile, username);
        sessionFile.close();
        return !username.empty();
    }
    return false;
}


void logout() {
    ofstream sessionFile("session.txt", ios::trunc);
    sessionFile.close();
    system("cls");

    cout << endl << "                                            You have logged out successfully." << endl;
    string choice;
    while (true) {
        title();
        desc();
        cout << "     1. Sign Up\n     2. Log In\n\n     - Choice: ";
        getline(cin, choice);


        if (choice == "1") {
            system("cls");

            createAccount();
        } else if (choice == "2") {

            login();

        } else {
            system("cls");
            cout << endl << "-> Invalid choice. Please try again." << endl << endl;
        }
    }

}

void mainMenu() {
    while (true) {

        title();
        ScheduleManager manager("data/" + username + "/schedule.txt");
//------------------------------------------------------------------------------------------------------------------------------------------------
        // Deadline reminders
        if (manager.hasUpcomingSoonEvent()) {
            cout << "                      *REMINDER: You have at least one upcoming deadline within the next 24 hours!\n\n";
            cout << "                                 Make sure you're prepared and check your schedule!\n\n";
        }

        if (manager.hasPastEvent()) {
            cout << "                         *WARNING: One or more events in your schedule are past their deadline!\n\n";
            cout << "                                 Consider updating or removing them to stay organized.\n\n";
        }

        cout << endl << "This is the main menu." << endl;
        cout << "1. Logout\n2. Deadline Manager\n3. Detox Time Reminder\n4. Exit\n\nChoice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            logout();

        } else if (choice == "2") {
            system("cls");
            title();
            ScheduleManager manager;
            manager.showMenu();
        } else if (choice == "3") {
            system("cls");
            startDetoxTimer();
        } else if (choice == "4") {
            system("cls");
            title();
            cout << endl << "                                                    Goodbye for now!" << endl << endl;
            exit(0);
}
 else {
            system("cls");
            cout << endl <<"                                              Please enter a valid choice." << endl;
        }
    }

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
void createAccount() {
    cout << endl;
    title();
    desc();
    string username, password, verifyPassword;
    int recoveryPIN;

    cout << "                        ___                  _               ___                           _   " << endl;
    cout << "                       / __| _ _  ___  __ _ | |_  ___       /   \\ __  __  ___  _  _  _ _  | |_ " << endl;
    cout << "                      | (__ | '_|/ -_)/ _` ||  _|/ -_)      | - |/ _|/ _|/ _ \\| || || ' \\ |  _|" << endl;
    cout << "                       \\___||_|  \\___|\\__/_| \\__|\\___|      |_|_|\\__|\\__|\\___/ \\_._||_||_| \\__|" << endl;
    cout << endl << endl;

    while (username.empty()) {

    cout << "                    (A 4-figit PIN will be generated upon creating an account to change a password.)" << endl << endl;
        cout << "          - Username: ";
        getline(cin, username);
        if (username.empty()) {
            cout << endl << "Username cannot be empty. Please enter a valid username." << endl << endl;
        }
    }

    while (true) {
        cout << "          - Password: ";
        getline(cin, password);

        if (!isValidPassword(password)) {
            cout << "Please enter a stronger password." << endl << endl;
            continue;
        }

        cout << "          - Verify Password: ";
        getline(cin, verifyPassword);

        if (password == verifyPassword) {
            break;
        } else {
            cout << "Passwords do not match. Please try again." << endl << endl;
        }
    }

    srand(time(0));
    recoveryPIN = rand() % 9000 + 1000;

    // Save credentials to file
    createUserDirectory(username);
    ofstream file("data/" + username + "/credentials.txt");
    file << username << endl << password << endl << recoveryPIN;

    file.close();
    system("cls");
    cout << endl << "                                       Your account has been created successfully!" << endl;
    cout << "                                                 Your recovery PIN: " << recoveryPIN << endl;
    cout << "                              (Keep this PIN safe, you will need it for password recovery.)" << endl;

    saveSession(username);

    mainMenu();
}

bool verifyLogin(const string& username, const string& password) {
    string credFile = "data/" + username + "/credentials.txt";
    ifstream file(credFile);

    string storedUser, storedPass;

    if (file.is_open()) {
        getline(file, storedUser);
        getline(file, storedPass);
        file.close();
        return username == storedUser && password == storedPass;
    }
    return false;
}

void login() {
    string username, password;
    int choice, recoveryPIN, enteredPIN;

    system("cls");
    cout << endl;
    title();
    desc();
    cout << "                                               _                _      " << endl;
    cout << "                                              | |   ___  ___   | | _ _ " << endl;
    cout << "                                              | |_ / . \\/ . |  | || ' |" << endl;
    cout << "                                              |___|\\___/\\_. |  |_||_|_|" << endl;
    cout << "                                                        [___|          " << endl;

    while (username.empty()) {
        cout << "          - Username: ";
        getline(cin, username);
        if (username.empty()) {
            cout << endl << "Username cannot be empty. Please enter a valid username." << endl << endl;
        }
    }

    string credFile = "data/" + username + "/credentials.txt";
    ifstream file(credFile);

    string storedUsername, storedPassword, verifyPassword;

    if (file) {
        getline(file, storedUsername);
        getline(file, storedPassword);
        file >> recoveryPIN;
        file.close();
    }

    while (true) {
        cout << "          - Password: ";
        getline(cin, password);

        if (verifyLogin(username, password)) {
            saveSession(username);
            system("cls");
            cout << endl << "                                             Login successful. Welcome, " << username << "!" << endl;
            mainMenu();
            return;
        } else {
            cout << endl << "- > Invalid username or password." << endl;

            while (true) {
                cout << "     1. Re-enter password" << endl;
                cout << "     2. Forgot password (Reset)" << endl << endl;
                cout << "   Choose an option: ";
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                        cout << endl ;
                    break;

                } else if (choice == 2) {
                    cout << endl << "          - Enter your 4-digit recovery PIN: ";
                    cin >> enteredPIN;
                    cin.ignore();

                    if (enteredPIN == recoveryPIN) {
                        while (true) {
                            cout << "          - Recovery PIN Verified! Enter a new Password: ";
                            getline(cin, password);

                            if (!isValidPassword(password)) {
                                cout << "Please enter a stronger password." << endl << endl;
                                continue;
                            }

                            cout << "          - Verify Password: ";
                            getline(cin, verifyPassword);

                            if (password == verifyPassword) {
                                break;
                            } else {
                                cout << "Passwords do not match. Please try again." << endl << endl;
                            }
                        }


                        ofstream outFile("credentials.txt");
                        outFile << username << endl << password << endl << recoveryPIN;
                        outFile.close();
                        system("cls");
                        cout << "                                   Your password has been successfully changed!" << endl;
                        return;

                    } else {
                        system("cls");
                        cout << "                              Incorrect recovery PIN or username. Password reset failed." << endl;
                        string choice;
                        while (true) {
                            cout << endl;
                            title();
                            desc();
                            cout << "     1. Sign Up\n     2. Log In\n\n     - Choice: ";
                            getline(cin, choice);

                            if (choice == "1") {
                                system("cls");

                                createAccount();
                            } else if (choice == "2") {

                                login();

                            } else {
                                system("cls");
                                cout << endl << "-> Invalid choice. Please try again." << endl << endl;
                            }
                        }
                    }
                } else {
                    cout << "Invalid option. Please enter 1 or 2." << endl;
                }
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
// Convert Sched to string for storage
string Schedule::toString() const {
    ostringstream ss;
    ss << event_name << "|" << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day
       << "|" << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
    return ss.str();
}

// Parse Schedule from a string
Schedule Schedule::fromString(const string &line) {
    Schedule schedule;
    istringstream ss(line);
    getline(ss, schedule.event_name, '|');

    string date_time;
    getline(ss, date_time, '|');
    istringstream date_stream(date_time);
    char dash;
    date_stream >> schedule.year >> dash >> schedule.month >> dash >> schedule.day;

    string time_str;
    getline(ss, time_str);
    istringstream time_stream(time_str);
    char colon;
    time_stream >> schedule.hour >> colon >> schedule.minute;

    return schedule;
}

time_t Schedule::toTimeT() const {
    tm event_time = {};
    event_time.tm_year = year - 1900;
    event_time.tm_mon = month - 1;
    event_time.tm_mday = day;
    event_time.tm_hour = hour;
    event_time.tm_min = minute;
    event_time.tm_sec = 0;

    return mktime(&event_time);
}

string getMonthName(int month) {
    static const string months[] = {
        "January", "February", "March",     "April",   "May",      "June",
        "July",    "August",   "September", "October", "November", "December"
    };

    if (month >= 1 && month <= 12)
        return months[month - 1];
    else
        return "Invalid Month";
}

bool isValidDate(int year, int month, int day) {
    // Basic range checks
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // Leap year check for February
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    return day <= daysInMonth[month - 1];
}

bool isValidTime(int hour, int minute) {
    return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
}

// Check if event is in the past
bool Schedule::isPastDeadline() const {
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    tm local_time = *localtime(&current_time);

    tm event_time = {};
    event_time.tm_year = year - 1900;
    event_time.tm_mon = month - 1;
    event_time.tm_mday = day;
    event_time.tm_hour = hour;
    event_time.tm_min = minute;
    event_time.tm_sec = 0;

    time_t event_time_t = mktime(&event_time);
    return event_time_t < current_time;
}

ScheduleManager::ScheduleManager(const string& userFile) : filename(userFile) {
    loadEvents();
}


void ScheduleManager::loadEvents() {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        events.push_back(Schedule::fromString(line));
    }
    file.close();
}

void ScheduleManager::saveEvents() {
    ofstream file(filename);
    for (const auto &event : events) {
        file << event.toString() << endl;
    }
    file.close();
}

void ScheduleManager::addEvent() {
    Schedule schedule;
    system("cls");
    title();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter event name: ";
    getline(cin, schedule.event_name);
    cout << endl;

    while (true) {

        // Year
        while (true) {
            cout << "Enter Planned Year ('YYYY' Format): ";
            cin >> schedule.year;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number for the year.\n";
                cout << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        // Month
        while (true) {
            cout << "Enter Planned Month  ('MM' Format): ";
            cin >> schedule.month;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number for the month.\n";
                cout << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        // Day
        while (true) {
            cout << "Enter Planned Day    ('DD' Format): ";
            cin >> schedule.day;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number for the day.\n";
                cout << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        if (!isValidDate(schedule.year, schedule.month, schedule.day)) {
            system("cls");
            title();
            cout << "\nInvalid date entered. Please try again.\n\n";
            continue;
        }

        break;
    }

cout << endl;

    while (true) {
        // Hours
        while (true) {
            cout << "Enter Planned Hour   (0 to 23 Format): ";
            cin >> schedule.hour;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number for the hour.\n";
                cout << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        // Minutes
        while (true) {
            cout << "Enter Planned Minute (0 to 59 Format): ";
            cin >> schedule.minute;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number for the minute.\n";
                cout << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        if (!isValidTime(schedule.hour, schedule.minute)) {
            system("cls");
            title();
            cout << "\nInvalid time entered. Please try again.\n\n";
            continue;
        }

        break;
    }

    system("cls");
    events.push_back(schedule);
    saveEvents();
    title();
    cout << endl;
    cout << "                                                Event added successfully!" << endl;
    Sleep(1500);
}

void ScheduleManager::displayEvents() {
    system("cls");
    title();
    if (events.empty()) {
        cout << "No events found!" << endl;
        return;
    }

// Sort events by time (near local date first)
    sort(events.begin(), events.end(), [](const Schedule& a, const Schedule& b) {
    return a.toTimeT() < b.toTimeT();
    });

    cout << "Deadline Manager:\n\n";
    for (size_t i = 0; i < events.size(); ++i) {
        const auto &event = events[i];
        cout << i + 1 << ". Title: " << event.event_name << endl;
        cout << "    Date: " << getMonthName(event.month) << " " << event.day << ", " << event.year << endl;
        cout << "    Time: " << setw(2) << setfill('0') << event.hour << ":" << setw(2) << setfill('0') << event.minute << endl;
        cout << "  Status: " << (event.isPastDeadline() ? "Past deadline!" : "Upcoming") << endl;
        cout << "-------------------------------\n";
    }
}

void ScheduleManager::deleteEvent() {
    displayEvents();
    if (events.empty()) return;

    cout << "Enter the number of the event to delete (0 to cancel): ";
    int index;

    // Validation
    while (true) {
        cin >> index;
        if (cin.fail() || index < 0 || index > static_cast<int>(events.size())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 0 and " << events.size() << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    if (index == 0) {
        system("cls");
        title();
        Sleep(1500);
        return;
    }

    // Confirm deletion
    string confirm;
    cout << "Are you sure you want to delete \"" << events[index - 1].event_name << "\"? (y/n): ";
    getline(cin, confirm);

    if (confirm == "y" || confirm == "Y") {
        events.erase(events.begin() + index - 1);
        saveEvents();
        system("cls");
        title();
        cout << "\n                                              Event deleted successfully!" << endl;
        Sleep(1500);
    } else {
        system("cls");
        title();
        cout << "\n                                           Deletion canceled by user." << endl;
        Sleep(1500);
    }
}

void ScheduleManager::editEvent() {
    displayEvents();
    if (events.empty()) return;

    cout << "Enter the number of the event to edit (0 to cancel): ";
    int index;

    // Validate input for index
    while (true) {
        cin >> index;
        if (cin.fail() || index < 0 || index > static_cast<int>(events.size())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 0 and " << events.size() << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    if (index == 0) {
        system("cls");
        title();
        return;
    }

    Schedule& schedule = events[index - 1];
    system("cls");
    title();
    cout << "Editing event: " << schedule.event_name << "\n\n";

    cout << "Enter new event name: ";
    getline(cin, schedule.event_name);

    // Input and validate date
    while (true) {
        cout << "\nEnter Planned Year ('YYYY' Format): ";
        while (!(cin >> schedule.year)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid year: ";
        }

        cout << "Enter Planned Month ('MM' Format): ";
        while (!(cin >> schedule.month)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid month: ";
        }

        cout << "Enter Planned Day ('DD' Format): ";
        while (!(cin >> schedule.day)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid day: ";
        }

        if (!isValidDate(schedule.year, schedule.month, schedule.day)) {
            cout << "\nInvalid date. Please enter a correct date.\n";
            continue;
        }
        break;
    }

cout << endl;

    // Input and validate time
    while (true) {
        cout << "Enter Planned Hour (0 to 23): ";
        while (!(cin >> schedule.hour)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid hour: ";
        }

        cout << "Enter Planned Minute (0 to 59): ";
        while (!(cin >> schedule.minute)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a valid minute: ";
        }

        if (!isValidTime(schedule.hour, schedule.minute)) {
            cout << "\nInvalid time. Please enter valid time values.\n";
            continue;
        }
        break;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    saveEvents();
    system("cls");
    title();
    cout << "\n                                               Event updated successfully!" << endl;
    Sleep(1500);
}

bool ScheduleManager::hasUpcomingSoonEvent() const {
    auto now = std::chrono::system_clock::now();
    time_t current_time = std::chrono::system_clock::to_time_t(now);

    for (const auto &event : events) {
        time_t event_time = event.toTimeT();
        double seconds_diff = difftime(event_time, current_time);

        // Within the next 24 hours (and not in the past)
        if (seconds_diff > 0 && seconds_diff <= 86400) {
            return true;
        }
    }
    return false;
}

bool ScheduleManager::hasPastEvent() const {
    for (const auto &event : events) {
        if (event.isPastDeadline()) {
            return true;
        }
    }
    return false;
}

void ScheduleManager::showMenu() {
    string Schedchoice;
    do {
        system("cls");
        title();
        cout << "Deadline Manager\n\n";

        // Always show current events
        displayEvents();
        cout << endl;

        cout << "1. Add Event\n";
        cout << "2. Edit Event\n";
        cout << "3. Delete Event\n";
        cout << "4. Go Back\n\n";
        cout << "Choice: ";
        cin >> Schedchoice;

        if (Schedchoice == "1"){
            addEvent();
        } else if (Schedchoice == "2"){
            editEvent();
        } else if (Schedchoice == "3"){
            deleteEvent();
        } else if (Schedchoice == "4") {
            return;
        } else {
            cout << "Invalid Choice";
            Sleep(1000);  // Pause briefly for clarity
        }

    } while (Schedchoice != "1","2","3","4");
}

void detoxTimerThread(int minutes) {
    detoxActive = true;
    int seconds = minutes * 60;

    std::this_thread::sleep_for(std::chrono::seconds(seconds));

    detoxActive = false;

    // Show alert
    cout << "\n\nDetox Time Reminder Here! Time to take a break or review your progress.\n";
    cout << "Please exit the Program, do yourself a favor and rest your eyes.\n";
    cout << "See you again soon!\n";
    cout << "\nContinue from the Actions above:";

    // Beep
    Beep(1000, 300);
    Beep(1200, 300);
    Beep(1400, 300);

    Sleep(2000);
}

void startDetoxTimer() {
    system("cls");
    title();

    if (detoxActive) {
        cout << "\nDetox Time Reminder is already running!\n";
        Sleep(1500);
        system("cls");
        return;
    }

    int minutes;
    cout << "Enter Detox Time Reminder in minutes: ";
    while (!(cin >> minutes) || minutes <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid positive number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string confirm;
    cout << "\nThis Would Interrupt what you were doing when timer reached it's end.\n";
    cout << "You cannot change the timer once it has started.\n";
    cout << "\nStart a Detox Timer for " << minutes << " minutes? (y/n): ";
    getline(cin, confirm);
    if (confirm != "y" && confirm != "Y") {
        cout << "\nDetox Time Reminder cancelled.\n";
        Sleep(1500);
        system("cls");
        return;
    }

    thread(detoxTimerThread, minutes).detach();

    cout << "\nDetox Time Reminder started! You'll get an alert when it's done.\n";
    Sleep(2000);
    system("cls");
}
