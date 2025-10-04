#include "base.cpp"

class Bike : public Vehicle {
public:
    Bike(string plate) : Vehicle(plate) {}

    string getType() const override {
        return "Bike";
    }

    int getRatePerHour() const override {
        return 20;
    }
};

class Car : public Vehicle {
public:
    Car(string plate) : Vehicle(plate) {}

    string getType() const override {
        return "Car";
    }

    int getRatePerHour() const override {
        return 50;
    }
};

class Truck : public Vehicle {
public:
    Truck(string plate) : Vehicle(plate) {}

    string getType() const override {
        return "Truck";
    }

    int getRatePerHour() const override {
        return 100;
    }
};