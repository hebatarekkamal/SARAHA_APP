#include<iostream>
#include<fstream>   //importing library for file handling
#include<string>
#include<vector>
#include "user.h"

int main()
{
    user u;
    vector<user> users;
    int choice, exit = 0;
    while (exit == 0)
    {
        cout << "\n1. SignIn/LogIn\n2. SignUp/Register\npress any key and enter to exit\n";
        cin >> choice;
        if (choice == 1)
            u.logIn();
        else if (choice == 2)
            u.Register(users);
        else
            exit = 1;
    }
}