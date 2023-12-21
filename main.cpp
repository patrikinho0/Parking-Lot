#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Observer
{
public:
    virtual void update(int numEmptySpots) = 0;
};

class Subject
{
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void unregisterObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class InfoDisplay : public Observer
{
private:
    static int infoID;
    int id;
public:
    InfoDisplay()
    {
        id = infoID;
        infoID++;
    }
    void update(int numEmptySpots) override
    {
        cout << "Info Display" << " " << getID() << " " << "Number of empty spots available: " << numEmptySpots << endl;
    }
    int getID()
    {
        return id;
    }
};
int InfoDisplay::infoID = 0;

class Car
{
private:
    string licensePlate;
public:
    Car(string modifiedLicensePlate)
    {
        licensePlate = modifiedLicensePlate;
    }

    string GetLicensePlate()
    {
        return licensePlate;
    }
};

class ParkingLot : public Subject
{
private:
    int numEmptySpots;
    vector<Observer*> observers;
public:
    ParkingLot() : numEmptySpots(0) {}
    void setNumEmptySpots(int numSpots)
    {
        numEmptySpots = numSpots;
        notifyObservers();
    }
    void registerObserver(Observer* observer) override
    {
        observers.push_back(observer);
    }
    void unregisterObserver(Observer* observer) override
    {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
        {
            observers.erase(it);
        }
    }
    void notifyObservers() override
    {
        for (Observer* observer : observers)
        {
            observer->update(numEmptySpots);
        }
    }
    bool Park(Car car)
    {
        if(numEmptySpots > 0)
        {
            setNumEmptySpots(numEmptySpots -= 1);
            cout << "Car parked CORRECTLY" << endl;
            cout << car.GetLicensePlate() << endl;
            return true;
        }
        else
        {
            cout << "Car parked INCORRECTLY" << endl;
            return false;
        }
    }
    bool Exit(Car car)
    {
        setNumEmptySpots(numEmptySpots += 1);
        cout << "Car exited CORRECTLY" << endl;
        cout << car.GetLicensePlate() << endl;
        return true;
    }
    int GetEmptySpots()
    {
        return numEmptySpots;
    }
};


int main()
{
    ParkingLot parkingLot;
    InfoDisplay infoDisplay1;
    InfoDisplay infoDisplay2;
    InfoDisplay infoDisplay3;


    Car car1("EZG 1000");
    Car car2("EZG 999");
    Car car3("EZG 998");
    Car car4("EZG 997");

    parkingLot.registerObserver(&infoDisplay1);
    parkingLot.registerObserver(&infoDisplay2);
    parkingLot.registerObserver(&infoDisplay3);

    parkingLot.setNumEmptySpots(4);

    parkingLot.Park(car1);
    cout << endl;

    parkingLot.Park(car2);
    cout << endl;

    parkingLot.Park(car3);
    cout << endl;

    parkingLot.Park(car4);
    parkingLot.Exit(car1);

    return 0;
}
