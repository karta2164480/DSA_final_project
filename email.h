#include <iostream>	//string
using namespace std;

class Email{
public:
	Email(char* file_path);
	string& getFrom();
	string& getDate();
	unsigned int getMessage_ID();
	string& getSubject();
	string& getTo();
	string& getContent();
private:
	string from;
	string to;
	string date;
	unsigned int message_id;
	string subject;
	string content;
};
