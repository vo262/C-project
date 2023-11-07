#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;
    int mileage;
    string plateNumber;
    int numSeats;

public:
    Vehicle(string make, string model, int year, int numSeats)
        : make(make), model(model), year(year), mileage(0), plateNumber("unknown"), numSeats(numSeats) {}

    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    int getMileage() const { return mileage; }
    string getPlateNumber() const { return plateNumber; }
    int getNumSeats() const { return numSeats; }

    void setPlateNumber(string plate) { plateNumber = plate; }
};

class Taxi : public Vehicle {
private:
    string taxiId;
    double fareTotal;
    int numOfFares;

public:
    Taxi(string make, string model, int year, int numSeats, string taxiId)
        : Vehicle(make, model, year, numSeats), taxiId(taxiId), fareTotal(0.0), numOfFares(0) {}

    string getId() const { return taxiId; }
    double getFareTotal() const { return fareTotal; }
    int getNumOfFares() const { return numOfFares; }

    void addFare(double fare) {
        fareTotal += fare;
        numOfFares++;
    }

    void resetFareInfo() {
        fareTotal = 0.0;
        numOfFares = 0;
    }
};

// Function to save taxi objects to a file
void saveTaxiToFile(const vector<Taxi>& taxis) {
    ofstream outFile("taxi.txt");
    if (outFile.is_open()) {
        for (const Taxi& taxi : taxis) {
            outFile << taxi.getMake() << "," << taxi.getModel() << "," << taxi.getYear() << ","
                    << taxi.getMileage() << "," << taxi.getPlateNumber() << "," << taxi.getNumSeats()
                    << "," << taxi.getId() << "," << taxi.getFareTotal() << "," << taxi.getNumOfFares() << "\n";
        }
        outFile.close();
    }
}

// Function to load taxi objects from a file
vector<Taxi> loadTaxiFromFile() {
    vector<Taxi> taxis;
    ifstream inFile("taxi.txt");
    if (inFile.is_open()) {
        string make, model, plateNumber, taxiId;
        int year, mileage, numSeats, numOfFares;
        double fareTotal;
        char comma;
        while (getline(inFile, make, ',') && getline(inFile, model, ',') && inFile >> year >> comma
               && inFile >> mileage >> comma && getline(inFile, plateNumber, ',') && inFile >> numSeats >> comma
               && getline(inFile, taxiId, ',') && inFile >> fareTotal >> comma && inFile >> numOfFares) {
            taxis.push_back(Taxi(make, model, year, numSeats, taxiId));
            taxis.back().setPlateNumber(plateNumber);
            taxis.back().addFare(fareTotal); // Updating fare info
            for (int i = 1; i < numOfFares; i++) {
                inFile >> fareTotal >> comma;
                taxis.back().addFare(fareTotal); // Adding additional fare info
            }
            inFile.ignore(); // Ignore the newline character
        }
        inFile.close();
    }
    return taxis;
}

int main() {
    vector<Taxi> taxis = loadTaxiFromFile();
    int choice;
    char comma;

    do {
        cout << "-----------MENU----------------" << endl;
        cout << "1. Add Taxi" << endl;
        cout << "2. Show Taxi List" << endl;
        cout << "3. Add Fare to Taxi" << endl;
        cout << "4. Reset Fare Info for a Taxi" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: " ;
        cin >> choice;

        switch (choice) {
        case 1: {
            string make, model, plateNumber, taxiId;
            int year, numSeats;

            cout << "Enter Taxi Make: ";
            cin >> make;
            cout << "Enter Taxi Model: ";
            cin >> model;
            cout << "Enter Taxi Year: ";
            cin >> year;
            cout << "Enter Taxi Number of Seats: ";
            cin >> numSeats;
            cout << "Enter Taxi ID: ";
            cin >> taxiId;

            taxis.push_back(Taxi(make, model, year, numSeats, taxiId));
            saveTaxiToFile(taxis);
            cout << "Taxi added successfully!" << endl;
            break;
        }

        case 2: {
            cout << "Taxi List:" << endl;
            for (const Taxi& taxi : taxis) {
                cout << taxi.getId() << " - " << taxi.getMake() << " " << taxi.getModel() << " ("
                     << taxi.getYear() << ") - " << taxi.getNumSeats() << " seats" << endl;
            }
            break;
        }

        case 3: {
            string taxiId;
            double fare;

            cout << "Enter Taxi ID: ";
            cin >> taxiId;
            cout << "Enter Fare Amount: ";
            cin >> fare;

            for (Taxi& taxi : taxis) {
                if (taxi.getId() == taxiId) {
                    taxi.addFare(fare);
                    saveTaxiToFile(taxis);
                    cout << "Fare added successfully!" << endl;
                    break;
                }
            }
            break;
        }

        case 4: {
            string taxiId;

            cout << "Enter Taxi ID: ";
            cin >> taxiId;

            for (Taxi& taxi : taxis) {
                if (taxi.getId() == taxiId) {
                    taxi.resetFareInfo();
                    saveTaxiToFile(taxis);
                    cout << "Fare info reset successfully!" << endl;
                    break;
                }
            }
            break;
        }

        case 5:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
