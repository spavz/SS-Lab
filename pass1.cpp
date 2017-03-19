#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;


int main() {

  ifstream code("code.txt");
  string x0,x1,x2;
  int start_address=0;
  unordered_map<string,int> Symtab;
  code >> x0 >> x1 >> x2;


  if(x1 == "START")
  {
  	start_address = stoi(x2,nullptr,16);
    code >> x0 >> x1 >> x2;
  }

  int locctr = start_address;

  while(x1!="END")
  {
  	if(x0!="-")
  		Symtab[x0]=locctr;

  	if(x1 == "RESW")
  		locctr+= 3 * stoi(x2);
  	else if(x1 == "RESB")
  		locctr+= stoi(x2);
  	else if(x1 == "BYTE")
  		locctr+= x2.length()/2;
  	else
  		locctr+= 3;

  	code >> x0 >> x1 >> x2;
  }

  cout << hex << (locctr-start_address) << endl;


  ofstream SYMTAB("SYMTAB.txt");
  for (auto& x:Symtab)
  {
  	cout << x.first <<" "<< x.second<<endl;
  	SYMTAB << hex << x.first <<" "<< x.second<<endl;
  }

  return 0;
}
