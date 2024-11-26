#pragma once

#include"bloom.h"

int bf_check(struct bloom* bloom, char* buffer, int buflen);

int bf_add(struct bloom* bloom, char* buffer, int buflen); 