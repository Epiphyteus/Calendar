//Ian Leuty May 18 2024 CS162-001 ileuty@pdx.edu Program4
//This file contains the main calling routine for this calendar program.

#include "calendar.h" 

//global functions to deal with user interaction
void welcome();
bool menu(calendar &events);

using namespace std;

int main(){
    calendar events;
    events.load_events();
    welcome();
    while(menu(events));

    return 0;
}

