#include"QueryResult.h"

string JudgeS(int num, const string &word, const string &end)
{
	return (num == 1) ? word : word + end;
}

ostream& print(ostream& os, const QueryResult& q)
{
	os << q.word << "occurs " << q.lines->size() << " " << JudgeS(q.lines->size(), "time", "s") << endl;
	for (auto num : *q.lines)
		os << "\t(line" << num + 1 << ")" << *(q.file->begin() + num) << endl;
	return os;
}