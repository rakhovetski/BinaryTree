#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "BST.cpp"
using namespace std;

struct wordNode
{
	string key;
	int frequency;
};

void print(wordNode ss)
{
	cout << ss.key << " " << ss.frequency << endl;
}

string trim(string input)
{
	stringstream ss;

	for (int x = 0; x < (int)input.size(); x++)
	{
		if (isalpha(input[x]))
		{
			ss << input[x];
		}
	}

	if (ss.str().length() > 0)
		return ss.str();
	else
		return "";
}

int main()
{
	int total = 0;
	BST<wordNode, string> tree;
	ifstream fin;
	fin.open("article.txt");
	if (fin.fail())
	{
		cout << "Input file opening failed.\n";
		exit(1);
	}

	string word;

	while (!fin.eof())
	{
		fin >> word;
		wordNode o;
		o.key = trim(word);
		if (tree._Retrieve(word, o))
		{
			(tree._Retrieve2(word, o))->data.frequency++;
			total++;
		}
		else
		{
			o.frequency = 1;
			tree._Insert(o);
			total++;
		}
	}

	fin.close();
	tree._Traverse(print);
	tree._Print();
	cout << "Total number of words: " << total << endl;
	return 0;
}