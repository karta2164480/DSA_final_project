#include "string.h"		//strtok
#include <map>			//map
#include <vector>		//vector
#include <algorithm>	//sort
#include "email.h"		//email 
#include "parser.h"		//parser

#define MAX_STRING_LENGTH 10000

int main(){

	string opr;
	unsigned int to_delete_id;
	char file_path[MAX_STRING_LENGTH];
	char query_filter[MAX_STRING_LENGTH];

	/*	main data structure */
	map< unsigned int, Email* >	id_map;
	map< string, map< string, multimap< long long, Email* > > > from_to_date_map;
	map< string, multimap< long long, Email* > > to_date_map;
	multimap< long long, Email* > date_map;
	map< int, map< int, int > > length_id_map;

	int cnt = 0;

	while(cin >> opr){
		switch(opr[0]){

			case 'a': {		//add

				cin >> file_path;

				Email *mail = new Email(file_path);
				bool duplicated = false;

				if(id_map[mail->getMessage_ID()] != NULL)
					duplicated = true;

				if(duplicated){
					cout << "-" << endl;
					delete mail;
				}else{
					id_map[mail->getMessage_ID()] = mail;
					pair< long long, Email* > mp(mail->getDate(), mail);
					from_to_date_map[mail->getFrom()][mail->getTo()].insert(mp);
					to_date_map[mail->getTo()].insert(mp);
					date_map.insert(mp);
					length_id_map[mail->getLength()][mail->getMessage_ID()] = 1;	//1 means exist
					cnt++;
					cout << cnt << endl;
				}
				break;
			}

			case 'r': {		//remove

				cin >> to_delete_id;

				bool found = false;
				Email *target = id_map[to_delete_id];

				if(target != NULL){

					found = true;

					from_to_date_map[target->getFrom()][target->getTo()].erase(target->getDate());
					if(from_to_date_map[target->getFrom()][target->getTo()].empty()){
						from_to_date_map[target->getFrom()].erase(target->getTo());
						if(from_to_date_map[target->getFrom()].empty())
							from_to_date_map.erase(target->getFrom());
					}

					pair< multimap< long long, Email* >::iterator, 
							multimap< long long, Email* >::iterator > ret;
					ret = to_date_map[target->getTo()].equal_range(target->getDate());
					multimap< long long, Email* >::iterator it;
					if(ret.first == ret.second){
						to_date_map[target->getTo()].erase(ret.first);
						to_date_map.erase(target->getTo());
					}else{
						for(it = ret.first; it != ret.second; ++it){
							if(it->second->getMessage_ID() == to_delete_id){
								to_date_map[target->getTo()].erase(it);
								break;
							}
						}
					}
						
					id_map.erase(target->getMessage_ID());

					ret = date_map.equal_range(target->getDate());
					for(it = ret.first; it != ret.second; ++it){
						if(it->second->getMessage_ID() == to_delete_id){
							date_map.erase(it);
							break;
						}
					}

					length_id_map[target->getLength()].erase(target->getMessage_ID());
					if(length_id_map[target->getLength()].empty())
						length_id_map.erase(target->getLength());

					delete target;
					cnt--;
					cout << cnt << endl;
				}

				if(!found)
					cout << "-" << endl;
				break;
			}

			case 'l': {		//longest

				if(cnt == 0)
					cout << "-" << endl;
				else{
					map< int, map< int, int > >::reverse_iterator rit = length_id_map.rbegin();
					cout << (rit->second).begin()->first << " " << rit->first << endl;
				}
				break;
			}	

			case 'q': {		//query

				fgets(query_filter, MAX_STRING_LENGTH, stdin);

				if(cnt == 0){
					cout << "-" << endl;
					break;
				}

				bool checkFrom = false, checkTo = false, checkDate = false;
				string from, to, expr;
				long long start_date, end_date;
				char d1[MAX_STRING_LENGTH], d2[MAX_STRING_LENGTH];
				int d1cnt = 0, d2cnt = 0;
				char *token = strtok(query_filter, " \n");

				while(token != NULL){
					if(token[0] == '-' && token[1] != 'd'){
						string temp;
						for(int i = 2; i < strlen(token); i++){
							if(isalpha(token[i]))
								temp.push_back(tolower(token[i]));
							else if(isdigit(token[i]))
								temp.push_back(token[i]);
						}
						switch(token[1]){
							case 'f':
								checkFrom = true;
								from = temp;
								break;
							case 't':
								checkTo = true;
								to = temp;
								break;
						}
					}else if(token[0] == '-' && token[1] == 'd'){
						checkDate = true;
						bool first = true;
						for(int i = 2; i < strlen(token); i++){

							if(token[i] == '~'){
								first = false;
								continue;
							}

							if(first){
								d1[d1cnt] = token[i];
								d1cnt++;
							}
							else{
								d2[d2cnt] = token[i];
								d2cnt++;
							}
						}
						char *eptr;
						if(d1cnt == 0)
							start_date = 0;
						else{
							start_date = strtoll(d1, &eptr, 10);
						}
						if(d2cnt == 0)
							end_date = 500000000000;	//Bigger than all valid date
						else{
							end_date = strtoll(d2, &eptr, 10);
						}
					}else{
						for(int i = 0; i < strlen(token); i++){
							if(isalpha(token[i]))
								expr.push_back(tolower(token[i]));
							else
								expr.push_back(token[i]);
						}
					}
					token = strtok(NULL, " \n");
				}

				Parser parser(expr);
				vector< unsigned int > chosen;
				bool need_sort = true;

				vector< multimap< long long, Email* >* > search_list;

				if(checkFrom){

					if(checkTo)
						search_list.push_back(&from_to_date_map[from][to]);
					else{
						map< string, multimap< long long, Email* > >::iterator it, end;
						it = from_to_date_map[from].begin();
						end = from_to_date_map[from].end();
						for(; it != end; ++it)
							search_list.push_back(&(it->second));
					}

				}else if(checkTo){
					search_list.push_back(&to_date_map[to]);
				}else{
					search_list.push_back(&date_map);
				}
				
				if(checkDate){

					for(int i = 0; i < search_list.size(); i++){
						multimap< long long, Email* >::iterator it, end;
						it = search_list[i]->lower_bound(start_date);
						end = search_list[i]->upper_bound(end_date);
						for(; it != end; ++it)
							if(parser.evaluate(it->second->getContent()))
								chosen.push_back(it->second->getMessage_ID());
					}
					/*
					if(has_filtered){
						for(int i = 0; i < search_list.size(); i++){
							map< long long, Email* >::iterator it, end;
							it = search_list[i]->lower_bound(start_date);
							end = search_list[i]->upper_bound(end_date);
							for(; it != end; ++it)
								if(parser.evaluate(it->second->getContent()))
									chosen.push_back(it->second->getMessage_ID());
						}
					}else{
						multimap< long long, Email* >::iterator it, end;
						it = date_map.lower_bound(start_date);
						end = date_map.lower_bound(end_date);
						for(; it != end; ++it)
							if(parser.evaluate(it->second->getContent()))
								chosen.push_back(it->second->getMessage_ID());
					}
					*/
				}else{
						
					for(int i = 0; i < search_list.size(); i++){
						multimap< long long, Email* >::iterator it, end;
						it = search_list[i]->begin();
						end = search_list[i]->end();
						for(; it != end; ++it)
							if(parser.evaluate(it->second->getContent()))
								chosen.push_back(it->second->getMessage_ID());
					}	

				}

				sort(chosen.begin(), chosen.end());

				if(chosen.size() != 0){
					sort(chosen.begin(), chosen.end());
					for(int i = 0; i < chosen.size(); i++)
						cout << chosen[i] << " ";
					cout << endl;
				}else{
					cout << "-" << endl;
				}

				break;
			}
		}
	}
	return 0;
}
