#include<iostream>
#include<fstream>   //importing library for file handling
#include<string>
#include<stack>
#include<vector>
#include "user.h"
using namespace std;

/****************favourite meassages**************/


void user::showall(deque<string>& fav_deque) {
    if (fav_deque.size() == 0)
    {
        cout << "list is empty" << endl;
        return;
    }
    for (int i = 0;i < fav_deque.size();i++)
        cout << fav_deque[i] << endl;

}
void user::readfile(deque<string>& fav_deque, string path) {
    fstream favfile;
    favfile.open(path.c_str());
    string allines;
    if (!favfile.peek())
    {

        return;
    }
    while (!favfile.eof()) {
        getline(favfile, allines);
        fav_deque.push_back(allines);
    }
   //favfile.close();
}
void user:: addfav(string m, deque<string>& fav_deque, string path) {
    fav_deque.push_back(m);
    fstream favfile;
    favfile.open(path, ios::app);
    favfile << m << endl;
    favfile.close();
}
void user::deleteoldest(deque<string>& fav_deque, string path) {

    if (fav_deque.empty()) {
        showall(fav_deque);
        return;
    }
    else {
        string lastline = fav_deque.front();
        fav_deque.pop_front();
        string lines;
        fstream favfile;
        ofstream tempp;
        favfile.open(path);
        tempp.open("tempp.txt");
        while (!favfile.eof()) {
            getline(favfile, lines);
            if (lines == lastline) {
                getline(favfile, lines);
                tempp << lines;
                continue;
            }
            else
            {
                tempp << lines << endl;
            }
        }
        favfile.close();
        tempp.close();
        const char* ptr = path.c_str();
        remove(ptr);
        rename("tempp.txt", ptr);
    }


}
//set new elements of deque for new user
void user:: delete_deque_element(deque<string>& fav_deque) {
    while (!fav_deque.empty()) {
        fav_deque.pop_back();
    }
}
/*end of fav function*/

string user:: generate_id(string file_path) {
    string line;
    string last_line;
    try
    {
        ifstream my_file(file_path);//read
        if (my_file.is_open())
        {
            int i = 0;
            while (getline(my_file, line))
            {
                i++;
            }
            i++;
            my_file.close();
            last_line = to_string(i);
        }
        else
        {
            cout << "Unable to open file" << endl;
        }
    }
    catch (exception& e)
    {
        cout << "standard exception " << e.what() << endl;
    }

    return last_line;
}

void user:: send_message(string text, string file_path)

{
    try
    {
        ofstream my_file;//write
        my_file.open(file_path, ios::out | ios::app);
        if (file_path != username + '1') {
            my_file << "Message of User ID : ";
            my_file << user_id + "\n";
        }
        my_file << text + "\n";
        my_file.close();
        if (file_path != username + '1')
            cout << "Message is sent successfully" << endl;
    }
    catch (exception& e)
    {
        cout << "standard exception " << e.what() << endl;
    }
}
stack<string> user::view_all_send_message(string file_path)
{
    stack<string>filelines;
    string line;
    try
    {
        ifstream my_file(file_path);//read

        if (my_file.is_open())
        {
            while (getline(my_file, line))
            {
                filelines.push(line);
            }
            my_file.close();
        }
        else
        {
            cout << "Unable to open file" << endl;
        }
    }
    catch (exception& e)
    {
        cout << "standard exception " << e.what() << endl;
    }

    return filelines;
}
void user::Undo_last_sent_message(string file_path, string val)
{
    string line;
    ifstream myfile2; //for reading records
    myfile2.open(file_path);

    ofstream temp;
    temp.open("temp.txt");
    while (getline(myfile2, line))
    {
        if (line != val)
            temp << line << endl;
        else
        {
            continue;
        }
    }
    myfile2.close();
    temp.close();
    const char* p = file_path.c_str();
    remove(p);
    rename("temp.txt", p);

}
vector<string> user::view_all_recieved_message(string file_path)
{
    vector<string>filelines;
    string line;
    try
    {
        ifstream my_file(file_path);//read

        if (my_file.is_open())
        {
            while (getline(my_file, line))
            {
                filelines.push_back(line);
            }
            my_file.close();
        }
        else
        {
            cout << "Unable to open file" << endl;
        }
    }
    catch (exception& e)
    {
        cout << "standard exception " << e.what() << endl;
    }

    return filelines;
}

