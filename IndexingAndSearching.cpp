// IndexingAndSearching.cpp : Defines the entry point for the console application.
//

// IndexingAndSearching.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <locale>
#include <algorithm>
#include <fstream>
using namespace std;

unordered_map<int, string> pageData;
unordered_map<string, vector<int>> wordIndex; // Can improve this by using unordered_set than vector which searches in O(1) time and no need to check for duplicate entires.

void addToWordIndex(string& token, int& lineNumber) {
	auto itr = wordIndex.find(string(token));
	if (itr != wordIndex.end()) {
		vector<int> temp = itr->second;
		auto vfitr = find(temp.begin(), temp.end(), lineNumber);
		if (vfitr == temp.end())
			itr->second.push_back(lineNumber);
	}
	else {
		vector<int> vec;
		vec.push_back(lineNumber);
		wordIndex.insert(make_pair(token, vec));
	}
}

void indexWords(string& buffer, int& lineNumber) {
	char* cbuffer = (char*)buffer.c_str();
	char* token = NULL;
	char* context = NULL;
	char delims[] = " `~!@#$%^&*()_-+=[]{}|:;<>,./?\t\n\'\"";

	token = strtok_s(cbuffer, delims, &context);
	while (token != NULL) {
		//cout << token << " ";
		if (token != NULL)
			addToWordIndex(string(token), lineNumber);
		token = strtok_s(NULL, delims, &context);
	}
	//cout << endl;
}

void printLinesOfSearchWords(vector<string>& searchWords) {
	vector<vector<int>> wordLines;
	for (auto itr = searchWords.begin(); itr != searchWords.end(); ++itr) {
		auto wiitr = wordIndex.find(*itr);
		if (wiitr != wordIndex.end()) {
			wordLines.push_back(wiitr->second);
		}
	}

	if (wordLines.size() == 0) {
		cout << "Sorry! These Words are not available in the document\n" << endl;
		return;
	}

	if (wordLines.size() == 1) {
		for (auto itr = wordLines.begin(); itr != wordLines.end(); ++itr) {
			vector<int> temp = *itr;
			for (auto itrtemp = temp.begin(); itrtemp != temp.end(); ++itrtemp)
				cout << "Line : " << *itrtemp << " " << pageData.find(*itrtemp)->second << endl;
		}
		return;
	}

	//find the intersection of lines.
	vector<int> frontVec = wordLines.front();
	vector<vector<int>>::iterator isitr = wordLines.begin();
	++isitr;

	for (auto fitr = frontVec.begin(); fitr != frontVec.end(); ++fitr) {
		int tempLine = *fitr;
		auto tempisitr = isitr;
		for (; tempisitr != wordLines.end(); ++tempisitr) {
			vector<int> tempVec = *tempisitr;
			auto fitr = std::find(tempVec.begin(), tempVec.end(), tempLine);
			if (fitr == tempVec.end())
				break;
		}
		if (tempisitr == wordLines.end()) {
			cout << "Line : " << tempLine << " " << pageData.find(tempLine)->second << endl;
		}
	}
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string buffer;
	std::ifstream infile("input.txt");
	int lineNumber = 1;
	while (std::getline(infile, buffer)) {
		pageData.insert(make_pair(lineNumber, buffer));
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
		indexWords(buffer, lineNumber);
		++lineNumber;
	}

	while (1) {
		string temp;
		vector<string> searchWords;
		int N;
		cout << "Enter Number of words you want to search; 0 to break\n";
		cin >> N;
		if (N == 0)
			break;
		for (int i = 0; i < N; i++) {
			cin >> temp;
			std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			searchWords.push_back(temp);
		}
		system("cls");
		printLinesOfSearchWords(searchWords);
	}

	return 0;
}