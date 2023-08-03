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
    void login();
    void multiple_register();
    void change_password();
    bool checkWeakPass(string pass);
    bool check_existed_username(string username);
    bool check_existed_password(string password);
    
};
bool constraint_check(std::string username);
bool password_constraint_check(std::string password);
