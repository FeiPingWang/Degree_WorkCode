#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<memory>
#include"QueryResult.h"
#include"TextQuery.h"

using namespace std;

int main()
{
	string word;
	ifstream infile("Text.txt");
	TextQuery tq(infile);
	while (true)
	{
		cout << "entry word to search: ";
		if (!(cin>>word) || word == "q")
			return 0;
		else
			print(cout, tq.query(word)) << endl;
	}
	return 0;
}