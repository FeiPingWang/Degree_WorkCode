#ifndef _QueryResult_H
#define _QueryResult_H

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<memory>
using namespace std;

class QueryResult{
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult();
	QueryResult(const string& w, shared_ptr<set<int>> p, shared_ptr<vector<string>> f) : word(w), lines(p), file(f){};

private:
	string word;
	shared_ptr<set<int>> lines;
	shared_ptr<vector<string>> file;
};

#endif