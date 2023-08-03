#pragma once
#include <iostream>
#include "bloomFilter.h"
#include <string>

using namespace std;

struct control_table {
    int sz = 1e6;
    bool bitarray[1000000];
    bool pass_bitarray[1000000];
    control_table();
    int current_state = 0;
    void choosing_operation();
    void create_account();
    bool checkWeakPass(string pass);

};
bool constraint_check(std::string username);
bool password_constraint_check(std::string password);
