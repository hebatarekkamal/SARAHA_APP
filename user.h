#include <string>
#include <vector>
#include <stack>
#include<iostream>
#include<fstream>   //importing library for file handling
#include<string>
#include<vector>

using namespace std;
#pragma once
class user
{
public:

	int tm;;
	vector<string>contact_buket;
	vector<string>v;
	string last_con;
	string last_mess;
	string username, password, fname, user_id;
	deque<string> favourite_deque;
public:
	void showall(deque<string>& fav_deque);
	void readfile(deque<string>& fav_deque, string path);
	void addfav(string m, deque<string>& fav_deque, string path);
	void deleteoldest(deque<string>& fav_deque, string path);
	void delete_deque_element(deque<string>& fav_deque);
	string generate_id(string file_path);
	void send_message(string text, string file_path);
	stack<string> view_all_send_message(string file_path);
	void Undo_last_sent_message(string file_path, string val);
	vector<string> view_all_recieved_message(string file_path);
	void Logic();
	void valid(string str);
	void logIn();
	void Register(vector<user> users);
	void add_contact();
	void show_all_contact();
	void readfile(vector<string>& contact_vector, string path);
	void search_about_specific_contact();
};

