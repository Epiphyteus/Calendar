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

*/

#include "event.h"

using namespace std;

//constructor - intializes dynamic memory.
event::event(){
    name = nullptr;
    desc = nullptr;
    start_month = 0;
    start_day = 0;
    start_year = 0;
    end_month = 0;
    end_day = 0;
    end_year = 0;
    price = 0.00;
    review = nullptr;
    guest = nullptr;
}

//destructor - removes dynamic memory.
event::~event(){
    delete [] name;
    delete [] desc;
    //delete [] start;
    //delete [] end;
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
    char oneday{'\0'};
    cout << "Enter an event name.\n>";
    get(name, SHORT);
    cout << "Enter a brief description of the event.\n>";
    get(desc, LONG);
    cout << "Enter the start date of the event with spaces between the month, day, and year.\n"
         << "(i.e. 5 24 2024)\n>";
    cin >> start_month >> start_day >> start_year;
    //get(start, SHORT);
    cout << "Is the event a multiple day event? (y/n)\n>";
    if(yn(oneday)){
        cout << "Enter the end date of the event with spaces between the month, day, and year.\n"
             << "(i.e. 5 24 2024)\n>";
        cin >> end_month >> end_day >> end_year;
        //get(end, SHORT);
    }
    else{
        //end = new char[strlen(start) +1];
        //strcpy(end, start);
        end_month = start_month;
        end_day = start_day;
        end_year = start_year;
    }
    cout << "Enter the price of admission to the event. (i.e. 12.99)\n>$";
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

//switch condition function 
void event::month_switch(int month){ 
    switch(month){
        case 1:
            cout << "January";
            break;
        case 2:
            cout << "February";
            break;
        case 3:
            cout << "March";
            break;
        case 4:
            cout << "April";
            break;
        case 5:
            cout << "May";
            break;
        case 6:
            cout << "June";
            break;
        case 7:
            cout << "July";
            break;
        case 8:
            cout << "August";
            break;
        case 9:
            cout << "September";
            break;
        case 10:
            cout << "October";
            break;
        case 11:
            cout << "November";
            break;
        case 12:
            cout << "December";
            break;
    }
}

//displays one event
void event::display(){
    cout << "Event Name: " << name << endl
         << "Description: " << desc << endl
         << "Happening: ";
    month_switch(start_month);
    cout << ' ' << start_day << ", " << start_year << " through ";
    month_switch(end_month);
    cout << ' ' << end_day << ", " << end_year << endl;
    cout << "Cost of Admission: $" << setprecision(2) << fixed << price << endl
         << "Review: " << review << endl
         << "Guest Speaker: " << guest << endl;

}

//checks if an event member *to be specified* is a match, takes a target phrase as a param 
bool event::is_match(char *&to_match){
    if(strcmp(to_match, name) == 0)
        return true;
    return false;
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




