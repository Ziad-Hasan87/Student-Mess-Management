#include<iostream>
#include<vector>
#include<string>
using namespace std;
//class houseRecord;
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

};
class house{
    int id;
    int water;
    int floor;
    int cost;
    bool vacant;
public:
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

        cout<<id<<"\t"<<water<<"\t"<<floor<<"\t"<<cost<<"\t"<<((vacant)?"Yes":"NO")<<"\n";
    }

};
class houseRecord{
    vector<house>record;
    public:
        houseRecord(){}
        void showAll(){
            cout<<"HouseId\tWater\tFloor\tCost\tVacancy\n";
            for(auto elem:record){

                elem.show();
            }
        }
        void addHouse(){
            int id, water, floor, cost;
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
            }
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
};
void rent(studentRecord &s, houseRecord &h){
    int id, houseId; string name;
    cout<<"Enter student name: "; cin.ignore(); cin>>name;
    cout<<"Enter student id: "; cin>>id;
    cout<<"Enter house id: "; cin>>houseId;
    if(h.isVacant(houseId)){
        h.setVacant(houseId, false);
        student x(name, id);
        s.addStudent(x, houseId);
    }
    else{
        cout<<"The house is not vacant\n";
    }
}
void leave(studentRecord &s, houseRecord &h){
    int id, houseId;
    cout<<"Enter student id: "; cin>>id;
    cout<<"Enter house id: "; cin>>houseId;
    if(s.exists(id, houseId)){
        h.setVacant(houseId, true);
    }
    else{
        cout<<"The house is not rented\n";
    }
}
int main(){
    houseRecord h; studentRecord s;
    while(true){
        cout<<"1.Register new house\n2.Rent house\n3.Leave house\n4.Show All house\n5.Exit\n\nYour choice: ";
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
            cout<<"Thanks for using our service\n";
            break;
        }
        else{
            cout<<"Error! Invalid Input\n";
        }
    }
}
