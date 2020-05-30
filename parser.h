#define KEYWORD_MAX_LENGTH 21

typedef struct node{
	char value[KEYWORD_MAX_LENGTH];
	node* left;
	node* right;
} Node;

class Parser{
public:
	Parser(string& expression);
	bool evaluate(string& content);
private:
	Node *root
};
