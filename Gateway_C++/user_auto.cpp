#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>
#include <time.h>
#include <unistd.h>

#include "gateway_auto.h"

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

    // Extract arguments
    string list1Str = argv[1];
    string list2Str = argv[2];
    char* param3 = argv[3];
    int param4 = atoi(argv[4]);

    // Split the lists into vectors of strings
    vector<string> Oi = splitString(list1Str, ',');
    vector<string> Ri = splitString(list2Str, ',');

    char res[300];

    //no verification
    if(param3[0] == '0'){
        snprintf(res, sizeof(res), "%s", authUserRequest(Oi, Ri));
    }
    else{ //with verification
        char* SGAi = param3;
        //choose which Timer option or None (Default)
        switch (param4) {
            case 1:
                snprintf(res, sizeof(res), "%s", userTimerRequest(Oi, Ri, SGAi));
                break;
            case 2:
                snprintf(res, sizeof(res), "%s", userTimerGenerationRequest(Oi, Ri, SGAi));
                break;
            case 3:
                snprintf(res, sizeof(res), "%s", userTimerStoringRequest(Oi, Ri, SGAi));
                break;
            case 4:
                snprintf(res, sizeof(res), "%s", userTimerVerificationRequest(Oi, Ri, SGAi));
                break;
            default:
                snprintf(res, sizeof(res), "%s", userRequest(Oi, Ri, SGAi));
        }
    }

    
    // get current Timestamp in UNIX format
    time_t t = time(NULL);
    char Ts[20];
    snprintf(Ts, sizeof(Ts), "%ld", t);

    uid_t userid = getuid();
    int Ui = static_cast<int>(userid);
    char user[30];
    sprintf(user,"%d",Ui);

    char filename[256];
    sprintf(filename, "granted_access/%s/granted_access_%s",user, Ts); //manually change the granted access save file number
    FILE *file = fopen(filename, "w");
    // Write the content of the res array to the file
    fprintf(file, "%s", res);

    // Close the file
    fclose(file);
    cout << "Access Granted!\n";
    return 0;
}
