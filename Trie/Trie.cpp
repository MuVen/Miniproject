// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include "timeutil.h"
using namespace std;

#define TRIE 0
#define LLTRIE 1
#define NODES 93

static string keystrokes("abcefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-=+_)(*&^%$#@!`~{}|\][;:\'\"<>,.?/ ");
vector<string> urlslist;

class iTrie{
public:
	virtual void addURL(string url) = 0;
	virtual void printAllURLs() = 0;
	virtual bool findURL(string url) = 0;
	virtual unsigned long long int getMemory() = 0;
	virtual string getNameOfTrie() = 0;
};

class normalTrie : public iTrie{
	unsigned long long int memory;
	unordered_map<char, int> map;
	int ucount = 0;
	struct trie{
		trie* childs[NODES];
		bool endOfUrl : 1;
		trie(){
			for (int i = 0; i < NODES; i++)
				childs[i] = nullptr;
			endOfUrl = 0;
		}
	};
	trie* getTrieNode(){
		trie* temp = new trie();
		int v = sizeof(temp->childs);
		memory += 1 + v;
		return temp;
	}
	void addKeyStrokes(){
		for (int i = 0; keystrokes[i] != '\0'; i++)
			map[keystrokes[i]] = i;
	}
	void printAllURLsUtil(trie* pCrawl){
		if (pCrawl == nullptr)
			return;

		if (pCrawl->endOfUrl == true){
			//cout << str.substr(1, str.length()) << endl;
			ucount++;
		}

		for (int i = 0; i < NODES; i++){
			if (pCrawl->childs[i] != nullptr)
				printAllURLsUtil(pCrawl->childs[i]);
		}
	}
	bool findURLUtil(trie* pCrawl, string url){
		if (pCrawl == nullptr)
			return false;

		for (int i = 0; url[i] != '\0'; i++){
			int index = map[url[i]];
			if (pCrawl->childs[index] == nullptr)
				return false;
			pCrawl = pCrawl->childs[index];
		}
		return pCrawl->endOfUrl == true;
	}
	trie* root = nullptr;
public:
	normalTrie(){
		memory = 0;
		root = getTrieNode();
		addKeyStrokes();
	}
	void addURL(string url){
		trie* pCrawl = root;
		for (int i = 0; url[i] != '\0'; i++){
			int index = map[url[i]];
			if (pCrawl->childs[index] == nullptr){
				pCrawl->childs[index] = getTrieNode();
			}
			pCrawl = pCrawl->childs[index];
		}
		pCrawl->endOfUrl = 1;
	}
	void printAllURLs(){
		printAllURLsUtil(root);
	}
	bool findURL(string url){
		return findURLUtil(root, url);
	}
	unsigned long long int getMemory() {
		return memory;
	}
	string getNameOfTrie() {
		return "Normal Trie";
	}
};

