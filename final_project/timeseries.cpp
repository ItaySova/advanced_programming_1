/*
 * Authors: Tomer Schwartz, Itay sova
 */

#include "timeseries.h"


TimeSeries::TimeSeries(const char* CSVfileName) : ts(ts) {
    ifstream in(CSVfileName);
    string head;
    in>>head;
    string att;
    stringstream hss(head);
    while(getline(hss,att,',')){
        vector<float> v;
        ts[att]=v;
        atts.push_back(att);
    }

    while(!in.eof()){
        string line;
        in>>line;
        string val;
        stringstream lss(line);
        int i=0;
        while(getline(lss,val,',')){
            if(val=="done"){
                continue;
            }
            ts[atts[i]].push_back(stod(val.c_str()));
            i++;
        }
    }
    in.close();

    dataRowSize = ts[atts[0]].size();

}

const map<string, vector<float>> &TimeSeries::getTs() const {
    return ts;
}

const vector<string> &TimeSeries::getAtts() const {
    return atts;
}

size_t TimeSeries::getDataRowSize() const {
    return dataRowSize;
}
