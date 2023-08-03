#pragma once
#include <string>

#define ll long long

// Hash Functions
int h1(std::string s, int arrSize);
int h2(std::string s, int arrSize);

// Lookup operation
bool lookup(bool* bitarray, int arrSize, std::string s);

// Insert operation
void insert(bool* bitarray, int arrSize, std::string s);

