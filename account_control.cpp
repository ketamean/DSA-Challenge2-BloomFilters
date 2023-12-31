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
    return lookup_pass(pass);
}
control_table::control_table() {
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
    cin.ignore();

    string username, password;
    std::cout<<"Please enter your username (enter x to exit): ";
    getline(cin, username);
    if (username == "X" || username == "x") {
        cout<<"--------------"<<endl;
        return;
    }
    std::cout<<"Please enter your password (enter x to exit): ";
    getline(cin, password);
    if (password == "X" || password == "x") {
        cout<<"--------------"<<endl;
        return;
    }
    bool cons1 = 0, cons2 = 0, cons3 = 1;

    while (!cons1 || !cons2 || cons3)
    {
        //check until username and password satisfy the constraints and havent been used before
        cons1 = constraint_check(username);
        if (!cons1)
        {
            std::cout<<"Invalid username"<<endl;

            std::cout<<"Please enter your username (enter x to exit): ";
            getline(cin, username);
            if (username == "X" || username == "x") {
                cout<<"--------------"<<endl;
                return;
            }
            std::cout<<"Please enter your password (enter x to exit): ";
            getline(cin, password);
            if (password == "X" || password == "x") {
                cout<<"--------------"<<endl;
                return;
            }

            continue;
        }
        cons2 = password_constraint_check(password);
        if (!cons2 || checkWeakPass(password))
        {
            if (checkWeakPass(password)) cout<<"Password is too weak"<<endl<<endl;
            
            std::cout<<"Please enter your username (enter x to exit): ";
            getline(cin, username);
            if (username == "X" || username == "x") {
                cout<<"--------------"<<endl;
                return;
            }
            std::cout<<"Please enter your password (enter x to exit): ";
            getline(cin, password);
            if (password == "X" || password == "x") {
                cout<<"--------------"<<endl;
                return;
            }

            continue;
        }
        cons3 = lookup(username);
        if (cons3)
        {
            std::cout<<"Username has been used before"<<endl<<endl;

            std::cout<<"Please enter your username (enter x to exit): ";
            getline(cin, username);
            if (username == "X" || username == "x") {
                cout<<"--------------"<<endl;
                return;
            }
            std::cout<<"Please enter your password (enter x to exit): ";
            getline(cin, password);
            if (password == "X" || password == "x") {
                cout<<"--------------"<<endl;
                return;
            }

            continue;
        }
    }
    current_state = 0;
    insert(username);
    user_pass[username] = password;
    cout<<"Account created successfully"<<endl;
    cout<<"--------------"<<endl;
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

        if (!constraint_check(name) || !password_constraint_check(password) || checkWeakPass(password) || lookup(name) || lookup_pass(password))
        {
            file_out << name << " " << password << endl;
        }
        else
        {
            insert(name);
            user_pass[name] = password;
        }
    }
    system("cls");
    cout << "Multiple register successfully!\n";
    cout<<"--------------"<<endl;
}

void control_table::login()
{ 
    system("cls");
    cin.ignore();
    string name, pass;
    int check_name = false;
    int check_pass = false;

    cout << "Please enter your username (enter x to exit): ";
    getline(cin, name);

    if (name == "X" || name == "x")
    {
        current_state = 0;
        cout<<"--------------"<<endl;
        return;
    }
    
    check_name = check_existed_username(name);
    
    if (!check_name)
    {
        cout << "Username is not exist!\n";
        cout<<"--------------"<<endl;
        return;
    }

    while (!check_pass)
    {
        cout << "Please enter your password (enter x to exit): ";
        getline(cin, pass);
        if (pass == "X" || pass == "x")
        {
            current_state = 0;
            cout<<"--------------"<<endl;
            return;
        }
        check_pass = check_correct_password(name, pass);
        if (!check_pass) cout << "Your password is not correct! Please try again! or Press X to exit\n";
    }

    cout << "Successfully logged in!\n";
    cout << "Press X to logout!\n";
    char c;
    cin >> c;
    if (c == 'X' || c == 'x')
    {
        current_state = 0;
        cout<<"--------------"<<endl;
        return;
    }
    else
    {
        cout << "Invalid input! Press X to logout!\n";
        return;
    }
}

void control_table::change_password()
{
    system("cls");
    cin.ignore();
    
    string name, pass, new_pass;
    string new_pass_2 = "";
    bool check_name = false;
    bool check_pass = false;
    bool check_new_pass = false;

    cout << "Please enter your username (enter x to exit): ";
    getline(cin, name);
    if (name == "X" || name == "x")
    {
        current_state = 0;
        cout<<"--------------"<<endl;
        return;
    }
    check_name = check_existed_username(name);
    
    if (!check_name)
    {
        cout << "Username is not exist!\n";
        cout<<"--------------"<<endl;
        return;
    }

    while (!check_pass)
    {
        cout << "Please enter your OLD password (enter x to exit): ";
        getline(cin, pass);
        if (pass == "X" || pass == "x")
        {
            current_state = 0;
            cout<<"--------------"<<endl;
            return;
        }
        check_pass = check_correct_password(name, pass);
        if (!check_pass) cout << "Your password is not correct! Please try again! or press X to exit\n";
    }

    while (!check_new_pass)
    {
        cout << "Please enter your NEW password: ";
        getline(cin, new_pass);
        check_new_pass = password_constraint_check(new_pass);
        check_new_pass = check_new_pass && !checkWeakPass(new_pass);
    }

    while (new_pass_2 != new_pass)
    {
        cout << "Please enter your NEW password one more time (enter x to exit): ";
        getline(cin, new_pass_2);
        if (new_pass_2 == "X" || new_pass_2 == "x")
        {
            current_state = 0;
            cout<<"--------------"<<endl;
            return;
        }
        if (new_pass_2 != new_pass) cout << "The new password is not correct! Please try again! or press X to exit\n";
    }

    cout << "Successfully changed password!\n";
    cout<<"--------------"<<endl;
    user_pass[name] = new_pass;
}

void control_table::choosing_operation() {
    start:
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
    else if (current_state == 5) {
        std::cout << "Goodbye!" << std::endl;
        //write all username and password from map to file = "account.txt"
        ofstream file_out;
        file_out.open("account.txt");
        for (auto it = user_pass.begin(); it != user_pass.end(); it++) {
            file_out << it->first << " " << it->second << endl;
        }
        return;
    }
    goto start;
}