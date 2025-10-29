#include "base.cpp"

class Bike : public Vehicle {
public:
    Bike(string plate) : Vehicle(plate) {}
    Bike(string plate, time_t t) : Vehicle(plate, t) {}

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
    Car(string plate, time_t t) : Vehicle(plate, t) {}

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
    Truck(string plate, time_t t) : Vehicle(plate, t) {}

    string getType() const override {
        return "Truck";
    }

    int getRatePerHour() const override {
        return 100;
    }
};

// static function for unique pointer to store in vector
unique_ptr<Vehicle> Vehicle::makeVehicle(const string &plate, const string &type, time_t entry) {
    if(type == "Car") return make_unique<Car>(plate, entry);
    else if(type == "Bike") return make_unique<Bike>(plate, entry);
    else if(type == "Truck") return make_unique<Truck>(plate, entry);
    return nullptr;
}