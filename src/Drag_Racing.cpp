#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class CarEngine {
private:
    int engineHP;
public:
    int get() {
        return engineHP;
    }
    void set(int engineHP) {
        this->engineHP = engineHP;
    }
    void boost(int engineHP) {
        this->engineHP += engineHP;
    }
};

class CarAirSystem {
private:
    int intakeHP;
    int exhaustHP;
public:
    int getIntake() {
        return intakeHP;
    }
    void setIntake(int intakeHP) {
        this->intakeHP = intakeHP;
    }
    void boostIntake(int intakeHP) {
        this->intakeHP += intakeHP;
    }
    int getExhaust() {
        return exhaustHP;
    }
    void setExhaust(int exhaustHP) {
        this->exhaustHP = exhaustHP;
    }
    void boostExhaust(int exhaustHP) {
        this->exhaustHP += exhaustHP;
    }
};

class User {
private:
    int points;
public:
    User() {
        points = 0;
    }
    int getPoints() {
        return points;
    }
    void addPoints(int points) {
        this->points += points;
    }
};


class Car : public User {
private:
    int numberOfWheels;
    int carHP;
    int chanceToWin;
    CarEngine carEngine;
    CarAirSystem carAir;
public:
    Car(int engine, int intake, int exhaust, int chanceToWin) {
        numberOfWheels = 4;
        this->chanceToWin = chanceToWin;
        carEngine.set(engine);
        carAir.setExhaust(exhaust);
        carAir.setIntake(intake);
        carHP = carEngine.get() + carAir.getExhaust() + carAir.getIntake();
    }
    virtual string getName() { return "ERROR getName"; }
    virtual void engineSound() {
        cout << "ENGINE SOUND NOT FOUND!!";
    }
    virtual void printStats() {
        cout << "Car HP = "<< carHP<< "\nProbability to win: "<< chanceToWin+10 <<endl;
    }
    int getCarHP() {
        return carHP;
    }
    bool randomLuck() {
        int luck = 10+chanceToWin;
        srand(time(0));
        if (rand() % luck == 5)
            return true;
        else
            return false;
    }
    void boostEngine(int price) {
        if (price <= this->getPoints()){
            carEngine.boost(5);
            carHP+=5;
            chanceToWin -= 1;
            this->addPoints(-price);
        }else
            cout << "Not enough points!!\nYou have: " << this->getPoints() << endl;
    }
    void boostIntake(int price) {
        if (price <= this->getPoints()) {
            carAir.boostIntake(5);
            carHP += 2;
            this->addPoints(-price);
        }else
            cout << "Not enough points!!\nYou have: " << this->getPoints() << endl;
    }
    void boostExhaust(int price) {
        if (price <= this->getPoints()) {
            carAir.boostExhaust(5);
            carHP += 2;
            this->addPoints(-price);
        }else
            cout << "Not enough points!!\nYou have: " << this->getPoints() << endl;
    }
};

class Fiat : public Car{
    string name = "Fiat Punto";
public:
    Fiat() : Car(80, 0, 0, 10) { }
    void engineSound() {
        cout << "\nmeoooooooow";
    }
    void printStats() {
        cout << "Auto: " << name << endl;
        Car::printStats();
    }
    string getName() { return name; }
};

class Volkswagen : public Car {
    string name = "Volkswagen Golf MK7";
public:
    Volkswagen() : Car(90, 0, 0, 5) { }
    void engineSound() {
        cout << "\nBRRRRRRRRRRM";
    }
    void printStats() {
        cout << "Auto: "<< name<<endl;
        Car::printStats();
    }
    string getName() { return name; }
};

class Toyota : public Car {
    string name = "Toyota Yaris GR";
public:
    Toyota() : Car(110, 0, 0, 0) { }
    void engineSound() {
        cout << "\nVROOOOOOOM";
    }
    void printStats() {
        cout << "Auto: " << name << endl;
        Car::printStats();
    }
    string getName() { return name; }
};

class ReadFile {
private:
    string fileName;
public:
    ReadFile(string name) {
        fileName = name;
    }
    void readFile() {
        char ch;
        ifstream file1;
        file1.open(fileName, ios::in);
        if (!file1)
        {
            cout << "Sorry the file you are looking for is not available" << endl;
            exit(-1);
        }
        while (!file1.eof())
        {
            file1 >> noskipws >> ch;
            cout << ch;
        }
        file1.close();
    }
};

int main()
{
    int temp=0;
    ReadFile meni("Rules.txt");
    Car* cars[2];
    cars[0] = new Toyota();
    cout << "\nWhat car do you want:\n1)Fiat Punto\n2)Golf MK7\nEnter number: ";
    cin >> temp;
    switch (temp) {
    case 1:
        cars[1] = new Fiat();
        break;
    case 2:
        cars[1] = new Volkswagen();
        break;
    }
    while (true) {
        meni.readFile();
        cin >> temp;
        
        switch (temp) {
        case -1:
            cout << "Shutdown!!";
            break;
        case 1:
            //Race
            system("cls");
            for(int i=0;i<6;i++)
                cars[1]->engineSound();
            if (cars[0]->getCarHP() < cars[1]->getCarHP() || cars[1]->randomLuck()) {
                cout << "\n\tWIN\nI guess this is your lucky day";
                cout << "\nPoints: " << cars[1]->getPoints() << " +10";
                cars[1]->addPoints(10);
                
            }
            else if(cars[0]->randomLuck()) {
                cout << "\n\tLOST\nBot with " << cars[0]->getName() << " has won!";
                cout << "\nPoints: " << cars[1]->getPoints() << " +2";
                cars[1]->addPoints(2);
            }
            else {
                cout << "\n\tLOST\nBot with " << cars[0]->getName() << " has won!";
                cout << "\nPoints: " << cars[1]->getPoints() << " +2";
                cars[1]->addPoints(2);
            }
            break;
        case 2:
            //Upgrade
            system("cls");
            cout << "\n1)Engine\n2)Intake\n3)Exhaust\n Your points: " << cars[1]->getPoints()<<"\nYou choose: ";
            cin >> temp;
            switch (temp) {
            case 1:
                cars[1]->boostEngine(50);
                break;
            case 2:
                cars[1]->boostIntake(10);
                break;
            case 3:
                cars[1]->boostExhaust(10);
                break;
            }
            break;
        case 3:
            //Print your and bots car
            system("cls");
            cout << "\nBOT:\n";
            cars[0]->printStats();
            cout << "\nUser:\n";
            cars[1]->printStats();
            break;
        default:
            cout << "ERROR MENU!!";
            break;
        }
        if (temp == -1)
            break;
    }
    return 0;
}