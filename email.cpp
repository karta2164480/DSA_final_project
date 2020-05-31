#include "email.h"
#include <stdio.h>	//FILE
#include <string.h>	//strcspn

#define MAX_STRING_LEN 1000

Email::Email(char* file_path) {

	FILE* fp = fopen(file_path, "r");

	char temp[MAX_STRING_LEN];

	fscanf(fp, "%s ", temp);
	fgets(temp, MAX_STRING_LEN, fp);
	temp[strcspn(temp, "\n")] = 0;
	string from(temp);
	this->from = from;

	fscanf(fp, "%s ", temp);
	fgets(temp, MAX_STRING_LEN, fp);
	temp[strcspn(temp, "\n")] = 0;
	string date(temp);
	this->date = date;

	fscanf(fp, "%s %u\n", temp, &message_id);

	fscanf(fp, "%s ", temp);
	fgets(temp, MAX_STRING_LEN, fp);
	temp[strcspn(temp, "\n")] = 0;
	string subject(temp);
	this->subject = temp;

	fscanf(fp, "%s ", temp);
	fgets(temp, MAX_STRING_LEN, fp);
	temp[strcspn(temp, "\n")] = 0;
	string to(temp);
	this->to = to;

	string content;
	fscanf(fp, "%s ", temp);
	while (fgets(temp, MAX_STRING_LEN, fp))
		content += temp;
	this->content = content;

	int length = 0;
	for (string::iterator it = content.begin(); it != content.end(); it++) 
	{
		if (isalnum((int)*it)) 
		{
			length++;
		}
	}
	this->length = length;

	fclose(fp);
}

string& Email::getFrom() {
	return from;
}

string& Email::getDate() {
	return date;
}

string& Email::getTo() {
	return to;
}

unsigned int Email::getMessage_ID() {
	return message_id;
}

string& Email::getSubject() {
	return subject;
}

string& Email::getContent() {
	return content;
}

int Email::getLength() 
{
	return length;
}