void user::Logic() {
    int n;
    deque<string>contact_name;
    string text;
    while (true)
    {
        cout << "To send messages press 1" << endl <<
            "To view all messages from latest to oldest press 2" << endl <<
            "To undo last sent  message press 3 " << endl <<
            "To view all received messages from specific contact press 4 " << endl <<
            "To view all favourite messages  press 5 " << endl <<
            "To add contact to your bucket press 6 " << endl <<
            "To view all contact  press 7 " << endl <<
            "To search about specific contact press 8 " << endl <<
            "To Exit press 9 " << endl;
        cin >> n;
        if (n == 1)
        {
            bool flag = false;
            string contact;
            cout << "Enter contact Name" << endl;
            cin >> contact;

            for (int i = 0;i < contact_buket.size();i++) {
                if (contact_buket[i] == contact) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                //contact_name.push_front(contact);
                cout << "Enter Your Message" << endl;
                cin >> ws;
                getline(cin, text);
                last_mess = text;
                send_message(text, contact);
                send_message(text, username + '1');
            }
            else {
                cout << "User Not Found !!" << endl;
            }

        }
        else if (n == 2)
        {
            int j = 0;
            stack<string>file_lines = view_all_send_message(username + '1');
            for (int i = 0; i < file_lines.size(); i++)
            {
                cout << file_lines.top() << endl;
                file_lines.pop();
            }

        }
        else if (n == 3)
        {
            Undo_last_sent_message(username + '1', last_mess);
        }
        else if (n == 4)
        {
            vector<string> check;
            vector<string>rec = view_all_recieved_message(username);
            cout << "Enter Id of the contact you want to see his message " << endl;
            char x; cin >> x;
            int l = 0;
            for (int i = 0; i < rec.size(); i += 2) {
                if (i < rec.size()) {
                    string str = rec[i];
                    if (str[str.size() - 1] == x)
                    {
                        cout << ++l << " : " << rec[i + 1] << endl;
                        check.push_back(rec[i + 1]);
                    }
                }

            }
            // put a message in favorites.
            if (!check.empty()) {
                cout << "if you want to add any message to favourite list enter **yes**" << endl;
                string answer;
                cin >> answer;
                while (answer == "yes") {
                    cout << "\nenter number of message you want to add it to favourite list" << endl;
                    int num;
                    cin >> num;



                    while (num - 1 > check.size())
                    {
                        cout << "enter right number ";
                        cin >> num;
                    }

                    addfav(check[num - 1], favourite_deque, username + "fav.txt");
                    cout << "if you want to add another message to favourite list enter yes" << endl;

                    cin >> answer;
                }

            }
        }
        else if (n == 5) {
            showall(favourite_deque);

            // remove the oldest message from favorites
            cout << "press 1 if you want to delete the oldest message" << endl;
            int answeer;
            cin >> answeer;
            if (answeer == 1)
            {
                deleteoldest(favourite_deque, username + "fav.txt");
                showall(favourite_deque);
            }

        }

        else if (n == 6) {
            add_contact();

        }
        else if (n == 7) {
            show_all_contact();

        }
        else if (n == 8) {
            search_about_specific_contact();
        }

        else if (n == 9) {
            delete_deque_element(favourite_deque);
            break;
        }

    }
}
int tm;

void user:: valid(string str) //function declaration for keeping records   
{
    string dir, user;
    ifstream file;
    dir = str + ".txt";
    file.open(dir.c_str());
    if (!file.is_open() && file.fail())
        return;
    else
    {
        tm++;
        if (tm == 3)
        {
            cout << "\nThis username already exists\nPlease try Again.";
            return;
        }
        cout << "\nThis username already exists!\nCreate a username:";
        cin >> username;
        valid(username);
    }
}

void user:: logIn()
{
    
    string usern, pw;
    ifstream filei;
    cout << "Enter your username:";
    cin >> username;
    cout << "\nEnter your password:";
    cin >> password;
    fname = username + ".txt";
    filei.open(fname.c_str());
    if (!filei.is_open() && filei.fail())
    {
        cout << "\nYou are not registered, please register before logging in.\n";
        filei.close();
        return;
    }
    getline(filei, usern);
    getline(filei, pw);
    if (username == usern && password == pw)
    {
        cout << "\nYou are successfully logged in:)\n";

        readfile(favourite_deque, usern + "fav.txt");//fav
        readfile(contact_buket, usern + "contact.txt");
        Logic();
        filei.close();
    }
    else
    {
        cout << "\nWrong username or password!\nPlease try Again.\n";
    }
    cout << endl;

}
void user::Register(vector<user> users)
{
    ofstream fileo;
    cout << "\nCreate a username:";
    cin >> username;
    tm = 0;
    valid(username);
    if (tm >= 3)
        return;
    cout << "\nCreate a password:";
    cin >> password;
    fname = username + ".txt";
    user_id = generate_id("ID_File.txt");
    ofstream my_file;//write
    my_file.open("ID_File.txt", ios::out | ios::app);
    my_file << user_id + "\n";
    my_file.close();

    fileo.open(fname.c_str());
    fileo << username << endl << password << endl << user_id << endl;
    
    cout << "\nYou are successfully registered:)";
    ofstream fileof_contact(username + "contact.txt");
    ofstream favourite(username + "fav.txt");
    fileo.close();



}

void user::add_contact() {
    string con_name;
    cout << "Enter contact Name" << endl;
    cin >> con_name;
    ofstream fileof_contact ;
    fileof_contact.open(username + "contact.txt",ios::app);
    fileof_contact << con_name<<endl;
    contact_buket.push_back(con_name);
   
};
void user::show_all_contact() {
    for (int i = 0;i < contact_buket.size();i++) {
        cout << contact_buket[i] << endl;
    }
};
void user::readfile(vector<string>& contact_vector, string path) {
    fstream filee;
    filee.open(path);
    string allines;
    if (!filee.peek())
    {

        return;
    }
    while (!filee.eof()) {
        getline(filee, allines);
        contact_vector.push_back(allines);
    }
   // filee.close();
}
void user::search_about_specific_contact() {
    bool flag = false;
    cout << "enter the contact name " << endl;
    string name_search;
    cin >> name_search;
    for (int i = 0; i < contact_buket.size(); i++) {
        if (contact_buket[i] == name_search) {
            cout <<"Contact is found" << endl;
            flag = true;
            break;
        }
        
    }
    if(!flag)
   cout << "NOT FOUND ";
    
};