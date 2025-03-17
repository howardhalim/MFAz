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

char *authUserRequest(const std::vector<std::string> &Oi, const std::vector<std::string> &Ri);

char *userTimerGenerationRequest(const std::vector<std::string> &Oi, const std::vector<std::string> &Ri, const char *SGAi);

char *userTimerVerificationRequest(const std::vector<std::string> &Oi, const std::vector<std::string> &Ri, const char *SGAi);