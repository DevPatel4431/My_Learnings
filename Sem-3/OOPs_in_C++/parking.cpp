#include "child.cpp"

string formateTime(time_t t) {
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &t);
    string s(buffer);
    s.pop_back();
    return s;
}

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

    bool removeVehicle(const string &plate) {
        auto it = plateToSpot.find(plate);

        if(it == plateToSpot.end()) {
            cout << "Vehicle with plate " << plate << " not found." << endl;
            return false;
        }

        int idx = it->second;
        unique_ptr<Vehicle> v = spots[idx].removeVehicle();

        if(!v) {
            cout << "Error removing vehicle" << endl;
            return false;
        }
        plateToSpot.erase(it);

        // Calculating Fees
        time_t exitTime = time(nullptr);
        double fees = v->claculateFee(exitTime);

        // printing details
        cout << "Vehicle " << v->getPlateNumber() << " (" << v->getType() << ") exited." << endl;
        cout << "Entry time " << formateTime(v->getEntryTime()) << endl;
        cout << "Exit time " << formateTime(exitTime) << endl;
        cout << fixed << setprecision(2);
        cout << "Parking Fee: ₹" << fees << endl;

        saveRecordToFile(*v, exitTime, fees);
        return true;
    }
};