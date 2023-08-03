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
    return lookup(pass);
}
control_table::control_table() {
    for (int i = 0; i < sz; i++) bitarray[i] = pass_bitarray[i] = 0;
    ifstream checklist("Weak-Pass.txt");
    string s;
    while (checklist >> s)
    {
        insert(s);
    }
    checklist.close();
    ifstream file("account.txt");
    string username, password;
    while (file >> username >> password)
    {
        insert(username);
        user_pass[username] = password;
    }
    file.close();
}
void control_table::create_account(){

    system("cls");

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
        cons3 = lookup(username);
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
    insert(username);
    string file_out = "account.txt";
    ofstream out;
    out.open(file_out, ios::app);
    out<<username<<" "<<password<<endl;
    out.close();
    user_pass[username] = password;
    cout<<"Account created successfully"<<endl;
    choosing_operation();
    
}

bool control_table::check_existed_username(string username)
{
    return lookup(username);
}

bool control_table::check_correct_password(string username, string password)
{
    return user_pass[username] == password;
}

void control_table::multiple_register()
{
    system("cls");
    string file = "SignUp.txt";
    string output = "Fail.txt";
    string accounts = "account.txt";

    ifstream file_in;
    ofstream out;
    ofstream file_out;

    file_in.open(file);
    file_out.open(output);
   out.open(accounts, ios::app);

    if (!file_in.is_open())
    {
        cout << "File not found!\n";
        return;
    }

    string name, password;

    while (!file_in.eof())
    {
        file_in >> name;
        file_in >> password;

        if (!constraint_check(name) || !password_constraint_check(name) || checkWeakPass(password) || lookup(name) || lookup(password))
        {
            file_out << name << " " << password << endl;
        }
        else
        {
            insert(name);
            user_pass[name] = password;
            out << name << password << endl;
        }
    }
}

void control_table::login()
{ 
    system("cls");
    string name, pass;
    int check_name = false;
    int check_pass = false;

    cout << "Please enter your username: ";
    cin>>name;
    check_name = check_existed_username(name);
    
    if (!check_name)
    {
        cout << "Username is not exist!\n";
        return;
    }

    while (!check_pass)
    {
        cout << "Please enter your password: ";
        cin>>pass;
        check_pass = check_correct_password(name, pass);
        if (!check_pass) cout << "Your password is not correct! Please try again!\n";
    }

    cout << "Successfully logged in!\n";
}

void control_table::change_password()
{
    system("cls");
    string name, pass, new_pass;
    string new_pass_2 = "";
    bool check_name = false;
    bool check_pass = false;
    bool check_new_pass = false;

    cout << "Please enter your username: ";
    cin>>name;
    check_name = check_existed_username(name);
    
    if (!check_name)
    {
        cout << "Username is not exist!\n";
        return;
    }

    while (!check_pass)
    {
        cout << "Please enter your OLD password: ";
        cin>>pass;
        check_pass = check_correct_password(name, pass);
        if (!check_pass) cout << "Your password is not correct! Please try again!\n";
    }

    while (!check_new_pass)
    {
        cout << "Please enter your NEW password: ";
        cin>>new_pass;
        check_new_pass = password_constraint_check(new_pass);
        check_new_pass = check_new_pass && !checkWeakPass(new_pass);
    }

    while (new_pass_2 != new_pass)
    {
        cout << "Please enter your NEW password one more time: ";
        cin>>new_pass_2;
        if (new_pass_2 != new_pass) cout << "The new password is not correct! Please try again!\n";
    }

    cout << "Successfully changed password!\n";
}

void control_table::choosing_operation() {
    std::cout << "Please choose an operation: " << std::endl;
    std::cout << "1. Create a new account" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Change password" << std::endl;
    std::cout << "4. Load accounts from file: " << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> current_state;
    std::cout << std::endl;

    if (current_state == 1) create_account();
    else if (current_state == 2) login();
    else if (current_state == 3) change_password();
    else if (current_state == 4) multiple_register();
    else if (current_state == 5) return;
    else {
        choosing_operation();
    }
}