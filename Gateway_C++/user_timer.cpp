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
    if (argc != 6)
    {
        cerr << "Usage: " << argv[0] << " <userid> <list1> <list2> <history> <choice>" << endl;
        return 1;
    }

    // Extract arguments
    int Ui = stoi(argv[1]);
    string list1Str = argv[2];
    string list2Str = argv[3];
    char *SGAi = argv[4];
    
    int functionChoice = atoi(argv[5]);

    // Split the lists into vectors of strings
    vector<string> Oi = splitString(list1Str, ',');
    vector<string> Ri = splitString(list2Str, ',');

    char res[300];
    //1: function timer
    //2: Generation Timer
    //3: Verification Timer
    switch (functionChoice) {
        case 1:
            snprintf(res, sizeof(res), "%s", userTimerRequest(Ui, Oi, Ri, SGAi));
            break;
        case 2:
            snprintf(res, sizeof(res), "%s", userTimerGenerationRequest(Ui, Oi, Ri, SGAi));
            break;
        case 3:
            snprintf(res, sizeof(res), "%s", userTimerStoringRequest(Ui, Oi, Ri, SGAi));
            break;
        case 4:
            snprintf(res, sizeof(res), "%s", userTimerVerificationRequest(Ui, Oi, Ri, SGAi));
            break;
        default:
            cerr << "Invalid function choice. Must be -1, -2, or -3." << endl;
            return 1;
    }
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
