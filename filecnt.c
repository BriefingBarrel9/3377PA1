//Timothy Baragar, TJB170002, CS 3377.0W1, Project 2

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include "version.h"

using namespace std;

//Here, i prototype the three recursive functions i use for counting directories, files, and bytes, respectively
int cntDir(string file);
int cntFil(string file);
long cntByt(string file);

int main (int argc, char *argv[]) {

	version v;
	v.displayVersion();

// this checks that there are the right number of arguments
    if (argc == 2) {

        // here i declare my variables, and assign them their calculated values when calling the functions
        string arg = argv[1];
        int numDir = cntDir(arg);
        int numFil = cntFil(arg);
        long numByt = cntByt(arg);

        //this is my output, which comes from the earlier calculated values, and goes out through cout
        cout << "The total number of directories in directory " << arg << " is: " << numDir << endl;
        cout << "The total number of files in directory " << arg << " is: " << numFil << endl;
        cout << "The total number of bytes occupied by all files in directory " << arg << " is: " << numByt << endl;
    }

    // this runs if there is an incorrect number of arguments passed into the program
    else {
        // this repeats the message 3 times, so that if it is passed through a pipe to the filedisp program, no matter the argument there, it still shows the error message
        for (int i = 0; i < 3; i++) {
            //the error message
            cout << "There is an incorrect number of arguments, only argument should be the file path" << endl;
        }
    }

    // the end of the program
    return 0;
}

// this function counts the number of directories in the file path passed in to it
int cntDir(string file) {

    // this is the start of the tracker
    int count = 0;

    // this is a struct of the library dirent, which is used for getting files and directories, and holds either, as well as the name, ino, and file type
    struct dirent *de;

    // this is a data type from the dirent.h library, and it is a data stream, specifically a stream of all the files and directories in a file "file.c_str()", as i called it
    DIR *dr = opendir(file.c_str());

    //this checks if it successfully opened the directory, if it did not, the program does not have permissions, and is ignored, returning -1 to the function that called it
    if (!dr) {
        return -1;
    }

    // this gets the . and .. directories out of the way, as they are at the beginning of the list, and are used for traversing back through the file path
    de = readdir(dr);
    de = readdir(dr);

    //this iterates through the entire directory stream
    while ((de = readdir(dr)) != NULL) {
        // this differentiates files from directories, as directories have a type of 4, while files have a type of 8
        if (de->d_type == 4) {
            // this goes further down the traversal by appending the new directory to the end of the current file path, and passing it back into the function, retrieving the number of directories in it, and then adding it to the counter
            string newFile = file + "/" + de->d_name;
            count += cntDir(newFile);
            count++;
        }
    }
    
    // this closes the directory stream, as it would otherwise take up a lot of memory, opening a stream for each directory, and leaving them open
    closedir(dr);

    //this returns the count of directories in the current directory to the function that called it
    return count;
}

// this counts the number of files, and operates almost exactly like the previous function. Differences will be noted
int cntFil(string file) {
    int count = 0;
	// hey look, it's a struct
    struct dirent *de;

    DIR *dr = opendir(file.c_str());
    if (!dr) {
        //returns 0 instead of -1 because there is no incrementing
        return 0;
    }
    de = readdir(dr);
    de = readdir(dr);

    while ((de = readdir(dr)) != NULL) {
        if (de->d_type == 4) {
            string newFile = file + "/" + de->d_name;
            count += cntFil(newFile);
            // doesn't increment the counter by one, because it is in a directory, not a file
        }

        // this checks if the file type is a file, which is labeled as type 8, and increments the counter for each file
        if (de->d_type == 8) {
            count++;
        }
    }

    closedir(dr);
    return count;
}

//again, same as the last ont, will note the differences
long cntByt(string file) {

    //Used a long instead of an int because there are a lot of bytes that can be used, and wanted to make sure there was enough room
    long count = 0;

    struct dirent *de;

    DIR *dr = opendir(file.c_str());
    if (!dr) {
        return 0;
    }
    de = readdir(dr);
    de = readdir(dr);

    while ((de = readdir(dr)) != NULL) {
        if (de->d_type == 4) {
            string newFile = file + "/" + de->d_name;
            count += cntByt(newFile);
        }
        if (de->d_type == 8) {
            string fileCheck = file + "/" + de->d_name;

            // this creates a structure stat that gets a lot of info about a file that is passed to it, it adds the size of the file to the counter
            struct stat st;
            stat(fileCheck.c_str(), &st);
            count += st.st_size;
        }
    }

    closedir(dr);
    return count;
}
