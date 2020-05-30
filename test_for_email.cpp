#include "email.h"

int main(int argc, char* argv[]){
	char* file_path = argv[1];
	Email test(file_path);
	cout << "From: " << test.getFrom() << endl;
	cout << "Date: " <<test.getDate() << endl;
	cout << "Message-ID: " << test.getMessage_ID() << endl;
	cout << "Subject: " << test.getSubject() << endl;
	cout << "To: " << test.getTo() << endl;
	cout << "Content:\n" << test.getContent();
	return 0;
}
