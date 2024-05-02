#include <iostream>
using namespace std;
#include <string>
#include<vector>

// Idea is Creating a family tree using a single linked list from head to bottom

class Person{
    public: //must specify otherwise default private
    string _name;
    vector<Person*> _children={}; //list of pointers not objects so if one object changes the change is reflected when accessing the pointer instead of ending up with 2 different objects in memory originating from 1 object change.

    Person(string name){_name=name;}

    void NullPtrCheck(){
        if (this == nullptr){
            cout<<"Error: Cannot perform action on Nullptr\n";
            return;
        }
    }

    #pragma region adders
    void addChild(Person* p){
        NullPtrCheck();
        // if (this == nullptr)
        //     cout<<"Error: Cannot add child to Nullptr\n";
        // else
            _children.push_back(p);
        }

    void addChild(string name){
        // if (this == nullptr)
        //     cout<<"Error: Cannot add child to Nullptr\n";
        // else{
        NullPtrCheck();
        Person* p = new Person(name);
        _children.push_back(p);
        // }
    }
    #pragma endregion

    #pragma region Printers
    void PrintChildren(){ //this could also be outside of Class in the form of PrintChildren(Person* p) since no private var access needed
        cout<<"Children of "<<this->returnName()<<": ";
        
        //print first child, seperated from loop just for the sake of output format not ending with a ","
        if (_children.size()>=1)
            cout<<_children[0]->returnName();

        for (int i = 1; i < _children.size(); i++)
        {
            cout<<", ";
            cout<<_children[i]->returnName();
        }
        cout<<"\n";
    }
    #pragma endregion

    #pragma region getters
    string returnName(){ //NOTE: SINCE CAN BE nullptr, CANNOT JUST PRINT this->name
        if (this != nullptr) {
            return this->_name;
        } else {
            return "NAN";
        }
    }

    vector<Person*> returnChildren(){ //NOTE: SINCE CAN BE nullptr, CANNOT JUST USE this->_children
        if (this != nullptr) {
            return this->_children;
        } else {
            return {};
        }
    }

    Person* getChild(string name){ //BFS same as isChild, just return object instead of bool
        for (Person* p : this->returnChildren()){
            if (p->returnName() == name)
                return p;
        }
        return nullptr;
    }

    // Person* getNthChild(string name){ //BFS or DFS to see if a person if part of the parent's lineage
    //     while (this->returnChildren() != {}){

    //     }
    //     return nullptr;
    // }

    // Person* getParent(Person* head){ //get Parent of specific entity. Need to start from head since it's single linked list
    //     if (this == head) //cannot be parent if you are yourself the root. If you're not the root then you must be someone's child
    //         return nullptr;

    //     Person* p = head;
    //     while (p->returnChildren()!={})
    //     {
    //         if(p->isChild(this->returnName())) //if i am the child of the current entity, then this entity is my parent
    //             return p;
    //     }
    // }
    #pragma endregion

    #pragma region checkers
    bool isChild(string name){ //O(n). BFS :) same as getChild, just return bool instead of object
        for (Person* p : this->returnChildren()){
            if (p->returnName() == name)
                return true;
        }
        return false;
    }

    bool isGrandChild(string name){//use isChild. DFS, O(n^2)
        for (Person* p : this->returnChildren()){ //for every child of this entity
            if (p->isChild(name)) //check if input is a child of the child iterated
                return true;
        }
        return false;
    }

    // bool isNthChild(string name, int n){ //DFS recursion of isChild
    //     return false;
    // } 
    #pragma endregion
};

#pragma region global functions
//no need for it to be in Class (part of object) since no private var access needed. If in Class, it would be in the same format as PrintChildren
void PrintTree(Person* head){ //BFS, should use PrintChildren
    cout<<head->returnName()<<": ";
    // Person *p = head;
    // While p.children is not empty{
    //     cout<<p->name<<", ";
    // }
    cout<<"\n";
}

Person* getPerson(Person* head, string name){ //BFS or DFS to see if a person is part of tree
        if (head->returnName() ==name)
            return head;

        // while (this->returnChildren() != {}){

        // }
        return nullptr;
    }

bool Exists(Person *head, string name){
    if (getPerson(head, name) ==nullptr)
        return false;
    return true;
}
#pragma endregion

int main(){
    //creating family tree ahmad->ali->edy
    cout<<"Tree design: ahmad->ali->edy\n";

    Person* ahmad = new Person("ahmad"); //creating pointers coz dealing with pointers is always better than passing objects to functions
    ahmad->addChild("Ali"); //creating child object using name string only
    Person* ali= ahmad->getChild("Ali"); //testing getting object by name of parent's child
    cout<<"Getting Ali as ahmad's child: "<<ali->returnName()<<'\n'; //expecting Ali
    ali= getPerson(ahmad, "Ali"); //testing getting object in tree
    cout<<"Getting Ali as a Person in the tree: "<<ali->returnName()<<'\n'; //expecting Ali


    Person* edy = new Person ("edy");
    ali->addChild(edy); //testing adding child as object (not string like above)

    cout<<"Ali is Ahmad's chid?: "<<ahmad->isChild("Ali")<<"\n"; //expect true
    cout<<"Zizo is Ahmad's chid?: "<<ahmad->isChild("Zizo")<<'\n'; //expect false
    cout<<"edy is Ahmad's grandchid?: "<<ahmad->isGrandChild("edy")<<'\n'; //expect true

    // cout<<"edy's parent is: "<<edy->getParent(ahmad)->returnName()<<"\n"; //Expect "ali"
    cout<<"Zizo exists in the tree?: "<<Exists(ahmad, "Zizo")<<'\n'; //expect false
    cout<<"edy exists in the tree?: "<<Exists(ahmad, "edy")<<'\n'; //expect true
    
    ahmad->PrintChildren();
    PrintTree(ahmad);
    return 0;
}