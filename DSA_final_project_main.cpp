#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include "email.h"
#include "parser.h"

#define MAX_FILE_PATH_LEN 1000
#define MAX_QUREY_LEN 1000

int main()
{

	string input;

	map<unsigned int, Email> ID_Map;
	map<string, vector<Email>> From_Map;
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

			if (ID_Map.count(temp.getMessage_ID()) == 0) 
			{
				if (From_Map.count(temp.getFrom()) == 0) 
				{
					vector<Email> From_vector;
					From_vector.push_back(temp);
					From_Map.insert(pair<string, vector<Email>>(temp.getFrom(), From_vector));
				}
				else 
				{
					From_Map[temp.getFrom()].push_back(temp);
				}

				if (To_Map.count(temp.getTo()) == 0)
				{
					vector<Email> To_vector;
					To_vector.push_back(temp);
					From_Map.insert(pair<string, vector<Email>>(temp.getTo(), To_vector));
				}
				else
				{
					To_Map[temp.getTo()].push_back(temp);
				}
				//wait for adding into Date_list

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
				//wait for removing from From_map ,To_map ,Date_list
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
			//wait for better data structure improvement
		}
		else if (input.compare("query") == 0)
		{
			
			vector<Email> answer_candidate;
			
			char query[MAX_QUREY_LEN] = { 0 };
			scanf("%s", query);		

			while (query[0] == '-') 
			{
				if (query[1] == 'f')
				{
					char temp[MAX_QUREY_LEN] = { 0 };
					for (int i = 3, j = 0; query[i] != '\"'; i++, j++)
					{
						temp[j] = query[i];
					}
					string From_query(temp);
					if (answer_candidate.empty()) 
					{
						answer_candidate = (From_Map[From_query]);
					}
					else 
					{
						for (vector<Email>::iterator it = answer_candidate.begin(); it != answer_candidate.end(); it++) 
						{
							if (it->getFrom() != From_query) 
							{
								answer_candidate.erase(it);
							}
						}
					}
				}
				else if (query[1] == 't') 
				{
					char temp[MAX_QUREY_LEN] = { 0 };
					for (int i = 3, j = 0; query[i] != '\"'; i++, j++) 
					{
						temp[j] = query[i];
					}
					string To_query(temp);
					if (answer_candidate.empty())
					{
						answer_candidate = (To_Map[To_query]);
					}
					else
					{
						for (vector<Email>::iterator it = answer_candidate.begin(); it != answer_candidate.end(); it++)
						{
							if (it->getTo() != To_query)
							{
								answer_candidate.erase(it);
							}
						}
					}
				}
				else if (query[1] == 'd') 
				{
					char temp1[MAX_QUREY_LEN] = { 0 };
					char temp2[MAX_QUREY_LEN] = { 0 };
					int i = 2;
					for (int j = 0; query[i] != '~'; i++, j++) 
					{
						temp1[j] = query[i];
					}
					i++;
					for (int j = 0; query[i] != 0; i++, j++)
					{
						temp2[j] = query[i];
					}
					string Date_query1(temp1);
					string Date_query2(temp2);
					//wait for Email class change
				}
				scanf("%s", query);
			}
			
			string expression(query);
			Parser parser(expression);

			priority_queue<int> answer_ID;

			for (vector<Email>::iterator it = answer_candidate.begin(); it != answer_candidate.end(); it++) 
			{
				if (parser.evaluate(it->getContent())) 
				{
					answer_ID.push(it->getMessage_ID());
				}
			}

			if (answer_ID.empty()) 
			{
				cout << "-" << "\n";
			}
			else 
			{
				cout << answer_ID.top() << " ";
				//check the priority
				answer_ID.pop();
			}


		}
	}


	//Upper and lower characters change
}