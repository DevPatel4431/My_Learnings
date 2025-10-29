#include "parking.cpp"

string getVehicleTypeFromUser () {
    cout << "Select vehicle type:" << endl;
    cout << "1. Car" << endl << "2. Bike"<< endl << "3. Truck" << endl << "Choice: ";
    int ch;
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(ch) {
        case 1: return "Car";
        case 2: return "Bike";
        case 3: return "Truck";
        default: return "";
    }
}

void showMenu() {
    cout << endl << "--- Smart Parking Lot Management System ---" << endl;
    cout << "1. Park a vehicle" << endl;
    cout << "2. Remove a vehicle" << endl;
    cout << "3. Show parking lot status" << endl;
    cout << "4. View parking history" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: " << endl;
}

int main() {
    const int lotsz = 10;
    parkingLot parkingLot(lotsz);

    while(true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(choice == 1) {
            string plate;
            cout << "Enter vehicle plate number: ";
            getline(cin, plate);
            string type = getVehicleTypeFromUser ();
            if(type.empty()) {
                cout << "Invalid vehicle type selected." << endl;
                continue;
            }
            time_t entryTime = time(nullptr);

            unique_ptr<Vehicle> vehicle;
            if(type == "Car") vehicle = make_unique<Car>(plate, entryTime);
            else if(type == "Bike") vehicle = make_unique<Bike>(plate, entryTime);
            else if(type == "Truck") vehicle = make_unique<Truck>(plate, entryTime);

            if(!parkingLot.parkVehicle(move(vehicle))) {
                cout << "Failed to park vehicle." << endl;
            }
        }
        else if(choice == 2) {
            string plate;
            cout << "Enter vehicle plate number to remove: ";
            getline(cin, plate);
            if(!parkingLot.removeVehicle(plate)) {
                cout << "Failed to remove vehicle." << endl;
            }
        }
        else if(choice == 3) {
            parkingLot.showStatus();
        }
        else if(choice == 4) {
            parkingLot.viewParkingHistory();
        }
        else if(choice == 5) {
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}