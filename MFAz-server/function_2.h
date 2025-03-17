#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
using namespace std;

string addition( string num1, string num2);

string session_id_generator(int id);

char *hashing(char *str, int strlength, char *hash);

char *authUserRequest(int Ui, const vector<string> &Oi, const vector<string> &Ri);

char *userRequest(int Ui, const vector<string> &Oi, const vector<string> &Ri, const char *SGAi);


#endif 