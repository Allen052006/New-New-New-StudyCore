#ifndef FUNCTIONDECLARATIONS_H_INCLUDED
#define FUNCTIONDECLARATIONS_H_INCLUDED
#include <fstream>
#include <string>
#include <vector>
//-------------------
#include <thread>
#include <atomic>


using namespace std;

class VirtualPet {
    public:
        int points;

    VirtualPet(int p) {
        points = p;
    }

    void mainMenu();
};
void title();
void desc();
bool isValidPassword(const string& password);
void saveSession(const string& username);
bool isUserLoggedIn(string& username);
void logout();
void mainMenu();
void createAccount();
bool verifyLogin(const string& username, const string& password);
void login();
;

//-------------------------added for deadline manager-----------------------------
struct Schedule {
    time_t toTimeT() const;
    int year, month, day, hour, minute;
    string event_name;

    string toString() const;
    static Schedule fromString(const string &line);
    bool isPastDeadline() const;
};

string getMonthName(int month);
bool isValidDate(int year, int month, int day);
bool isValidTime(int hour, int minute);

class ScheduleManager {
private:
    vector<Schedule> events;
    const string filename = "schedule.txt";

    void loadEvents();
    void saveEvents();

public:
    ScheduleManager();
    void addEvent();
    void displayEvents();
    void deleteEvent();
    void editEvent();
    void showMenu();

    bool hasPastEvent() const;
    bool hasUpcomingSoonEvent() const;
};

//--------------------------added for detox reminder------------------------------
void startDetoxTimer();
void detoxTimerThread(int minutes);

#endif // FUNCTIONDECLARATIONS_H_INCLUDED
