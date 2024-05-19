//Ian Leuty May 18 2024 CS162-001 ileuty@pdx.edu Program4

/*
This file contains the implementation of the functions in the list class
"calendar"


The data members are liked nodes defined as:
struct node{
    event data;
    node *link;
};
*/

#include "calendar.h"

using namespace std;

//constructor - initilizes head of the lll
cal::cal(){
    head = nullptr;
}

//destructor - automatically deallocates nodes in the lll
cal::~cal(){
    if(!head);
    else if(!head -> next)
        delete head;
    else{
        node *temp{nullptr};
        while(head){
            temp = head -> next;
            delete head;
            head = temp;
        }
    temp = nullptr;
    delete temp;
    }
}

/*getter - reads in events from the user until they want to stop
essentially the "build" function for the lll
*/
void cal::get_events(){
    char again{'\0'};
    do{

        node *temp{new node};
        temp -> data.read();
        temp -> next = nullptr;
        if(!head){
            head = temp;
        }
        else if(!head -> next){
            head -> next = temp;
        }
        else{
            node *current{head};
            while(current -> next)
                current = current -> next;
            current -> next = temp;
        } 
        cout << "Again?\n>";
        cin >> again;
        cin.ignore(100, '\n');
    }while('Y' == toupper(again));

        
}

//display all - displays all the events stored in lll
void cal::display_events(){
    node *current{head};
    while(current){
        current -> data.display();
        cout << endl;
        current = current -> next;
    } 
    current = nullptr;
    delete current;
}


//searches for a match from the items
bool cal::search(){
    bool match{false};
    char *find{nullptr};
    node *current{head};

    cout << endl << "Enter an event title to search for.\n>";
    current -> data.get(find, SHORT);
    if(!head)
        return match;
    while(current){
        if(current -> data.is_match(find)){
            cout << endl << "Match Found!" << endl;
            current -> data.display();
            cout << endl;
            match = true;
        }
        
        current = current -> next;
    } 
    find = nullptr;
    current = nullptr;
    delete current;
    delete find;
    return match; 
}


//removes the item at just one node found when searching. called within search.
void cal::remove(){
}
