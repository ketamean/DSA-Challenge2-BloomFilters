#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "bloomFilter.h"


struct control_table {
    int sz = 1e6;
    int assigned = 0;
    bool bitarray[1000000] = {0};
    int current_state;
    void choosing_operation();
    void create_account();

    vector<int> hash(string s);
    bool lookup(string s);
    void insert(string s);
};
bool constraint_check(std::string username);