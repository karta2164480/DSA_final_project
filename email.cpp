#include "email.h"
#include <assert.h>	//assert()
#include <stdio.h>	//fopen(), FILE

#define MAX_STRING_LEN 100

Email::Email(char* file_path){

	FILE* fp = fopen(file_path, "r");
	assert(fp != NULL);

	char temp[MAX_STRING_LEN];

	fscanf(fp, "From:%s\n", temp);
	string from(temp);
	this->from = from;

	fscanf(fp, "Date:%[^\n]s", temp);
	string date(temp);
	this->date = date;

	fscanf(fp, "Message-ID:%u\n", &message_id);

	fscanf(fp, "Subject:%s\n", temp);
	string subject(temp);
	this->subject = temp;

	fscanf(fp, "To:%s\n", temp);
	string to(temp);
	this->to = to;

	fscanf(fp, "%s", temp);
	string content(temp);
	this->content = content;

	fclose(fp);
}

string& Email::getFrom(){
	return from;
}

string& Email::getTo(){
	return to;
}

unsigned Email::getMessage_ID(){
	return message_id;
}

string& Email::getSubject(){
	return subject;
}

string& Email::getContent(){
	return content;
}
