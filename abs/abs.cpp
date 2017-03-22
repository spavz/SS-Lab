#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	
	ifstream object("object.txt");
	string x;

	object >> x >> x;
	int addr=stoi(x,nullptr,16);
	object >> x >> x;

	ofstream memory("memory.txt");

	while(x=="T")
	{
		object >> x ;
		addr = stoi(x,nullptr,16);
		object >> x >> x;

		while(!(x=="T" || x=="E"))
		{
			memory << hex << addr <<"\t"<< x <<"\n";
			addr += x.length()/2;
			object >> x;
		}	
	}
	return 0;
}
