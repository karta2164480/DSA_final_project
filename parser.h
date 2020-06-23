#include <string>
#include "email.h"

using namespace std;

class Node{
public:
	string value;
	Node* left;
	Node* right;
};

class Parser{
public:
	Parser(string& expression);
	~Parser();
	bool evaluate(string content);
private:
	Node *root;
};
