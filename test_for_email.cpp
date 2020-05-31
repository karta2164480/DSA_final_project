#include "email.h"

int main(){
	char file_path[1000];
	printf("Enter file path: ");
	while(scanf("%s", file_path) != 0){
		Email test(file_path);
		cout << "From: " << test.getFrom() << endl;
		cout << "Date: " <<test.getDate() << endl;
		cout << "Message-ID: " << test.getMessage_ID() << endl;
		cout << "Subject: " << test.getSubject() << endl;
		cout << "To: " << test.getTo() << endl;
		cout << "Content:\n" << test.getContent();
	}
	return 0;
}
