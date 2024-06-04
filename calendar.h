//Ian Leuty May 18 2024 CS162-001 ileuty@pdx.edu Program4

/*
This is the header file for the list class.

The program will use this list class to manage events. The class will use a linear linked list to
dynamically add new items. 

The list object will have:
1. Constructor
2. Destructor
3. Read in function
4. Display all events function
5. Search for event based on one info field
6. Cancel attending

The list class will have the following data members:
1. Pointer to event class item
2. Size of the array
3. Number of events stored in the array

UNLESS A LLL IS USED INSTEAD, IN WHICH CASE:

If we implement the list class as a linear linked list instead, it can use nodes which point to a variable 
of the item class type.
*/

#include "event.h" 

//node structure for linear linked list!
struct node{
    event data;
    node *link;
};

class calendar{
    public:
         calendar();
        ~calendar();
        void get_events();
        void display_events();
        void search();
        bool remove(node *&to_remove);
        void load_events();
        void save();
        void read_events();
        void capitalize(char chars[]);
        void rm_punct(char chars[], char new_word[]);
        void lower_chars(char chars[]);
    private:
        //void rec_search(char *find, node *&prev, node *&current);
        void rec_search_V1(char *find, node *&head);
        void ordered_insert(node *&head, node *&temp);
        void remove_all(node *&head);
        void display_events(node *head);
        node *head;
};

