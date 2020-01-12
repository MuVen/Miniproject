#ifndef TIMEUTIL_H
#define TIMEUTIL_H
#include <ctime>
#include <ratio>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

high_resolution_clock::time_point startTime;
high_resolution_clock::time_point endTime;

#define STARTTIME {\
	startTime = high_resolution_clock::now(); \
}\

#define ENDTIME {\
	endTime = high_resolution_clock::now(); \
}\

#define PRINTTIMEMS {\
	auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime); \
	std::cout << "It Took " << int_ms.count() << " milliseconds" << endl; \
}\

#define PRINTTIMESECONDS {\
	auto time_span = duration_cast<duration<double>>(endTime - startTime); \
	std::cout << "It Took " << time_span.count() << " seconds" << endl; \
}\

#define PRINTTIMEMILLISECONDS {\
	auto int_ms = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime); \
	std::cout << "It Took " << int_ms.count() / 1000.0f << " milli seconds" << endl; \
}\

#define PRINTTIMEMICROSECONDS {\
	auto int_ms = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime); \
	std::cout << "It Took " << int_ms.count() << " microseconds" << endl; \
}\

#define PRINTTIME {\
	PRINTTIMEMICROSECONDS; \
	PRINTTIMEMILLISECONDS; \
	PRINTTIMESECONDS; \
}\

#endif