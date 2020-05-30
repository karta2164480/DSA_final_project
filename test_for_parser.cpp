#include "parser.h"


int main(){

	cout << "Enter content:" << endl;
	string content;
	getline(cin, content);

	string expr;
	cout << "Enter query:" << endl;
	while(cin >> expr){
		Parser parser(expr);
		cout << "Result: " << parser.evaluate(content) << endl;
	}
	return 0;
}
