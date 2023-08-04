#include<iostream>
#include<string>
using namespace std;

class student;
class studentRecord;
class house;
class houseRecord;

class student {
    string name;
    int id;
public:
    student() {}
    student(string name, int id) {
        this->name = name;
        this->id = id;
    }
    int getID() {
        return id;
    }
    friend class studentRecord;
};

class studentRecord {
    pair<student, int>* record;
    int size;
public:
    studentRecord() {
        record = nullptr;
        size = 0;
    }
    ~studentRecord() {
        delete[] record;
    }

    bool exists(int id, int houseId) {
        bool exist = false;
        for (int i = 0; i < size; i++) {
            if (record[i].first.getID() == id && record[i].second == houseId) {
                exist = true;
                for (int j = i; j < size - 1; j++) {
                    record[j] = record[j + 1];
                }
                size--;
                break;
            }
        }
        return exist;
    }

    void addStudent(student stu, int houseId) {
        pair<student, int>* newRecord = new pair<student, int>[size + 1];
        for (int i = 0; i < size; i++) {
            newRecord[i] = record[i];
        }
        newRecord[size] = { stu, houseId };
        delete[] record;
        record = newRecord;
        size++;
    }

    void rent(studentRecord& s, houseRecord& h);
    void leave(studentRecord& s, houseRecord& h);
};

class house {
    int id;
    int water;
    int floor;
    int cost;
    bool vacant;
public:
    friend class houseRecord;
    house() {}
    house(int id, int water, int floor, int cost, bool vacant) {
        this->id = id;
        this->water = water;
        this->floor = floor;
        this->cost = cost;
        this->vacant = vacant;
    }
    int getID() {
        return id;
    }
    bool getVacant() {
        return vacant;
    }
    void setVacant(bool what) {
        vacant = what;
    }
    void show() {
        cout << id << "\t" << water << "\t" << floor << "\t\t" << cost << "\t" << ((vacant) ? "Yes" : "NO") << "\n";
    }
    friend void query(houseRecord);
};

class houseRecord {
    house* record;
    int size;
public:
    houseRecord() {
        record = nullptr;
        size = 0;
    }
    ~houseRecord() {
        delete[] record;
    }

    void showAll() {
        cout << "HouseId\tWater\tFloor\t\tCost\tVacancy\n";
        for (int i = 0; i < size; i++) {
            record[i].show();
        }
    }

    void addHouse() {
        int id, water, floor, cost;
        cout << " -----------------------------" << endl;
        cout << "|         Add New House       |" << endl;
        cout << " -----------------------------" << endl;
        cout << "Enter house id: "; cin >> id;
        cout << "Enter water condition[1(Good), 2(Salty)]: "; cin >> water;
        cout << "Enter floor[0(Ground),1(DownRoof),2(Others)]: "; cin >> floor;
        cout << "Enter cost: "; cin >> cost;
        if (id < 0 || !(water == 1 || water == 2) || !(floor == 0 || floor == 1 || floor == 2) || cost < 0) {
            cout << "Wrong input for adding house\n";
        }
        else {
            house h(id, water, floor, cost, true);
            house* newRecord = new house[size + 1];
            for (int i = 0; i < size; i++) {
                newRecord[i] = record[i];
            }
            newRecord[size] = h;
            delete[] record;
            record = newRecord;
            size++;
            cout << "\nHouse Registered Successfully!\n\n";
        }
    }

    void removeHouse() {
        int id, water, floor, cost;
        cout << " -----------------------------" << endl;
        cout << "|         Remove a House      |" << endl;
        cout << " -----------------------------" << endl;
        cout << "Enter house id: "; cin >> id;
        cout << "Enter water condition[1(Good), 2(Salty)]: "; cin >> water;
        cout << "Enter floor[0(Ground),1(DownRoof),2(Others)]: "; cin >> floor;
        cout << "Enter cost: "; cin >> cost;
        for (int i = 0; i < size; i++) {
            if (record[i].id == id && record[i].water == water && record[i].floor == floor && record[i].cost == cost) {
                for (int j = i; j < size - 1; j++) {
                    record[j] = record[j + 1];
                }
                size--;
                cout << "\nHouse successfully removed!\n\n";
                return;
            }
        }
        cout << "\nThis house doesn't exist in the record\n\n";
    }

