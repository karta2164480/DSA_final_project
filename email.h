#include <iostream>	//string
using namespace std;

class Email{
public:
	Email(char* file_path);
	string& getFrom();
	string& getTo();
	unsigned getMessage_ID();
	string& getSubject();
	string& getContent();
private:
	string from;
	string to;
	string date;
	unsigned message_id;
	string subject;
	string content;
};
