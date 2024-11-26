#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>
#include <time.h>

#include <unistd.h>

#include "gateway_rpi.h"

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
    //read parameters
    FILE *params = fopen("custom_authorization.txt","r");
    char param3[300];
    fgets(param3, 300, params);
    size_t len = strlen(param3);
    if(len>0 && param3[len-1] == '\n'){
        param3[len-1] = '\0';
    }
    int param4;
    fscanf(params, "%d", &param4);
    fclose(params);

    cout<<param3<<endl<<param4<<endl;

    // Simulate extraction of arguments
    string list1Str = "read,write"; 
    string list2Str = "resc1,resc2"; 
    char *choice = param3;
    int timer_choice  = param4;

    char res[300];

    vector<string> Oi = splitString(list1Str, ',');
    vector<string> Ri = splitString(list2Str, ',');

    if(choice[0] == '0')
    {
        snprintf(res, sizeof(res), "%s", authUserRequest(Oi, Ri));
    }
    else{
        if(timer_choice =='2'){
            snprintf(res, sizeof(res), "%s", userTimerGenerationRequest(Oi, Ri, param3));
        }
        else{
            snprintf(res, sizeof(res), "%s", userTimerVerificationRequest(Oi, Ri, param3));
        }
        
    }
    if(!strcmp(res, "Access Denied")){
        cout<< "Access Denied!";
        return 0;
    }
    // // get current Timestamp in UNIX format
    time_t t = time(NULL);
    char Ts[20];
    snprintf(Ts, sizeof(Ts), "%ld", t);

    uid_t userid = getuid();
    int Ui = static_cast<int>(userid);
    Ui = 1000;
    char user[30];
    sprintf(user,"%d",Ui);

    char filename[500];
    sprintf(filename, "granted_access/%s/granted_access_%s",user, Ts); //manually change the granted access save file number
    FILE *file = fopen(filename, "w");
    // Write the content of the res array to the file
    fprintf(file, "%s", res);

    // Close the file
    fclose(file);
    cout << "Access Granted!\n";
    return 0; // Access granted
}
