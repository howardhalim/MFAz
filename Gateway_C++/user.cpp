#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>
#include <time.h>

#include "gateway.h"

using namespace std;


// Function to split a string by a delimiter and return a vector of strings
vector<string> splitString(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}



int main(int argc, char *argv[])
{
    // Check if the number of arguments is correct
    if (argc != 5)
    {
        cerr << "Usage: " << argv[0] << " <userid> <list1> <list2> <history>" << endl;
        return 1;
    }

    // Extract arguments
    int Ui = stoi(argv[1]);
    string list1Str = argv[2];
    string list2Str = argv[3];
    char *granted_history = argv[4];
    

    // Split the lists into vectors of strings
    vector<string> Oi = splitString(list1Str, ',');
    vector<string> Ri = splitString(list2Str, ',');

    char res[300];

    snprintf(res, sizeof(res), "%s", userRequest(Ui, Oi, Ri, granted_history));
    if(!strcmp(res, "Access Denied")){
        cout<< "Access Denied!";
        return 0;
    }
    // get current Timestamp in UNIX format
    time_t t = time(NULL);
    char Ts[20];
    snprintf(Ts, sizeof(Ts), "%ld", t);

    char filename[256];
    sprintf(filename, "granted_access/%s/granted_access_%s",argv[1], Ts); //manually change the granted access save file number
    FILE *file = fopen(filename, "w");
    // Write the content of the res array to the file
    fprintf(file, "%s", res);

    // Close the file
    fclose(file);
    cout << "Access Granted!";
    return 0;
}
