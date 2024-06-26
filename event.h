//Ian Leuty May 18 2024 CS162-001 ileuty@pdx.edu Program4
/*
The purpose of this program is to create a dynamic array or LLL of events, in the format of a calendar.
This program will make use of pointers, dynamocally allocated arrays, and classes.

This is the main header file. It includes the pre-processor directives 
and the definition of the class to manage single events

An event will include the following information:
1. Name of event (i.e. "Air Show")
2. Description of the event
3. Start date of event
4. End date of event
5. Price of admission
6. Review of the event
7. If it is a one day event
8. Start time
*/

#include <iomanip>
#include <iostream>
#include <cctype>
#include <cstring>
#include <cmath>
#include <fstream>

const int SHORT{46};
const int LONG{501};


struct event{
        event();
        ~event();
        void get(char *&array, const int size);
        void read();
        void month_switch(int month);
        void display();
        bool is_match(char *&to_match);
        bool yn(char &yes_no);

        char *name;
        char *desc;
        //char *start;
        //char *end;
        int start_month;
        int start_day;
        int start_year;
        int end_month;
        int end_day;
        int end_year;
        float price;
        char *review;
        char *guest;
};

