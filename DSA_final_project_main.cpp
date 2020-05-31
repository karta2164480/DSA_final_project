#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include "email.h"
#include "parser.h"

#define MAX_FILE_PATH_LEN 1000

int main()
{

	string input;

	map<unsigned int, Email> ID_Map;
	map<string, vector<Email>> Form_Map;
	map<string, vector<Email>> To_Map;
	list<Email> Date_list;

	int mail_count = 0;

	while (cin >> input)
	{
		if (input.compare("add") == 0)
		{
			char path[MAX_FILE_PATH_LEN];
			scanf("%s", path);
			Email temp(path);

			if (ID_Map.find(temp.getMessage_ID()) == ID_Map.end())
			{


				ID_Map.insert(pair<unsigned int, Email>(temp.getMessage_ID(), temp));
				mail_count++;
				cout << mail_count << "\n";
			}
			else
			{
				cout << "-" << "\n";
			}
		}
		else if (input.compare("remove") == 0)
		{
			int id;
			cin >> id;

			if (ID_Map.find(id) == ID_Map.end())
			{
				cout << "-" << "\n";
			}
			else
			{

				ID_Map.erase(id);
				mail_count--;
				cout << mail_count << "\n";
			}
		}
		else if (input.compare("longest") == 0)
		{
			int max_length = 0;
			int max_id = -1;
			for (map<unsigned int, Email>::iterator it = ID_Map.begin(); it != ID_Map.end(); it++)
			{
				int now_length = (it->second.getLength());
				if (now_length > max_length)
				{
					max_length = now_length;
					max_id = it->second.getMessage_ID();
				}
			}
			if (max_id == -1)
			{
				cout << "-" << "\n";
			}
			else
			{
				cout << max_id << " " << max_length << "\n";
			}
		}
		else if (input.compare("query") == 0)
		{

		}
	}



}