#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	cout << "Please input some works:" << endl;
	string input;
	cin >> input;
	
	ofstream fout("5.txt");
	if (!fout)
	{
		cout << "Open the 5.txt error!" << endl;
		exit(1);
	}
	fout << input;
	fout.close();
	
	string output;
	ifstream fin("5.txt",ios::in);
	if (!fin)
	{
		cout << "Open the 5.txt error!" << endl;
		exit(1);
	}
	fin >> output;
	fin.close();
	cout << "The content in the 5.txt:" << endl << output << endl;
	return 0;
} 
