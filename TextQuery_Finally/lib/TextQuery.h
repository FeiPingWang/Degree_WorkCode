#ifndef _TextQuery_H
#define _TextQuery_H

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<memory>

using namespace std;

class QueryResult;

class TextQuery{
public:
	TextQuery();
	TextQuery(ifstream& );
	const QueryResult query(const string& ) const;
	using line_no = vector<string>::size_type;

private:
	shared_ptr<vector<string>> file; 
	map<string, shared_ptr<set<int>>> wm;
}; 

#endif

