#include "account_control.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool constraint_check(string username)
{
    for (int i = 0; i < username.size(); i++)
        if (username[i] == ' ') {
            cout<<"Username cannot contain space"<<endl;
            return false;
        }
    if (username.size() <= 5 || username.size() >= 10)
    {
        cout<<"Username must be between 5 and 10 characters"<<endl;
        return false;
    }
    return true;
}
bool password_constraint_check(string password)
{
    int len = password.size();
    if (len <= 10 || len >= 20) {
        cout<<"Password must be between 10 and 20 characters"<<endl;
        return false;
    }
    bool has_upper = false, has_lower = false, has_digit = false, has_number = false, has_speical = false;
    for (int i = 0; i < len; i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z') has_upper = true;
        if (password[i] >= 'a' && password[i] <= 'z') has_lower = true;
        if (password[i] >= '0' && password[i] <= '9') has_digit = true;
        if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '%' || password[i] == '^' || password[i] == '&' || password[i] == '*' || password[i] == '(' || password[i] == ')' || password[i] == '-' || password[i] == '+') has_speical = true;
    }  
    if (!has_upper || !has_lower || !has_digit || !has_speical) {
        cout<<"Password must contain at least one uppercase letter, one lowercase letter, one digit, and one special character"<<endl;
        return false;
    }
    return true;
}
bool control_table::checkWeakPass(string pass)
{
    return lookup(pass_bitarray, sz, pass);
}
control_table::control_table() {
    for (int i = 0; i < sz; i++) bitarray[i] = pass_bitarray[i] = 0;
    ifstream checklist("Weak-Pass.txt");
    string s;
    while (checklist >> s)
    {
        insert(pass_bitarray, sz, s);
    }
    checklist.close();
}
void control_table::create_account(){
    string username, password;
    std::cout<<"Please enter your username: ";
    std::cin>>username;
    std::cout<<"Please enter your password: ";
    std::cin>>password;
    bool cons1 = 0, cons2 = 0, cons3 = 1;

    while (!cons1 || !cons2 || cons3)
    {
        //check until username and password satisfy the constraints and havent been used before
        cons1 = constraint_check(username);
        if (!cons1)
        {
            std::cout<<"Please enter your username: ";
            std::cin>>username;
            std::cout<<"Please enter your password: ";
            std::cin>>password;
            continue;
        }
        cons2 = password_constraint_check(password);
        if (!cons2 || checkWeakPass(password))
        {
            if (checkWeakPass(password)) cout<<"Password is too weak"<<endl;
            std::cout<<"Please enter your username: ";
            std::cin>>username;
            std::cout<<"Please enter your password: ";
            std::cin>>password;
            continue;
        }
        cons3 = lookup(bitarray, sz, username);
        if (cons3)
        {
            std::cout<<"Username has been used before"<<endl;
            std::cout<<"Please enter your username: ";
            std::cin>>username;
            std::cout<<"Please enter your password: ";
            std::cin>>password;
            continue;
        }
    }
    current_state = 0;
    insert(bitarray, sz, username);
    ofstream out("account.txt");
    out<<username<<" "<<password<<endl;
    out.close();
    user_pass[username] = password;
    cout<<"Account created successfully"<<endl;
    choosing_operation();
}

void control_table::choosing_operation() {
    std::cout << "Please choose an operation: " << std::endl;
    std::cout << "1. Create a new account" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Change password" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> current_state;
    std::cout << std::endl;
    if (current_state == 1) create_account();
}