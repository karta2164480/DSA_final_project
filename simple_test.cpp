#include "parser.h"

int main(){

	char file_path[1000];
	printf("Enter file path:\n");
	scanf("%s", file_path);
	Email test(file_path);

	printf("------------------------Email Data-----------------------\n");
	cout << "From: " << test.getFrom() << endl;
	cout << "Date: " <<test.getDate() << endl;
	cout << "Message-ID: " << test.getMessage_ID() << endl;
	cout << "Subject: " << test.getSubject() << endl;
	cout << "To: " << test.getTo() << endl;
	printf("---------------------------------------------------------\n");

	cout << "Enter query:" << endl;
	string expr;
	while(cin >> expr){
		Parser parser(expr);
		cout << "Result: " << parser.evaluate(test) << endl;
	}

}
