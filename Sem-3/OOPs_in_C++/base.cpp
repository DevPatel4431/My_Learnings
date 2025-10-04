#include<iostream>
#include<string>
#include <ctime>
using namespace std;

// members
// plate, entrytime

// member functions
// constructor
// get's
// virtual gettype, getrate
// calcfee

class Vehicle {
protected:
    string plateNumber;
    time_t entryTime;

public:
    Vehicle(const string &plate, time_t entry) {
        plateNumber = plate;
        entryTime = entry;
    }
    Vehicle(const string &plate) {
        plateNumber = plate;
        entryTime = time(nullptr);
    }

    // getters
    string getPlateNumber() const {
        return plateNumber;
    }
    time_t getEntryTime() const {
        return entryTime;
    }

    // pure virtual getters
    virtual string getType() const = 0;
    virtual double getRatePerHour() const = 0;
    
    double claculateFee(time_t exitTime) const {
        double hours = difftime(exitTime, entryTime) / 3600.00;
        if(hours < 1.0) hours = 1.0;

        return hours * getRatePerHour();
    }

    // operators for sorting data
    bool operator<(const Vehicle &other) const {
        return entryTime < other.entryTime;
    }
    bool operator>(const Vehicle &other) const {
        return entryTime > other.entryTime;
    }
    bool operator==(const Vehicle &other) const {
        return entryTime == other.entryTime;
    }
};