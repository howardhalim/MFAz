#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include "gateway.h"
#include <time.h>

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
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <userid> <list1> <list2> <history>" << endl;
        return 1;
    }

    // Extract arguments
    int Ui = stoi(argv[1]);
    string list1Str = argv[2];
    string list2Str = argv[3];

    // Split the lists into vectors of strings
    vector<string> Oi = splitString(list1Str, ',');
    vector<string> Ri = splitString(list2Str, ',');

    char res[300];
    time_t t = time(NULL);
    char Ts[20];
    snprintf(Ts, sizeof(Ts), "%ld", t);

    snprintf(res, sizeof(res), "%s", authUserRequest(Ui, Oi, Ri));
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
