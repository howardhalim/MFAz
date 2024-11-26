#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "miracl.h"

char *concatenateData(int Ui, const std::vector<std::string> &Oi, const std::vector<std::string> &Ri, const char *Ts);

big generateVerificationPoint(const char *GAij, const char *Si);

bool checkVerificationPoint(struct bloom * bloom, big check_vp);

void addVerificationPoint(struct bloom * bloom, big VPij);

char *userRequest(int Ui, const std::vector<std::string> &Oi, const std::vector<std::string> &Ri, const char *SGAi);

char *authUserRequest(int Ui, const std::vector<std::string> &Oi, const std::vector<std::string> &Ri);

char *userTimerRequest(int Ui, const std::vector<std::string> &Oi, const std::vector<std::string> &Ri, const char *SGAi);

char *userTimerGenerationRequest(int Ui, const std::vector<std::string> &Oi, const std::vector<std::string> &Ri, const char *SGAi);

char *userTimerVerificationRequest(int Ui, const std::vector<std::string> &Oi, const std::vector<std::string> &Ri, const char *SGAi);

char *userTimerStoringRequest(int Ui, const std::vector<std::string> &Oi, const std::vector<std::string> &Ri, const char *SGAi);