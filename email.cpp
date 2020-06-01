#include "email.h"
#include <stdio.h>	//FILE
#include <string.h>	//strcspn, sscanf

#define MAX_STRING_LEN 1000

void formatDate(char* raw, string& date){
	char day[3];
	char year[50];
	char time[6];
	char min[3];
	char month[20];
	sscanf(raw, " %s %s %s at %s", day, month, year, time);
	printf("day:%s, month:%s, year:%s, time:%s\n", day, month, year, time);
	if(strlen(day) == 1){
		day[2] = '\0';
		day[1] = day[0];
		day[0] = '0';
	}
	switch(month[0]){
		case 'J':
			if(month[1] == 'a'){
				month[0] = '0'; month[1] = '1'; month[2] = '\0';
			}else if(month[2] == 'n'){
				month[0] = '0'; month[1] = '6'; month[2] = '\0';
			}else{
				month[0] = '0'; month[1] = '7'; month[2] = '\0';
			}
			break;
		case 'F':
			month[0] = '0'; month[1] = '2'; month[2] = '\0';
			break;
		case 'M':
			if(month[2] == 'r'){
				month[0] = '0'; month[1] = '3'; month[2] = '\0';
			}else{
				month[0] = '0'; month[1] = '5'; month[2] = '\0';
			}
			break;
		case 'A':
			if(month[1] == 'p'){
				month[0] = '0'; month[1] = '4'; month[2] = '\0';
			}else{
				month[0] = '0'; month[1] = '8'; month[2] = '\0';
			}
			break;
		case 'S':
			month[0] = '0'; month[1] = '9'; month[2] = '\0';
			break;
		case 'O':
			month[0] = '1'; month[1] = '0'; month[2] = '\0';
			break;
		case 'N':
			month[0] = '1'; month[1] = '1'; month[2] = '\0';
			break;
		case 'D':
			month[0] = '1'; month[1] = '2'; month[2] = '\0';
			break;
	}

	time[2] = time[3];
	time[3] = time[4];
	time[4] = '\0';

	strcat(year, month);
	strcat(year, day);
	strcat(year, time);
	date += string(year);
}

Email::Email(char* file_path){

	FILE* fp = fopen(file_path, "r");

	char temp[MAX_STRING_LEN];

	fscanf(fp, "%s ", temp);					//From:
	fgets(temp, MAX_STRING_LEN, fp);
	temp[strcspn(temp, "\n")] = 0;
	string from(temp);
	this->from = from;

	fscanf(fp, "%s ", temp);					//Date:	
	fgets(temp, MAX_STRING_LEN, fp);
	temp[strcspn(temp, "\n")] = 0;
	string date;
	formatDate(temp, date);
	this->date = date;

	fscanf(fp, "%s %u\n", temp, &message_id);	//Message-ID:

	fscanf(fp, "%s ", temp);					//Subject:	
	fgets(temp, MAX_STRING_LEN, fp);
	temp[strcspn(temp, "\n")] = 0;
	string subject(temp);
	this->subject = temp;

	fscanf(fp, "%s ", temp);					//To:	
	fgets(temp, MAX_STRING_LEN, fp);
	temp[strcspn(temp, "\n")] = 0;
	string to(temp);
	this->to = to;

	string content;
	fscanf(fp, "%s ", temp);					//Content:	
	while(fgets(temp, MAX_STRING_LEN, fp))
		content += temp;
	this->content = content;

	fclose(fp);
}

string& Email::getFrom(){
	return from;
}

string& Email::getDate(){
	return date;
}

string& Email::getTo(){
	return to;
}

unsigned int Email::getMessage_ID(){
	return message_id;
}

string& Email::getSubject(){
	return subject;
}

string& Email::getContent(){
	return content;
}
