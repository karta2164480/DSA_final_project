#include <iostream>	//string
#include <map>		//for content
#include "trie.h"

using namespace std;

class Email{
public:
	Email(char* file_path);
	~Email();
	string& getFrom();
	string& getDate();
	unsigned int getMessage_ID();
	string& getSubject();
	string& getTo();
	TrieNode *getContent();
private:
	string from;
	string to;
	string date;
	unsigned int message_id;
	string subject;
	TrieNode *contentTrie;
};
