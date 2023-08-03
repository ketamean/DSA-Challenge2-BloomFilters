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
int h1(string s, int arrSize)
{
    ll int hash = 0;
    for (int i = 0; i < s.size(); i++) 
    {
        hash = (hash + ((int)s[i]));
        hash = hash % arrSize;
    }
    return hash;
}
  
// hash 2
int h2(string s, int arrSize)
{
    ll int hash = 1;
    for (int i = 0; i < s.size(); i++) 
    {
        hash = hash + pow(19, i) * s[i];
        hash = hash % arrSize;
    }
    return hash % arrSize;
}

int control_table::hash(string s) {
    int _h1 = h1(s, sz);
    int _h2 = h2(s, sz);
    int h = 0;
    for (int i = 0; i < assigned; i++) {
        h += _h1 + i * _h2;
    }
    return h;
}
  
// lookup operation
bool control_table::lookup(string s)
{
    int h = hash(s);
  
    if (bitarray[h])
        return true;
    else
        return false;
}
  
// insert operation
void control_table::insert(string s)
{
    // check if the element in already present or not
    if (lookup(s))
        cout << s << " is Probably already present" << endl;
    else 
    {
        int h = hash(s);
        if (bitarray[h] == false) {
            assigned++;
            bitarray[h] = true;
        }
    }
}