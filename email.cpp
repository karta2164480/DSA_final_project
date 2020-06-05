#include "email.h"
#include <stdio.h>	//FILE
#include <string.h>	//strcspn, strcpy
#include <stdlib.h>	//strtoll, strtoul
#include <ctype.h>	//isalpha, isdigit, tolower

#define MAX_STRING_LEN 1000

void formatDate(char* raw, long long* date){
	char day[3];
	char year[50];
	char time[6];
	char month[20];
	sscanf(raw, " %s %s %s at %s", day, month, year, time);
	
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
			break; case 'S':
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

	char *eptr;
	*date = strtoll(year, &eptr, 10);
}

void formatContent(string& content, TrieNode *root, int *length){

	string temp;
	for(int i = 0; i < content.size(); i++){
		if(isalpha(content[i])){
			temp.push_back(tolower(content[i]));
			(*length)++;
		}else if(isdigit(content[i])){
			temp.push_back(content[i]);	
			(*length)++;
		}else{
			trie_insert(root, temp);
			temp.clear();
		}
	}

}

Email::Email(char* file_path){

	FILE* fp = fopen(file_path, "r");

	char raw[MAX_STRING_LEN];
	char temp[MAX_STRING_LEN];

	fgets(raw, MAX_STRING_LEN, fp);					//From:
	raw[strcspn(raw, "\n")] = 0;
	strcpy(temp, raw + sizeof(char) * 6);
	from = string(temp);
	for(int i = 0; i < from.length(); i++)				//To lower case
		from[i] = tolower(from[i]);

	fgets(raw, MAX_STRING_LEN, fp);					//Date:
	raw[strcspn(raw, "\n")] = 0;
	strcpy(temp, raw + sizeof(char) * 6);
	formatDate(temp, &date);

	fgets(raw, MAX_STRING_LEN, fp);					//Message-ID:
	raw[strcspn(raw, "\n")] = 0;
	strcpy(temp, raw + sizeof(char) * 12);
	char *eptr;
	message_id = strtoul(temp, &eptr, 10);

	fgets(raw, MAX_STRING_LEN, fp);					//Subject:
	raw[strcspn(raw, "\n")] = 0;
	char temp_subject[MAX_STRING_LEN] = {'\0'};			//For empty subject
	strcpy(temp_subject, raw + sizeof(char) * 9);
	subject = string(temp_subject);

	fgets(raw, MAX_STRING_LEN, fp);					//Date:
	raw[strcspn(raw, "\n")] = 0;
	strcpy(temp, raw + sizeof(char) * 4);
	to = string(temp);
	for(int i = 0; i < to.length(); i++)				//To lower case
		to[i] = tolower(to[i]);

	string content;
	fscanf(fp, "%s ", temp);					//Content:	
	while(fgets(temp, MAX_STRING_LEN, fp))
		content += string(temp);

	contentTrie = getNode();					//Construct trie
	length = 0;
	formatContent(content, contentTrie, &length);

	int subject_len;						//Subject need to be searched
	formatContent(subject, contentTrie, &subject_len);

	fclose(fp);
}

Email::~Email(){
	trie_release(contentTrie);
}

string& Email::getFrom(){
	return from;
}

long long Email::getDate() {
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

TrieNode* Email::getContent(){
	return contentTrie;
}

int Email::getLength() 
{
	return length;
}
