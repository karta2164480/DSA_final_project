/*	this data structure is for content query  */

#include "trie.h"
#include <stdlib.h>	//memset
#include <ctype.h>	//isalpha
#include <assert.h>	//assert


//construct a new trie node
TrieNode *getNode(){

	TrieNode *node = new TrieNode;
	memset(node->children, 0, sizeof(TrieNode*) * CHARACTER_NUM);
	node->isEndOfWord = false;

	return node;
}

void insert(TrieNode *root, string& key){

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

bool search(TrieNode *root, string& key){

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

void release(TrieNode *root){
	for(int i = 0; i < CHARACTER_NUM; i++){
		if(root->children[i] != NULL)
			release(root->children[i]);
	}
	delete root;
}
