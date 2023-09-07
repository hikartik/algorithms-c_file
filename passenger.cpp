QUESTION 5 
CODE :

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Passenger {
public:
    Passenger(const string& name, int age) : name(name), age(age) {}

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

private:
    string name;
    int age;
};

class Train {
public:
    Train(int trainNumber, const string& name, const string& source, const string& destination)
        : trainNumber(trainNumber), name(name), source(source), destination(destination), seats(50, false) {}

    int getTrainNumber() const {
        return trainNumber;
    }

    string getName() const {
        return name;
    }

    string getSource() const {
        return source;
    }

    string getDestination() const {
        return destination;
    }

    bool bookSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > 50) {
            cout << "Invalid seat number." << endl;
            return false;
        }

        if (seats[seatNumber - 1]) {
            cout << "Seat " << seatNumber << " is already booked." << endl;
            return false;
        }

        seats[seatNumber - 1] = true;
        cout << "Seat " << seatNumber << " booked successfully." << endl;
        return true;
    }

private:
    int trainNumber;
    string name;
    string source;
    string destination;
    vector<bool> seats;
};

class ReservationSystem {
public:
    void addTrain(const Train& train) {
        trains.push_back(train);
    }

    void displayTrains() const {
        cout << "Available Trains:" << endl;
        for (const Train& train : trains) {
            cout << "Train " << train.getTrainNumber() << ": " << train.getName() << " (" << train.getSource() << " to " << train.getDestination() << ")" << endl;
        }
    }

    void bookTicket(int trainNumber, int seatNumber, const Passenger& passenger) {
        for (Train& train : trains) {
            if (train.getTrainNumber() == trainNumber) {
                if (train.bookSeat(seatNumber)) {
                    bookedTickets.push_back(make_pair(passenger, train));
                    cout << "Ticket booked for " << passenger.getName() << " on Train " << train.getName() << " (Seat " << seatNumber << ")." << endl;
                }
                return;
            }
        }
        cout << "Train with number " << trainNumber << " not found." << endl;
    }

private:
    vector<Train> trains;
    vector<pair<Passenger, Train>> bookedTickets;
};

int main() {
    ReservationSystem reservationSystem;
    vector<Passenger> passengers;
    int ch;
    cout << "Enter your choice (1=Add Train, 2=Add Passenger, 3=Book Ticket, 0=Quit): ";
    cin >> ch;
    
    while(ch)
    {
        if(ch == 1)
        {
            int TrainNumber;
            string TrainName;
            string TrainSource;
            string TrainDestination;
            cout <<  "Enter train Number: ";
            cin >> TrainNumber ;
            cout <<  "Enter train Name: ";
            cin >> TrainName ;
            cout <<  "Enter train Source: ";
            cin >> TrainSource ;
            cout <<  "Enter train Destination: ";
            cin >> TrainDestination ;
            Train train(TrainNumber,TrainName,TrainSource,TrainDestination);
            reservationSystem.addTrain(train);
        }
        else if(ch == 2)
        {
            string PassengerName;
            int PassengerAge;
            cout << "Enter Passenger Name: ";
            cin >> PassengerName;
            cout << "Enter Passenger Age: ";
            cin >> PassengerAge;
            Passenger passenger(PassengerName,PassengerAge);
            passengers.push_back(passenger);
        }
        else if(ch == 3)
        {
            int trainnumber;
            int seatnumber;
            int passengernumber;
            reservationSystem.displayTrains();
            cout << "Enter Train Number: ";
            cin >> trainnumber;
            cout << "Enter Seat Number: ";
            cin >> seatnumber;
            cout << "Enter Passenger Number: ";
            cin >> passengernumber;
            reservationSystem.bookTicket(trainnumber, seatnumber, passengers[passengernumber]);
        }
        else
            cout << "Invalid Choice" << endl;
        cout << "Enter your choice again (1=Add Train, 2=Add Passenger, 3=Book Ticket, 0=Quit): ";
        cin >> ch;
    }

    return 0;
}
