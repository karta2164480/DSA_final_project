#include "parser.h"
#include <stack>	
#include <vector>
#include <ctype.h>		//isdigit, isalpha
#include <algorithm>	//reverse

class Token{
public:
	string str;
	bool isWord;
	int order;		//bigger -> higher precedence
};

Node* construcNode(vector<Token>& tokens,int *i){
	
	if(tokens[*i].isWord){
		Node *leaf = new Node();
		leaf->value = tokens[*i].str;
		leaf->left = NULL;
		leaf->right = NULL;
		return leaf;
	}

	Node *root = new Node();
	root->value = tokens[*i].str;
	if(root->value == "!"){
		(*i)++;
		root->left = construcNode(tokens, i);
		root->right = NULL;
	}else{
		(*i)++;
		root->left = construcNode(tokens, i);
		(*i)++;
		root->right = construcNode(tokens, i);
	}
	return root;
}

void destroyNode(Node* root){

	if(root->left == NULL && root->right == NULL){
		delete root;
		return;
	}

	if(root->left == NULL){

		destroyNode(root->right);
		delete root;

	}else if(root->right == NULL){

		destroyNode(root->left);
		delete root;

	}else{

		destroyNode(root->right);
		destroyNode(root->left);
		delete root;

	}
}

Parser::~Parser(){
	destroyNode(root);	
}

Parser::Parser(string& expr){

	vector<Token> tokens;

	for(int i = 0; i < expr.length(); i++){

		if(isdigit(expr[i]) || isalpha(expr[i])){

			Token temp;
			temp.isWord = true;

			while((isdigit(expr[i]) || isalpha(expr[i])) && i < expr.length()){
				temp.str.push_back(expr[i]);
				i++;
			}

			tokens.push_back(temp);	

			if(i >= expr.length())
				break;

		}

		Token temp;
		temp.isWord = false;

		switch(expr[i]){
			case '(': {
				temp.str = ")";		//for reverse
				temp.order = 5;
				break;
			}
			case ')': {
				temp.str = "(";
				temp.order = 5;
				break;
			}
			case '!': {
				temp.str = "!";
				temp.order = 3;

				if(!(isdigit(expr[i]) || isalpha(expr[i])))		// case like: !(a|b)
					break;

				i++;
				Token temp2;
				temp2.isWord = true;
				while((isdigit(expr[i]) || isalpha(expr[i])) && i < expr.length()){
					temp2.str.push_back(expr[i]);
					i++;
				}
				i--;
				tokens.push_back(temp2);

				break;
			}
			case '&': {
				temp.str = "&";
				temp.order = 2;
				break;
			}
			case '|': {
				temp.str = "|";
				temp.order = 1;
				break;
			}
		}
		tokens.push_back(temp);
	}

	reverse(tokens.begin(), tokens.end());

	vector<Token> postfix;
	stack<Token> token_stack;

	for(int i = 0; i < tokens.size(); i++){
		if(tokens[i].isWord)
			postfix.push_back(tokens[i]);
		else{
			if(tokens[i].str == ")"){
				while(token_stack.top().str != "("){
					postfix.push_back(token_stack.top());
					token_stack.pop();
				}
				token_stack.pop();
			}else{
				while(!token_stack.empty() && token_stack.top().order >= tokens[i].order){

					if(token_stack.top().order == 5)	// if stack top is "("
						break;

					postfix.push_back(token_stack.top());
					token_stack.pop();
				}
				token_stack.push(tokens[i]);
			}
		}
	}

	while(!token_stack.empty()){
		postfix.push_back(token_stack.top());
		token_stack.pop();
	}

	reverse(postfix.begin(), postfix.end());

	int i = 0;
	root = construcNode(postfix, &i);

#ifdef DEBUG
	cout << "input expr: " << expr << endl;

	cout << "tokenized: " << endl;
	for(int i = 0; i < tokens.size(); i++)
		cout << tokens[i].str << " ";
	cout << endl;

	cout << "prefix: " << endl;
	for(int i = 0; i < postfix.size(); i++)
		cout << postfix[i].str << " ";
	cout << endl;
#endif

}

bool recurEval(Node* root, TrieNode* content){

	if(root->value == "&")
		return (recurEval(root->left, content) && recurEval(root->right, content));
	else if(root->value == "|")
		return (recurEval(root->left, content) || recurEval(root->right, content));
	else if(root->value == "!")
		return !(recurEval(root->left, content));

	/*	leaf node	*/
	else{		

		/*		old method
		regex e("\\b"+root->value+"\\b");
		smatch m;
		return regex_search(content, m, e);
		*/
		
		return search(content, root->value);
		
	}
}

bool Parser::evaluate(TrieNode* content){
	return recurEval(root, content);
}

