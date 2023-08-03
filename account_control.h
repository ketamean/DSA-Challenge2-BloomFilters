#pragma once
#include <iostream>
#include "bloomFilter.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>

using namespace std;

struct control_table {
    int sz = 1e6;
    int assigned = 0;
    bool bitarray[1000000];
    bool pass_bitarray[1000000];
    int current_state = 0;

    map<string, string> user_pass;
    control_table();

    vector<int> hash(string s);
    bool lookup(string s);
    void insert(string s);
    void choosing_operation();
    void create_account();
    void login();
    void multiple_register();
    void change_password();
    bool checkWeakPass(string pass);
    bool check_existed_username(string username);
    bool check_correct_password(string username, string password);
    
};
bool constraint_check(std::string username);
bool password_constraint_check(std::string password);
