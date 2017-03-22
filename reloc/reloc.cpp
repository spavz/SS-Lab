#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <bitset>

using namespace std;

int stoii(string x)
{
	return stoi(x,nullptr,16);
}

int main()
{
	
	ifstream object("object.txt");
	string x;

	object >> x >> x;
	int progaddr=stoii(x);
	object >> x >> x;

	ofstream memory("memory.txt");

	while(x=="T")
	{
		object >> x ;
		int addr = stoii(x)+progaddr;
		object >> x >> x;

		string b = bitset<12>(stoii(x)).to_string();
		object >> x ;

		int i=0;
		while(!(x=="T" || x=="E"))
		{
			if(b[i] =='1')
			{
				int direct = stoii(x.substr(x.length()-4)) + progaddr;
				memory << hex << addr <<"\t"<< x.substr(0,2) << setfill('0') << setw(4) << direct << "\n";
			}
			else
				memory << hex << addr <<"\t"<< x <<"\n";
			addr += x.length()/2;
			object >> x;
			i++;

		}	
	}
	return 0;
}
