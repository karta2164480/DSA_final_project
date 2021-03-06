#include <climits>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string>
#include <set>
#include "parser.h"

using namespace std;

#define MAX_QUREY_LEN 1000

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

struct Longest {
	unsigned int id;
	int length;
	bool operator < (const Longest& a) const {
		if (this->length > a.length) {
			return true;
		} else if (this->length == a.length && this->id < a.id) {
			return true;
		} else {
			return false;
		}
	}
};

int main()
{

	string input;

	map<unsigned int, Email*> ID_Map;
	map<string, vector<Email*> > From_Map;
	map<string, vector<Email*> > To_Map;
	list<Email*> Date_list;
	set<Longest> longest;

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

			if (ID_Map.count(temp->getMessage_ID()) == 0) 
			{
				if (From_Map.count(temp->getFrom()) == 0)
				{
					vector<Email*> From_vector;
					From_vector.push_back(temp);
					From_Map[temp->getFrom()] = From_vector;
				}
				else 
				{
					From_Map[temp->getFrom()].push_back(temp);
				}

				if (To_Map.count(temp->getTo()) == 0)
				{
					vector<Email*> To_vector;
					To_vector.push_back(temp);
					To_Map.insert(pair<string, vector<Email*> >(temp->getTo(), To_vector));
				}
				else
				{
					To_Map[temp->getTo()].push_back(temp);
				}
				
				Date_list.push_back(temp);
				ID_Map.insert(pair<unsigned int, Email*>(temp->getMessage_ID(), temp));

				longest.insert({temp->getMessage_ID(), temp->getLength()});
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
				
				for (vector<Email*>::iterator it = From_Map[wait_to_remove->getFrom()].begin(); it != From_Map[wait_to_remove->getFrom()].end(); it++)
				{
					if ((*it)->getMessage_ID() == id) 
					{
						From_Map[wait_to_remove->getFrom()].erase(it);
						break;
					}
				}

				for (vector<Email*>::iterator it = To_Map[wait_to_remove->getTo()].begin(); it != To_Map[wait_to_remove->getTo()].end(); it++)
				{
					if ((*it)->getMessage_ID() == id)
					{
						To_Map[wait_to_remove->getTo()].erase(it);
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

				longest.erase({id, wait_to_remove->getLength()});
				ID_Map.erase(id);
				delete wait_to_remove;
				mail_count--;
				cout << mail_count << "\n";
			}
		}
		else if (input.compare("longest") == 0)
		{
			if (longest.size() > 0) {
				Longest to_be_selected = *longest.begin();
				cout << to_be_selected.id << " " << to_be_selected.length << "\n";
			} else {
				cout << "-" << "\n";
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
								it = answer_candidate.erase(it);
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
								it = answer_candidate.erase(it);
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
						Date_list.sort(compare_date);

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
								it = answer_candidate.erase(it);
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
