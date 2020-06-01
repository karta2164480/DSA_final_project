#define CHARACTER_NUM 36	//a-z0-9
#include <string>	

using namespace std;

typedef struct trieNode{

	struct trieNode *children[CHARACTER_NUM];
	bool isEndOfWord;

} TrieNode;

TrieNode *getNode();

void insert(TrieNode *root, string& key);

bool search(TrieNode *root, string& key);

void release(TrieNode *root);
