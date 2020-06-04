#include <iostream>	//string
#include <map>		//for content
#include "trie.h"

using namespace std;

class Email{
public:
	Email(char* file_path);
	~Email();
	string& getFrom();
	long long getDate();
	unsigned int getMessage_ID();
	string& getSubject();
	string& getTo();
	int getLength();
	TrieNode *getContent();
private:
	string from;
	string to;
	long long date;
	unsigned int message_id;
	string subject;
	int length;
	TrieNode *contentTrie;
};
