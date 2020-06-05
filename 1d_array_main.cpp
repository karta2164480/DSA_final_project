#include "parser.h"
#include <vector>
#include <algorithm>
#include "string.h"

int main(){

	string opr;
	unsigned int to_delete_id;
	char file_path[1000];
	char query_filter[1000];

	Email* pool[100000] = {0};

	int cnt = 0;

	while(cin >> opr){
		switch(opr[0]){

			case 'a': {										//add
				scanf("%s", file_path);
				Email *mail = new Email(file_path);
				bool duplicated = false;
				for(int i = 0; i < cnt; i++){
					if(pool[i]->getMessage_ID() == mail->getMessage_ID()){
						duplicated = true;
						break;
					}
				}
				if(duplicated)
					cout << "-" << endl;
				else{
					pool[cnt] = mail;
					cnt++;
					cout << cnt << endl;
				}
				break;
			}

			case 'r': {										//remove
				cin >> to_delete_id;
				bool found = false;
				for(int i = 0; i < cnt; i++){
					if(pool[i]->getMessage_ID() == to_delete_id){
						found = true;
						cnt--;
						delete pool[i];
						pool[i] = pool[cnt];
						cout << cnt << endl;
						break;
					}
				}
				if(!found)
					cout << "-" << endl;
				break;
			}

			case 'l': {										//longest
				if(cnt == 0)
					cout << "-" << endl;
				else{
					int max_len = 0;
					int max_len_id = 0;
					for(int i = 0; i < cnt; i++){
						if(pool[i]->getLength() == max_len && pool[i]->getMessage_ID() < max_len_id)
							max_len_id = pool[i]->getMessage_ID();
						else if(pool[i]->getLength() > max_len){
							max_len = pool[i]->getLength();
							max_len_id = pool[i]->getMessage_ID();
						}
					}
					cout << max_len_id << " " << max_len << endl;
				}
				break;
			}	

			case 'q': {										//query
				fgets(query_filter, 10000, stdin);
				bool checkFrom = false, checkTo = false, checkDate = false;
				string from, to, expr;
				long long start_date, end_date;
				char *token = strtok(query_filter, " \n");
				char c1[100], c2[100];
				int c1cnt = 0, c2cnt = 0;
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
								c1[c1cnt] = token[i];
								c1cnt++;
							}
							else{
								c2[c2cnt] = token[i];
								c2cnt++;
							}
						}
						char *eptr;
						if(c1cnt == 0)
							start_date = 0;
						else{
							start_date = strtoll(c1, &eptr, 10);
						}
						if(c2cnt == 0)
							end_date = 500000000000;
						else{
							end_date = strtoll(c2, &eptr, 10);
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

				//cout << start_date << endl;
				//cout << end_date << endl;

				Parser *p = new Parser(expr);
				vector<unsigned int> chosen;
				for(int i = 0; i < cnt; i++){
					bool valid = true;
					if(checkFrom && pool[i]->getFrom() != from){
						valid = false;
					}
					if(checkTo && pool[i]->getTo() != to)
						valid = false;
					if(checkDate){
						if(pool[i]->getDate() < start_date)
							valid = false;
						if(pool[i]->getDate() > end_date)
							valid = false;
					}
					if(valid && p->evaluate(pool[i]->getContent())){
						chosen.push_back(pool[i]->getMessage_ID());
					}
				}
				if(chosen.size() != 0){
					sort(chosen.begin(), chosen.end());
					for(int i = 0; i < chosen.size(); i++)
						cout << chosen[i] << " ";
					cout << endl;
				}else{
					cout << "-" << endl;
				}
				delete p;
				break;
			}
		}
	}
	return 0;
}
