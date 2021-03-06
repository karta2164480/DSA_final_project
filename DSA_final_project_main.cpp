#include <climits>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string>
#include "parser.h"

using namespace std;

#define MAX_QUREY_LEN 1000

struct compare_longest
{
	bool operator()(Email* email1, Email* email2)
	{
		if (email1->getLength() > email2->getLength())
		{
			return 0;
		}
		if (email1->getLength() < email2->getLength())
		{
			return 1;
		}
		if (email1->getMessage_ID() > email2->getMessage_ID())
		{
			return 1;
		}
		if (email1->getMessage_ID() < email2->getMessage_ID())
		{
			return 0;
		}
		return 0;
	}
};


bool compare_date(Email* email1, Email* email2) 
{
	if (email1->getDate() < email2->getDate())
	{
		return 1;

	}
	else if (email1->getDate() > email2->getDate())
	{
		return 0;
	}
	else 
	{
		if (email1->getMessage_ID() < email2->getMessage_ID())
		{
			return 1;
		}
		else 
		{
			return 0;
		} 
	}
}


int main()
{

	string input;

	map<unsigned int, Email*> ID_Map;
	map<string, vector<Email*> > From_Map;
	map<string, vector<Email*> > To_Map;
	list<Email*> Date_list;
	priority_queue<Email*, vector<Email*>, compare_longest > longest_queue;

	int mail_count = 0;

	while (cin >> input)
	{
		if (input.compare("add") == 0)
		{
			string path;
			cin >> path;
			Email *temp;

			char* path_char_array = new char[path.length() + 1];
			strcpy(path_char_array, path.c_str());

			temp = new Email(path_char_array);

			unsigned id = temp->getMessage_ID();

			if (ID_Map.count(id) == 0)
			{
				string from = temp->getFrom();
				
				if (From_Map.count(from) == 0)
				{
					vector<Email*> From_vector;
					From_vector.push_back(temp);
					From_Map[from] = From_vector;
				}
				else 
				{
					From_Map[from].push_back(temp);
				}

				string to = temp->getTo();

				if (To_Map.count(to) == 0)
				{
					vector<Email*> To_vector;
					To_vector.push_back(temp);
					To_Map.insert(pair<string, vector<Email*> >(to, To_vector));
				}
				else
				{
					To_Map[to].push_back(temp);
				}

				longest_queue.push(temp);
				
				Date_list.push_back(temp);

				ID_Map.insert(pair<unsigned int, Email*>(id, temp));

				mail_count++;
				cout << mail_count << "\n";
			}
			else
			{
				cout << "-" << "\n";
			}
			delete path_char_array;
		}
		else if (input.compare("remove") == 0)
		{
			unsigned int id;
			cin >> id;

			if (ID_Map.find(id) == ID_Map.end())
			{
				cout << "-" << "\n";
			}
			else
			{
				Email* wait_to_remove = ID_Map[id];
				string from = wait_to_remove->getFrom();

				for (vector<Email*>::iterator it = From_Map[from].begin(); it != From_Map[from].end(); it++)
				{
					if ((*it)->getMessage_ID() == id) 
					{
						(*it) = From_Map[from].back();
						From_Map[from].pop_back();
						break;
					}
				}

				string to = wait_to_remove->getTo();

				for (vector<Email*>::iterator it = To_Map[to].begin(); it != To_Map[to].end(); it++)
				{
					if ((*it)->getMessage_ID() == id)
					{
						(*it) = To_Map[to].back();
						To_Map[to].pop_back();
						break;
					}
				}

				for (list<Email*>::iterator it = Date_list.begin(); it != Date_list.end(); it++) 
				{
					if ((*it)->getMessage_ID() == id)
					{
						Date_list.erase(it);
						break;
					}
				}

				ID_Map.erase(id);
				mail_count--;
				cout << mail_count << "\n";
			}
		}
		else if (input.compare("longest") == 0)
		{
			if (longest_queue.empty()) 
			{
				cout << "-" << "\n";
			}
			else 
			{
				while ((!longest_queue.empty()) && ID_Map.count((longest_queue.top()->getMessage_ID())) == 0) 
				{
					Email* wait_to_remove = longest_queue.top();
					longest_queue.pop();
					delete wait_to_remove;
				}
				if (longest_queue.empty()) 
				{
					cout << "-" << "\n";
				}
				else 
				{
					cout << longest_queue.top()->getMessage_ID() << " " << longest_queue.top()->getLength() << "\n";
				}
			}
		}
		else if (input.compare("query") == 0)
		{
			
			vector<Email*> answer_candidate;
			
			char query[MAX_QUREY_LEN] = { 0 };
			scanf("%s", query);	

			bool From_To_Date_flag = 0;
			bool fail_flag = 0;

			while (query[0] == '-') 
			{
				From_To_Date_flag = 1;
				
				if (query[1] == 'f')
				{
					char temp[MAX_QUREY_LEN] = { 0 };
					for (int i = 3, j = 0; query[i] != '\"'; i++, j++)
					{
						temp[j] = tolower(query[i]);
					}
					string From_query(temp);
					if (answer_candidate.empty()) 
					{
						answer_candidate = (From_Map[From_query]);
					}
					else 
					{
						vector<Email*>::iterator it = answer_candidate.begin();
						while (it < answer_candidate.end()) 
						{
							if ((*it)->getFrom() != From_query)
							{
								(*it) = answer_candidate.back();
								answer_candidate.pop_back();
							}
							else 
							{
								it++;
							}
						}
					}
					if (answer_candidate.size() == 0) 
					{
						fail_flag = 1;
						break;
					}
				}
				else if (query[1] == 't') 
				{
					char temp[MAX_QUREY_LEN] = { 0 };
					for (int i = 3, j = 0; query[i] != '\"'; i++, j++) 
					{
						temp[j] = tolower(query[i]);
					}
					string To_query(temp);
					if (answer_candidate.empty())
					{
						answer_candidate = (To_Map[To_query]);
					}
					else
					{
						vector<Email*>::iterator it = answer_candidate.begin();
						while (it < answer_candidate.end())
						{
							if ((*it)->getTo() != To_query) 
							{
								(*it) = answer_candidate.back();
								answer_candidate.pop_back();
							}
							else
							{
								it++;
							}
						}
					}
					if (answer_candidate.size() == 0)
					{
						fail_flag = 1;
						break;
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

					long long int Date_query1 = atoll(temp1);
					long long int Date_query2 = atoll(temp2);

					if (Date_query2 == 0) 
					{
						Date_query2 = LLONG_MAX;
					}

					if (answer_candidate.empty())
					{
						for (list<Email*>::iterator it = Date_list.begin(); it != Date_list.end(); it++)
						{
							if ((*it)->getDate() >= Date_query1 && (*it)->getDate() <= Date_query2)
							{
								answer_candidate.push_back(*it);
							}
						}
					}
					else 
					{
						vector<Email*>::iterator it = answer_candidate.begin();
						while (it < answer_candidate.end())
						{
							if ((*it)->getDate() < Date_query1 || (*it)->getDate() > Date_query2)
							{
								(*it) = answer_candidate.back();
								answer_candidate.pop_back();
							}
							else
							{
								it++;
							}
						}
					}
					if (answer_candidate.size() == 0)
					{
						fail_flag = 1;
						break;
					}
				}
				scanf("%s", query);
			}
			if (fail_flag == 1) 
			{
				scanf("%s", query);
				while (query[0] == '-') 
				{
					scanf("%s", query);
				}
				//mean to avoid the expression is "add,remove,longest,query"
			}

			if (fail_flag == 0) 
			{
				for (int i = 0; query[i] != 0; i++) 
				{
					query[i] = tolower(query[i]);
				}
				string expression(query);
				Parser parser(expression);

				priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int> > answer_ID;

				if (From_To_Date_flag == 1)
				{
					for (vector<Email*>::iterator it = answer_candidate.begin(); it != answer_candidate.end(); it++)
					{
						if (parser.evaluate((*it)->getContent()))
						{
							answer_ID.push((*it)->getMessage_ID());
						}
					}
				}
				else
				{
					for (map<unsigned int, Email*>::iterator it = ID_Map.begin(); it != ID_Map.end(); it++)
					{
						if (parser.evaluate((*(it->second)).getContent()))
						{
							answer_ID.push((*(it->second)).getMessage_ID());
						}
					}
				}


				if (answer_ID.empty())
				{
					cout << "-" << "\n";
				}
				else
				{
					while (!answer_ID.empty())
					{
						unsigned int answer = answer_ID.top();
						answer_ID.pop();
						if (!answer_ID.empty()) 
						{
							cout << answer << " ";
						}
						else 
						{
							cout << answer;
						}
					}
					cout << "\n";
				}
			}
			else 
			{
				cout << "-" << "\n";
			}


		}
	}
}
