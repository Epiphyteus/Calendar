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
    

//destructor - automatically deallocates nodes in the lll
calendar::~calendar(){
    remove_all(head);
}


//adds events in sorted order. 
void calendar::read_events(){
    char again{'\0'};
    do{
        node *temp{new node};
        char *punct;
        temp -> data.read();
        punct = new char[strlen(temp -> name)+1];
        strcpy(punct, temp -> name);

        temp -> link = nullptr;
        ordered_insert(head, temp);
        cout << "Again?\n>";
        cin >> again;
        cin.ignore(100, '\n'); 
    }while('Y' == toupper(again));
}

//recursively finds the spot a new item belongs and adds it.
void calendar::ordered_insert(node *&head, node *&temp){
    if(head && strcmp(temp -> data.name, head -> data.name) < 0){
        temp -> link = head;
        head = temp;
        return;
    }
    if(head && strcmp(temp -> data.name, head -> data.name) < 0){
        temp -> link = head -> link;
        head -> link = temp;
        return;
    }
    if(!head){
        head = temp;
        temp -> link = head -> link;
        return;
    }
    ordered_insert(head -> link, temp);    
}
/*    
void calendar::date_search(){
    cout << "Enter 
*/

//main display definition, no args, calls recursive display
void calendar::display_events(){
    if(!head){
        cout << endl << "No events currently in your calendar." << endl;
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

    (rec_search_V1(find, head));
    delete [] find;
    find = nullptr;
}

/*
//ugly recursive search
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
*/

void calendar::rec_search_V1(char *find, node *&head){
    if(!head) return;
    if(head -> data.is_match(find)){
        cout << endl << "Match Found!" << endl;
        head -> data.display();
        node *temp = head -> link;
        if(remove(head))
            head = temp;
        return;
    }
    rec_search_V1(find, head -> link);
}

//removes the item at just one node found when searching. called within search.
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
            filein >> add -> data.start_month;
            filein.ignore(100, '/');
            filein >> add -> data.start_day;
            filein.ignore(100, '/');
            filein >> add -> data.start_year;
            filein.ignore(100, '|');
            filein >> add -> data.end_month;
            filein.ignore(100, '/');
            filein >> add -> data.end_day;
            filein.ignore(100, '/');
            filein >> add -> data.end_year;
            filein.ignore(100, '|');
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
            ordered_insert(head, add);

            filein.get(temp, LONG, '|');
            filein.ignore(100, '|'); 
        }
    filein.close();
    }
}

//saves to external file
void calendar::save(){
    ofstream fileout;
    node *current{head};
    fileout.open("events.txt");
    if(fileout){
        while(current){
            fileout << current -> data.name << '|'
                    << current -> data.desc << '|'
                    << current -> data.start_month << '/'
                    << current -> data.start_day << '/'
                    << current -> data.start_year << '|'
                    << current -> data.end_month << '/'
                    << current -> data.end_day << '/'
                    << current -> data.end_year<< '|'

                    /*
                    << current -> data.start << '|'
                    << current -> data.end << '|'
                    */
                    << setprecision(2) << fixed << current -> data.price << '|' 
                    << current -> data.review << '|'
                    << current -> data.guest << endl;
            current = current -> link;
        }
        fileout.close();
    }
}




//capitalize the first character of every word in a phrase array
void calendar::capitalize(char chars[]){
    int length{0}, g{0};
    length = strlen(chars);
    for(g = 0; g < length; g++)
        chars[g] = tolower(chars[g]);
    
    for(g = 0; g < length; g++){
        if(isblank(chars[g]))
            chars[g+1] = toupper(chars[g+1]);  
    }
    chars[0] = toupper(chars[0]);
}


//remove punctuation from a word
void calendar::rm_punct(char chars[], char new_word[]){
    int len_chars{0};
    int o{0}, k{0};
    len_chars = strlen(chars);

    for(k = 0, o = 0; k <= len_chars; ++k){
        if(ispunct(chars[k]) == false){
            new_word[o] = chars[k]; //similar proccess to separating words
            ++o;
            new_word[o+1] = '\0';
        }
    }
}

//convert a character array to lowercase
//easy, just covert everything one by one
void calendar::lower_chars(char chars[]){
    int len_chars{0}, n{0};
    len_chars = strlen(chars);

    for(n = 0; n < len_chars; ++n){
        chars[n] = tolower(chars[n]);
    }
}

