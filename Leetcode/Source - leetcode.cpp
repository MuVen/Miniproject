#include "stdafx.h"
#include <iostream>
#include <wchar.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <sstream>

using namespace std;
typedef pair<int, int> mypair;

int countD(int N) {
	int count = 0;
	while (N) {
		count++;
		N = N / 10;
	}
	return count;
}

int printWithSpaces(set<int>& mset) {
	int count1 = 0;
	int countSpaces = 0;
	for (auto it = mset.begin(); it != mset.end(); ++it, count1++) {
		int dcount = countD(*it);
		int aspace = 5 - dcount;
		while (aspace--) {
			cout << " ";
		}

		cout << *it << "  ";
		countSpaces += 6;
		if (countSpaces % 102 == 0)
			cout << endl;
	}
	return count1;
}

int main() {
	stringstream ss;
	freopen("leetcode.txt", "r", stdin);
	unordered_map<int, int> map;
	set<int> mset;
	set<int> excelset;
	set<int> cmset;
	int N;
	for (int i = 1; i <= 907; i++) {
		cin >> N;
		//cout << N << " ";
		map[N]++;
	}

	//solved problems count
	int tsolved;
	cin >> tsolved;
	for (int i = 1; i <= tsolved; i++) {
		cin >> N;
		mset.insert(N);
	}

	//excel count;
	int excel;
	cin >> excel;
	for (int i = 1; i <= excel; i++) {
		cin >> N;
		excelset.insert(N);
	}

	//github count;
	int tadded;
	cin >> tadded;
	for (int i = 1; i <= tadded; i++) {
		cin >> N;
		cmset.insert(N);
	}

	vector<pair<int, int>> myvec;
	vector<int> sprobs;
	for (auto it = map.begin(); it != map.end(); ++it)
		myvec.push_back({ it->first, it->second });


	int count1 = printWithSpaces(mset);
	cout << endl << endl;
	cout << "Solved Problems " << count1 << endl << endl;


	{
		//mset - excelset will give me list of ids which is not updated in
		//the excel;
		set<int> cmset = mset;
		for (auto it = excelset.begin(); it != excelset.end(); ++it) {
			cmset.erase(*it);
		}
		for (auto i : cmset)
			cout << i << " ";
		cout << endl;
		cout << "Update These to Excel " << cmset.size() << endl << endl;
	}

	sort(myvec.begin(), myvec.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {return p1.first < p2.first; });
	for (auto it = myvec.begin(); it != myvec.end(); it++)
		sprobs.push_back(it->first);


	for (auto it = mset.begin(); it != mset.end(); ++it) {
		auto val = *it;
		auto vitr = find(sprobs.begin(), sprobs.end(), val);
		if (vitr != sprobs.end())
			sprobs.erase(vitr);
	}

	int count2 = 0;
	int countSpaces = 0;
	for (auto it = sprobs.begin(); it != sprobs.end(); ++it, count2++) {
		int dcount = countD(*it);
		int aspace = 5 - dcount;
		while (aspace--) {
			cout << " ";
		}

		int val = *it;
		//cout << val << " " << map[val]<<endl;
		cout << val << "  ";
		countSpaces += 6;
		if (countSpaces % 102 == 0)
			cout << endl;
	}
	cout << endl << endl << "Solve These Problems " << count2 << endl << endl;
	cout << "Total Problems to Be Solved " << count1 + count2 << endl << endl;


	//update these files in GIT
	for (auto it = cmset.begin(); it != cmset.end(); ++it)
		mset.erase(*it);

	cout << "Update these solutions to your github - " << mset.size() << endl;
	printWithSpaces(mset);
	cout << endl << endl;

	//add these solutions to git.
	// 16 19 40 47 61 62 63 64 77 79 82 83 130 142 147 148 179 201 211 216 328 371 389 401 461 476 485 542 686 693 704 705 706 717 724 788 812 844 961 980 1019 1021 1160 1170 1219 1247 1260
	cout << endl << "As of 25-November-2019 Solved 300 problems and need to Solve 363 Problems" << endl;

	// 16 19 40 47 60 61 62 63 64 77 79 82 83 130 142 147 148 179 201 211 216 328 371 389 401 461 476 485 542 581 686 693 704 705 706 717 724 788 812 844 961 980 1019 1021 1114 1160 1170 1219 1247 1260
	cout << endl << "As of 28-November-2019 Solved 303 problems and need to Solve 361 Problems" << endl;

	//31 33 135 153 172 221 402 962 1115 1116 1261 1271 1272 1273 1275 1281 1290 1291 1293
	cout << endl << "As of 19-December-2019 Solved 322 problems and need to Solve 355 Problems" << endl;

	//31 33 72 75 135 143 153 172 202 217 221 279 384 402 412 557 622 766 767 962 1115 1116 1261 1271 1272 1273 1275 1281 1290 1291 1293 1295
	cout << endl << "As of 23-December-2019 Solved 335 problems and need to Solve 350 Problems" << endl;

	//31 33 72 75 118 135 143 153 172 202 217 221 279 287 295 322 349 384 394 397 402 412 441 477 496 504 557 622 739 766 767 796 962 989 1047 1115 1116 1261 1271 1272 1273 1275 1281 1290 1291 1293 1295
	cout << endl << "As of 26-December-2019 Solved 350 problems and need to Solve 343 Problems" << endl;

	//31 33 55 72 75 81 118 135 143 153 172 202 217 221 279 287 295 322 347 349 350 384 394 397 402 412 441 477 496 504 557 593 622 668 739 766 767 796 946 962 989 1047 1115 1116 1195 1252 1261 1267 1268 1271 1272 1273 1275 1281 1290 1291 1293 1295 1299 1300 1302 1304 1305 1306
	cout << endl << "As of 31-December-2019 Solved 367 problems and need to Solve 340 Problems" << endl;

	//31 33 55 72 75 81 118 135 143 153 172 202 217 221 279 287 295 322 345 347 349 350 383 384 394 397 402 412 441 468 477 496 504 551 557 593 611 622 668 696 739 766 767 796 819 946 962 989 1024 1047 1115 1116 1195 1252 1261 1267 1268 1271 1272 1273 1275 1281 1290 1291 1293 1295 1299 1300 1302 1304 1305 1306
	cout << endl << "As of 02-January-2020 Solved 375 problems and need to Solve 340 Problems" << endl;

	//31 33 55 72 75 81 118 135 143 153 172 202 205 217 221 279 287 290 295 303 322 345 347 349 350 383 384 394 397 402 412 434 441 468 477 496 504 541 551 557 593 611 622 668 680 696 703 739 766 767 796 819 884 946 962 989 1024 1047 1115 1116 1195 1252 1261 1267 1268 1271 1272 1273 1275 1281 1290 1291 1293 1295 1299 1300 1302 1304 1305 1306 1309 1310
	cout << endl << "As of 06-January-2020 Solved 385 problems and need to Solve 330 Problems" << endl;

	//31 33 55 72 75 81 118 122 135 143 153 172 202 205 217 219 221 279 287 290 295 303 322 345 347 349 350 374 383 384 394 397 402 409 412 434 441 468 477 496 504 506 541 551 557 593 611 622 668 680 696 703 739 766 767 796 819 884 946 962 989 1024 1047 1115 1116 1195 1252 1261 1266 1267 1268 1271 1272 1273 1275 1281 1290 1291 1293 1295 1299 1300 1302 1304 1305 1306 1309 1310
	cout << endl << "As of 07-January-2020 Solved 391 problems and need to Solve 325 Problems" << endl;

	//31 33 55 72 75 81 118 122 135 143 153 172 202 205 217 219 221 279 287 290 295 299 303 322 345 347 349 350 374 383 384 394 397 402 409 412 434 441 468 477 496 504 506 521 541 551 557 593 599 605 611 622 665 668 674 680 696 703 739 747 748 766 767 796 819 884 946 962 989 1024 1046 1047 1115 1116 1195 1252 1261 1266 1267 1268 1271 1272 1273 1275 1281 1290 1291 1293 1295 1299 1300 1302 1304 1305 1306 1309 1310
	cout << endl << "As of 08-January-2020 Solved 400 problems and need to Solve 318 Problems" << endl;

	/*
	31     33     34     55     72     75     81    118    122    135    143    153    162    172    202    205    217
	219    221    227    279    287    290    295    299    303    322    345    347    349    350    374    383    384
	394    397    402    409    412    434    441    443    447    468    477    496    504    506    521    541    551
	557    593    599    605    611    622    665    668    674    680    696    703    739    747    748    766    767
	796    819    884    946    962    989   1024   1046   1047   1115   1116   1195   1252   1261   1266   1267   1268
	1271   1272   1273   1275   1281   1290   1291   1293   1295   1299   1300   1302   1304   1305   1306   1309   1310
	*/
	cout << endl << "As of 10-January-2020 Solved 400 problems and need to Solve 318 Problems" << endl;


	/*
	31     33     34     55     72     75     81    118    120    122    135    143    152    153    162    172    202
	205    213    217    219    220    221    227    278    279    287    290    295    299    303    322    345    347
	349    350    374    377    383    384    394    397    402    409    412    416    434    441    443    447    468
	474    477    496    504    506    521    541    551    557    593    599    605    611    621    622    665    668
	674    680    696    703    739    747    748    766    767    794    796    819    874    884    946    962    989
	1024   1025   1046   1047   1071   1115   1116   1195   1252   1261   1266   1267   1268   1271   1272   1273   1275
	1281   1287   1290   1291   1293   1295   1299   1300   1302   1304   1305   1306   1309   1310   1313   1315   1317
	1318   1323   1324   1325   1329   1331   1332   1341
	*/
	cout << endl << "As of 02-Feburary-2020 Solved 430 problems and need to Solve 306 Problems" << endl;
}