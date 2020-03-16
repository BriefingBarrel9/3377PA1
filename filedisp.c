//Timothy Baragar, TJB170002, CS 3377.0W1, Project 2
// this program is surprisingly short
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

// this accepts either -d, -f, or -b as arguments
int main (int argc, char *argv[]) {
    
    //this checks that there is the right number of arguments
    if (argc == 2) {
        //this creates the variables to hold the 3 strings of input for the file, and gets the 3 lines of input from the filecnt output
        string line1;
        string line2;
        string line3;
        getline(cin, line1);
        getline(cin, line2);
        getline(cin, line3);

    
        // this checks the argument passed in, and displays a different line for each different argument
        if (strcmp(argv[1], "-d") == 0) {
            //displays line one (directories) if the argument is -d
            cout << line1 << endl;
        }
        else if (strcmp(argv[1], "-f") == 0) {
            //displays line two (files) if the argument is -f
            cout << line2 << endl;
        }
        else if (strcmp(argv[1], "-b") == 0) {
            //displays line three (bytes) if the argument is -b
            cout << line3 << endl;
        }
        else {
            // if the argument was not one of the three, send an error message
            cout << "Something was wrong with the command, unexpected argument to filedisp, the argument should be either -d, -f, or -b" << endl;
        }
    }
    else {
        // if there was not enough or too many arguments, throw an error message
        cout << "filedisp requires one argument, that argument being either -d, -f, or -b" << endl;
    }
    return 0;
}
