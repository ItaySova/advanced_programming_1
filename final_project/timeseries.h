/*
 * Authors: Tomer Schwartz, Itay sova
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <iostream>
#include <string.h>
#include <fstream>
#include<map>
#include <vector>
#include <string.h>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

class TimeSeries{


	map<string,vector<float>> ts;
	vector<string> atts;
	size_t dataRowSize;
public:


	TimeSeries(const char* CSVfileName);


    const vector<float>& getAttributeData(string name)const{
		return ts.at(name);
	}

	const vector<string>& gettAttributes()const{
		return atts;
	}

	size_t getRowSize()const{
		return dataRowSize;
	}

	~TimeSeries(){

	}

    const map<string, vector<float>> &getTs() const;

    const vector<string> &getAtts() const;

    size_t getDataRowSize() const;
};



#endif /* TIMESERIES_H_ */
