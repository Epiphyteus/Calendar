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
calendar::calendar(){
    head = nullptr;
}

//recursive remove all items
void calendar::remove_all(node *&head){
    if(!head) return;
    else if(!head -> link){
        delete head;
        return;
    }
    node *temp{head -> link};
    delete head;
    head = temp;
    remove_all(head);
}
    

//destructor - automaticalendarly deallocates nodes in the lll
calendar::~calendar(){
    remove_all(head);
}

/*getter - reads in events from the user until they want to stop
essentially the "build" function for the lll
*/
void calendar::get_events(){
    char again{'\0'};
    do{

        node *temp{new node};
        temp -> data.read();
        temp -> link = nullptr;
        if(!head){
            head = temp;
        }
        else if(!head -> link){
            head -> link = temp;
        }
        else{
            node *current{head};
            while(current -> link)
                current = current -> link;
            current -> link = temp;
        } 
        cout << "Again?\n>";
        cin >> again;
        cin.ignore(100, '\n');
    }while('Y' == toupper(again));

        
}

//main display definition, no args, calendarls recursive display
void calendar::display_events(){
    if(!head){
        cout << endl << "No events currently in your calendarendar." << endl;
        return;
    }
    display_events(head);
}

//display all - displays all the events stored in lll recursively
void calendar::display_events(node *head){
    if(head){
        head -> data.display();
        cout << endl;
        display_events(head -> link);
    }
}


//searches for a match from the items
void calendar::search(){
    char *find{nullptr}; //char * for the event name to find
    node *current{head -> link}; //to traverse
    node *prev{head}; //to drag

    cout << endl << "Enter an event title to search for.\n>";
    current -> data.get(find, SHORT); //get the event name, put in 'find'

    (rec_search(find, prev, current));
    delete [] find;
    find = nullptr;
}


//recursive search
void calendar::rec_search(char *find, node *&prev, node*&current){
    node *temp;
    
    if(head -> data.is_match(find)){
        cout << endl << "Match Found!" << endl;
        head -> data.display();
        temp = head -> link;
        if(remove(head))
            head = temp;
        return;
    }
    if(current -> data.is_match(find)){ //item we're on currently is a match
        cout << endl << "Match Found!" << endl;
        current -> data.display();
        temp = current -> link;
        if(remove(current))
            prev -> link = temp;
        return;
    }
    if(current)
        (rec_search(find, current, current -> link));
    return;
}

//removes the item at just one node found when searching. calendarled within search.
bool calendar::remove(node *&to_remove){
    char choice{'\0'};

    cout << endl << "Do you want to delete or change this item?\n"
                 << "(C)hange\n(D)elete\n(N)either\n>";
    cin >> choice;
    cin.ignore(100, '\n');
    while('D' != toupper(choice) && 'C' != toupper(choice) && 'N' != toupper(choice)){
        cout << endl << "Please enter (C)hange, (D)elete, or (N)either." << endl;
        cin >> choice;
        cin.ignore(100, '\n');
    }
    if('D' == toupper(choice)){
        delete to_remove;
        to_remove = nullptr;
        cout << endl << "Item deleted." << endl;
        return true;
    }
    if('C' == toupper(choice)){
        cout << endl;
        to_remove -> data.read();
    }
    else if('N' == toupper(choice))
        cout << endl << "Nothing was changed or deleted." << endl;
    return false;
}

//reads in events from external file to streamline testing
void calendar::load_events(){
    char temp[LONG];
    ifstream filein;
    filein.open("events.txt");
    if(filein){
        filein.get(temp, LONG, '|');
        filein.ignore(100, '|');
        while(!filein.eof()){
            node *add{new node};
            add -> link = nullptr;
            add -> data.name = new char[strlen(temp)+1];
            strcpy(add -> data.name, temp);
            filein.get(temp, LONG, '|');
            filein.ignore(100, '|');
            add -> data.desc = new char[strlen(temp)+1];
            strcpy(add -> data.desc, temp);
            filein.get(temp, LONG, '|');
            filein.ignore(100, '|');
            add -> data.start = new char[strlen(temp)+1];
            strcpy(add -> data.start, temp);
            filein.get(temp, LONG, '|');
            filein.ignore(100, '|');
            add -> data.end = new char[strlen(temp)+1];
            strcpy(add -> data.end, temp);
            filein >> add -> data.price;
            filein.ignore(100, '|');
            filein.get(temp, LONG, '|');
            filein.ignore(100, '|');
            add -> data.review = new char[strlen(temp)+1];
            strcpy(add -> data.review, temp);
            filein.get(temp, LONG, '\n');
            filein.ignore(100, '\n');
            add -> data.guest = new char[strlen(temp)+1];
            strcpy(add -> data.guest, temp);
            if(!head)
                head = add;
            else if(!head -> link)
                head -> link = add;
            else{
                node *current{head};
                while(current -> link)
                    current = current -> link;
                current -> link = add;
            }
            filein.get(temp, LONG, '|');
            filein.ignore(100, '|'); 
        }
    filein.close();
    }
}

//saves to external file
void calendar::save(){
    ofstream fileout;
}
