#include "function.h"
#include "account_control.h"
#include "bloomFilter.h"

bool control_table::check_existed_username(string username)
{
    return lookup(bitarray, sz, username);
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

        if (!constraint_check(name) || !password_constraint_check(name) || checkWeakPass(password) || lookup(bitarray, sz, name) || lookup(bitarray, sz, password))
        {
            file_out << name << " " << password << endl;
        }
        else
        {
            insert(bitarray, sz, name);
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