    void setVacant(int id, bool what) {
        for (int i = 0; i < size; i++) {
            if (record[i].getID() == id) {
                record[i].setVacant(what);
                return;
            }
        }
    }

    bool isVacant(int id) {
        for (int i = 0; i < size; i++) {
            if (record[i].getID() == id && record[i].getVacant()) {
                return true;
            }
        }
        return false;
    }

    friend void query(houseRecord);

    void rent(studentRecord& s, houseRecord& h);
    void leave(studentRecord& s, houseRecord& h);
};

void rent(studentRecord& s, houseRecord& h) {
    int id, houseId; string name;
    cout << " -----------------------------" << endl;
    cout << "|         Rent a house        |" << endl;
    cout << " -----------------------------" << endl;
    cout << "Enter student name: "; cin.ignore(); getline(cin, name);
    cout << "Enter student id: "; cin >> id;
    cout << "Enter house id: "; cin >> houseId;
    if (h.isVacant(houseId)) {
        h.setVacant(houseId, false);
        student x(name, id);
        s.addStudent(x, houseId);
        cout << "\nHouse rented successfully!\n\n";
    }
    else {
        cout << "\nThe house is not vacant\n\n";
    }
}

void leave(studentRecord& s, houseRecord& h) {
    int id, houseId;
    cout << " -----------------------------" << endl;
    cout << "|          Leave house        |" << endl;
    cout << " -----------------------------" << endl;
    cout << "Enter student id: "; cin >> id;
    cout << "Enter house id: "; cin >> houseId;
    if (s.exists(id, houseId)) {
        h.setVacant(houseId, true);
        cout << "Thank you\n";
    }
    else {
        cout << "The house is not rented\n";
    }
    cout << "\n";
}

void query(houseRecord h) {
    int water, floor, maxCost;
    cout << " -----------------------------" << endl;
    cout << "|         Search house        |" << endl;
    cout << " -----------------------------" << endl;
    cout << "Water condition: [1(Good), 2(Salty)] "; cin >> water;
    cout << "Floor: [0(Ground Floor), 1(DownRoof), Others] "; cin >> floor;
    cout << "Maximum cost: "; cin >> maxCost;
    bool found = false;
    cout << "\n---------------------------------------\n";
    cout << "HouseId\tWater\tFloor\t\tCost\tVacancy\n";
    for (int i = 0; i < h.size; i++) {
        if (h.record[i].water == water && h.record[i].floor == floor && h.record[i].cost <= maxCost) {
            if (h.record[i].vacant) {
                found = true;
                h.record[i].show();
            }
        }
    }
    if (!found)
        cout << "\nNo house found!\n";
    cout << "---------------------------------------\n";
    cout << "\n";
}

int main() {
    houseRecord h;
    studentRecord s;

    while (true) {
        cout << "********************************" << endl;
        cout << "*    Student Mess Management   *" << endl;
        cout << "********************************" << endl;
        cout << "| 1.Register new house\n| 2.Rent house\n| 3.Leave house\n| 4.Show All house\n| 5.Search House\n| 6.Remove House\n| 0.Exit\n\nYour choice: ";
        int i; cin >> i;
        if (i == 1) {
            h.addHouse();
        }
        else if (i == 2) {
            rent(s, h);
        }
        else if (i == 3) {
            leave(s, h);
        }
        else if (i == 4) {
            h.showAll();
        }
        else if (i == 5) {
            query(h);
        }
        else if (i == 6) {
            h.removeHouse();
        }
        else if (i == 0) {
            cout << "Thanks for using our service\n";
            break;
        }
        else {
            cout << "Error! Invalid Input\n";
        }
    }
}
