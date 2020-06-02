/*	this data structure is for content query  */

#include "trie.h"
#include <memory.h>	//memset
#include <ctype.h>	//isalpha
#include <assert.h>	//assert


//construct a new trie node
TrieNode *getNode(){

	TrieNode *node = new TrieNode;
	memset(node->children, 0, sizeof(TrieNode*) * CHARACTER_NUM);
	node->isEndOfWord = false;

	return node;
}

void trie_insert(TrieNode *root, string& key){

	TrieNode *crawler = root;

	for(int i = 0; i < key.length(); i++){

		int index;
		if(isalpha(key[i]))
			index = key[i] - 'a' + 10;
		else	
			index = key[i] - '0';

		if(crawler->children[index] == NULL)
			crawler->children[index] = getNode();

		crawler = crawler->children[index];
	}

	crawler->isEndOfWord = true;
}

bool trie_search(TrieNode *root, string& key){

	TrieNode *crawler = root;

	for(int i = 0; i < key.length(); i++){

		int index;
		if(isalpha(key[i]))
			index = key[i] - 'a' + 10;
		else	
			index = key[i] - '0';

		if(crawler->children[index] == NULL)
			return false;
		crawler = crawler->children[index];
	}

	assert(crawler != NULL);

	return crawler->isEndOfWord;
}

void trie_release(TrieNode *root){
	for(int i = 0; i < CHARACTER_NUM; i++){
		if(root->children[i] != NULL)
			trie_release(root->children[i]);
	}
	delete root;
}
