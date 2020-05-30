#include <iostream>

#define KEYWORD_MAX_LENGTH 21

using namespace std;

typedef struct node{
	string value;
	node* left;
	node* right;
} Node;

class Parser{
public:
	Parser(string& expression);
	bool evaluate(string& content);
private:
	Node *root;
};
