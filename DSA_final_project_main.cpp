#include <iostream>
#include "email.h"
#define MAX_STRING_LEN 1000

int main() 
{
	
	string input;

	while (cin >> input) 
	{
		if (input.compare("add") == 0)
		{
			char path[MAX_STRING_LEN];
			scanf("%s", path);
			Email temp(path);

		}
		else if (input.compare("remove") == 0)
		{

		}
		else if (input.compare("longest") == 0)
		{

		}
		else if (input.compare("query") == 0)
		{

		}
	}



}