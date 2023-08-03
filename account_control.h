#pragma once
#include <iostream>
#include "bloomFilter.h"


struct control_table {
    int sz = 1e6;
    bool bitarray[1000000] = {0};
    int current_state;
    void choosing_operation();
    void create_account();

};
bool constraint_check(std::string username);