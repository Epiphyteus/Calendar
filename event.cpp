//Ian Leuty May 18 2024 CS162-001 ileuty@pdx.edu Program4
/*
This file contains the implementation of the functions in the single item 
class "event"
The data members are:
        char *name;
        char *desc;
        char *start;
        char *end;
        float price;
        char *review;
        char oneday;

*/

#include "event.h"

using namespace std;

//constructor - intializes dynamic memory.
event::event(){
    name = nullptr;
    desc = nullptr;
    start = nullptr;
    end = nullptr;
    price = 0.0;
    review = nullptr;
    oneday = '\0';
    guest = nullptr;
}

//destructor - removes dynamic memory.
event::~event(){
    delete [] name;
    delete [] desc;
    delete [] start;
    delete [] end;
    delete [] review;
    delete [] guest;
}

//gets and error checks for length any char* 
void event::get(char *&array, const int size){
    char temp[SHORT];

    cin.get(temp, size, '\n');
    while(cin.peek() != '\n'){
        cin.ignore(100, '\n');
        cout << "Please enter less than " 
             << size << " characters" 
             << endl;
        cin.get(temp, size, '\n');
    }
    cin.ignore(100, '\n');

    array = new char[strlen(temp)+1];
    strcpy(array, temp);
}

//reads in one event
void event::read(){
    cout << "Enter an event name.\n>";
    get(name, SHORT);
    cout << "Enter a brief description of the event.\n>";
    get(desc, LONG);
    cout << "Enter the start date of the event. (i.e. May 18, 2024)\n>";
    get(start, SHORT);
    cout << "Is the event a multiple day event? (y/n)\n>";
    if(yn(oneday)){
        cout << "Enter the end date of the event in the same format as the start.\n>";
        get(end, SHORT);
    }
    else{
        end = new char[strlen(start)];
        strcpy(end, start);
    }
    cout << "Enter the price of admission to the event. (i.e. 12.99)\n> $";
    cin >> price;
    cin.ignore(100, '\n');
    cout << "Enter a review of the event based on past attendance." << endl
         << "(500 characters or less)\n>";
    get(review, LONG);
    cout << "If there is a guest speaker enter their name, otherwise, enter 'NONE'" 
         << endl << "(i.e. 'Gottfried Wilhelm Leibniz' or 'NONE')\n>";
    get(guest, SHORT);
    cout << endl;
}

//displays one event
void event::display(){
    cout << "Event Name: " << name << endl
         << "Description: " << desc << endl
         << "Happening: " << start << " through " << end << endl
         << "Cost of Admission: " << price << endl
         << "Review: " << review << endl
         << "Guest Speaker: " << guest << endl;

}

//checks if an event member *to be specified* is a match, takes a target phrase as a param 
bool event::is_match(char *&to_match){
    return true;
}


bool event::yn(char &yes_no){
    bool choice{true};
    do{
        cin >> yes_no;
        cin.ignore(100, '\n');
        if('Y' == toupper(yes_no));
        else if('N' == toupper(yes_no))
            choice = false;
        else
            cout << "Please enter 'Y' or 'N'. Try again.\n" << '>';
    }while('Y' != toupper(yes_no) && 'N' != toupper(yes_no));
    return choice;
}




