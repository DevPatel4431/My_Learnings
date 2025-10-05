#include "child.cpp"

class parkingSpot {
    int spotNumber;
    bool occupied;
    unique_ptr<Vehicle> vehicle;

public:
    parkingSpot(int num) : spotNumber(num), occupied(false), vehicle(nullptr) {}

    int getSpotNumber() const {
        return spotNumber;
    }
    bool isOccupied() const {
        return occupied;
    }
    Vehicle* getVehicle() const {
        return vehicle.get();
    }

    bool parkVehicle(unique_ptr<Vehicle> v) {
        if(occupied) return false;
        vehicle = move(v);
        occupied = true;
        return true;
    }

    unique_ptr<Vehicle> removeVehicle() {
        if(!occupied) return nullptr;
        occupied = false;
        return move(vehicle);
    }
};

class parkingLot {
    vector<parkingSpot> spots;
    unordered_map<string, int> plateToSpot;
    const int totalSpots;

public:
    parkingLot(int sz) : totalSpots(sz) {
        for(int i=1; i<=sz; i++) {
            spots.emplace_back(i);
        }
    }

    int findNearestSpot() {
        for(int i=1; i<=totalSpots; i++) {
            if(!spots[i].isOccupied()) return i;
        }
        return -1;
    }

    bool parkVehicle(unique_ptr<Vehicle> v) {
        if(plateToSpot.find(v->getPlateNumber()) != plateToSpot.end()) {
            cout << "Vehicle with plate " << v->getPlateNumber() << " is already parked." << endl;
            return false;
        }
        int idx = findNearestSpot();
        if(idx == -1) {
            cout << "Parking lot is currently full." << endl;
            return false;
        }

        if(spots[idx].parkVehicle(move(v))) {
            plateToSpot[spots[idx].getVehicle()->getPlateNumber()] = idx;
            cout << "Vehicle parked at spot " << spots[idx].getSpotNumber() << ".\n";
            return true;
        }
        return false;
    }
};