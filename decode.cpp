#include <math.h>
#include <iostream>
#include <string>
using namespace std;
string inverted_seq(string a)
{
  string opstr="";
	for (int i = str.length()-1; i >= 0; i--)
	{
		opstr += str[i];
	}
  return opstr;
}
int bin_to_dec(string str,int len)
{
	int output=0;
	for (int i = 0; i < len; i++)
	{
		if (str[i]=='1')
		output +=  pow(2, i);
	}
	return output;
}
void decode_ldrstr(string a){}
void decode_operate(string a)
{
 	string opcode = a.substr(21,4);
	string rn = a.substr(16,4);
	string rd = a.substr(12, 4);
	string op2 = a.substr(0,12);
	int rnintex = bin_to_dec(rn, 4);
	if (opcode == "0000")
		cout << "AND  ";
	if (opcode == "0010")
		cout << "ADD  ";
	if (opcode == "0101")
		cout << "CMP  ";
	if (opcode == "1011")
		cout << "MOV  ";
	if (opcode == "0011")
		cout << "ORR  ";
	cout << "R" << bin_to_dec(rd, 4) << ",";
	if (rnintex!=0)
	cout<<"R"<< rnintex << ",";
	if (a[25] == '1')
	{
		cout << "#" << bin_to_dec(op2, 12);
	}
	else
	{
		cout << "R" << bin_to_dec(op2, 12);
	}
}
void decode_mul(string a){}
void decode_mrs(string a){}
void decode_swi(string a){}
void decode_branche(string a){}
void classification(string line){}
void openfiles()
{
  ifstream in("arm.txt");
	string str;
	while (!in.eof())
	{
		getline(in, str);
		classification(str);
		cout << endl;
	}
	in.close();
}
int main()
{
  return 0;
}
