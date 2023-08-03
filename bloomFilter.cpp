#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include "account_control.h"

#define ll long long
using namespace std;
  
// hash 1
unsigned int h1(string s, int arrSize)
{
    unsigned ll int hash = 0;
    for (int i = 0; i < s.size(); i++) 
    {
        hash = (hash + ((int)s[i]));
        hash = hash % arrSize;
    }
    return hash;
}
  
// hash 2
unsigned int h2(string s, int arrSize)
{
    unsigned ll int hash = 1;
    for (int i = 0; i < s.size(); i++) 
    {
        hash = hash + pow(4, i) * s[i];
        hash = hash % arrSize;
    }
    return hash % arrSize;
}

vector<int> control_table::hash(string s) {
    unsigned int _h1 = h1(s, sz);
    unsigned int _h2 = h2(s, sz);

    vector<int> res;
    for (int i = 0; i < min(assigned + 1, 25); i++) {
        res.push_back((_h1 + i * _h2) % sz);
    }
    return res;
}

// lookup operation
bool control_table::lookup(string s)
{
    vector<int> h = hash(s);
    for (int i = 0; i < h.size(); ++i) {
        if (bitarray[h[i]] == 0)
            return false;
    }
    return true;
}
  
// insert operation
void control_table::insert(string s)
{
    // check if the element in already present or not
    if (lookup(s))
        cout << s << " is Probably already present" << endl;
    else
    {
        vector<int> h = hash(s);
        for (int i = 0; i < h.size(); ++i) {
            if (bitarray[h[i]] == false) {
                assigned++;
                bitarray[h[i]] = true;
            }
        }

    }
}