class linkedListTrie : public iTrie{
	unsigned long long int memory;
	int ucount = 0;
	struct lltrie{
		char ch;
		lltrie* next;
		lltrie* child;
		bool endOfWord;
		lltrie(char sch){
			next = child = nullptr;
			ch = sch;
			endOfWord = false;
		}
	};
	lltrie* llroot = nullptr;
	lltrie* getLLTrieNode(char sch){
		lltrie* ltemp = new lltrie(sch);
		memory += sizeof(ltemp->next) + sizeof(ltemp->child) + sizeof(ltemp->ch);
		return ltemp;
	}
	lltrie* findCharInTheChild(char& sch, lltrie** pCrawl){
		lltrie* tpCrawl = *pCrawl;
		lltrie* tpCrawlChild = tpCrawl->child;
		while (tpCrawlChild){
			if (tpCrawlChild->ch == sch)
				return tpCrawlChild;
			tpCrawlChild = tpCrawlChild->next;
		}
		return nullptr;
	}
	void printAllURLsUtil(lltrie* pCrawl, string& str){
		if (pCrawl == nullptr)
			return;

		str += pCrawl->ch;
		if (pCrawl->endOfWord == 1){
			//cout << str.substr(1, str.length()) << endl;
			ucount++;
		}
		printAllURLsUtil(pCrawl->child, str);

		str = str.substr(0, str.length() - 1);
		printAllURLsUtil(pCrawl->next, str);
	}
	bool findWordUtil(lltrie* root, string& url){
		if (root == nullptr)
			return false;

		lltrie* pCrawl = root;
		for (int i = 0; url[i] != '\0'; i++){
			char sch = url[i];
			lltrie* pCrawlChild = findCharInTheChild(sch, &pCrawl);
			if (pCrawlChild == nullptr)
				return false;
			pCrawl = pCrawlChild;
		}
		return pCrawl->endOfWord == true;
	}
public:
	linkedListTrie(){
		llroot = getLLTrieNode(';');
	}
	void addURL(string url){
		lltrie* pCrawl = llroot;
		for (int i = 0; url[i] != '\0'; i++){
			char sch = url[i];
			lltrie* pCrawlChild = findCharInTheChild(sch, &pCrawl);
			if (pCrawlChild == nullptr){
				if (pCrawl->child == nullptr){
					pCrawl->child = getLLTrieNode(sch);
				}
				else{
					lltrie* lltemp = getLLTrieNode(sch);
					lltemp->next = pCrawl->child;
					pCrawl->child = lltemp;
				}
				pCrawl = pCrawl->child;
				continue;
			}
			pCrawl = pCrawlChild;
		}
		pCrawl->endOfWord = true;
	}
	void printAllURLs(){
		string urls;
		printAllURLsUtil(llroot, urls);
	}

	bool findURL(string url){
		return findWordUtil(llroot, url);
	}
	unsigned long long int getMemory() {
		return memory;
	}
	string getNameOfTrie() {
		return "LinkedList Trie";
	}
};

void loadData(){
	int T;
	ifstream inFile;
	inFile.open("input.txt");
	string url;
	getline(inFile, url);
	T = stoi(url);
	for (int i = 1; i <= T; i++){
		getline(inFile, url);
		urlslist.push_back(url);
	}
}

class whichTrie{
	iTrie* trieInterface = nullptr;
public:
	whichTrie(iTrie* tIn){
		trieInterface = tIn;
	}

	void addURL(string url){
		trieInterface->addURL(url);
	}
	void printAllURLs(){
		trieInterface->printAllURLs();
	}
	bool findURL(string url){
		return trieInterface->findURL(url);
	}
	unsigned long long int getMemory(){
		return trieInterface->getMemory();
	}
	string getName(){
		return trieInterface->getNameOfTrie();
	}
};

void verify(){
	int option;
	while (true){
		cout << "Enter Trie Mode. 0 - break; 1 - Normal Trie; 2 - LinkedList Trie " << endl;
		cin >> option;
		whichTrie* wtrie = nullptr;
		if (option == 0)
			break;
		if (option == 1)
			wtrie = new whichTrie(new normalTrie());
		if (option == 2)
			wtrie = new whichTrie(new linkedListTrie());
		cout << "Inserting URLs to " << wtrie->getName() << endl<<endl;
		STARTTIME;
		for (int i = 0; i < urlslist.size(); i++)
			wtrie->addURL(urlslist[i]);
		ENDTIME;
		cout << "Insertion Time taken for " << urlslist.size() << " URLs in " << wtrie->getName()<< endl;
		PRINTTIME;
		cout << endl << endl;
		cout << "Searching URLs in " << wtrie->getName() << endl << endl;
		STARTTIME;
		int count = 0;
		for (int i = 0; i < urlslist.size(); i++)
			wtrie->findURL(urlslist[i]) ? count++ : count;
		ENDTIME;
		cout << "Search Time taken for " << count << " URLs in " << wtrie->getName() << endl;
		PRINTTIME;
		cout << endl << endl << endl;
		cout << "Memory Consumed " << wtrie->getMemory() / 1000000 << " MB used in "<<wtrie->getName() << endl;
		cout << "----------------------------------------------------------------------------" << endl<<endl<<endl;
		delete wtrie;
	}
}

//NOTE: Memorey Leaks are obvious as i didnt focus on cleaning part.
//Be careful while runing. Dont try to run normal trie mode more than once
int _tmain(int argc, _TCHAR* argv[])
{
	loadData();
	verify();
	return 0;
}

