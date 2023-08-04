#include<iostream>
#include<vector>
#include<string>
using namespace std;
class student;
class studentRecord;
class house;
class houseRecord;
class student{
    string name;
    int id;
public:
    student(){}
    student(string name, int id){
        this->name=name;
        this->id=id;
    }
    int getID(){
        return id;
    }
    friend class studentRecord;
};
class studentRecord{
    vector<pair<student, int>>record;
public:
    studentRecord(){}
    bool exists(int id, int houseId){
        bool exist=false;
        auto it=record.begin();
        for(auto elem:record){
            if(elem.first.getID()==id &&  elem.second==houseId){
                exist=true;
                record.erase(it);
                break;
            }
            it++;
        }
        return exist;
    }
    void addStudent(student stu, int houseId){
        record.push_back({stu, houseId});
    }
    void rent(studentRecord &s, houseRecord &h);
    void leave(studentRecord &s, houseRecord &h);

};
class house{
    int id;
    int water;
    int floor;
    int cost;
    bool vacant;
public:
    friend class houseRecord;
    house(){}
    house(int id, int water, int floor, int cost, bool vacant){
        this->id=id;
        this->water=water;
        this->floor=floor;
        this->cost=cost;
        this->vacant=vacant;
    }
    int getID(){
        return id;
    }
    bool getVacant(){
        return vacant;
    }
    void setVacant(bool what){
        vacant=what;
    }
    void show(){

        cout<<id<<"\t"<<water<<"\t"<<floor<<"\t\t"<<cost<<"\t"<<((vacant)?"Yes":"NO")<<"\n";

    }
    friend void query(houseRecord);

};
class houseRecord{
    vector<house>record;
    public:
        houseRecord(){}
        void showAll(){
            cout<<"HouseId\tWater\tFloor\t\tCost\tVacancy\n";
            for(auto elem:record){

                elem.show();
            }
        }
        void addHouse(){
            int id, water, floor, cost;
            cout << " -----------------------------" << endl;
            cout << "|         Add New House       |" << endl;
            cout << " -----------------------------" << endl;
            cout<<"Enter house id: "; cin>>id;
            cout<<"Enter water condition[1(Good), 2(Salty)]: "; cin>>water;
            cout<<"Enter floor[0(Ground),1(DownRoof),2(Others)]: ";cin>>floor;
            cout<<"Enter cost: "; cin>>cost;
            if(id<0 || !(water==1 || water==2) || !(floor==0 || floor==1 || floor==2) || cost<0){
                cout<<"Wrong input for adding house\n";
            }
            else{
                house h(id, water, floor, cost, true);
                record.push_back(h);
                cout<<"\nHouse Registered Successfully!\n\n";
            }
        }
        void removeHouse(){
            int id, water, floor, cost;
            cout << " -----------------------------" << endl;
            cout << "|         Remove a House      |" << endl;
            cout << " -----------------------------" << endl;
            cout<<"Enter house id: "; cin>>id;
            cout<<"Enter water condition[1(Good), 2(Salty)]: "; cin>>water;
            cout<<"Enter floor[0(Ground),1(DownRoof),2(Others)]: ";cin>>floor;
            cout<<"Enter cost: "; cin>>cost;
            auto it=record.begin();
            for(auto elem:record){
                if(elem.id==id && elem.water==water && elem.floor==floor && elem.cost==cost){
                    record.erase(it);
                    cout<<"\nHouse successfully removed!\n\n";
                    return;
                }
                it++;
            }
            cout<<"\nThis house don't exist in the record\n\n";
        }
        void setVacant(int id, bool what){
            for(auto &elem: record){
                if(elem.getID()==id){
                    elem.setVacant(what);
                }
            }
        }
        bool isVacant(int id){
            for(auto elem: record){
                if(elem.getID()==id && elem.getVacant()){
                    return true;
                }
            }
            return false;
        }
        friend void query(houseRecord);
        void rent(studentRecord &s, houseRecord &h);
        void leave(studentRecord &s, houseRecord &h);
};
void rent(studentRecord &s, houseRecord &h){
    int id, houseId; string name;
    cout << " -----------------------------" << endl;
    cout << "|         Rent a house        |" << endl;
    cout << " -----------------------------" << endl;
    cout<<"Enter student name: "; cin.ignore(); cin>>name;
    cout<<"Enter student id: "; cin>>id;
    cout<<"Enter house id: "; cin>>houseId;
    if(h.isVacant(houseId)){
        h.setVacant(houseId, false);
        student x(name, id);
        s.addStudent(x, houseId);
        cout<<"\nHouse rented successfully!\n\n";
    }
    else{
        cout<<"\nThe house is not vacant\n\n";
    }
}
void leave(studentRecord &s, houseRecord &h){
    int id, houseId;
    cout << " -----------------------------" << endl;
    cout << "|          Leave house        |" << endl;
    cout << " -----------------------------" << endl;
    cout<<"Enter student id: "; cin>>id;
    cout<<"Enter house id: "; cin>>houseId;
    if(s.exists(id, houseId)){
        h.setVacant(houseId, true);
        cout<<"Thank you\n";
    }
    else{
        cout<<"The house is not rented\n";
    }
    cout<<"\n";
}
void query(houseRecord h){
    int water, floor, maxCost;
    cout << " -----------------------------" << endl;
    cout << "|         Search house        |" << endl;
    cout << " -----------------------------" << endl;
    cout<<"Water condition: [1(Good), 2(Salty)] "; cin>> water;
    cout<<"Floor: [0(Ground Floor), 1(DownRoof), Others] "; cin>>floor;
    cout<<"Maximum cost: ";cin>>maxCost;
    bool found=false;
    cout<<"\n---------------------------------------\n";
    cout<<"HouseId\tWater\tFloor\t\tCost\tVacancy\n";
    for(auto elem: h.record){

        if(elem.water==water && elem.floor==floor && elem.cost<=maxCost){
            if(elem.vacant){
                found=true;
                elem.show();
            }
        }
    }
    if(!found)
    cout<<"\nNo house found!\n";
    cout<<"---------------------------------------\n";
    cout<<"\n";
}
int main(){
    houseRecord h; studentRecord s;
    while(true){
        cout << "********************************" << endl;
        cout << "*    Student Mess Management   *" << endl;
        cout << "********************************" << endl;
        cout<<"| 1.Register new house\n| 2.Rent house\n| 3.Leave house\n| 4.Show All house\n| 5.Search House\n| 6.Remove House\n| 0.Exit\n\nYour choice: ";
        int i; cin>>i;
        if(i==1){
            h.addHouse();
        }
        else if(i==2){
            rent(s, h);
        }
        else if(i==3){
            leave(s,h);
        }
        else if(i==4){
            h.showAll();
        }
        else if(i==5){
            query(h);
        }
        else if(i==6){
            h.removeHouse();
        }
        else if(i==0){
            cout<<"Thanks for using our service\n";
            break;
        }
        else{
            cout<<"Error! Invalid Input\n";
        }
    }
}
