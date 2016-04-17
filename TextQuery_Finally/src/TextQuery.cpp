#include "TextQuery.h"
#include "QueryResult.h"

TextQuery::TextQuery(ifstream &is) : file(new vector<string>)
{
	string text;
	while (getline(is, text))  //每次读取一行
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word)
		{
			auto &lines = wm[word];  //lines为动态指针的引用，改变lines同样会改变wm中的内容
			if (!lines)
				lines.reset(new set<int>);    //reset是shared_ptr的成员函数用.运算符
			lines->insert(n);
		}
	}
}

const QueryResult
TextQuery::query(const string &word) const
{
	static shared_ptr<set<int>> nodata(new set<int>);
	auto loc = wm.find(word);
	if (loc != wm.end())
		return QueryResult(word, loc->second, file);
	else
		return QueryResult(word, nodata, file);
}